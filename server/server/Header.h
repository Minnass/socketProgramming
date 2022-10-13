#define CURL_STATICLIB
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
//
#ifndef mylibrary
#define mylibrary
#pragma comment	(lib,"ws2_32.lib")
#include<winSock2.h>
#include<iostream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<tchar.h>
#include<Windows.h>
#include<conio.h>
#include<WS2tcpip.h>
#include<sstream>
#include<fstream>
#include<thread>
#include <curl/curl.h> // phải được add vào visual studio, có ghi rõ cách add ở phần báo cáo
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
struct User_infor {
	string user_Name;
	string password;
};
void READ_FILE(string fileName, infor Arr[], int& n);
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
void crawlDataFromWebToFile(string fileName, string url);
int HandLe_Option(string Option, SOCKET& sock);
void Handle_SearchOption(string Option, SOCKET& sock);
void Send_EachInfor(infor _user, SOCKET& sock);
string Time_Handle(string Time_);
void listenForConnection(SOCKET* client);
void update_();
#endif


