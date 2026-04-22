create_project_lib(Hash_Tables)

target_sources( Hash_Tables PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Hash_Table_C.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hash_Table_C.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Hash_Table_OA.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hash_Table_OA.h
)

# Добавляем текущую директорию для включения заголовочных файлов
target_include_directories(Hash_Tables PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_depend(Hash_Tables TVector ..\\lib_TVector)
add_depend(Hash_Tables List ..\\lib_List)
add_depend(Hash_Tables ITable ..\\lib_ITable)