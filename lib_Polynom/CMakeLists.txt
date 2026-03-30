create_project_lib(Polynom)

target_sources(Polynom PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Monom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Monom.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Polynom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Polynom.h
)

# Добавляем текущую директорию для включения заголовочных файлов
target_include_directories(Polynom PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_depend(Polynom TVector ..\\lib_TVector)
add_depend(Polynom List ..\\lib_List)