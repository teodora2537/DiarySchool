#pragma once
#include <afxdialogex.h>
#include "CTabStudent.h"
#include "CTabSubject.h"
#include "CTabScore.h"
#include <iostream>
using namespace std;

typedef enum {
    SORT_None = 0,
    SORT_AZ = -1,
    SORT_ZA = 1,
} SortOrder;

typedef struct SubStruct {
    CString idRoom;
    CString subject;
    CString nameTeacher;
} ListData;

typedef struct StudentStruct {     // data layout for each row
    int idStudent;
    CString nameStudent;
    CString birthday;
} SampleListData;

typedef struct ScoreStruct {     // data layout for each row
    int idScore;
    CString idStudent;
    CString nameStudent;
    CString subject;
    CString score;
    CString date;
} SampleListData_;


class CListMethods :
    public CDialogEx,
    public CListCtrl
{
public:
    void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);

public:
    CListMethods() : m_list() {}

private:
    CListCtrl m_list;
public:
  
    void SortListSub(int sortClm, list<SubStruct>& listFromStruct, SortOrder order);
    void SortListScore(int sortClm, list<ScoreStruct>& listFromStruct, SortOrder order);
    void SortListStudent(int sortClm, list<StudentStruct>& listFromStruct, SortOrder order);
};