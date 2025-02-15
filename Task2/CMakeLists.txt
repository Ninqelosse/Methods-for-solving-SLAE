cmake_minimum_required(VERSION 3.10)

# Установите имя проекта
project(task2)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 11)

# Укажите путь к GTest, если он не установлен в стандартном месте
set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/googletest")# Замените на фактический путь к папке googletest

add_subdirectory(${GTEST_ROOT} ${CMAKE_BINARY_DIR}/gtest)

# Создаем исполняемый файл
add_executable(MyExecutable test.cpp)

# Линкуем Google Test с вашим исполняемым файлом
target_link_libraries(MyExecutable gtest gtest_main pthread)