#ifndef mylibrary
#define mylibrary
#include<iostream>
#include<string >
#include<ws2tcpip.h>
#include<string>
#include<fstream>
#include<iomanip>
#include<conio.h>

#pragma comment(lib,"ws2_32.lib")
using namespace std;
struct infor {
	string Buy;
	string Sell;
	string Company;
	string Brand;
	string Updated;
	string Brand1;
	string Day;
	string ID;
	string Type;
	string CODE;
};
int Choose_Handle(int nChoose);
int Main_Menu();
bool Check_InputIP(string str);
void HandleOption(int& Command, SOCKET& sock);
string Input_Syntax();
int Search_Menu();
void HandleSearch_Option(int& Command, SOCKET& sock, int& Flag);
void Recv_EachInfor(infor& _user, SOCKET& sock);
void OutpUt_EachInfor(infor _user[], int n);
#endif

