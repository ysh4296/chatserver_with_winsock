#include "client.h"


client::client(std::string ip, int port)
:m_ip(ip), m_port(port)
{
}


client::~client()
{
	Cleanup();
}

bool client::Init()//winsock 초기화
{
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);
	return wsInit == 0;
}

void client::Cleanup()// 윈속 해제
{
	WSACleanup();
}

SOCKET client::Connect()
{

	SOCKET consock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);// 소켓생성 / 주소패밀리,소캣형식,통신옵션
	if (consock != INVALID_SOCKET)
	{
		sockaddr_in insock;//sockaddr_in 에 소켓에 저장할 정보를 저장
		insock.sin_family = AF_INET;
		insock.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ip.c_str(), &insock.sin_addr);// ip주소를 이진데이터로 변환해서 저장함
		int result = connect(consock, (sockaddr*)&insock, sizeof(insock));// connect 함수를 통해 서버에 접속
		if (result == SOCKET_ERROR)
		{
			cout << "connection failed open server first\r\n" << endl;
		}
		else
		{
			cout << "connection succeed\r\n" << endl;
		}

	}
	return consock;
}

void client::Run()
{
	char message[MAX_BUFFER_SIZE];
	std::string str;
	int byteReceive = 0;
	SOCKET server = Connect();//listen socket 생성
	do
	{

		//ZeroMemory(message, MAX_BUFFER_SIZE);
		//recv(server, message, MAX_BUFFER_SIZE, 0);// 1: signin 2: login
		//cout << message << endl;
		
		Get(server, message);
		cin >> str;// 메뉴 선택
		Send(server, str);
		if (str == "1")
		{
			Get(server, message);// enrolling a user

			Get(server, message);// id 를 입력하세요
			cin >> str;
			Send(server, str);// id send

			Get(server, message);// ps 를 입력하세요
			cin >> str;
			Send(server, str);// psword send


			Get(server, message);//회원가입에 성공/실패하였습니다.
		}
		else if(str == "2")
		{
			Get(server, message);// login a user


			Get(server, message);// id 를 입력하세요
			cin >> str;
			Send(server, str);//id send
			Get(server, message);// psword 를 입력하세요
			cin >> str;
			Send(server, str);//psword send
			Get(server, message);// 로그인에 성공/실패 하였습니다.
		}
		else
		{
			Get(server, message);// wrong message
		}
	} while (true);
	closesocket(server);
	cout << "서버연결 종료" << endl << endl;
}
void client::Send(int serverSocket, std::string msg)
{
	send(serverSocket, msg.c_str(), msg.size() + 1, 0);
}
void client::Get(SOCKET server,char msg[])
{
	ZeroMemory(msg, MAX_BUFFER_SIZE);
	recv(server, msg, MAX_BUFFER_SIZE, 0);
	cout << msg << endl << endl;
}