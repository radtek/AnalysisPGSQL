#include "Protocol.h"
#include <fstream> 
#include <string>
#include "stdafx.h"
int main() {

	string s;
	char data[150000];
	int len = 0;
	Protocol A;
	ifstream file;

	file.open("T_start.bin");
	if (!file.is_open()) {
		cout << "���ļ�ʧ��  ����������\n";
		return 0;
	}
	len = 0;
	while (file) {
		data[len++] = file.get();
	}
	data[--len] = '\0';
	file.close();

	A.CompleteToDB(data, len);
	A.ParseToDB();



	//pop:
	//	cout << "������Դ�ڷ������İ�����������0��\n";
	//	cout << "�������͵��������İ�����������1��\n";
	//	cin >> s;
	//
	//	if (!(s == "0" || s == "1"))
	//	{
	//		cout << "����������\n";
	//		goto pop;
	//	}
	//	count = 0;
	//up:
	//	string a;
	//	cout << "�������ļ�"<<count<<"   ����shutdown�Ƴ�" << endl;
	//	cin >> a;
	//	if (s == "shutdown")
	//		goto down;
	//	file.open(a);
	//	if (!file.is_open()) {
	//		cout << "���ļ�ʧ��  ����������\n";
	//		return 0;
	//	}
	//	count++;
	//	len = 0;
	//	while (file) {
	//		data[len++] = file.get();
	//	}
	//	data[--len] = '\0';
	//	file.close();
	//	bool com;
	//	if (s == "0")
	//		com = A.CompleteFromDB(data, len);
	//	else
	//		com = A.CompleteToDB(data, len);
	//	if (com) {
	//		cout << "��ʼ����\n\n";
	//	if (s == "0") 
	//			A.ParseFromDB();
	//	else
	//			A.ParseToDB();
	//		cout << "�������" << endl;
	//		goto down;
	//
	//	}
	//	else {
	//		cout << "�������ļ���ȫ�������������\n";
	//		goto up;
	//	}
	//down:
	//	cout << "���������������continue�����������˳�\n";
	//	cin >> s;
	//	if (s == "continue")
	//		goto pop;
	//	else return 0;
}