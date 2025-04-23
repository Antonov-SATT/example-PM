//
// Created by zav3330 on 23.04.2025.
//

//---------------------------------------------------------------------------

#ifndef vs_mainH
#define vs_mainH
#pragma pack(push, 1)
//---------------------------------------------------------------------------
//Определение псевдонимов
  typedef double REAL;
  typedef int INTEGER;
  typedef unsigned char BOOLEAN;

//Определение стандартных типов данных
  class BYTEARRAY
  {
      friend void SetVarState(BYTEARRAY &Current, bool fMayResize, unsigned long vSize, unsigned long vMaxSize, unsigned long vMinSize);
      friend char SyncWriteVal(BYTEARRAY &Etalon, BYTEARRAY &Local);
      friend char SyncReadVal(BYTEARRAY &Etalon, BYTEARRAY &Local);
      friend char CloneReadVal(BYTEARRAY &Etalon, BYTEARRAY &Local);

    private:
        long ecLastErrorCode;
        unsigned char vNULL;

    public:

        bool fMayResize;
        char *pValue;
        unsigned long vSize;
        unsigned long vMaxSize;
        unsigned long vMinSize;

      //Конструкторы и деструкторы
        BYTEARRAY();
        BYTEARRAY(bool fMayResize, unsigned long vSize, unsigned long vMaxSize, unsigned long vMinSize);
        BYTEARRAY(const BYTEARRAY &);
        ~BYTEARRAY();
      //Перегруженные операции
        const BYTEARRAY & operator = (BYTEARRAY);
        const BYTEARRAY & operator = (char *);
        const BYTEARRAY & operator = (REAL);
        const BYTEARRAY & operator = (INTEGER);
        const BYTEARRAY & operator = (BOOLEAN);
        bool operator == (const BYTEARRAY & );
        bool operator != (const BYTEARRAY & );
        unsigned char & operator [] (unsigned long);
        unsigned long operator () ();
        bool operator () (unsigned long);
        void * operator () (unsigned long, unsigned long);
        const BYTEARRAY & operator ~();
        const BYTEARRAY & operator !();
        friend BYTEARRAY operator + (BYTEARRAY &, BYTEARRAY &);
        friend BYTEARRAY operator + (BYTEARRAY &, const unsigned char);
        //friend BYTEARRAY operator - (BYTEARRAY &, const unsigned char);
        friend BYTEARRAY operator & (BYTEARRAY &, BYTEARRAY &);
        friend BYTEARRAY operator & (BYTEARRAY &, const unsigned char);
        friend BYTEARRAY operator | (BYTEARRAY &, BYTEARRAY &);
        friend BYTEARRAY operator | (BYTEARRAY &, const unsigned char);
        friend BYTEARRAY operator ^ (BYTEARRAY &, BYTEARRAY &);
        friend BYTEARRAY operator ^ (BYTEARRAY &, const unsigned char);
        const BYTEARRAY & operator ++ ();
        const BYTEARRAY & operator -- ();
        const BYTEARRAY & operator += (REAL);
        const BYTEARRAY & operator += (INTEGER);
        const BYTEARRAY & operator += (BOOLEAN);
        const BYTEARRAY & operator += (char*);
        const BYTEARRAY & operator << (REAL);
        const BYTEARRAY & operator << (INTEGER);
        const BYTEARRAY & operator << (BOOLEAN);
        const BYTEARRAY & operator << (char*);
        bool operator < (const BYTEARRAY & );
        bool operator > (const BYTEARRAY & );
        bool operator <= (const BYTEARRAY & );
        bool operator >= (const BYTEARRAY & );


      //Основные управляющие функции
        //Очистить переменную
        bool Clear();
        //Определение размера переменной
        unsigned long GetSize();
        //Установка нового размера переменной
        bool SetSize(unsigned long vNewSize);
        //Установка флагов
        bool SetParams(const BYTEARRAY &Etalon);
        //Выдать код последней ошибки
        long GetLastError() const;
        //Определение фиксированного размера
        bool IsFixedSize();
      //Функции манипуляции данными
        //Установка/получение битов и байтов
          //Получить значение i-го бита
          unsigned char GetBit(unsigned long vBitNum);
          //Получить значение i-го бита в k-м байте
          unsigned char GetBit(unsigned char vBitNum, unsigned long vByteNum);
          //Получить значение i-го байта
          unsigned char GetByte(unsigned long vByteNum);
          //Установить значение i-го бита
          bool SetBit(unsigned long vBitNum, unsigned char vValue);
          //Установить значение i-го бита в k-м байте
          bool SetBit(unsigned char vBitNum, unsigned long vByteNum, unsigned char vValue);
          //Установить значение i-го байта
          bool SetByte(unsigned long vByteNum, unsigned char vValue);
        //Работа с блоками данных
          //Получить блок
          void *GetBlock(unsigned long vStart, unsigned long vLength);
          //Установить блок
          bool SetBlock(unsigned long vStart, unsigned long vLength, void *pBlock);
          //Заменить значение на блок
          bool WriteBlock(unsigned long vLength, void *pBlock);
       //Работа с указателями на значения
         //Получить указатель на вещественное значение
         REAL* GetPtr_REAL(unsigned long vStart);
         //Получить указатель на целое значение
         INTEGER* GetPtr_INTEGER(unsigned long vStart);
         //Получить указатель на логическое значение
         BOOLEAN* GetPtr_BOOLEAN(unsigned long vStart);
      //Утилитарные функции
        //Заполнить все содержимое k-м символом
        bool Fill(unsigned char vValue);
        //Заполнить часть содержимого k-м символом
        bool Fill(unsigned char vValue, unsigned long vStart, unsigned long vLength);
        //Обнулить все содержимое
        bool FillZero();
        //Обнулить часть содержимого
        bool FillZero(unsigned long vStart, unsigned long vLength);
        //Поменять местами два байта
        bool SwapBytes(unsigned long vByte1, unsigned long vByte2);
      //Конец
  };
    //Коды ошибок в классе
      #define erba_NONE 0                //Нет ошибки
      #define erba_NONECREATE 1          //Не отведена память
      #define erba_SIZEMIN 2             //Пытаются установить размер меньше минимального
      #define erba_SIZEMAX 3             //Пытаются установить размер больше максимального
      #define erba_NOTRESIZE 4           //Пытаются установить размер для переменной размер которой менять нельзя
      #define erba_NOTSTART 5            //Начало области выходит за границу памяти
      #define erba_NOTLENGTH 6           //Конец области выходит за границу памяти
      #define erba_NULL 7                //Операция не выполнена т.к. значение пустое
      #define erba_NOTBYTE1 8            //Первый байт выходит за границы значения
      #define erba_NOTBYTE2 9            //Второй байт выходит за границы значения
      #define erba_NOTBYTENUM 10         //Неправильный номер байта
      #define erba_NOTBITNUM 11          //Неправильный номер бита
      #define erba_OPENFILEREAD 12       //Ошибка при открытии файла для чтения
      #define erba_OPENFILEWRITE 13      //Ошибка при открытии файла для записи
      #define erba_ERRORREAD 14          //Ошибка при чтении данных
      #define erba_ERRORWRITE 15         //Ошибка при записи данных
      #define erba_BADINDEX 16           //Не валидный индекс элемента
      #define erba_SIZENOTEQV 17         //Размеры обеих переменных не равны
      #define erba_NOTLOW 18             //Размер уже минимальный, еще уменьшать нельзя

  typedef BYTEARRAY bytearray;

  //

#pragma pack(pop)

//==========================================================
// Copyright "ANTONOV Flight Simulator Dep."
//
// Project:	AMS
// Module:	vs_main.h - описание базового класса байтового
//              массива
// Spec:	C++
// Edition:	[0.0.2.1] {14.09.2004}
//==========================================================

#endif
