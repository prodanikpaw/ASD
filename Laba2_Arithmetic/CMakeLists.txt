cmake_minimum_required(VERSION 3.10)
project(Laba2_Arithmetic)

# Создаем исполняемый файл из ВСЕХ исходников
add_executable(Laba2_Arithmetic
    calculator.cpp
    calculator.h
    expression.cpp
    expression.h
    lexem.cpp
    lexem.h
    parser.cpp
    parser.h
    main.cpp
)

# Подключаем зависимости от внешних библиотек
target_link_libraries(Laba2_Arithmetic
    Stack
    List
    TVector
)

# Указываем пути к заголовочным файлам зависимостей
target_include_directories(Laba2_Arithmetic PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib_stack
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib_list
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib_TVector
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Настройки компиляции C++
set_target_properties(Laba2_Arithmetic PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Дополнительные флаги компиляции (опционально)
if(MSVC)
    target_compile_options(Laba2_Arithmetic PRIVATE /W4 /WX)
else()
    target_compile_options(Laba2_Arithmetic PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()