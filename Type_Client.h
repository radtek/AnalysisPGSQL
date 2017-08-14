#pragma once
#include "stdafx.h"

//ͬ�����������
//���ĵ�Ϊ�ͻ��˷�����������������װ��
//class ���캯��char * data, int &from, int len
//���캯��from���д���  ��֤��һ���ԣ�������buffer����İ�������
//�ù��캯���Զ��������е�˽������
//����print�������
//���ֵİ�û�й̶���ʽ������
//��struct  ����һ������ ָ��Ϊ��ʱ����û��������
//��Field countΪ����=2ʱ ����һ������Ϊ3������  ��һ��Ϊͷ��� 
//����while��count--�����й����������


class Termination :private Type {		//�Ͽ�����
public:
	Termination(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
	}
	void print() {
		cout << "�Ͽ�����\n";
		cout << "����;" << T_Length << endl;
		cout << endl;
	}
};

class Simple_Query :private Type {				//�򵥲�ѯ
private:
	char * Query;
public:
	Simple_Query(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
		point_from(Query, data, from);
	}

	void print() {
		cout << "Simple_Query\n";
		cout << "����;" << T_Length << endl;
		cout << "Query;" << Query << endl;
		cout << endl;
	}
};

class Password_message :private Type {
private:
	char * Password;
public:
	Password_message(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
		point_from(Password, data, from);
	}

	void print() {
		cout << "Password_message\n";
		cout << "����;" << T_Length << endl;
		cout << "Password;" << Password << endl;
		cout << endl;
	}

};

class Pars :private Type {
private:
	char *Statement;
	char *Query;
	short Paraments;
	int *CTL;
public:
	Pars(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;

		point_from(Statement, data, from);
		point_from(Query, data, from);
		Paraments = CCI2(data, from);
		int count = Paraments;
		CTL = new int[count];
		for (int i = 0; i < count; i++)
			CTL[i] = CCI(data, from);
	}

	void print() {
		cout << "Pars\n";
		cout << "����;" << T_Length << endl;
		cout << "Statement;" << Statement << endl;
		cout << "Query;" << Query << endl;
		cout << "Paraments;" << Paraments << endl;
		int count_1 = Paraments;
		for (int i = 0; i < count_1; i++)
			cout << "Type_OID" << CTL[i] << endl;
		cout << endl;
	}
	~Pars()
	{
		delete[] CTL;
	}
};

class Bind :private Type {
private:
	char *Portal;
	char *Statement;
	short Parmenter_formats;
	short *CTL1;
	short Parameter_values;
	T_Date_row * CTL2;
	short Result_formats;
public:
	Bind(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
		point_from(Portal, data, from);
		point_from(Statement, data, from);
		Parmenter_formats = CCI2(data, from);

		short count1 = Parmenter_formats;

		CTL1 = new short[count1];
		for (short i = 0; i < count1; i++)
			CTL1[i] = CCI(data, from);

		Parameter_values = CCI2(data, from);
		short count2 = Parameter_values;

		T_Date_row *First = CTL2;
		if (count2--) {
			First = new T_Date_row;
			First->Column_length = CCI(data, from);
			First->Data = (char*)malloc(sizeof(char) * (First->Column_length + 1));
			First->Data[First->Column_length] = '\0';
			strcpy_from(First->Data, data, from);
			CTL2 = First;
		}
		while (count2--) {
			T_Date_row *Node = new T_Date_row;
			Node->Column_length = CCI(data, from);
			Node->Data = (char*)malloc(sizeof(char) * (Node->Column_length + 1));
			Node->Data[Node->Column_length] = '\0';
			strcpy_from(Node->Data, data, from);
			First->next = Node;
			First = First->next;
		}
		Result_formats = CCI2(data, from);
	}

	void print() {
		cout << "Bind\n";
		cout << "����;" << T_Length << endl;
		cout << "Portal;" << Portal << endl;
		cout << "Statement;" << Statement << endl;
		cout << "Parmenter_formats;" << Parmenter_formats << endl;
		int count_1 = Parmenter_formats;
		for (short i = 0; i < count_1; i++)
			cout << "formats:" << CTL1[i]<< endl;

		int count_2 = Parameter_values;
		T_Date_row *First_2 = CTL2;
		while (count_2--) {
			cout << "Column_length:" << First_2->Column_length << endl;
			cout << "Data" << First_2->Data << endl;
			First_2 = First_2->next;
		}
		cout << "Result_formats:" << Result_formats << endl;
		cout << endl;
	}

	~Bind() {
		delete [] CTL1;
		while (CTL2 != NULL) {
			T_Date_row *N = CTL2;
			CTL2 = CTL2->next;
			free(N->Data);
			delete N;
		}
	}
};

class Execute : private Type {
private:
	char * Protal;
	int Returns;
public:
	Execute(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;

		point_from(Protal, data, from);
		Returns = CCI(data, from);
	}
	void print() {
		cout << "Type:Execute\n";
		cout << "����;" << T_Length << endl;
		cout << "Portal;" << Protal << endl;
		cout << "Returns;" << Returns << endl;
		cout << endl;
	}
};

class Sync :private Type {		//�Ͽ�����
public:
	Sync(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
	}
	void print() {
		cout << "Sync\n";
		cout << "����;" << T_Length << endl;
		cout << endl;
	}
};

class Describle : private Type{
private:
	char * Portal;
public:
	Describle(char * data, int& from) {
		T_Type = data[from++];
		T_Length = CCI(data, from) + 1;
		point_from(Portal, data, from);
	}

	void print() {
		cout << "Simple_Query\n";
		cout << "����;" << T_Length << endl;
		cout << "Portal;" << Portal << endl;
		cout << endl;
	}
};

class Start_up : private Type{
private:
	Parameter *CTL;
public:
	Start_up(char * data, int& from) {
		T_Type = 0;
		T_Length = CCI(data, from) ;
		from += 4;
		CTL = new Parameter;
		Parameter *First = CTL;
		point_from(First->name, data, from);
		point_from(First->value, data, from);
		int a = 2;
		while (from!=T_Length-1)
		{
			Parameter *Node = new Parameter;
			point_from(Node->name, data, from);
			point_from(Node->value, data, from);
			First->next = Node;
			First = First->next;
		}
		from++;
	}
	void print() {
		cout << "Start_up\n";
		cout << "����;" << T_Length << endl;
		Parameter *First_1 = CTL;
		while (First_1!=NULL)
		{
			cout << "Parameter name:" << First_1->name << endl;;
			cout << "Parameter value:" << First_1->value << endl;;
			First_1 = First_1->next;
		}
		cout << endl;
	}
	~Start_up()
	{
		
		while (CTL != NULL) {
			Parameter *N = CTL;
			CTL = CTL->next;

			delete N;
		}
	}

};