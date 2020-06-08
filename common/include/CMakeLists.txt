# add header only directories
add_library(${PROJECT_NAME})target_include_directories(${PROJECT_NAME}
        INTERFACE
            ${PROJECT_SOURCE_DIR}/sutil)