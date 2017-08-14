#pragma once
#include <iostream>
using namespace std;

class Type {			//����
public:
	char T_Type;
	int T_Length;

	virtual void print() = 0;
};

int CCI(const char *data, int &from) {//���εĳ���
	unsigned char c[4];
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		c[i] = data[from+i];
		result += (unsigned int)(c[i]) << (8 * (3 - i));
	}
	if (data[from] >= 0x80) {
	
		~result;
		result += 1;
	
	}
	from += 4;
	return result;

}

int CCI_NO(const char *data, int from) {//�����εĳ���
	unsigned char c[4];
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		c[i] = data[from + i];
		result += (unsigned int)(c[i]) << (8 * (3 - i));
	}
	if (data[from] >= 0x80) {
		~result;
		result += 1;

	}
	return result;
}



short CCI2(const char* data, int &from) {

	unsigned char c[2];
	short result = 0;
	for (int i = 0; i < 2; i++)
	{
		c[i] = data[from + i];
		result += (unsigned int)(c[i]) << (8 * (1 - i));
	}
	if (data[from] >= 0x80) {

		~result;
		result += 1;

	}
	from += 2;
	return result;
}


void strcpy_from(char* destaddr, char *srcaddr, int &from)//��������ʼ������ֱ��\0�����ս� 0Ҳ������ȥ
{
	if ((NULL == destaddr) || (NULL == srcaddr))
		throw "Invalid argument(s)";
	char *c = destaddr;
	while (*c != '\0') {
		*c++ = *(srcaddr + from++);
	}
}

void point_from(char* &dest, char *src, int &from) {
	dest = src + from;
	from += (int)strlen(dest) + 1;
}

struct T_Row_desc {

	int Table_OID;  //4 2 4 2 4 2Ϊ���εĳ���
	int Column_index;
	int Type_OID;
	int Column_length;
	int Type_modifier;
	int	Format;

	T_Row_desc * next = NULL;
	char *Column_name;
};

struct T_Date_row {

	int Column_length;
	T_Date_row * next = NULL;

	char *Data;
};

struct T_Pars_formats
{
	int formats;
	T_Pars_formats *next = NULL;
};

struct Parameter
{
	char* name;
	char* value;
	Parameter *next=NULL;

};