#include"Header.h"
#define WIN32_LEAN_AND_MEAN
#define MAXIMUM_CONNECTIONS 20
int connectionsCount = 0;
SOCKET clients[MAXIMUM_CONNECTIONS];

void main()
{
	//Init winsock
	WSADATA wsData;
	int retcode;
	WORD ver = MAKEWORD(2, 2);
	int wSok = WSAStartup(ver, &wsData);
	if (wSok != 0) {
		cout << "cant Initialize winsock! Quitting" << endl;
		return;
	}
	//Create socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cout << "can't Create a Socket! Quitting" << endl;
		return;
	}
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	//bind the socket to an  ip adrress and port
	retcode = bind(listening, (sockaddr*)&hint, sizeof(hint));
	if (retcode == SOCKET_ERROR) {
		cout << "Bind failed" << endl;
		return;
	}
	int iResult = listen(listening, SOMAXCONN);
	crawlDataFromWebToFile( "data.txt", "https://tygia.com/json.php"); //http request to get data from web
	thread Update_data(update_); //function update data 30 minues later.
	Update_data.detach();
	do {

		clients[connectionsCount] = accept(listening, NULL, NULL);
		if (clients[connectionsCount] != INVALID_SOCKET)
		{
			cout << "#SOCK: " << clients[connectionsCount] << " has been connected\n";
			thread listenThread(listenForConnection, &clients[connectionsCount++]);
			listenThread.detach();
		}

	} while (true);

	closesocket(listening);
	WSACleanup();
}

