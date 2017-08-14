#pragma once
#include "stdafx.h"
//���ĵ�Ϊ������������������������װ��
//class ���캯��char * data, int &from, int len
//���캯��from���д���  ��֤��һ���ԣ�������buffer����İ�������
//�ù��캯���Զ��������е�˽������
//����print�������
//���ֵİ�û�й̶���ʽ������
//��struct  ����һ������ ָ��Ϊ��ʱ����û��������
//��Field countΪ����=2ʱ ����һ������Ϊ3������  ��һ��Ϊͷ��� 
//����while��count--�����й����������


class Command :private Type {			//�������
private:
	char * Tag;
public:
	Command(char * data, int &from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
		point_from(Tag, data, from);
	}
	void print() {
		cout << "�������\n";
		cout << "����;" << T_Length << endl;
		cout << "Tag:";
		cout << endl;
	}
};

class Ready :private Type {				//׼��
private:
	char Staus;
public:
	Ready(char * data, int &from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
		Staus = data[from++];
	}
	void print() {
		cout << "�������\n";
		cout << "����;" << T_Length << endl;
		if (Staus == 73)
			cout << "Staus:Idle";
		else cout << "Staus:" << Staus<<endl;
		cout << endl;
	}
};

class Error :private Type {				//����
private:
	char *Severity;
	char *Code;
	char *Message;
	char *error;
	char *File;
	char *Line;
	char *Routine;
public:
	Error(char * data, int &from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;

		point_from(Severity, data, from);
		point_from(Code, data, from);
		point_from(Message, data, from);
		point_from(error, data, from);
		point_from(File, data, from);
		point_from(Line, data, from);
		point_from(Routine, data, from);
	}
	void print() {
		cout << "�������\n";
		cout << "����;" << T_Length << endl;
		cout << "Severity:" << Severity << endl;
		cout << "Code:" << Code << endl;
		cout << "Message:" << Message << endl;
		cout << "error:" << error << endl;
		cout << "File:" << File << endl;
		cout << "Line:" << Line << endl;
		cout << "Routine:" << Routine << endl;
		cout << endl;

	}
};

class Row_desc : private Type {			//������
private:
	int Field_count;

	T_Row_desc  *CTL;
public:

	Row_desc(char * data, int &from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;

		Field_count = CCI2(data, from);
		int count = Field_count;

		T_Row_desc *First;

		if (count--) {
		First= new T_Row_desc;
		point_from(First->Column_name, data, from);
		First->Table_OID = CCI(data, from);
		First->Column_index = CCI2(data, from);
		First->Type_OID = CCI(data, from);
		First->Column_length = CCI2(data, from);
		First->Type_modifier = CCI(data, from);
		First->Format = CCI2(data, from);
		CTL = First;
		}
		while (count--) {
			T_Row_desc *Node = new T_Row_desc;
			point_from(Node->Column_name, data, from);
			Node->Table_OID = CCI(data, from);
			Node->Column_index = CCI2(data, from);
			Node->Type_OID = CCI(data, from);
			Node->Column_length = CCI2(data, from);
			Node->Type_modifier = CCI(data, from);	
			Node->Format = CCI2(data, from);
			First->next = Node;
			First = First->next;
		}
	}
	void print() {
		cout << "������\n";
		cout << "����;" << T_Length << endl;
		cout << "������" << Field_count << endl;
		int count_1 = Field_count;
		T_Row_desc  *First_1 = CTL;
		while (count_1--) {
			cout << "Column_name��" << First_1->Column_name << endl;
			cout << "Table_OID��" << First_1->Table_OID << endl;
			cout << "Column_index��" << First_1->Column_index << endl;
			cout << "Type_OID��" << First_1->Type_OID << endl;
			cout << "Column_length��" << First_1->Column_length << endl;
			cout << "Type_modifier��" << First_1->Type_modifier << endl;
			cout << "Format��" << First_1->Format << endl;
			First_1 = First_1->next;
		}
		cout << endl;
	}
	~Row_desc() {
	
		while (CTL != NULL) {

			T_Row_desc *N = CTL;
			CTL = CTL->next;
			delete N;
		}
	}
};

class Data_row :private Type				//����
{
private:
	int Field_count;
	T_Date_row *CTL;
public:
	Data_row(char * data, int &from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;

		Field_count = CCI2(data, from);
		int count = Field_count;

		T_Date_row *First;

		if (count--) {
			First = new T_Date_row;
			First->Column_length = CCI(data, from);
			First->Data = (char*)malloc(sizeof(char) * (First->Column_length + 1));
			First->Data[First->Column_length] = '\0';
			strcpy_from(First->Data, data, from);
			CTL = First;
		}
		while (count--) {
			T_Date_row *Node = new T_Date_row;
			Node->Column_length = CCI(data, from);
			Node->Data = (char*)malloc(sizeof(char) * (Node->Column_length + 1));
			Node->Data[Node->Column_length] = '\0';
			strcpy_from(Node->Data, data, from);
			First->next = Node;
			First = First->next;
		}
	}

	void print() {
		cout << "����:Data_row\n";
		cout << "����;" << T_Length << endl;
		cout << "������" << Field_count << endl;
		int count_1 = Field_count;
		T_Date_row  *First_1 = CTL;
		while (count_1--) {
			cout << "Column_length:" << First_1->Column_length << endl;
			cout << "Data:" << First_1->Data << endl;
			First_1 = First_1->next;
		}
		cout << endl;
	}

	~Data_row() {
		while (CTL != NULL) {
			T_Date_row *N = CTL;
			CTL = CTL->next;
			free(N->Data);
			delete N;
		}
	}
};

class Authentication : private Type {
private:
	int Authentication_type;
	int Salt_value;
public:
	Authentication(char * data, int &from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
		Authentication_type = CCI(data, from);
		Salt_value = CCI(data, from);
	}

	void print() {
		cout << "Type :Authentication\n";
		cout << "����;" << T_Length << endl;
		cout << "Authentication_type:" << Authentication_type << endl;
		cout << "Salt_value:" <<hex<< (int)Salt_value << endl;
		cout << endl;
	}

};

class Parameter_status :private Type {
private:
	char* P_name;
	char* P_value;
public:
	Parameter_status(char * data, int &from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
		point_from(P_name, data, from);
		point_from(P_value, data, from);
	}

	void print() {
		cout << "Type :Parameter_status\n";
		cout << "����;" << T_Length << endl;
		cout << "P_name:" << P_name << endl;
		cout << "P_value:" << P_value << endl;
		cout << endl;
	}

};

class Pars_C :private Type {
public:
	Pars_C(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
	}
	void print() {
		cout << "�Ͽ�����\n";
		cout << "����;" << T_Length << endl;
	}
};

class Bind_C :private Type {
public:
	Bind_C(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
	}
	void print() {
		cout << "Type :Bind_C\n";
		cout << "����;" << T_Length << endl;
	}
};

class Backend_Key : private Type {
private:
	int PID;
	int Key;
public:
	Backend_Key(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;

		PID = CCI(data, from);
		Key = CCI(data, from);
	}

	void print() {
		cout << "Type :Backend_Key\n";
		cout << "����;" << T_Length << endl;
		cout << "PID:" << PID << endl;
		cout << "Key:" << Key << endl;
		cout << endl;
	}
};

class No_Data :private Type {		//�Ͽ�����
public:
	No_Data(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
	}
	void print() {
		cout << "Type :No_Data\n";
		cout << "����;" << T_Length << endl;
		cout << endl;
	}
};
