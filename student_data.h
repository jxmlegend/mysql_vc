#ifndef STUDENT_DATA_H
#define STUDENT_DATA_H
#include <atlstr.h>
#include <map>
#include <vector>
#include "mysql.h"

using namespace std;
using std::vector;
class Student
{
public:
	Student(){};
	Student(CString stu_id, CString nname, CString sex, CString birth){
		student_id = stu_id;
		name_ = nname;
		sex_ = sex;
		birth_ = birth;
	}
	~Student(){};
public:
	CString student_id;
	CString name_;
	CString sex_;
	CString birth_;
private:

};
class Student_DataManager
{
public:
	Student_DataManager();
	~Student_DataManager();

public:
	void LoadDataFromMySQL();
	bool InsertData(Student* student);
	bool UpdateData(Student* student);
	bool DeleteData(Student* student);//删除数据
	bool SelectData(Student* student, vector<Student*>&stuvec);//查询数据

public:
	map<CString, Student*> student_list_;
private:
	MYSQL* pDB_Connection;
	MYSQL DB_Conn;
};

#endif