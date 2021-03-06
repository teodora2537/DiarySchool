#pragma once
#include <list>
#include "Library.h"
#include "Student.h"
#include "Score.h"
#include "Subject.h"
using namespace std;

typedef enum {
    SORT_None = 0,
    SORT_AZ = -1,
    SORT_ZA = 1,
} SortOrder;

class CListMethods :
    public CDialogEx,
    public CListCtrl
{

public:
    CListMethods() : m_list() {}

private:
    CListCtrl m_list;
public:
    void SortListSub( const int sortClm, list<SUBJECT>& listFromStruct, SortOrder order);
    void SortListScore(const int sortClm, list<SCORE>& listFromStruct, SortOrder order);
    void SortListReference(const int sortClm, list<REFERENCE>& listFromStruct, SortOrder order, bool bIsNames);
    void SortListStudent(const int sortClm, list<STUDENT>& listFromStruct, SortOrder order);
};


/*
struct SubStruct {
    
    int nIdRoom;
    CString strSubject;
    CString strNameTeacher;
};
*/
/*
 typedef struct StudentStruct {
    int nIdStudent;
    CString strNameStudent;
    CString strBirthday;
};

typedef struct ReferenceStruct {
    int nIdStudent;
    CString strClm0;
    CString strClm1;
    CString strClm2;
    CString strClm3;
};

typedef struct ScoreStruct {
    int nIdScore;
    int nIdStudent;
    CString strNameStudent;
    CString strSubject;
    CString strScore;
    CString strDate;
};
*/