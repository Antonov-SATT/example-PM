//
// Created by zav3330 on 23.04.2025.
//

#ifdef _WIN32
#include <windows.h>
#endif

#include "MyModel/MyModel.h"

// Статичний глобальний об'єкт моделі
static MyModel g_myModel;

// Експортуємо вказівник на базовий клас моделі для доступу моделюючої системи
extern "C" {
  __declspec(dllexport) tPMSystem* GetModelPtr() {
    return &g_myModel;
  }
}

// Точка входу DLL (опціонально можна не змінювати)
BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD ul_reason_for_call, LPVOID lpReserved) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    // Ініціалізація DLL, якщо потрібно
    // (Можна викликати DisableThreadLibraryCalls(hInst) для оптимізації, якщо не використовуються DLL_THREAD_ATTACH)
  } else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
    // Деініціалізація DLL, якщо потрібно
  }
  return TRUE; // Успішне підключення DLL
}
