#pragma once
#include "BaseProtocol.h"
#include "Type_Server.h"
#include "Type_Client.h"
#include "Buffer.h"
class Protocol : public BaseProtocol {
public:
	bool CompleteFromDB(const char* data, const int len);
	void ParseFromDB();
	bool CompleteToDB(const char* data, const int len);
	void ParseToDB();

};

bool Protocol::CompleteFromDB(const char* data, const int len) {
	if (My_Buffer.get_B_complete() == false) {//不全的话接着补
		int take = My_Buffer.get_B_length_take();//from变成还剩多少的take
		if (len <= take)
			My_Buffer.Buffer_Write(data, 0, len);
		else {
			while (take < len) {
				int length = CCI_NO(data, take + 1) + 1;
				if (take + length > len) {
					My_Buffer.Buffer_Add(length);//判断
					My_Buffer.Buffer_Write(data, take, length);
					return false;
				}
				else if (take + length == len) {
					My_Buffer.Buffer_Write(data, take, length);
					return true;
				}
				else {
					My_Buffer.Buffer_Write(data, take, length);
				}
				take += length;
			}
		}
		return My_Buffer.get_B_complete();
	}
	else {
		My_Buffer.NewBuffer(len);
		int from = 0;
		while (from < len) {
			int length = CCI_NO(data, from + 1) + 1;
			if (from + length > len) {
				cout << from + length << endl;
				My_Buffer.NewBuffer(from + length);//判断
				My_Buffer.Buffer_Write(data, from, len);
				return false;
			}
			if (from + length == len) {
				My_Buffer.Buffer_Write(data, from, len);
				return true;
			}
			My_Buffer.Buffer_Write(data, from, length);
			from += length;
		}
		return false;
	}

}

void  Protocol::ParseFromDB() {

	int len = My_Buffer.get_B_length_need();
	int from = 0;
	char* data = My_Buffer.Buffer_Read();
	while (from < len) {
		int type = data[from];
		switch (type) {
		case 0x31: { Pars_C A(data, from); A.print(); break; }
		case 0x32: { Bind_C A(data, from); A.print(); break; }
		case 0x43: { Command A(data, from); A.print(); break; }
		case 0x44: { Data_row A(data, from); A.print(); break; }
		case 0x45: { Error A(data, from); A.print(); break; }
		case 0x4B: {Backend_Key A(data, from); A.print(); break; }
		case 0x52: { Authentication A(data, from); A.print(); break; }
		case 0x53: { Parameter_status A(data, from); A.print();  break; }
		case 0x54: { Row_desc A(data, from); A.print();  break; }
		case 0x5A: { Parameter_status A(data, from); A.print(); break; }
		case 0x6E: { No_Data A(data, from); A.print(); break; }

		default: {
			cout << "服务器发送未知类型" << data[from] << endl;;
			int from1 = from + 1;
			int len1 = CCI_NO(data, from1) + 1;
			from += len1;
			break; }
		}
	}
}

bool Protocol::CompleteToDB(const char* data, const int len) {

	if (My_Buffer.get_B_complete() == false) {//不全的话接着补
		int take = My_Buffer.get_B_length_take();//from变成还剩多少的take
		if (len <= take)
			My_Buffer.Buffer_Write(data, 0, len);
		else {
			while (take < len) {
				int length = CCI_NO(data, take + 1) + 1;
				if (take + length > len) {
					My_Buffer.Buffer_Add(length);//判断
					My_Buffer.Buffer_Write(data, take, length);
					return false;
				}
				else if (take + length == len) {
					My_Buffer.Buffer_Write(data, take, length);
					return true;
				}
				else {
					My_Buffer.Buffer_Write(data, take, length);
				}
				take += length;
			}
		}
		return My_Buffer.get_B_complete();
	}

	else {
		My_Buffer.NewBuffer(len);
		int from = 0;
		if (data[from] == 0) {
			My_Buffer.NewBuffer(CCI_NO(data, from));
			My_Buffer.Buffer_Write(data, from, len);
			return true;
		}
		while (from < len) {
			int length = CCI_NO(data, from + 1) + 1;
			if (from + length > len) {
				My_Buffer.NewBuffer(from + length);//判断
				My_Buffer.Buffer_Write(data, from, len);
				return false;
			}
			if (from + length == len) {
				My_Buffer.Buffer_Write(data, from, len);
				return true;
			}
			My_Buffer.Buffer_Write(data, from, length);
			from += length;
		}
		return false;
	}
}

void Protocol::ParseToDB() {

	int len = My_Buffer.get_B_length_need();
	int from = 0;
	char* data = My_Buffer.Buffer_Read();
	while (from < len) {
		int type = data[from];
		switch (type) {
		case 0x00: { Start_up A(data, from); A.print(); ; break; }
		case 0x42: { Bind A(data, from); A.print();  break; }
		case 0X44: { Describle A(data, from); A.print();  break; }
		case 0x45: { Execute A(data, from); A.print();  break; }
		case 0x50: { Pars A(data, from); A.print(); break; }
		case 0x51: { Simple_Query A(data, from); A.print();  break; }
		case 0x53: { Sync A(data, from); A.print(); break; }
		case 0x58: { Termination A(data, from); A.print();  break; }
		case 0x70: { Password_message A(data, from); A.print(); break; }
		default: {
			cout << "客户端发送未知类型" << data[from] << endl;
			int from1 = from + 1;
			int len1 = CCI_NO(data, from1) + 1;
			from += len1;
			break; }
		}
	}
}