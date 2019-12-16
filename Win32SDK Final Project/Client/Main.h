#ifndef __AMC_MAIN_H__
#define __AMC_MAIN_H__


#include <windows.h>
#include <stdio.h>
#include <commctrl.h>  //for ListView
#include "AstroMediComp_Project.h"
#include "Menu.h"
#include "AMC_Functions.h"
#include "SplashScreen.h"


/*************** MACRO DEFINE ***********************************/
#define ID_EDIT_FIRSTNAME             0
#define ID_EDIT_LASTNAME              1
#define ID_EDIT_ADDRESS               2
#define ID_EDIT_EMAIL                 3
#define ID_EDIT_MOBILE                4

#define ID_RADIOBUTTON_MALE           5
#define ID_RADIOBUTTON_FEMALE         6

#define ID_LIST_DAYOFWEEK_DOB         7
#define ID_STATIC_DAYOFWEEK_DOB       8
#define ID_BUTTON_DAYOFWEEK_DOB       9

#define ID_LIST_MONTH_DOB            10
#define ID_STATIC_MONTH_DOB          11
#define ID_BUTTON_MONTH_DOB          12

#define ID_LIST_YEAR_DOB             13
#define ID_STATIC_YEAR_DOB           14
#define ID_BUTTON_YEAR_DOB           15

#define ID_LIST_DAYOFWEEK_JOINING    16
#define ID_STATIC_DAYOFWEEK_JOINING  17
#define ID_BUTTON_DAYOFWEEK_JOINING  18

#define ID_LIST_MONTH_JOINING        19
#define ID_STATIC_MONTH_JOINING      20
#define ID_BUTTON_MONTH_JOINING      21

#define ID_LIST_YEAR_JOINING         22
#define ID_STATIC_YEAR_JOINING       23
#define ID_BUTTON_YEAR_JOINING       24

#define ID_LIST_DEPARTMENT           25
#define ID_STATIC_DEPARTMENT         26
#define ID_BUTTON_DEPARTMENT         27

#define ID_EDIT_EMPLOYEE_ID          28

#define ID_BUTTON_OK                 29
#define ID_BUTTON_RESET              30

#define ID_READ_BUTTON               31

#define ID_SEARCH_EDIT               32

#define SORT_ASCENDING               TRUE
#define SORT_DESCENDING              FALSE

#define MAXREAD 8192


/*************** ENUM DEFINE ***********************************/
enum MONTH {
							NONE = 0,
							JANUARY    ,  FEBRUARY,     MARCH      ,  APRIL   ,      MAY        ,  JUNE    ,
							JULY       ,  AUGUST  ,			SEPTEMBER  ,  OCTOMBER,     NOVEMBER    ,  DECEMBER
						};

/*************** DECLARATION OF CALLBACK'S ***********************************/
LRESULT CALLBACK WndProc             (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ListProc            (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DataEntryWndProc    (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ShowRecordWndProc   (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SearchRecordWndProc (HWND, UINT, WPARAM, LPARAM);
int     CALLBACK ListViewCompareFunc (LPARAM, LPARAM, LPARAM);

/*************** Function Declaration *************************/
void AMC_ReleaseCOM();

/*************** GLOBAL VARIABLE ***********************************************/
extern IReadRecordFile *pIReadRecord;
extern IWriteRecordFile *pIWriteRecord;

extern BOOL sortFlag;

#endif
