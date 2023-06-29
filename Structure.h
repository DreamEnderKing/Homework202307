#pragma once

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>

namespace Structure
{
	static class __Snippet__
	{
	public:
		static void MyDebugError(std::string message);
		static std::string EncodeBase64(std::string content);
		static std::string DecodeBase64(std::string content);
		static const std::string to_b64;
	} Snippet;

	enum ModifyStatus
	{
		Added = 0,
		Modified = 1,
		Deleted = 2
	};

	// ѧ������ͳ����Ϣ
	struct StudentBriefData
	{
		StudentBriefData() 
		{
			averageScore = 0, totalPoint = 0;
		}
		StudentBriefData(float _avg, int _t)
		{
			averageScore = _avg, totalPoint = _t;
		}
		float averageScore;
		int totalPoint;
	};

	// �޸ĵ�Ԫ
	struct ModifyLog
	{
		ModifyLog() 
		{
			status = Added, stuId = 0, score = 0, oldScore = 0;
		}
		ModifyLog(ModifyStatus _status, int _stu, int _score, int _old = 0)
		{
			status = _status, stuId = _stu, score = _score, oldScore = _old;
		}
		ModifyStatus status;
		int stuId, score, oldScore;
	};

	class ClassData;
	class StudentInfo;
	class ClassInfo;

	// �γ̳ɼ�����
	class ClassData
	{
	public:
		// ͨ���γ���ţ��γ����ƣ��γ�ѧ�ֺͿγ��ļ���ʼ���γ�����
		ClassData(const int _id, const std::string _name, const int _point, std::ifstream& _file);
		// ��ѯѧ���ɼ�����������ڷ���-1��
		int GetScore(int _id);
		// ����ѧ����Ŀ(����������޸ģ����������������)
		void UpdateStudentData(int _id, int _score);
		// ɾ��ѧ����Ŀ(������������޶���)
		void DeleteStudentData(int _id);
		// ��ѯ�γ����ݱ仯�����仯д���޸Ĳ���
		void ScanUpdate(const ClassData& _newData);
		// ����������������γ����ݱ仯
		void InitialUpdate();
		// ��տγ����ݱ仯
		void ClearModifiedList();
		// ����γ̳ɼ����ݿ�(�ڶ�������ָ���Ƿ����ı���ʽд��)
		void SaveClassData(std::ostream& _file, bool _textMode = true) const;
		// ��ȡ�޸Ĳ���
		std::vector<ModifyLog> GetModifiedList() const;
		// �γ�������Ϣ
		const int ID;	
		const std::string Name; 
		const int Point;
	protected:
		// �޸Ĳ��ֵ������棬����UpdateClass���д���
		// Key���޸�״̬��Value��(ѧ��id��ѧ���µĳɼ�)
		std::vector<ModifyLog> ModifiedList = {};
		// �γ����ݿ�
		// Key��ѧ��id��Value��ѧ���ɼ�
		std::map<int, int> StudentList = {};
	};

	// ѧ�����ݿ�
	class StudentInfo
	{
	public:
		// �½�ѧ�����ݿ�
		StudentInfo();
		// ͨ��ѧ���ļ���ȡѧ�����ݿ�
		StudentInfo(std::istream& _file);
		// ��ȡѧ��ѧϰ�γ��б����������ڷ��ؿ��б���
		std::vector<std::pair<int, std::shared_ptr<ClassData>>> GetClasses(int _id);
		// ���¿γ�����
		void UpdateClassData(const std::shared_ptr<ClassData>& _class);
		// ���ӿγ����ݿ�
		void JoinClassInfo(const std::map<int, std::shared_ptr<ClassData>>& _classInfo);
		// ����ѧ�����ݿ�
		void SaveStudentInfo(std::ostream& _file, bool _textMode = true);
	protected:
		// ѧ�������ļ���
		// Key��ѧ��id��Value��(ѧ��������Ϣ��(�γ�id���γ̱���)�б�)
		// Ԥ�����ڴ�����ռ䣬�ڿ��ܵĴ�������ǰ����ֻ�������ɸ�ClassData
		std::map<int, std::pair<StudentBriefData, std::vector<std::pair<int, std::shared_ptr<ClassData>>>>> Data = {};
	};

	// �γ�id�����ƺ�ѧ�����ݿ�
	class ClassInfo
	{
	public:
		// ��ʼ���µĿγ�id�����ƺ�ѧ�����ݿ�
		ClassInfo();
		// ͨ���ļ���ʼ��id�����ƺ�ѧ�����ݿ�
		ClassInfo(std::istream& _file);
		// ����ѧ�����ݿ���ʵ��д���¼����
		void JoinStudentInfo(StudentInfo* _studentInfo);
		// ָ���γ������ļ��洢����ַ
		// �ڶ�������ָ���ļ��洢����ַ��ԭ��ַ��ͬʱ����Ϊ
		// ���ΪTrue�����ƶ��������ݣ�ΪFalse������ָ����ַ��ˢ��StudentData
		void ChangeBaseUri(std::string _newUri, bool _moveData = true);
		// ��ȡ�γ̳ɼ�����
		std::shared_ptr<ClassData> GetClassData(int _id);
		// ���¿γ�id�����ƺ�ѧ������
		// ���û�пγ���Ϣ�����½��γ���Ϣ
		// ����γ���Ϣ�Ѵ��ڣ�����¿γ���Ϣ
		void UpdateClassData(ClassData& _data);
		// ����ѧ�����ݿ�
		void SaveClassInfo(std::ostream& _file, bool _textMode = true);
	protected:
		// �γ����ݿ�
		// Key���γ�id��Value���γ�����
		std::map<int, std::shared_ptr<ClassData>> Data = {};
		// �󶨵�ѧ�����ݿ�
		std::shared_ptr<StudentInfo> StudentList = nullptr;
		// �γ������ļ��洢����ַ
		std::string BaseUri = "";
		// ѧ���ɼ��ļ���ַ(���)
		std::string StuUri = "Student.dat";
	};
}

#endif