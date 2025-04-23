cmake_minimum_required(VERSION 3.15)
project(MyModel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MyModel SHARED
        src/DllMain.cpp
        src/MyModel.cpp
        include/vs_main.h
)

# макрос для експорту/імпорту символів
if(WIN32)
    target_compile_definitions(MyModel PRIVATE MYMODEL_EXPORTS)
endif()

# Куди шукати заголовки
target_include_directories(MyModel
        PRIVATE
        "${CMAKE_SOURCE_DIR}/include"  # для pm_PMSystem.h, sv_interplr.h
        "${CMAKE_SOURCE_DIR}/src"      # для твоїх власних *.h у src/
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
