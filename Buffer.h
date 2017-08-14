#include <iostream>
using namespace std;

class Buffer {
private:
	int B_length_count = 0;//�ܳ���
	int B_length_need = 0;//�����data�ܳ���
	int B_length_used = 0;//��ʹ�ó���
	bool B_complete = true;//�жϻ������Ƿ�����
	char * B_Buffer = NULL;//������
public:

	Buffer(int a, int b, int c, bool d) {
		B_length_count = a;
		B_length_need = b;
		B_length_used = c;
		B_complete = d;
	};

	int get_B_length_take();//����Ҫ�೤
	int get_B_length_need();
	bool get_B_complete();

	void NewBuffer(const int length_need);//�ж�+�½�������

	void Buffer_Add(const int length_need);

	void Buffer_Write(const char *data, const int from, const int length_write);//�򻺳�������
	char* Buffer_Read();//������

	~Buffer() {
		free(B_Buffer);
	}
};

int Buffer::get_B_length_need() {
	return B_length_need;
}

int Buffer::get_B_length_take() {
	return B_length_need - B_length_used;
}

bool Buffer::get_B_complete() {
	return B_complete;
}

void Buffer::NewBuffer(const int length_need) {
	if (length_need > B_length_count) {//�ж��Ƿ���Ҫ�½�
		free(B_Buffer);
		B_Buffer = (char*)malloc(length_need + 1);
	}
	B_length_count = length_need + 1;
	B_Buffer[length_need] = '\0';//ĩβ��0
	B_length_need = length_need;//��Ҫ���ȸı�
	B_length_used = 0;//��ʹ������
};

void Buffer::Buffer_Add(const int length_add) {
	B_length_count += length_add;
	int count1 = B_length_count;
	char* buffer1 = B_Buffer;
	B_Buffer = (char*)malloc(count1);
	while (count1--) {
		buffer1[count1] = B_Buffer[count1];
	}
	free(buffer1);
	B_length_need = count1;//��Ҫ���ȸı�
};

void Buffer::Buffer_Write(const char *data, const int from, const int length_write) {



	for (int i = 0; i < length_write; i++)
		B_Buffer[B_length_used + i] = data[from + i];//��data�����￪ʼ��
	B_length_used += length_write;//��ʹ�õ����
	if (B_length_used == B_length_need)//�ж�����
		B_complete = true;
	else if (B_length_used > B_length_need)
		cout << "�ڴ����\n";
	else B_complete = false;
};

char* Buffer::Buffer_Read() {
	return B_Buffer;
}

extern Buffer My_Buffer(0, 0, 0, true);//ȫ�ֱ���buffer