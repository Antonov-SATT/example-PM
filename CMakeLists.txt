cmake_minimum_required(VERSION 3.15)
project(MyModel LANGUAGES CXX)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Збираємо DLL-бібліотеку MyModel
add_library(MyModel SHARED
        src/MyModel.cpp
        src/DllMain.cpp
)

# Визначаємо макрос експорту символів DLL
if(WIN32)
    target_compile_definitions(MyModel PRIVATE MYMODEL_EXPORTS)
endif()

# Підключаємо шляхи до заголовків (твоїх та зовнішніх)
target_include_directories(MyModel PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKESource_DIR}/include/external"
)


# якщо треба лінкуватися з бібліотекою платформи
# target_link_libraries(MyModel PRIVATE PMSystemLib)


# де лежать заголовки базової платформи
# target_include_directories(MyModel PRIVATE "${CMAKE_SOURCE_DIR}/third_party/sdk/include")

# якщо треба лінкуватися з бібліотекою платформи
# target_link_libraries(MyModel PRIVATE PMSystemLib)

# опційно — складати DLL у bin/
# set_target_properties(MyModel PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
