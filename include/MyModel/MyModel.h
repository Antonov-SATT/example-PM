//
// Created by zav3330 on 23.04.2025.
//

#ifndef MYMODEL_H
#define MYMODEL_H

// Підключення заголовка базового класу tPMSystem (шлях може відрізнятися)
#include "external/pm_PMSystem.h"  // припускаємо, що базовий клас оголошено тут

// Унікальний ідентифікатор моделі (визначається провідним інженером або у .hrs файлі)
#define MYMODEL_ID 10000  // TODO: змінити на фактичний ID моделі

// Макрос для експорт/імпорт символів DLL
#ifdef _WIN32
  #ifdef MYMODEL_EXPORTS
    #define MYMODEL_API __declspec(dllexport)
  #else
    #define MYMODEL_API __declspec(dllimport)
  #endif
#else
  #define MYMODEL_API
#endif

// Клас моделі, наслідуваний від tPMSystem
class MYMODEL_API MyModel : public tPMSystem {
public:
    MyModel();
    virtual ~MyModel();

    // Перевизначення віртуальних методів моделюючої системи:
    virtual long GetSystemID() const override;
    virtual int  RegReadVariables() override;
    virtual int  RegWriteVariables() override;
    virtual int  Unset(long* plMsgCode) override;
    virtual int  ResetParam(long iterationIndex, long* plMsgCode) override;
    virtual int  ResetDevice(long iterationIndex, long* plMsgCode) override;
    virtual int  Model(long* plMsgCode) override;
    virtual int  StopDevice(long* plMsgCode) override;

private:
    // Оголошення локальних змінних моделі (стан, параметри тощо):
    // Приклад:
    // double VALUER;
    // double RVAL;
    // unsigned char L_1;
};

#endif // MYMODEL_H
