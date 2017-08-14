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
		cout << "打开文件失败  请重新输入\n";
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
	//	cout << "解析来源于服务器的包请输入数字0：\n";
	//	cout << "解析发送到服务器的包请输入数字1：\n";
	//	cin >> s;
	//
	//	if (!(s == "0" || s == "1"))
	//	{
	//		cout << "请重新输入\n";
	//		goto pop;
	//	}
	//	count = 0;
	//up:
	//	string a;
	//	cout << "请输入文件"<<count<<"   输入shutdown推出" << endl;
	//	cin >> a;
	//	if (s == "shutdown")
	//		goto down;
	//	file.open(a);
	//	if (!file.is_open()) {
	//		cout << "打开文件失败  请重新输入\n";
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
	//		cout << "开始解析\n\n";
	//	if (s == "0") 
	//			A.ParseFromDB();
	//	else
	//			A.ParseToDB();
	//		cout << "解析完成" << endl;
	//		goto down;
	//
	//	}
	//	else {
	//		cout << "被解析文件不全，请输入后续包\n";
	//		goto up;
	//	}
	//down:
	//	cout << "继续解析请输出入continue：输入其他退出\n";
	//	cin >> s;
	//	if (s == "continue")
	//		goto pop;
	//	else return 0;
}