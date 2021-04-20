#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
using namespace std;

template <class T>
T ROR(T value, int times)
{
	T temp = 0;
	int sizet = sizeof(T) * 8;
	for (int i = 0; i < sizet - times; i++)
		temp = temp | (T(1) << i);
	return ((value >> times) & temp) | (value << (sizet - times));
}

template <class T>
T ROL(T value, int times)
{
	return ROR(value, sizeof(T) * 8 - times);
}


unsigned int getComputerID()
{
	char computername[17];
	DWORD nSize = 16;
	GetComputerNameA(computername, &nSize);
	int i = 0;
	int eax = 0;
	int ebx = 0;
	int ecx = 0;
	int edx = 0;
	while (computername[i] && computername[i] != -52)
	{
		char dl = ~computername[i + 1];
		char al = ROR(computername[i], 4);
		al += dl;
		eax = (eax & 0xFFFFFF00) | (al & 0xFF);
		edx = (edx & 0xFFFFFF00) | (dl & 0xFF);
		ebx += eax;
		edx *= eax;
		ecx += edx;
		swap(ebx, edx);
		i += 2;
	}
	return _byteswap_ulong(ebx) + ecx;
}

string getSerial(unsigned int id, string username)
{
	int ebx = 0;
	int ecx = 0x00007FFF;
	int edx = 0;
	int eax = id;
	for (int i = 0; i < username.length(); i++)
	{
		ebx = (ebx & 0xFFFF0000) | ((int(username[i + 1]) & 0xFF) << 8) | (username[i] & 0xFF);
		ebx = ebx << 8;
		eax = id;
		eax = eax & 0x00F8F800;
		ebx = ((ebx ^ eax) + 0x6C6F6C) ^ 0x10101010;
		edx += ebx;
		ecx = (ecx + ebx - 0x2D3D2D) * 8 + eax;
	}
	int esi = 0;
	int edi = 0;
	for (int i = 16; i > 0; --i)
	{
		esi += edx;
		edi += ecx;
		edi = _byteswap_ulong(edi);
		esi = _byteswap_ulong(esi);
		edi = ROL(edi, 16);
		esi = ROR(esi, 16);
	}
	char buff[36];
	sprintf_s(buff, "%08X-%08X-%08X-%08X", ecx, edx, edi, esi);
	return string(buff);
}

int main()
{
	string username;
	while (1)
	{
		cout << "Input username: ";
		cin >> username;
		if (username.length() < 4 || username.length() > 32)
			cout << "Username must be between 4 and 32 characters length" << endl;
		else
			break;
	}
	cout << "Your serial: " << getSerial(getComputerID(), username);
	_getch();
	return 0;
}