#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

string basestring = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int baselen = basestring.length();

char getCharFromBaseString(int pos, int offs)
{
	if (pos + offs < baselen)
		return basestring[pos + offs];
	else
		return basestring[pos + offs - baselen];
}

int getOffsetFromPos(int pos, char character)
{
	if (pos >= baselen || pos < 0)
		return -1;
	int counter = 0;
	int i = pos;
	while (1)
	{
		if (basestring[i] == '\0')
		{
			i = 0;
			continue;
		}
		if (basestring[i] == character)
			break;
		if (i == pos - 1)
			return -1;
		i++;
		counter++;
	}
	return counter;
}

char ROL(char num, int times)
{
	return (num << times) | (num >> (8 - times));
}

string stripUsername(string username)
{
	for (int i = 0; i < username.length(); i++)
	{
		if (basestring.find(username[i]) == string::npos)
		{
			username.erase(i, 1);
			i--;
		}
	}
	return username;
}

string encryptUsername(string username, int startPositionInBaseString)
{
	int DL = int(ROL(username[0], 3));
	string res = "";
	for (int i = 0; i < username.length(); i++)
	{
		int AL = username[i] ^ username[i + 1];
		AL = (AL + DL) & 0xFF;
		DL = (AL + DL) & 0xFF;
		int offset = AL % baselen;
		char ch = getCharFromBaseString(startPositionInBaseString, offset);
		res.push_back(ch);
	}
	return res;
}

string getSerial(string username, string encryptedUname, int startPosInBaseString)
{
	string res = "";
	for (int i = 0; i < username.length(); i++)
	{
		int offs = getOffsetFromPos(startPosInBaseString, username[i]);
		int pos2 = getOffsetFromPos(0, encryptedUname[i]);
		res.push_back(getCharFromBaseString(pos2, offs));
	}
	return res;
}



int main()
{
	cout << "Input username: ";
	string username;
	cin >> username;
	username = stripUsername(username);
	cout << "Your username: " << username << endl;
	int pos = 4 * username.length();
	if (pos > 60)
		pos = 30;
	string encrytedUname = encryptUsername(username, pos);
	string serial = getSerial(username, encrytedUname, pos);
	cout << "Your Serial: " << serial << endl;
	_getch();
	return 0;
}