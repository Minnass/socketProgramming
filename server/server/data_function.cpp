#include"Header.h"
void READ_FILE(string fileName, infor Arr[], int& n) {
	fstream Input_inf;
	Input_inf.open(fileName, ios::in);
	string Temp;
	while (!Input_inf.eof()) {
		getline(Input_inf, Temp, '[');
		int k = Temp.find("golds");
		if (k > 0) {
			break;
		}
	}
	while (!Input_inf.eof()) {
		getline(Input_inf, Temp, '[');
		int k = Temp.find("value");
		if (k > 0) {
			char Check = 't';
			int _Count = 1;
			infor A;
			while (Check != ']') {
				Input_inf >> Check;
				if (Check == ':') {
					Input_inf >> Check;
					if (_Count == 1) {
						getline(Input_inf, A.Buy, '"');
						if (A.Buy == "") {
							A.Buy = "x";
						}
					}
					else if (_Count == 2) {
						getline(Input_inf, A.Sell, '"');
						if (A.Sell == "") {
							A.Sell = "x";
						}
					}
					else if (_Count == 3) {
						getline(Input_inf, A.Company, '"');
						if (A.Company == "") {
							A.Company = "x";
						}
					}
					else if (_Count == 4) {
						getline(Input_inf, A.Brand, '"');
						if (A.Brand == "") {
							A.Brand = "x";
						}
					}
					else if (_Count == 5) {
						getline(Input_inf, A.Updated, '"');
						if (A.Updated == "") {
							A.Updated = "x";
						}
					}
					else if (_Count == 6) {
						getline(Input_inf, A.Brand1, '"');
						if (A.Brand1 == "") {
							A.Brand1 = "x";
						}
					}
					else if (_Count == 7) {
						getline(Input_inf, A.Day, '"');
						if (A.Day == "") {
							A.Day = "x";
						}
					}
					else if (_Count == 8) {
						getline(Input_inf, A.ID, '"');
						if (A.ID == "") {
							A.ID = "x";
						}
					}
					else if (_Count == 9) {
						getline(Input_inf, A.Type, '"');
						if (A.Type == "") {
							A.Type = "x";
						}
					}
					else if (_Count == 10) {
						getline(Input_inf, A.CODE, '"');
						if (A.CODE == "") {
							A.CODE = "x";
						}
					}
					_Count++;
					if (_Count == 11) {
						_Count = 1;
						Arr[n] = A;
						n++;
						if (n > 999)return;
					}
				}
			}
		}
	}
}
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}
void crawlDataFromWebToFile(string fileName, string url) {
	fstream output;
	output.open(fileName, ios::out);
	CURL* curl;
	CURLcode res;
	string readBuffer;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		output << readBuffer;
		output.close();
	}
}
