#include <iostream>
using namespace std;

class Buffer {
private:
	int B_length_count = 0;//总长度
	int B_length_need = 0;//缓冲的data总长度
	int B_length_used = 0;//已使用长度
	bool B_complete = true;//判断缓冲区是否完整
	char * B_Buffer = NULL;//缓冲区
public:

	Buffer(int a, int b, int c, bool d) {
		B_length_count = a;
		B_length_need = b;
		B_length_used = c;
		B_complete = d;
	};

	int get_B_length_take();//还需要多长
	int get_B_length_need();
	bool get_B_complete();

	void NewBuffer(const int length_need);//判断+新建缓冲区

	void Buffer_Add(const int length_need);

	void Buffer_Write(const char *data, const int from, const int length_write);//向缓冲区存入
	char* Buffer_Read();//缓冲区

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
	if (length_need > B_length_count) {//判断是否需要新建
		free(B_Buffer);
		B_Buffer = (char*)malloc(length_need + 1);
	}
	B_length_count = length_need + 1;
	B_Buffer[length_need] = '\0';//末尾归0
	B_length_need = length_need;//需要长度改变
	B_length_used = 0;//已使用清零
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
	B_length_need = count1;//需要长度改变
};

void Buffer::Buffer_Write(const char *data, const int from, const int length_write) {



	for (int i = 0; i < length_write; i++)
		B_Buffer[B_length_used + i] = data[from + i];//在data的哪里开始存
	B_length_used += length_write;//已使用的相加
	if (B_length_used == B_length_need)//判断完整
		B_complete = true;
	else if (B_length_used > B_length_need)
		cout << "内存溢出\n";
	else B_complete = false;
};

char* Buffer::Buffer_Read() {
	return B_Buffer;
}

extern Buffer My_Buffer(0, 0, 0, true);//全局变量buffer