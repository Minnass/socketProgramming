#include"Header.h"

bool Check_login(User_infor Account)
{
	fstream fileIn;
	string userName;
	string passWord;
	fileIn.open("user.txt", ios::in);
	while (!fileIn.eof()) {
		getline(fileIn, userName);
		getline(fileIn, passWord);
		if (Account.password == passWord && Account.user_Name == userName)
		{
			return true;
		}
	}
	fileIn.close();
	return false;
}
bool SignUp(User_infor Account) {
	fstream fileIn;
	fstream fileOut;
	fileIn.open("user.txt", ios::in);
	string Check = "";
	string mk = "";
	while (!fileIn.eof()) {
		getline(fileIn, Check);
		getline(fileIn, mk);
		if (Check == Account.user_Name) {
			return false;
		}
	}
	fileOut.open("user.txt", ios::app);
	fileOut << Account.user_Name << endl;
	fileOut << Account.password << endl;
	fileIn.close();
	fileOut.close();
	return true;
}
//
int  HandLe_Option(string Option, SOCKET& sock)
{

	int byteReceived = -2;
	if (Option == "login") {
		User_infor u_ser;
		char buf_nameId[4096];
		char buf_password[4096];
		string message = "";
		byteReceived = recv(sock, buf_nameId, 4096, 0);
		if (byteReceived == -1 || byteReceived == 0) {
			cout << "#SOCK: " << sock << " disconneted" << endl;
			return 3;
		}
		u_ser.user_Name = string(buf_nameId);
		byteReceived = recv(sock, buf_password, 4096, 0);
		if (byteReceived == -1 || byteReceived == 0) {
			cout << "#SOCK: " << sock << " disconneted" << endl;
			return 3;
		}
		u_ser.password = string(buf_password);
		bool login_Check = Check_login(u_ser);
		if (login_Check == true) {
			cout << "#SOCK: " << sock << " Logn in successfully!" << endl;
			message = "true";
			send(sock, message.c_str(), message.size() + 1, 0);
			while (true) {
				byteReceived = recv(sock, buf_nameId, 4096, 0);
				if (byteReceived == -1 || byteReceived == 0) {
					cout << "#SOCK: " << sock << " disconneted" << endl;
					return 3;
				}
				if (string(buf_nameId) == "exit") {
					Option = "exit";
					break;
				}
				else {
					Handle_SearchOption(string(buf_nameId), sock);
				}
			}
		}
		else {
			message = "false";
			cout << "#SOCK: " << sock << " Login falied !" << endl;
			send(sock, message.c_str(), message.size() + 1, 0);
		}
		return 1;
	}
	else if (Option == "signup") {
		User_infor u_ser;
		char buf_nameId[4096];
		char buf_password[4096];
		string message = "";
		recv(sock, buf_nameId, 4096, 0);
		if (byteReceived == -1 || byteReceived == 0) {
			cout << "#SOCK: " << sock << " disconneted" << endl;
		}
		u_ser.user_Name = string(buf_nameId);
		recv(sock, buf_password, 4096, 0);
		if (byteReceived == -1 || byteReceived == 0) {
			cout << "#SOCK: " << sock << " disconneted" << endl;
		}
		u_ser.password = string(buf_password);
		bool SignUp_Check = SignUp(u_ser);
		if (SignUp_Check == true) {
			cout << "#SOCK: " << sock << " has been Registed" << endl;
			message = "true";
			send(sock, message.c_str(), message.size() + 1, 0);
		}
		else {
			message = "false";
			cout << "#SOCK: " << sock << " couldn't Register !" << endl;
			send(sock, message.c_str(), message.size() + 1, 0);
		}
		return 2;
	}
	if (Option == "exit") {
		cout << "#SOCK: " << sock << " exited" << endl;
		return 3;
	}
}
void Handle_SearchOption(string Option, SOCKET& sock) {
	infor Arr[1000];
	infor Temp_[500];
	int pos = 0;
	int n = 0;
	READ_FILE("data.txt", Arr, n);
	string message = "";
	char buf[4096];

	if (Option == "date") {
		recv(sock, buf, 4096, 0);
		int Count = 0;
		string Value_Handled = Time_Handle(string(buf));
		for (int i = 0; i < n; i++) {
			if (Arr[i].Day.find(Value_Handled) != -1) {
				Temp_[pos++] = Arr[i];
				Count++;
			}
		}
		if (Count > 70) {
			Count = 70;
		}
		string Str = to_string(Count);
		send(sock, Str.c_str(), Str.size() + 1, 0);
		if (Count > 0) {
			for (int i = 0; i < Count; i++) {
				Send_EachInfor(Temp_[i], sock);
			}
		}
	}
	if (Option == "type") {
		recv(sock, buf, 4096, 0);
		int Count = 0;
		for (int i = 0; i < n; i++) {
			if (Arr[i].Company == string(buf)) {
				Temp_[pos++] = Arr[i];
				Count++;
			}
		}
		if (Count > 70) {
			Count = 70;
		}
		string Str = to_string(Count);
		send(sock, Str.c_str(), Str.size() + 1, 0);
		if (Count > 0) {
			for (int i = 0; i < Count; i++) {
				Send_EachInfor(Temp_[i], sock);
			}
		}
	}
}
void Send_EachInfor(infor _user, SOCKET& sock) {
	char buf[4096];
	send(sock, _user.ID.c_str(), _user.ID.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.Company.c_str(), _user.Company.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.Brand.c_str(), _user.Brand.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.Buy.c_str(), _user.Buy.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.Sell.c_str(), _user.Sell.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.Updated.c_str(), _user.Updated.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.Brand1.c_str(), _user.Brand1.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.CODE.c_str(), _user.CODE.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.Day.c_str(), _user.Day.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	send(sock, _user.Type.c_str(), _user.Type.size() + 1, 0);
	recv(sock, buf, 4096, 0);

}
string Time_Handle(string Time_) {
	string reSult = "";
	int last = Time_.length() - 1;
	int begin;
	for (int i = Time_.length() - 1; i >= 0; i--) {
		if (Time_[i] == '/') {
			begin = i + 1;
			reSult += Time_.substr(begin, last - begin + 1);
			last = begin - 2;
		}
	}
	reSult += Time_.substr(0, last + 1);
	return reSult;
}
void listenForConnection(SOCKET* client)
{
	string message = "connect is successful";
	send(*client, message.c_str(), message.size() + 1, 0);
	int iResult;
	char recvbuf[4096];
	int Command = -1;
	do
	{
		iResult = recv(*client, recvbuf, 4096, 0);
		if (iResult == -1) {
			cout << "#SOCK: " << *client << " disconnected" << endl;
			return;
		}
		if (iResult > 0)
		{
			Command = HandLe_Option(string(recvbuf), *client);
		}

		else
		{
			closesocket(*client);
			WSACleanup();
			return;
		}
	} while (Command != 3);
}
void update_()
{
	while (1)
	{
		Sleep(1800000);
		crawlDataFromWebToFile("data.txt", "https://tygia.com/json.php");
	}
}