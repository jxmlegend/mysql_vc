#include "stdafx.h"
#include "student_data.h"

void ConvertUtf8ToGBK(CString &strUtf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, (char *)_bstr_t(strUtf8)/*T2A(strUtf8)*/, -1, NULL, 0);
	wchar_t * wszGBK = new wchar_t[len];
	memset(wszGBK, 0, len);
	MultiByteToWideChar(CP_UTF8, 0, (char *)_bstr_t(strUtf8), -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);

	strUtf8 = szGBK;
	delete[] szGBK;
	delete[] wszGBK;
}



//GBK转化为UTF8格式

void ConvertGBKToUtF8(CString &strGBK)
{
	int len = MultiByteToWideChar(CP_ACP, 0, (char *)_bstr_t(strGBK), -1, NULL, 0);
	wchar_t * wszUtf8 = new wchar_t[len];
	memset(wszUtf8, 0, len);
	MultiByteToWideChar(CP_ACP, 0, (char *)_bstr_t(strGBK), -1, wszUtf8, len);

	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);

//	WCHAR *wch = _T("季");

//	strGBK = szUtf8;
//	strGBK = wch;
	//char *ch = (char*)strGBK.GetBuffer(strGBK.GetLength() + 1);
	//strGBK.ReleaseBuffer();
	strGBK.Format(_T("%s"), szUtf8);

	delete[] szUtf8;
	delete[] wszUtf8;
}
// CString GBKToUTF8(CString & strGBK)
// {
// 	
// 	CString strOutUTF8 = "";
// 	
// 	WCHAR * str1;
// 	
// 	int n = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
// 	
// 	str1 = new WCHAR[n];
// 	
// 	MultiByteToWideChar(CP_ACP, 0, strGBK, -1, str1, n);
// 	
// 	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
// 	
// 	char * str2 = new char[n];
// 	
// 	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
// 	
// 	strOutUTF8 = str2;
// 	
// 	delete[]str1;
// 	
// 	str1 = NULL;
// 	
// 	delete[]str2;
// 	
// 	str2 = NULL;
// 	
// 	return strOutUTF8;
// 	
// }
// 

Student_DataManager::Student_DataManager()
{
	mysql_init(&DB_Conn);

	pDB_Connection = mysql_real_connect(&DB_Conn,
		"192.168.1.90", "root", "root", "students", 3306,
		(char*)NULL, 0);
	if (!pDB_Connection)
	{
		AfxMessageBox(L"连接数据库失败");
		return;
	}
	int iSQL_Stat=mysql_query(&DB_Conn, "set names gbk");
	LoadDataFromMySQL();
}
Student_DataManager::~Student_DataManager()
{
	for (map<CString, Student*>::iterator Iter_Pos = student_list_.begin(); Iter_Pos != student_list_.end(); ++Iter_Pos)
	{
		delete Iter_Pos->second;
	}
	mysql_close(pDB_Connection);
}
void Student_DataManager::LoadDataFromMySQL()
{
	for (map<CString, Student*>::iterator Iter_Pos = student_list_.begin(); Iter_Pos != student_list_.end(); ++Iter_Pos) 
	{
		delete Iter_Pos->second;
	}
	MYSQL_RES* pSQL_Result;
	MYSQL_ROW SQL_ROW;

	int iSQL_Stat;
	char strSQL[512];

	//@ load bullet
	strcpy(strSQL, "select * from students");

	iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	if (!iSQL_Stat) {
		pSQL_Result = mysql_store_result(pDB_Connection);
		int index = 0;
		while ((SQL_ROW = mysql_fetch_row(pSQL_Result)) != NULL) {
			Student* bullet = new Student(CString(SQL_ROW[0]), CString(SQL_ROW[1]), CString(SQL_ROW[2]), CString(SQL_ROW[3]));
			student_list_[CString(SQL_ROW[0])] = bullet;
		}
	}//
}
bool Student_DataManager::InsertData(Student* student)
{
	MYSQL_RES* pSQL_Result;

	int iSQL_Stat;
	char strSQL[512] = {0};
	if (student_list_.find(student->student_id)
		== student_list_.end())
	{		
		strcpy(strSQL, "INSERT INTO students(student_id, name,sex,birth) VALUES('");
		CString id = student->student_id;
		CString name = student->name_;
		CString sex = (student->sex_);
		CString birth = student->birth_;
		USES_CONVERSION;
 		char* id_str = T2A(id);
		char* name_str = T2A(name);
 		char* sex_str = T2A(sex);
 		char* birth_str = T2A(birth);
 		strcat(strSQL, id_str);
 		//strcat(strSQL, "',");
 		strcat(strSQL, "','");
 
 		strcat(strSQL, name_str);
 		strcat(strSQL, "','");
 
 		strcat(strSQL, sex_str);
 		strcat(strSQL, "','");
 
 		strcat(strSQL, birth_str);
 		strcat(strSQL, "')");
	}
	iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	return !iSQL_Stat;
}
bool Student_DataManager::UpdateData(Student* student)
{
	MYSQL_RES* pSQL_Result;

	int iSQL_Stat;
	char strSQL[512] = {0};
	if (student_list_.find(student->student_id)
		== student_list_.end())

	{
		strcpy(strSQL, "insert into students(student_id, name,sex,birth) values('");
		CString id = student->student_id;
		CString name = student->name_;
		CString sex = (student->sex_);
		CString birth = student->birth_;
		USES_CONVERSION;
		char* id_str = T2A(id);
		char* name_str = T2A(name);
		char* sex_str = T2A(sex);
		char* birth_str = T2A(birth);
		strcat(strSQL, id_str);
		//strcat(strSQL, "',");
		strcat(strSQL, "','");

		strcat(strSQL, name_str);
		strcat(strSQL, "','");

		strcat(strSQL, sex_str);
		strcat(strSQL, "','");

		strcat(strSQL, birth_str);
		strcat(strSQL, "')");
 		iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	}
	else
	{
		if (student->student_id.IsEmpty())
		{
			return false;
		}
		strcpy(strSQL, "update students set ");
		CString id = student->student_id;
		CString name = student->name_;
		CString sex = (student->sex_);
		CString birth = student->birth_;
		USES_CONVERSION;

 		char* id_str = T2A(id);
 		char* name_str = T2A(name);
 		char* sex_str = T2A(sex);
 		char* birth_str = T2A(birth);
		if (!name.IsEmpty())
		{
			strcat(strSQL, "name='");
			strcat(strSQL, name_str);
			strcat(strSQL, "'");
		
		}
		if (!sex.IsEmpty())
		{
			strcat(strSQL, ",");
			strcat(strSQL, "sex='");
			strcat(strSQL, sex_str);
			strcat(strSQL, "'");
			
		}
		if (!birth.IsEmpty())
        {
			strcat(strSQL, ",");
			strcat(strSQL, "birth='");
			strcat(strSQL, birth_str);
			strcat(strSQL, "'");
			
        }
		strcat(strSQL, " where student_id=");
		strcat(strSQL, id_str);
 
 		iSQL_Stat = mysql_query(pDB_Connection, strSQL);

	}
	return !iSQL_Stat;
}
bool Student_DataManager::SelectData(Student* student, vector<Student*>&stuvec)
{
	MYSQL_RES* pSQL_Result;
	MYSQL_ROW SQL_ROW;
	int iSQL_Stat;
	char strSQL[512] = { 0 };
	//if (student_list_.find(student->student_id)
	//	== student_list_.end())

	//{
	//	
	//	
	//}
	//else
	//{
		strcpy(strSQL, "SELECT * FROM  students  WHERE ");
		CString id = student->student_id;
		CString name = student->name_;
		CString sex = (student->sex_);
		CString birth = student->birth_;
		USES_CONVERSION;
		char* id_str = T2A(id);
		char* name_str = T2A(name);
		char* sex_str = T2A(sex);
		char* birth_str = T2A(birth);

		if (!id.IsEmpty())
		{
			strcat(strSQL, "student_id=");
			strcat(strSQL, id_str);
		}
		if (!name.IsEmpty())
		{
			if (!id.IsEmpty()){
				strcat(strSQL, "AND name='");
			}
			else
			{
				strcat(strSQL, "name='");
			}

			strcat(strSQL, name_str);
			strcat(strSQL, "' ");
		}
		if (!sex.IsEmpty())
		{
			if ((!id.IsEmpty()) || (!name.IsEmpty()))
			{
				strcat(strSQL, "AND sex='");
			}
			else
			{
				strcat(strSQL, " sex='");
			}
			strcat(strSQL, sex_str);
			strcat(strSQL, "'");
		}
		if (!birth.IsEmpty())
		{
			if ((!id.IsEmpty()) || (!name.IsEmpty()) || (!sex.IsEmpty()))
			{
				strcat(strSQL, "AND birth='");
			}
			else
			{
				strcat(strSQL, " birth_str='");
			}
			strcat(strSQL, sex_str);
			strcat(strSQL, "'");
		}
	//}
	iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	if (!iSQL_Stat)
	{
		pSQL_Result = mysql_store_result(pDB_Connection);
		int index = 0;
		while ((SQL_ROW = mysql_fetch_row(pSQL_Result)) != NULL)
		{
			/*student->student_id = CString(SQL_ROW[0]);
			student->name_ = CString(SQL_ROW[1]);
			student->sex_ = CString(SQL_ROW[2]);
			student->birth_ = CString(SQL_ROW[3]);*/
			Student* bullet = new Student(CString(SQL_ROW[0]), CString(SQL_ROW[1]), CString(SQL_ROW[2]), CString(SQL_ROW[3]));
			stuvec.push_back(bullet);

		}

	}

	return !iSQL_Stat;
}
bool Student_DataManager::DeleteData(Student* student)
{
	MYSQL_RES* pSQL_Result;

	int iSQL_Stat;
	char strSQL[512];

	strcpy(strSQL, "delete from students where student_id = ");
	CString id = student->student_id;
	USES_CONVERSION;
	char* id_str = T2A(id);
	strcat(strSQL, id_str);
	iSQL_Stat = mysql_query(pDB_Connection, strSQL);
	CString delrow("");
	delrow.Format(_T("删除条数=%d条"), mysql_affected_rows(pDB_Connection));
	AfxMessageBox(delrow);

	return !iSQL_Stat;
}

