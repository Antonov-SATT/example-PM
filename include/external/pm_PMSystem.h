//
// Created by zav3330 on 23.04.2025.
//


#ifndef __PM_PMSYSTEM_H
#define __PM_PMSYSTEM_H
#include "sv_interplr.h"
#include "vs_main.h"

// Research Flight Bench System

//===== Базовый класс програмной модели =====
class tPMSystem
{
public:
	// Метод для получения уникального идентификатора модели
	virtual long GetSystemID() const      = 0;
	// Метод для установки значений локальных переменных
	virtual int  RegWriteVariables()      = 0;
	// Метод для получения значений локальных переменных
	virtual int  RegReadVariables()       = 0;
	// Однотактовая инициализация
	virtual int  Unset( long* plMSGCode ) = 0;
	// Реализация алгоритма модели
	virtual int  Model( long* plMSGCode ) = 0;
	// Многотактовая инициализация параметров
	virtual int  ResetParam( long /*lIterationIndex*/, long* /*plMSGCode*/ )   { return 1; }
	// Многотактовая инициализация аппаратуры
	virtual int  ResetDevice( long /*lIterationIndex*/, long* /*plMSGCode*/ )  { return 1; }
	// Реализация завершающей настройки
	virtual int  StopDevice( long* /*plMSGCode*/ ) { return 1; }
	// Реализация восстановления после остановки
	virtual int  ResumeDevice( long* /*plMSGCode*/ ) { return 1; }
	// Многотактовый останов аппаратуры
	virtual int  TheEnd( long /*lIterationIndex*/, long* /*plMSGCode*/ )  { return 1; }
	//Доп. методы
 		// Реализация дополнительной многотактовой функции моделирования
		virtual int  SubModel( long* /*plMSGCode*/, double /*dLocalTime*/ ) { return 1; }
 		// Реализация дополнительной многотактовой функции моделирования
		virtual int  RealTimeTerminate( long* /*plMSGCode*/, bool /*bThisModel*/, double /*dTimeValue*/) { return 1; }

	// Деструктор модели
	virtual ~tPMSystem() {}
};
//==========

#define IDS_USER_RFS_MSG  91
#define IDS_MSG_CREATE_OBJ_EXECUTED_SUCCESS_1  (IDS_USER_RFS_MSG + 0)
				                   // Создание объекта <%s> выполнено успешно
#define IDS_ERR_NOT_MEMORY_CREATE_OBJ_1        (IDS_USER_RFS_MSG + 1)
		                           // Нехватка памяти при создании объекта\n<%s>
#define IDS_ERR_RESET_PARAM_IS_NOT_EXECUTED_1  (IDS_USER_RFS_MSG + 2)
									// Переустановка параметров объекта <%s> не выполнена
#define IDS_ERR_RESET_DEVICE_IS_NOT_EXECUTED_1 (IDS_USER_RFS_MSG + 3)
									// Переустановка физических устройств объекта <%s> не выполнена

#endif

//==========================================================
// Copyright "ANTONOV Flight Simulator Dep."
//
// Project:	AMS
// Module:	pm_PMSystem.h - описание базового класса програмных моделей
// Spec:	C++
// Edition:	[0.1.0.0] {02.04.2005}
//==========================================================
