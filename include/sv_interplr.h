//
// Created by zav3330 on 23.04.2025.
//

#ifndef __SV_INTERPLR_H
#define __SV_INTERPLR_H

#include <stdio.h>
#pragma warning (disable : 4710)
#pragma warning (disable : 4100)
#include <list>
#pragma warning (default : 4100)

const double DEFINED_ZERO_ = 1.0e-08;

//#define AMS_OFFLINEUSESQLSDB_
#define AMS_INTERPLRDBWIN32_

#if !defined(SV_INTERPLR_LIBAPI_)
#define SV_INTERPLR_LIBAPI_ __declspec(dllimport)
#else
class tInterplrTable;
extern int   MakeFullPath_ (const char* lpszDir, const char* lpszName, char** lplpszPath, unsigned short* lpwPathLength);
extern int   FindStringID_ (FILE* fpt, const char* lpszStringID, char* lpchNext);
extern int   FindStringID_ (FILE* fpt, const char* lpszStringID, const char* lpchSepar, short nNumSepar, char* lpchLast);
extern int   FindNextChar_ (FILE* fpt, char chFind, char chLast);
extern int   ScanFuncArgsTbi_ (FILE* fpt, char** lplpszArgID, short* lpnStrLen, short nNumArg, char chLast);
extern void  ScanFuncArgsTbl_ (FILE* fpt, char*** lplplpszArgID, short* lpnNumArg);
extern short CreateArray_ (FILE* fpt, double** lplpdArray, char chLast);
extern int   IgnoreChars_ (FILE* fpt, const char* lpchArray, short nCount, char* lpchLast);
extern void  ScanFuncVectTbl_ (FILE* fpt, double** lplpdFuncVectVal, short* lpnFuncVectIndex, long lNumFuncVect, const char* const* lplpszArgID, const double* const* lplpdArgVectVal, const long* lplArgVectSize, short nArgIndex, double definedZero);
extern void  ScanCurrArgTbl_ (FILE* fpt, const char* lpszArgID, char chOpenBracket, long* lplIndex, char chClosBracket, char chEqual, double* lpdValue);
extern int   FindChar_ (char ch, const char* lpchArray, short nCount);
extern short ScanStringVal_ (FILE* fpt, const char* lpchSepar, short nNumSepar, const char* lpchIgnore, short nNumIgnore, char** lplpszRetVal, char* lpchLast);
extern int   ScanLongVal_ (FILE* fpt, const char* lpchSepar, short nNumSepar, const char* lpchIgnore, short nNumIgnore, long* lplRetVal, char* lpchLast);
extern int   ScanDoubleVal_ (FILE* fpt, const char* lpchSepar, short nNumSepar, const char* lpchIgnore, short nNumIgnore, double* lpdRetVal, char* lpchLast);
extern int   ScanDoubleVectTbl_ (FILE* fpt, double* lpdVect, short nCount);
extern int   ReadString_ (FILE* fpt, char** lplpszOutput, short* lpnStrLen);
extern void  StrTrimRight_ (char* lpsz);
extern void  StrTrimLeft_ (char* lpsz);
extern void  SortingTbl (short nNumArg, const long* lplArgVectSize,	double*** lplplpdFuncVect,	long lNumFuncVect);
extern int   ConvertIndexTbl_ (long lArgIndex, const long* plArgVectSize, long lSumIndex, double** ppdNewFuncVect, double** ppdFuncVect,	long lNumFuncVect, const long* lplSizeCf, long* lplOldIndex);
extern void  ReadTbl_ (FILE* fpt, const char* lpszFuncID, char*** lplplpszArgID, short* lpnNumArg,
				 double*** lplplpdArgVectVal, long** lplplArgVectSize,
				 double*** lplplpdFuncVectVal, long* lplNumFuncVect, double definedZero);
extern void  CreateTable_(FILE* fpt, short nFirstArgVectSize, const char* const* lplpszNextArgID, short nNumNextArg, double definedZero, std::list<tInterplrTable*>** lplpHeadListTable);
#if defined (AMS_INTERPLRDBWIN32_) || defined (AMS_OFFLINEUSESQLSDB_)
extern void  CreateTable_(DBPROCESS* dbproc, short nNumInformColumn, short nNumNextArg, short nFuncVectSize, double definedZero, std::list<tInterplrTable*>** lplpHeadListTable);
#endif
extern void  CreateTableTbl_(short nArgIndex, const long* plArgVectSize, const double* const* ppdArgVectVal, short nNumArg, const double* const* ppdFuncVect, long lNumFuncVect, tInterplrTable** ppTable, long* plRowIndex);
#endif


extern "C" SV_INTERPLR_LIBAPI_ double  Interplr_ (double argValue, const double* pdArgVect, const double* pfFuncVect, short nVectSize);
extern "C" SV_INTERPLR_LIBAPI_ double* ReadFloatVectFromTxt_ (const char* lpszVectID, const char* lpszFileName, const char* lpszDirName, double* pdVect, short* pnVectSize);
extern "C" SV_INTERPLR_LIBAPI_ void    ReleaseFloatVect_ (double* pdVect);
inline int ReadFloatParamFromTxt_ (const char* lpszVectID, const char* lpszFileName, const char* lpszDirName, double* pdParam)
{
	short nVectSize = 1;
	return (ReadFloatVectFromTxt_ (lpszVectID, lpszFileName, lpszDirName, pdParam, &nVectSize) != NULL) ? 1 : 0;
}

#if defined (AMS_OFFLINEUSESQLSDB_)
extern "C" SV_INTERPLR_LIBAPI_ DBPROCESS* SQLSOpenDB_ (const char* lpszServerName, const char* lpszUserName, const char* lpszPassword, const char* lpszAppName,	DBERRHANDLE_PROC* lplpfnErrHandler, DBMSGHANDLE_PROC* lplpfnMsgHandler);
extern "C" SV_INTERPLR_LIBAPI_ void       SQLSCloseDB_ (DBPROCESS* dbproc, DBERRHANDLE_PROC* lplpfnErrHandler, DBMSGHANDLE_PROC* lplpfnMsgHandler);
extern "C" SV_INTERPLR_LIBAPI_ int        SQLSErrHandler_ (PDBPROCESS dbproc, INT severity, INT dberr, INT oserr, LPCSTR dberrstr, LPCSTR oserrstr);
extern "C" SV_INTERPLR_LIBAPI_ int        SQLSMsgHandler_ (PDBPROCESS dbproc, DBINT msgno, INT msgstate, INT severity, LPCSTR msgtext, LPCSTR server, LPCSTR procedure, DBUSMALLINT line);
#endif


class tInterplrTable {
public:
	virtual ~tInterplrTable ();
	virtual double          RecursiveInterplr (const double* rgFirstArgVect, double firstArgValue, const double* rgNextArgValue) const = 0;
	virtual tInterplrTable* Clone() const = 0;
	virtual double          RecursiveGetFuncValue (unsigned short wFirstArgIndex, const unsigned short* lpwNextArgIndex) const = 0;
	virtual unsigned short  RecursiveGetVectSize (unsigned short wArgIndex) const;
	virtual double          RecursiveGetArgValue (unsigned short wArrayIndex, unsigned short wArgIndex) const;
#if defined (AMS_INTERPLRDEBUG_) && defined (_DEBUG)
	virtual void Print (FILE* fpt) const = 0;
#endif
	unsigned short GetVectSize () const;
	double         GetArgValue () const;
	tInterplrTable (double argValue, unsigned short wVectSize);
protected:
	tInterplrTable (const tInterplrTable& table);
protected:
	double            m_argValue;
	unsigned short    m_wVectSize;
	unsigned short    m_wCurrIndex;
};

inline unsigned short tInterplrTable::GetVectSize () const
{
	return m_wVectSize;
}

inline double tInterplrTable::GetArgValue () const
{
	return m_argValue;
}

class tInterplrTableParent : public tInterplrTable
{
public:
	virtual ~tInterplrTableParent ();
	virtual double RecursiveInterplr (const double* rgFirstArgVect, double firstArgValue, const double* rgNextArgValue) const;
	virtual tInterplrTable* Clone() const;
	virtual double RecursiveGetFuncValue (unsigned short wFirstArgIndex, const unsigned short* lpwNextArgIndex) const;
	virtual unsigned short RecursiveGetVectSize (unsigned short wArgIndex) const;
	virtual double RecursiveGetArgValue (unsigned short wArrayIndex, unsigned short wArgIndex) const;
#if defined (AMS_INTERPLRDEBUG_) && defined (_DEBUG)
	virtual void Print (FILE* fpt) const;
#endif
	tInterplrTableParent (double argValue, const tInterplrTable* const* ppTable, unsigned short wVectSize);
	tInterplrTableParent (double argValue, const std::list<tInterplrTable*>* lpListTable);
	void Destroy();
protected:
	tInterplrTableParent (const tInterplrTableParent& table);
protected:
	tInterplrTable** m_rglpTable;
};

class tInterplrTableEmbedded : public tInterplrTable
{
public:
	virtual ~tInterplrTableEmbedded ();
	virtual double RecursiveInterplr (const double* rgFirstArgVect, double firstArgValue, const double* rgNextArgValue) const;
	virtual tInterplrTable* Clone() const;
	virtual double RecursiveGetFuncValue (unsigned short wFirstArgIndex, const unsigned short* lpwNextArgIndex) const;
#if defined (AMS_INTERPLRDEBUG_) && defined (_DEBUG)
	virtual void Print (FILE* fpt) const;
#endif
	tInterplrTableEmbedded (double argValue, const double* rgFuncVect, unsigned short wVectSize);
	void Destroy();
protected:
	tInterplrTableEmbedded (const tInterplrTableEmbedded& table);
protected:
	double* m_rgFuncVect;
};


// ***********************************************
//  Базовый класс для реализации интерполяционных
//  зависимостей функций нескольких переменных
// ***********************************************

class SV_INTERPLR_LIBAPI_ tInterplrFunc {
public:
	tInterplrFunc (const char* lpszFuncID, const char* lpszFileName, const char* lpszDirName, short nNumArg, double definedZero, double defRetValue);
#if defined (AMS_OFFLINEUSESQLSDB_)
	tInterplrFunc (const char* lpszFuncID, short nNumArg, DBPROCESS* dbproc, const char* lpszDBName, double definedZero, double defRetValue);
#endif
#ifdef AMS_INTERPLRDBWIN32_
	tInterplrFunc (const char* lpszFuncName, short nNumArg, double definedZero, double defRetValue);
#endif
	~tInterplrFunc ();
#if defined (AMS_INTERPLRDEBUG_) && defined (_DEBUG)
	void  Print (FILE* fpt);
#endif
	double         Interplr (double firstArgValue, const double* lpNextArgValue) const;
	int            IsLoaded() const;
	double         GetFuncValue (unsigned short wFirstArgIndex, const unsigned short* lpwNextArgIndex) const;
	unsigned short GetVectSize (unsigned short wArgIndex) const;
	double         GetArgValue (unsigned short wArrayIndex, unsigned short wArgIndex) const;
protected:
	void CreateFromTbi (FILE* fpt, const char* lpszFuncID, short nNumArg, double definedZero);
	void CreateFromTbl (FILE* fpt, const char* lpszFuncID, short nNumArg, double definedZero);
protected:
	double*          m_rgFirstArgVect;
	tInterplrTable** m_rglpTable;
	double           m_defRetValue;
	unsigned short   m_wTableVectSize;
	short            m_nNumArg;
	unsigned short   m_wCurrIndex;
};

inline int tInterplrFunc::IsLoaded () const
{
	return (m_rglpTable != NULL && m_rgFirstArgVect != NULL) ? 1 : 0;
}

inline double tInterplrFunc::GetFuncValue (unsigned short wFirstArgIndex, const unsigned short* lpwNextArgIndex) const
{
	return m_rglpTable [*lpwNextArgIndex]->RecursiveGetFuncValue (wFirstArgIndex, lpwNextArgIndex + 1);
}

// **************************************************************************
//  Класс, реализующий интерполяционную зависимость функции одной переменной
// **************************************************************************
class SV_INTERPLR_LIBAPI_ tInterplrFuncOneArg {
public:
	tInterplrFuncOneArg (const char* lpszFuncID, const char* szFileName, const char* lpszDirName, double definedZero, double defRetValue);
#if defined (AMS_OFFLINEUSESQLSDB_)
	tInterplrFuncOneArg (const char* lpszFuncID, DBPROCESS* dbproc, const char* lpszDBName, double definedZero, double defRetValue);
#endif
#ifdef AMS_INTERPLRDBWIN32_
	tInterplrFuncOneArg (const char* lpszFuncName, double definedZero, double defRetValue);
#endif
	~tInterplrFuncOneArg();
#if defined (AMS_INTERPLRDEBUG_) && defined (_DEBUG)
	void Print (FILE* fpt) const;
#endif
	double Interplr (double dX) const;
	int    IsLoaded() const;
	unsigned short GetVectSize () const;
	double GetArgValue (unsigned short wIndex) const;
	double GetFuncValue (unsigned short wIndex) const;
protected:
	void CreateFromTbi (FILE* fpt, const char* szFuncID, double definedZero);
	void CreateFromTbl (FILE* fpt, const char* szFuncID, double definedZero);
protected:
	double*        m_rgArgVect;
	double*        m_rgFuncVect;
	double         m_defRetValue;
	unsigned short m_wVectSize;
	unsigned short m_wCurrIndex;
};

inline int tInterplrFuncOneArg::IsLoaded() const
{
	return  (m_rgArgVect != NULL && m_rgFuncVect != NULL) ? 1 : 0;
}

inline double tInterplrFuncOneArg::Interplr (double x) const
{
	return  (m_rgArgVect != NULL && m_rgFuncVect != NULL) ? Interplr_ (x, m_rgArgVect, m_rgFuncVect, m_wVectSize) : m_defRetValue;
}

inline unsigned short tInterplrFuncOneArg::GetVectSize () const
{
	return m_wVectSize;
}

inline double tInterplrFuncOneArg::GetArgValue (unsigned short wIndex) const
{
	return m_rgArgVect [wIndex];
}

inline double tInterplrFuncOneArg::GetFuncValue (unsigned short wIndex) const
{
	return m_rgFuncVect [wIndex];
}

// **************************************************************************
//  Класс, реализующий интерполяционную зависимость функции двух переменных
// **************************************************************************
class SV_INTERPLR_LIBAPI_ tInterplrFuncTwoArg : public tInterplrFunc {
public:
	tInterplrFuncTwoArg (const char* lpszFuncID, const char* szFileName, const char* lpszDirName, double definedZero, double defRetValue);
#if defined(AMS_OFFLINEUSESQLSDB_)
	tInterplrFuncTwoArg (const char* lpszFuncID, DBPROCESS* dbproc, const char* lpszDBName, double definedZero, double defRetValue);
#endif
#ifdef AMS_INTERPLRDBWIN32_
	tInterplrFuncTwoArg (const char* lpszFuncName, double definedZero, double defRetValue);
#endif
	double         Interplr (double x, double y) const;
	unsigned short GetFirstArgVectSize () const;
	unsigned short GetSecondArgVectSize () const;
	double         GetFirstArgValue (unsigned short wArrayIndex) const;
	double         GetSecondArgValue (unsigned short wArrayIndex) const;
	double         GetFuncValue (unsigned short wArgIndexX, unsigned short wArgIndexY) const;
};

inline double tInterplrFuncTwoArg::Interplr (double x, double y) const
{
	return tInterplrFunc::Interplr (x, &y);
}

inline unsigned short tInterplrFuncTwoArg::GetFirstArgVectSize () const
{
	return tInterplrFunc::GetVectSize (0);
}

inline unsigned short tInterplrFuncTwoArg::GetSecondArgVectSize () const
{
	return tInterplrFunc::GetVectSize (1);
}

inline double tInterplrFuncTwoArg::GetFirstArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 0);
}

inline double tInterplrFuncTwoArg::GetSecondArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 1);
}

// **************************************************************************
//  Класс, реализующий интерполяционную зависимость функции трех переменных
// **************************************************************************
class SV_INTERPLR_LIBAPI_ tInterplrFuncThreeArg : public tInterplrFunc {
public:
	tInterplrFuncThreeArg (const char* lpszFuncID, const char* szFileName, const char* lpszDirName, double definedZero, double defRetValue);
#if defined(AMS_OFFLINEUSESQLSDB_)
	tInterplrFuncThreeArg (const char* lpszFuncID, DBPROCESS* dbproc, const char* lpszDBName, double definedZero, double defRetValue);
#endif
#ifdef AMS_INTERPLRDBWIN32_
	tInterplrFuncThreeArg (const char* lpszFuncName, double definedZero, double defRetValue);
#endif
	double         Interplr (double x, double y, double z) const;
	unsigned short GetFirstArgVectSize () const;
	unsigned short GetSecondArgVectSize () const;
	unsigned short GetThirdArgVectSize () const;
	double         GetFirstArgValue (unsigned short wArrayIndex) const;
	double         GetSecondArgValue (unsigned short wArrayIndex) const;
	double         GetThirdArgValue (unsigned short wArrayIndex) const;
	double         GetFuncValue (unsigned short wArgIndexX, unsigned short wArgIndexY, unsigned short wArgIndexZ) const;
};

inline double tInterplrFuncThreeArg::Interplr (double x, double y, double z) const
{
	double rgNextArgValue [2];
	rgNextArgValue[0] = y;
	rgNextArgValue[1] = z;
	return tInterplrFunc::Interplr (x, &rgNextArgValue [0]);
}

inline unsigned short tInterplrFuncThreeArg::GetFirstArgVectSize () const
{
	return tInterplrFunc::GetVectSize (0);
}

inline unsigned short tInterplrFuncThreeArg::GetSecondArgVectSize () const
{
	return tInterplrFunc::GetVectSize (1);
}

inline unsigned short tInterplrFuncThreeArg::GetThirdArgVectSize () const
{
	return tInterplrFunc::GetVectSize (2);
}

inline double tInterplrFuncThreeArg::GetFirstArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 0);
}

inline double tInterplrFuncThreeArg::GetSecondArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 1);
}

inline double tInterplrFuncThreeArg::GetThirdArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 2);
}

// **************************************************************************
//  Класс, реализующий интерполяционную зависимость функции четырех переменных
// **************************************************************************
class SV_INTERPLR_LIBAPI_ tInterplrFuncFourArg : public tInterplrFunc {
public:
	tInterplrFuncFourArg (const char* lpszFuncID, const char* szFileName, const char* lpszDirName, double definedZero, double defRetValue);
#if defined(AMS_OFFLINEUSESQLSDB_)
	tInterplrFuncFourArg (const char* lpszFuncID, DBPROCESS* dbproc, const char* lpszDBName, double definedZero, double defRetValue);
#endif
#ifdef AMS_INTERPLRDBWIN32_
	tInterplrFuncFourArg (const char* lpszFuncName, double definedZero, double defRetValue);
#endif
	double         Interplr (double x, double y, double z, double a) const;
	unsigned short GetFirstArgVectSize () const;
	unsigned short GetSecondArgVectSize () const;
	unsigned short GetThirdArgVectSize () const;
	unsigned short GetFourthArgVectSize () const;
	double         GetFirstArgValue (unsigned short wArrayIndex) const;
	double         GetSecondArgValue (unsigned short wArrayIndex) const;
	double         GetThirdArgValue (unsigned short wArrayIndex) const;
	double         GetFourthArgValue (unsigned short wArrayIndex) const;
	double         GetFuncValue (unsigned short wArgIndexX, unsigned short wArgIndexY, unsigned short wArgIndexZ, unsigned short wArgIndexA) const;
};

inline double tInterplrFuncFourArg::Interplr (double x, double y, double z, double a) const
{
	double rgNextArgValue [3];
	rgNextArgValue[0] = y;
	rgNextArgValue[1] = z;
	rgNextArgValue[2] = a;
	return tInterplrFunc::Interplr (x, &rgNextArgValue [0]);
}

inline unsigned short tInterplrFuncFourArg::GetFirstArgVectSize () const
{
	return tInterplrFunc::GetVectSize (0);
}

inline unsigned short tInterplrFuncFourArg::GetSecondArgVectSize () const
{
	return tInterplrFunc::GetVectSize (1);
}

inline unsigned short tInterplrFuncFourArg::GetThirdArgVectSize () const
{
	return tInterplrFunc::GetVectSize (2);
}

inline unsigned short tInterplrFuncFourArg::GetFourthArgVectSize () const
{
	return tInterplrFunc::GetVectSize (3);
}

inline double tInterplrFuncFourArg::GetFirstArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 0);
}

inline double tInterplrFuncFourArg::GetSecondArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 1);
}

inline double tInterplrFuncFourArg::GetThirdArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 2);
}

inline double tInterplrFuncFourArg::GetFourthArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 3);
}


// *************************************************************************
//  Класс, реализующий интерполяционную зависимость функции пяти переменных
// *************************************************************************
class SV_INTERPLR_LIBAPI_ tInterplrFuncFiveArg : public tInterplrFunc {
public:
	tInterplrFuncFiveArg (const char* lpszFuncID, const char* szFileName, const char* lpszDirName, double definedZero, double defRetValue);
#if defined (AMS_OFFLINEUSESQLSDB_)
	tInterplrFuncFiveArg (const char* lpszFuncID, DBPROCESS* dbproc, const char* lpszDBName, double definedZero, double defRetValue);
#endif
#ifdef AMS_INTERPLRDBWIN32_
	tInterplrFuncFiveArg (const char* lpszFuncName, double definedZero, double defRetValue);
#endif
	double         Interplr (double x, double y, double z, double a, double b) const;
	unsigned short GetFirstArgVectSize () const;
	unsigned short GetSecondArgVectSize () const;
	unsigned short GetThirdArgVectSize () const;
	unsigned short GetFourthArgVectSize () const;
	unsigned short GetFifthArgVectSize () const;
	double         GetFirstArgValue (unsigned short wArrayIndex) const;
	double         GetSecondArgValue (unsigned short wArrayIndex) const;
	double         GetThirdArgValue (unsigned short wArrayIndex) const;
	double         GetFourthArgValue (unsigned short wArrayIndex) const;
	double         GetFifthArgValue (unsigned short wArrayIndex) const;
	double         GetFuncValue (unsigned short wArgIndexX, unsigned short wArgIndexY, unsigned short wArgIndexZ, unsigned short wArgIndexA, unsigned short wArgIndexB) const;
};

inline double tInterplrFuncFiveArg::Interplr (double x, double y, double z, double a, double b) const
{
	double rgNextArgValue [4];
	rgNextArgValue [0] = y;
	rgNextArgValue [1] = z;
	rgNextArgValue [2] = a;
	rgNextArgValue [3] = b;
	return tInterplrFunc::Interplr (x, &rgNextArgValue [0]);
}

inline unsigned short tInterplrFuncFiveArg::GetFirstArgVectSize () const
{
	return tInterplrFunc::GetVectSize (0);
}

inline unsigned short tInterplrFuncFiveArg::GetSecondArgVectSize () const
{
	return tInterplrFunc::GetVectSize (1);
}

inline unsigned short tInterplrFuncFiveArg::GetThirdArgVectSize () const
{
	return tInterplrFunc::GetVectSize (2);
}

inline unsigned short tInterplrFuncFiveArg::GetFourthArgVectSize () const
{
	return tInterplrFunc::GetVectSize (3);
}

inline unsigned short tInterplrFuncFiveArg::GetFifthArgVectSize () const
{
	return tInterplrFunc::GetVectSize (4);
}

inline double tInterplrFuncFiveArg::GetFirstArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 0);
}

inline double tInterplrFuncFiveArg::GetSecondArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 1);
}

inline double tInterplrFuncFiveArg::GetThirdArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 2);
}

inline double tInterplrFuncFiveArg::GetFourthArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 3);
}

inline double tInterplrFuncFiveArg::GetFifthArgValue (unsigned short wArrayIndex) const
{
	return tInterplrFunc::GetArgValue (wArrayIndex, 4);
}

/*
#define IDS_ERR_OPEN_ERROR_FILE_1       0   //Ошибка открытия файла\n<%s>
#define IDS_MSG_INT_DEPEND_LOADING_EXEC_CORRECTLY_1  1 // Загрузка интерполяционной зависимости\n<%s>  выполнена корректно
#define IDS_ERR_INT_DEPEND_NOT_FOUND_1  2   //Интерполяционная зависимость\n<%s>  не найдена
#define IDS_ERR_INT_DEPEND_READ_ARG_1   3   //Ошибка чтения аргументов интерполяционной зависимости\n<%s>
#define IDS_ERR_INT_DEPEND_INCORRECT_DEFINITION_FORMAT_1 4 // Некорректный формат описания интерполяционной зависимости\n<%s>
#define IDS_ERR_INT_DEPEND_REDEFINITION_1 5 // Повторное определение интерполяционной зависимости\n<%s>
#define IDS_ERR_INT_DEPEND_NOT_MEMORY_1   6 // Нехватка памяти при создании объекта интерполяционная зависимость\n<%s>
#define IDS_MSG_FLOAT_VECT_LOADING_EXEC_CORRECTLY_1  7 // Загрузка вектора вещественных чисел\n<%s>  выполнена корректно
#define IDS_ERR_FLOAT_VECT_NOT_FOUND_1    8 // Вектор вещественных чисел  <%s>  не найден
#define IDS_ERR_FLOAT_VECT_INCORRECT_DEFINITION_FORMAT_1 9 // Некорректный формат описания вектора вещественных чисел\n<%s>
#define IDS_ERR_FLOAT_VECT_REDEFINITION_1 10 // Повторное определение вектора вещественных чисел\n<%s>
*/



#define IDS_USER_INT_MSG  58
#define IDS_MSG_INT_DEPEND_LOADING_EXEC_CORRECTLY_1                 (IDS_USER_INT_MSG + 0)
                            // "Загрузка интерполяционной зависимости\n<%s>  выполнена корректно"
#define IDS_MSG_FLOAT_VECT_LOADING_EXEC_CORRECTLY_1                 (IDS_USER_INT_MSG + 1)
                            // "Загрузка вектора вещественных чисел\n<%s>  выполнена корректно"
#define IDS_MSG_INT_DEPEND_SQLS_1                                   (IDS_USER_INT_MSG + 2)
                            // "SQL Server message %s"
#define IDS_ERR_OPEN_ERROR_FILE_1                                   (IDS_USER_INT_MSG + 3)
                            // "Ошибка открытия файла\n<%s>"
#define IDS_ERR_INT_DEPEND_NOT_FOUND_1                              (IDS_USER_INT_MSG + 4)
                            // "Интерполяционная зависимость\n<%s>  не найдена"
#define IDS_ERR_INT_DEPEND_READ_ARG_1                               (IDS_USER_INT_MSG + 5)
                            // "Ошибка чтения аргументов интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_INCORRECT_DEFINITION_FORMAT_1            (IDS_USER_INT_MSG + 6)
                            // "Некорректный формат описания интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_REDEFINITION_1                           (IDS_USER_INT_MSG + 7)
                            // "Повторное определение интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_NOT_MEMORY_1                             (IDS_USER_INT_MSG + 8)
                            // "Нехватка памяти при создании объекта интерполяционная зависимость\n<%s>"
#define IDS_ERR_INT_DEPEND_INCORRECT_DEFINITION_FORMAT_VECT_ARG_1   (IDS_USER_INT_MSG + 9)
                            // "Некорректный формат описания вектора\nаргумента интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_INCORRECT_DEFINITION_FORMAT_VECT_FUNC_1  (IDS_USER_INT_MSG + 10)
                            // "Некорректный формат описания вектора\nфункции интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_INCORRECT_INDEXING_VECT_ARG_1            (IDS_USER_INT_MSG + 11)
                            // "Некорректная индексация вектора\nаргумента интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_INCORRECT_INDEXING_VECT_FUNC_1           (IDS_USER_INT_MSG + 12)
                            // "Некорректная индексация вектора\nфункции интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_VAL_MISMATCH_VECT_ARG_1                  (IDS_USER_INT_MSG + 13)
                            // "Несоответствие значений вектора\nаргумента интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_NEXT_VAL_SMALLER_LAST_VAL_VECT_ARG_1    (IDS_USER_INT_MSG + 14)
                            // "Последующее значение вектора аргумента больше\nпредидущего, в интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_MISMATCH_NUM_ARG_1                      (IDS_USER_INT_MSG + 15)
                            // "Несоответствие количества аргументов интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_INCORRECT_SORTING_1                     (IDS_USER_INT_MSG + 16)
                            // "Некорректная сортировка при создании объекта\nинтерполяционная зависимость\n<%s>"
#define IDS_ERR_INT_DEPEND_INS_BUFF_SIZE_DIR_TBL_1                 (IDS_USER_INT_MSG + 17)
                            // "Недостаточнай размер буфера для размещения имени каталога tbl - файла, при создании интерполяционной зависимости <%s>"
#define IDS_ERR_INT_DEPEND_INCORRECT_POINTER_stCONNECT_DB_1        (IDS_USER_INT_MSG + 18)
                            // "Некорректное значение указателя на структуру stCONNECT_DB, при создании интерполяционной зависимости <%s>"
#define IDS_ERR_INT_DEPEND_SQLS_ADDS_TEXT_TO_COMMAND_BUFFER_1      (IDS_USER_INT_MSG + 19)
                            // "Ошибка занесения текста в командный буфер\nпри создании интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_SQLS_FULFILMENT_DB_QUERY_1              (IDS_USER_INT_MSG + 20)
                            // "Ошибка при выполнении SQL запроса\nпри создании интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_SQLS_BINDS_RES_COLUMN_TO_VARIABLE_1     (IDS_USER_INT_MSG + 21)
                            // "Ошибка установления связи результирующего столбца таблицы с переменной\nпрограммы, при создании интерполяционной зависимости\n<%s>"
#define IDS_ERR_INT_DEPEND_SQLS_DB_LIBRARY_1                       (IDS_USER_INT_MSG + 22)
                            // "DB - Library error:\n%s"
#define IDS_ERR_INT_DEPEND_SQLS_NET_LIBRARY_2                      (IDS_USER_INT_MSG + 23)
                            // "Net-Lib error %d:  %s"
#define IDS_ERR_INT_DEPEND_SQLS_OPERATIING_SYSTEM_1                (IDS_USER_INT_MSG + 24)
                            //  "Operating-system error:\n%s"
#define IDS_ERR_SQLS_LOGINREC_CANNOT_ALLOCATED_1                   (IDS_USER_INT_MSG + 25)
                            // "Ошибка размещения структуры LOGINREC\nпри подключении логина <%s>"
#define IDS_ERR_SQLS_UNABLE_CONNECT_1                              (IDS_USER_INT_MSG + 26)
                            // "Соединение с SQL Server не установлено\nпри подключении логина <%s>"
#define IDS_ERR_SQLS_CALL_LIBFUNC_DBUSE_1                          (IDS_USER_INT_MSG + 27)
                            // "Ошибка при вызове функции ::dbuse() для базы данных\n<%s>"
#define IDS_ERR_FLOAT_VECT_NOT_FOUND_1                             (IDS_USER_INT_MSG + 28)
                            // "Вектор вещественных чисел  <%s>  не найден"
#define IDS_ERR_FLOAT_VECT_INCORRECT_DEFINITION_FORMAT_1           (IDS_USER_INT_MSG + 29)
                            // "Некорректный формат описания вектора вещественных чисел\n<%s>"
#define IDS_ERR_FLOAT_VECT_REDEFINITION_1                          (IDS_USER_INT_MSG + 30)
                            // "Повторное определение вектора вещественных чисел\n<%s>"
#define IDS_ERR_FLOAT_VECT_NOT_MEMORY_1                             (IDS_USER_INT_MSG + 31)
                            // "Нехватка памяти при создании вектора вещественных чисел\n<%s>"

#endif

