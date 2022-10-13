#include"Header.h"

void main()
{
	string ipaddress = ""; // địa chỉ ip của sever kết nối đến có thể nhập = tay xem địa chỉ này = cách cmd gõ lênh ipconfig
	int port = 54000;       // port của sever để kết nối đến 
	//Initialize winsock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2); // phiên bản k cần quan tâm, mặc định laf vậy r
	int wsresult = WSAStartup(ver, &data);
	if (wsresult != 0) {
		cerr << "Can't start winsock, Err#" << WSAGetLastError() << endl;
		return;
	}
	bool Check_ip = false;
	do {
		cout << "Nhap dia chi IP sever: ";
		getline(cin, ipaddress);
		Check_ip = Check_InputIP(ipaddress);
	} while (Check_ip == false);
	//Create Socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // tạo 1 socket kết nối đến sever
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket ,Err#" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	//Fill in a hint structure
	sockaddr_in hint;  // khai báo cấu trúc của địa chỉ ip
	hint.sin_family = AF_INET;  // AF_INET là địa chỉ IPv4 , cái này mặc định 
	hint.sin_port = htons(port);  // cổng kết nối của client
	inet_pton(AF_INET, ipaddress.c_str(), &hint.sin_addr); // chuyển địa chỉ IP từ string sang dangj nhị phân máy tính ms hiểu  
	// Connect to server
	int connectResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectResult == SOCKET_ERROR) {
		cerr << "Can't connect to sever Err#" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		system("pause");
		return;
	}
	char buf[4096];
	string userInput;
	int byteReceived = recv(sock, buf, 4096, 0);
	if (byteReceived == -1 || byteReceived == 0) {
		cerr << "Server Closes connection. Quitted" << endl;
	}
	if (byteReceived == SOCKET_ERROR) {
		cerr << "Error in receive. Quitted " << endl;
	}
	else {
		cerr << string(buf, 0, byteReceived) << endl;
		system("pause");
	}
	int Command = -1;
	while (Command != 3) {
		system("cls");
		Command = Choose_Handle(Main_Menu());
		HandleOption(Command, sock);
	}
	cout << "\t\t";
	system("pause");
	closesocket(sock);
	WSACleanup();
}


