#include "server.h"


server::server(std::string ip,int port)// 생성자 /맴버 초기화
:m_ip(ip), m_port(port)
{
}
server::~server()// destructor
{
	Cleanup();//winsock 해제
}
bool server::Init()// winsock 초기화 소켓 네트워크를 하기위해 가장 처음으로 거쳐야되는 과정
{
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);//winsock 초기화
	return wsInit == 0;
}
void server::Cleanup()
{
	WSACleanup();//winsock 해제
}
SOCKET server::CreateSocket()
{
	SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);// 소켓생성 / 주소패밀리,소캣형식,통신옵션
	if (listensock != INVALID_SOCKET)
	{
		sockaddr_in insock;//sockaddr_in 에 소켓에 저장할 정보를 저장
		insock.sin_family = AF_INET;
		insock.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ip.c_str(), &insock.sin_addr);// ip주소를 이진데이터로 변환해서 저장함
		bind(listensock, (sockaddr*)&insock, sizeof(insock));// bind 함수를 통해 소켓에 ip주소/포트값/ip주소 이진데이터값을 저장

		listen(listensock, SOMAXCONN);//listensock을 listen상태로 저장
	}
	return listensock;
}
void server::Run()//실제 서버동작의 함수
{
	char String[MAX_BUFFER_SIZE];
	char String2[MAX_BUFFER_SIZE];
	while (true)//컴파일 후 서버는 항상 열린상태
	{
		cout << "waiting for a client\r\n" << endl;
		int byteReceive = 0;
		int byteReceive2 = 0;
		SOCKET listensock = CreateSocket();//listen socket 생성

		if (listensock == INVALID_SOCKET)
		{
			break;
		}
		string start = "1: sign up 2: log in";
		cout << "\n\n\n  인증되었씁니다 \n\n\n" << endl;
		SOCKET client = WaitForConnection(listensock);//listensocket을 client와 연결 == 연결socket을 생성

		cout << "accepting client\r\n" << endl;
		closesocket(listensock);// 듣기 소켓은 이제 사용안함
		do
		{
			Send(client, start);
			ZeroMemory(String, MAX_BUFFER_SIZE);
			byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);//menu메세지를 입력받음
			string Menu = std::string(String, 0, byteReceive);
			if (byteReceive > 0)
			{
			}
			if (Menu != "1"&& Menu != "2")
			{
					string end = "wrong message.";

					Send(client, end);
			}
			else if (Menu == "1")
			{
				cout << "client의 회원가입 신청\r\n" << endl;
				int YN;
				Send(client, "Enrolling a user");
				Send(client, "id를 입력하세요");
				ZeroMemory(String, MAX_BUFFER_SIZE);
				byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);// client로 부터 id 입력받음
				cout << "id입력값\r\n" + std::string(String, 0, byteReceive) << endl << endl;
				Send(client, "\r\npsword를 입력하세요");
				ZeroMemory(String2, MAX_BUFFER_SIZE);
				byteReceive2 = recv(client, String2, MAX_BUFFER_SIZE, 0);// client로 부터 psword 입력받음
				cout << "psword입력값\r\n" + std::string(String2, 0, byteReceive2) << endl << endl;
				signin Sign(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				YN = Sign.Enroll(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				if (YN == 1)
				{
					Send(client, "\r\nsignin succeed!");
				}
				else
				{
					Send(client, "\r\nsignin failed!");
				}
			}
			else if (Menu == "2")
			{
				cout << "client의 로그인 신청\r\n" << endl;
				int YN;
				Send(client, "login a user");
				Send(client, "id를 입력하세요");
				ZeroMemory(String, MAX_BUFFER_SIZE);
				byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);// client로 부터 id 입력받음
				cout << "id입력값\r\n" + std::string(String, 0, byteReceive) << endl << endl;
				Send(client, "\r\npsword를 입력하세요");
				ZeroMemory(String2, MAX_BUFFER_SIZE);
				byteReceive2 = recv(client, String2, MAX_BUFFER_SIZE, 0);// client로 부터 psword 입력받음
				cout << "psword입력값\r\n" + std::string(String2, 0, byteReceive2) << endl << endl;
				login Log(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				YN = Log.Login(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				if (YN == 1)
				{
					Send(client, "\r\nlogin succeed!");
				}
				else
				{
					Send(client, "\r\nlogin failed!");
				}
			}
		} while (byteReceive > 0);
		closesocket(client);
		cout << "closing client\r\n" << endl;
	}

}
SOCKET server::WaitForConnection(SOCKET listensock)
{
	SOCKET client = accept(listensock, NULL, NULL);
	return client;
}
void server::Send(int clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}