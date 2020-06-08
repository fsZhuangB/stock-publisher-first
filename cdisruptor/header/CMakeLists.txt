project(cdisruptor)

aux_source_directory(. DIR_SRC)

add_library(cdisruptor SHARED ${DIR_SRC})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR})
