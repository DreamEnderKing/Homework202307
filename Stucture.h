#pragma once

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <memory>

namespace Stucture
{
	enum ModifyStatus
	{
		Added = 0,
		Modified = 1,
		Deleted = 2
	};

	// �γ̳ɼ�����
	class ClassData
	{
	public:
		// ͨ���γ���ţ��γ����ƣ��γ�ѧ�ֺͿγ��ļ���ʼ���γ�����
		ClassData(int _id, std::string _name, int _point, std::ifstream& _file);
		// ��ѯѧ���ɼ�����������ڷ���-1��
		int GetScore(int _id);
		// ����ѧ����Ŀ
		void AddStudentData(int _id, int _score);
		// �޸�ѧ����Ŀ
		void ModifyStudentData(int _id, int _score);
		// ��ѯ�γ����ݱ仯�����仯д���޸Ĳ���
		void ScanUpdate(ClassData& _newData);
		// ����γ̳ɼ�
		void ArrangeData();
		// ����γ̳ɼ����ݿ�
		void SaveClassData(std::ofstream& _file);
		// ��Ԫ��������
		friend void StudentInfo::UpdateClassData(ClassData& _class);
		// �γ�������Ϣ
		const int ID;	
		const std::string Name; 
		const int Point;
	protected:
		// �Ƿ��������
		bool Arranged = false;
		// �޸Ĳ��ֵ������棬����UpdateClass���д���
		// Key���޸�״̬��Value��(ѧ��id��ѧ���µĳɼ�)
		std::map<ModifyStatus, std::pair<int, int>> ModifiedList = {};
		// �γ����ݿ�
		// Key��ѧ��id��Value��ѧ���ɼ�
		std::map<int, int> StudentList = {};
	};

	// �γ�id�����ƺ�ѧ�����ݿ�
	class ClassInfo
	{
	public:
		// ��ʼ���µĿγ�id�����ƺ�ѧ�����ݿ�
		ClassInfo();
		// ͨ���ļ���ʼ��id�����ƺ�ѧ�����ݿ�
		ClassInfo(std::ifstream& _file);
		// ����ѧ�����ݿ���ʵ��д���¼����
		void JoinStudentInfo(StudentInfo& _studentInfo);
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
		void SaveClassInfo(std::ofstream& _file);
	protected:
		// �γ����ݿ�
		// Key���γ�id��Value���γ�����
		std::map<int, ClassData> Data = {};
		// �󶨵�ѧ�����ݿ�
		StudentInfo* StudentList = nullptr;
		// �γ������ļ��洢����ַ
		std::string BaseUri = "";
	};

	// ѧ�����ݿ�
	class StudentInfo
	{
	public:
		// �½�ѧ�����ݿ�
		StudentInfo();
		// ͨ��ѧ���ļ���ȡѧ�����ݿ�
		StudentInfo(std::istream& _file);
		// ��ȡѧ��ѧϰ�γ��б��������ڷ��ؿ��б�
		std::vector<int> GetClasses(int _id);
		// ���¿γ�����
		void UpdateClassData(ClassData& _class);
		// ����ѧ�����ݿ�
		void SaveStudentInfo(std::ostream& _file);
	protected:
		// ѧ�����ݿ�
		// Key��ѧ��id��Value��(ƽ��ѧ�ּ����γ��б�)
		std::map<int, std::pair<float, std::vector<std::shared_ptr<ClassData>>>> Data = {};
	};
}