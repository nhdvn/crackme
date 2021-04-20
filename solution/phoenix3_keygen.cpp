#include <iostream>
#include <vector>
#include <string>
using namespace std;

string activationCode = "FCFDFEFCFBFBFBF8F0F1F2F0FFFFFFFCECEDEEECFBFBFBF8";

unsigned int encryptUsername(string username)
{
	unsigned int res = 0xDEADC0DE;
	for (int i = 0; i < username.length(); ++i)
	{
		unsigned int temp = username[i];
		temp = temp * 16777216 + temp * 65536 + temp * 256 + temp;
		res = ((res ^ temp) & 0xFEFED0D0) | 0x000159A3;
		temp = res & 0xFFFF;
		res /= 65536;
		res = res ^ temp;
	}
	return res & 0xFFFF;
}

string generateSerial(string username)
{
	int encryptedUsername = encryptUsername(username);
	string res = "";
	vector<int> fibonacci = { 0x2AC2, 0x452F, 0x6FF1, 0xB520, 0x2511 };
	for (int i = 0; i < 5; ++i)
	{
		int temp = fibonacci[i] ^ encryptedUsername;
		int k = 10000;
		for (int j = 0; j < 5; ++j)
		{
			res.push_back(char(temp / k + '0'));
			temp %= k;
			k /= 10;
		}
		if (i != 4)
			res.push_back('-');
	}
	return res;
}

int main()
{
	cout << "Input username: ";
	string username;
	cin >> username;
	if (username.length() > 31)
		username = username.substr(0, 31);
	cout << "Username: " << username << endl;
	cout << "Serial: " << generateSerial(username) << endl;
	cout << "Activation code: " << activationCode << endl;
	return 0;
}