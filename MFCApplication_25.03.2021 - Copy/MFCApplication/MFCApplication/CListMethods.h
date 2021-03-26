#pragma once
#include <afxdialogex.h>
#include "CTabStudent.h"
#include "CTabSubject.h"
#include "CTabScore.h"
#include "CTabReference.h"
#include <iostream>
using namespace std;

typedef enum {
    SORT_None = 0,
    SORT_AZ = -1,
    SORT_ZA = 1,
} SortOrder;

typedef struct SubStruct {
    CString strIdRoom;
    CString strSubject;
    CString strNameTeacher;
};

typedef struct StudentStruct {
    int nIdStudent;
    CString strNameStudent;
    CString strBirthday;
};

typedef struct ScoreStruct {
    int nIdScore;
    CString strIdStudent;
    CString strNameStudent;
    CString strSubject;
    CString strScore;
    CString strDate;
};

typedef struct ReferenceStruct {
    
    int nIdStudent;
    CString strNameStudent;
    CString strSubject;
    CString strAvgScore;
};

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