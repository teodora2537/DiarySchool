#include "pch.h"
#include "AddStudent.h"
#include "Library.h"
#include "Student.h"


void CAddStudent::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	
	UpdateData(TRUE);
	Library lib;
	string row = "";

	Student student(_ttoi(classNum), lib.ConvertToStirng(fn, row), lib.ConvertToStirng(ln, row), lib.ConvertToStirng(birthday, row));
	lib.AddInStudent();
}
