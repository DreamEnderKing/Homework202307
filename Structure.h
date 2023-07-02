#pragma once

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include <map>
#include <string>
#include <stdexcept>
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

	// 学生初步统计信息
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

	// 修改单元
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

	// 成绩单单元
	struct ClassItem
	{
		ClassItem()
		{
			ID = 0, Name = "", ClassPoint = 0, Point = 0;
		}
		ClassItem(int _id, std::string _name, int _classPoint, int _point)
		{
			ID = _id, Name = _name, ClassPoint = _classPoint, Point = _point;
		}
		int ID;
		std::string Name;
		int ClassPoint;
		int Point;
	};

	class ClassData;
	class StudentInfo;
	class ClassInfo;

	// 课程成绩数据
	class ClassData
	{
	public:
		// 通过课程序号，课程名称，课程学分和课程文件初始化课程数据
		ClassData(const int _id, const std::string _name, const int _point);
		virtual ~ClassData();
		// 从流中读取数据
		void ReadFromStream(std::istream& _file);
		// 查询学生成绩（如果不存在返回-1）
		int GetScore(int _id);
		// 更新学生条目(如果存在则修改，如果不存在则新增)
		void UpdateStudentData(int _id, int _score);
		// 删除学生条目(如果不存在则无动作)
		void DeleteStudentData(int _id);
		// 查询课程数据变化并将变化写入修改部分
		void ScanUpdate(const ClassData& _newData);
		// 将所有数据新增入课程数据变化
		void InitialUpdate();
		// 清空课程数据变化
		void ClearModifiedList();
		// 统计单项学分绩在该区间的学生
		std::vector<std::pair<int, float>> CountAverageBetween(float min, float max);
		// 统计单项课程平均学分绩
		float GetAverageScore();
		// 保存课程成绩数据库(参数指定是否以文本方式写入)
		void SaveClassData(std::ostream& _file, bool _textMode = true) const;
		// 获取修改部分
		std::vector<ModifyLog> GetModifiedList() const;
		// 课程其他信息
		const int ID;	
		const std::string Name; 
		const int Point;
	protected:
		// 修改部分单独保存，方便UpdateClass进行处理
		// Key：修改状态；Value：(学生id，学生新的成绩)
		std::vector<ModifyLog> ModifiedList = {};
		// 课程数据库
		// Key：学生id；Value：学生成绩
		std::map<int, int> StudentList = {};
	};

	// 学生数据库
	class StudentInfo
	{
	public:
		// 新建学生数据库
		StudentInfo();
		// 通过学生文件读取学生数据库
		StudentInfo(std::istream& _file);
		virtual ~StudentInfo();
		// 获取学生学习课程列表（若不存在返回空列表）
		std::vector<std::pair<int, std::shared_ptr<ClassData>>> GetClasses(int _id);
		// 更新课程数据
		void UpdateClassData(const std::shared_ptr<ClassData>& _class);
		// 删除所有与该课程ID关联的信息
		void DeleteClassData(int _id);
		// 链接课程数据库
		void JoinClassInfo(const std::map<int, std::shared_ptr<ClassData>>& _classInfo);
		// 刷新平均成绩(防止Debug阶段导致的可能误差)
		void RefreshAverageScore();
		// 统计平均学分绩在该区间的学生
		std::vector<std::pair<int, float>> CountAverageBetween(float min, float max);
		// 保存学生数据库
		void SaveStudentInfo(std::ostream& _file, bool _textMode = true);
	protected:
		// 学生数据文件库
		// Key：学生id；Value：(学生简明信息，(课程id，课程本体)列表)
		// 预留出内存管理空间，在可能的大数据面前允许只加载若干个ClassData
		std::map<int, std::pair<StudentBriefData, std::vector<std::pair<int, std::shared_ptr<ClassData>>>>> Data = {};
	};

	// 课程id，名称和学分数据库
	class ClassInfo
	{
	public:
		// 通过文件初始化id，名称和学分数据库
		ClassInfo(std::string _uri, bool initial = false);
		// 链接学生数据库以实现写入记录功能
		void JoinStudentInfo(StudentInfo* _studentInfo);
		// 刷新学生数据库统计信息
		void RefreshStatistics();
		// 统计平均学分绩在该区间的学生
		std::vector<std::pair<int, float>> CountAverageBetween(float min, float max);
		// 获取课程成绩数据
		std::shared_ptr<ClassData> GetClassData(int _id);
		// 获取学生课程数据
		std::vector<ClassItem> GetStudentData(int _id);
		// 更新课程id，名称和学分数据
		// 如果没有课程信息，则新建课程信息
		// 如果课程信息已存在，则更新课程信息
		void UpdateClassData(ClassData& _data);
		// 保存学分数据库
		void SaveClassInfo(bool _textMode = true);
	protected:
		// 课程数据库
		// Key：课程id，Value：课程数据
		std::map<int, std::shared_ptr<ClassData>> Data = {};
		// 绑定的学生数据库
		std::shared_ptr<StudentInfo> StudentList = nullptr;
		// 课程数据文件存储基地址
		std::string BaseUri = "";
		// 学生成绩文件地址(相对)
		std::string StuUri = "Student.dat";
	};
}

#endif