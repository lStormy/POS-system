cmake_minimum_required(VERSION 3.10)
project(POS C)

include_directories(include libs/cJSON)

set(CJSON_SRC libs/cJSON/cJSON.c)

add_executable(pos_system
    src/process.c
    src/compra.c
    ${CJSON_SRC}
)

target_link_libraries(pos_system m) 
