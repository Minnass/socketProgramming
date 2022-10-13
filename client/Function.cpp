#include"Header.h"
bool Check_InputIP(string str) {
	if (str.size() < 0 || str.size() > 15) {
		return false;
	}
	return true;
}
int Main_Menu() {

	cout << "\n\n\n\n\t\t||=========== WELCOM CONNECTED SEVER ============||\n";
	cout << "\t\t||\t\t     " << setw(28) << left << "1. Login" << "||\n";
	cout << "\t\t||\t\t     " << setw(28) << left << "2. Sign up" << "||\n";
	cout << "\t\t||\t\t     " << setw(28) << left << "3. Exit" << "||\n";
	cout << "\t\t||===============================================||\n";
	return 3;
}
int Choose_Handle(int nChoose) {
	int n;
	cout << "\t\t----Choose: ";
	cin >> n;
	while (cin.fail() == true || n<1 || n >> nChoose) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\t\tEnter Again: ";
		cin >> n;
	}
	return n;
}
void HandleOption(int& Command, SOCKET& sock)
{
	string Input_user = "";
	string byteReceiv = "";
	int byteReceived = -2;
	int Result;
	char buf[4096];
	if (Command == 1) {
		string user_name;
		string pass_word;
		Input_user = "login";
		Result = send(sock, Input_user.c_str(), Input_user.size() + 1, 0);
		if (Result == SOCKET_ERROR) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			return;
		}
		cout << "\n\t\tUsername: ";
		cin >> user_name;
		Result = send(sock, user_name.c_str(), user_name.size() + 1, 0);
		if (Result == SOCKET_ERROR) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			return;
		}
		cout << "\n\t\tPassword: ";
		pass_word = Input_Syntax();
		Result = send(sock, pass_word.c_str(), pass_word.size() + 1, 0);
		if (Result == SOCKET_ERROR) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			return;
		}
		byteReceiv = recv(sock, buf, 4096, 0);
		if (byteReceived == -1 || byteReceived == 0) {
			cout << "\nServer Closes connection. Quitted" << endl;
		}
		else
		{
			if (string(buf) == "false") {
				cout << "\n\t\tFailed login, username or password is not correct !" << endl;
			}
			else {
				cout << "\n\t\tLogin is Successful !\n\t\t";
				system("pause");
				int com_mand = -1;
				while (com_mand != 3) {
					system("cls");
					com_mand = Choose_Handle(Search_Menu());
					HandleSearch_Option(com_mand, sock, Command);
				}

			}
		}
	}
	else if (Command == 2) {
		string user_name;
		string pass_word;
		Input_user = "signup";
		Result = send(sock, Input_user.c_str(), Input_user.size() + 1, 0);
		if (Result == SOCKET_ERROR) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			return;
		}
		cout << "\n\t\tUsername: ";
		cin >> user_name;
		Result = send(sock, user_name.c_str(), user_name.size() + 1, 0);
		if (Result == SOCKET_ERROR) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			return;
		}
		cout << "\n\t\tPassword: ";
		pass_word = Input_Syntax();
		Result = send(sock, pass_word.c_str(), pass_word.size() + 1, 0);
		if (Result == SOCKET_ERROR) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			return;
		}
		byteReceiv = recv(sock, buf, 4096, 0);
		if (byteReceived == -1 || byteReceived == 0) {
			cout << "\nServer Closes connection. Quitted" << endl;
		}
		else {
			if (string(buf) == "false") {
				cout << "\n\t\tCan't register, username has been registered ! " << endl;
			}
			else {
				cout << "\n\t\tRegister is Successful ! " << endl;
			}
		}
	}
	if (Command == 3) {
		Input_user = "exit";
		send(sock, Input_user.c_str(), Input_user.size() + 1, 0);
		return;
	}
	cout << "\t\t";
	system("pause");
}
string Input_Syntax() {
	char x = '1';
	char mk[50];
	int size = 0;
	while (x != 13) {
		x = _getch();
		if (x == 13) {
			break;
		}
		if (x == 8) {
			if (size != 0) {
				mk[size] = '\0';
				size--;
				cout << "\b \b";
			}
		}
		else {
			cout << x;
			mk[size++] = x;
			cout << "\b \b*";
		}
	}
	mk[size] = '\0';
	string END = mk;
	return END;
}
int Search_Menu() {

	cout << "\n\n\n\n\t\t||============= LOCKUP TABLE ============||\n";
	cout << "\t\t||\t\t  " << setw(23) << left << "1. Lookup by date" << "||\n";
	cout << "\t\t||\t\t  " << setw(23) << left << "2. Lookup by type" << "||\n";
	cout << "\t\t||\t\t  " << setw(23) << left << "3. Exit" << "||\n";
	cout << "\t\t||=======================================||\n";
	return 3;
}
void HandleSearch_Option(int& Command, SOCKET& sock, int& Flag) {
	string keyWord = "";
	string message = "";
	int byteReceived = -2;
	char buf[4096];
	int Result;
	if (Command == 1) {
		message = "date";
		Result = send(sock, message.c_str(), message.size() + 1, 0);
		if (Result == SOCKET_ERROR || Result == -1 || Result == 0) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			Flag = 3;
			return;
		}
		cout << "\n\t\tEnter a day(dd/mm/yy/): ";
		cin >> keyWord;
		Result = send(sock, keyWord.c_str(), keyWord.size() + 1, 0);
		if (Result == SOCKET_ERROR || Result == -1 || Result == 0) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			Flag = 3;
			return;
		}
		byteReceived = recv(sock, buf, 4096, 0);
		if (byteReceived == 0 || byteReceived == -1) {
			cout << " Sever has closed connection, Exited\n";
		}
		else {
			if (string(buf) == "0") {
				cout << "\n\t\tNot Found ! \n\t\t";
				system("pause");
			}
			else {
				int Count = atoi(buf);
				infor _user[500];
				for (int i = 0; i < Count; i++) {
					Recv_EachInfor(_user[i], sock);
				}
				OutpUt_EachInfor(_user, Count);
				cout << "\n\t\t";
				system("pause");
			}
		}
	}
	else if (Command == 2) {

		message = "type";
		Result = send(sock, message.c_str(), message.size() + 1, 0);
		if (Result == SOCKET_ERROR) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			Flag = 3;
			return;
		}
		cout << "\n\t\tEnter a Type: ";
		cin >> keyWord;
		Result = send(sock, keyWord.c_str(), keyWord.size() + 1, 0);
		if (Result == SOCKET_ERROR) {
			cout << "\n\t\tSever disconnected\n";
			Command = 3;
			Flag = 3;
			return;
		}
		byteReceived = recv(sock, buf, 4096, 0);
		if (byteReceived == 0 || byteReceived == -1) {
			cout << " Sever has closed connection, Exited\n";
		}
		else {
			if (string(buf) == "0") {
				cout << "\n\t\tNot Found ! \n\t\t";
				system("pause");
			}
			else {
				int Count = atoi(buf);
				infor _user[500];
				for (int i = 0; i < Count; i++) {
					Recv_EachInfor(_user[i], sock);
				}
				OutpUt_EachInfor(_user, Count);
				cout << "\n\t\t";
				system("pause");
			}
		}
	}
	if (Command == 3) {
		message = "exit";
		send(sock, message.c_str(), message.size() + 1, 0);
		Flag = 3;
	}

}
void Recv_EachInfor(infor& _user, SOCKET& sock) {
	string message = ".";
	char buf[4096];
	recv(sock, buf, 4096, 0);
	_user.ID = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.Company = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.Brand = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.Buy = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.Sell = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.Updated = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.Brand1 = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.CODE = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.Day = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
	recv(sock, buf, 4096, 0);
	_user.Type = string(buf);
	send(sock, message.c_str(), message.size() + 1, 0);
}
void OutpUt_EachInfor(infor _user[], int n) {
	cout << "\n\n====================================================================================================\n";
	cout << "|    ID   | Company |              Brand               |    Buy    |    Sell   |       Update      |" << endl;
	cout << "====================================================================================================\n";
	for (int i = 0; i < n; i++) {
		cout << "|" << setw(9) << left << _user[i].ID << "|" << setw(9) << left << _user[i].Company << "|" << setw(34) << left << _user[i].Brand << "|" << setw(11) << left << _user[i].Buy << "|" << setw(11) << left << _user[i].Sell << "|" << _user[i].Updated << "|\n";
	}
	cout << "====================================================================================================\n";
}