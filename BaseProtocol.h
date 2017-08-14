#pragma once

class BaseProtocol {
public:
	/* ��Ϣ���麯�������𽫿ͻ��˷��͸����ݿ�����ݰ��������������Ϣ��
	*  ע��һ��������Ϣ�ĳ��ȿ��ܴﵽ��ǧ�ֽ����ϡ���һ��IP��һ���һǧ����ֽ����ҡ�
	*  ����һ����Ϣ���ܻ�ֳɶ�����ݰ����з���
	*  ��������ץȡ�����ݰ������Ȼ���������ֱ���յ���������Ϣ�ٽ��н�����
	*  ������
	*       data:���յ���������,�Ѿ�����TCP/IPͷ
	*       len���������ݵĳ���
	*  ����ֵ��
	true-������������Ϣ��false-����������Ϣ.
	*/
	virtual bool CompleteToDB(const char* data, const int len) = 0;

	/*
	*   ͬ�ϣ��������ݿ�����������ͻ��˵���Ϣ
	*/
	virtual bool CompleteFromDB(const char* data, const int len) = 0;

	/*
	*   ��������ɵ�������Ϣ���н���
	*/
	virtual void ParseToDB() = 0;

	/*
	*   ��������ɵ�������Ϣ���н���
	*/
	virtual void ParseFromDB() = 0;
};