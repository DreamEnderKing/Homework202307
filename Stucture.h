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

	// 课程成绩数据
	class ClassData
	{
	public:
		// 通过课程序号，课程名称，课程学分和课程文件初始化课程数据
		ClassData(int _id, std::string _name, int _point, std::ifstream& _file);
		// 查询学生成绩（如果不存在返回-1）
		int GetScore(int _id);
		// 创建学生条目
		void AddStudentData(int _id, int _score);
		// 修改学生条目
		void ModifyStudentData(int _id, int _score);
		// 查询课程数据变化并将变化写入修改部分
		void ScanUpdate(ClassData& _newData);
		// 排序课程成绩
		void ArrangeData();
		// 保存课程成绩数据库
		void SaveClassData(std::ofstream& _file);
		// 友元函数声明
		friend void StudentInfo::UpdateClassData(ClassData& _class);
		// 课程其他信息
		const int ID;	
		const std::string Name; 
		const int Point;
	protected:
		// 是否排序完成
		bool Arranged = false;
		// 修改部分单独保存，方便UpdateClass进行处理
		// Key：修改状态；Value：(学生id，学生新的成绩)
		std::map<ModifyStatus, std::pair<int, int>> ModifiedList = {};
		// 课程数据库
		// Key：学生id；Value：学生成绩
		std::map<int, int> StudentList = {};
	};

	// 课程id，名称和学分数据库
	class ClassInfo
	{
	public:
		// 初始化新的课程id，名称和学分数据库
		ClassInfo();
		// 通过文件初始化id，名称和学分数据库
		ClassInfo(std::ifstream& _file);
		// 链接学生数据库以实现写入记录功能
		void JoinStudentInfo(StudentInfo& _studentInfo);
		// 指定课程数据文件存储基地址
		// 第二个参数指定文件存储基地址与原地址不同时的行为
		// 如果为True，则移动所有数据；为False，重新指定地址并刷新StudentData
		void ChangeBaseUri(std::string _newUri, bool _moveData = true);
		// 获取课程成绩数据
		std::shared_ptr<ClassData> GetClassData(int _id);
		// 更新课程id，名称和学分数据
		// 如果没有课程信息，则新建课程信息
		// 如果课程信息已存在，则更新课程信息
		void UpdateClassData(ClassData& _data);
		// 保存学分数据库
		void SaveClassInfo(std::ofstream& _file);
	protected:
		// 课程数据库
		// Key：课程id，Value：课程数据
		std::map<int, ClassData> Data = {};
		// 绑定的学生数据库
		StudentInfo* StudentList = nullptr;
		// 课程数据文件存储基地址
		std::string BaseUri = "";
	};

	// 学生数据库
	class StudentInfo
	{
	public:
		// 新建学生数据库
		StudentInfo();
		// 通过学生文件读取学生数据库
		StudentInfo(std::istream& _file);
		// 获取学生学习课程列表（若不存在返回空列表）
		std::vector<int> GetClasses(int _id);
		// 更新课程数据
		void UpdateClassData(ClassData& _class);
		// 保存学生数据库
		void SaveStudentInfo(std::ostream& _file);
	protected:
		// 学生数据库
		// Key：学生id；Value：(平均学分绩，课程列表)
		std::map<int, std::pair<float, std::vector<std::shared_ptr<ClassData>>>> Data = {};
	};
}