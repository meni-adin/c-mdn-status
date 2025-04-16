set(TARGET_NAME mdn_status)

set(TARGET_SOURCES
    "status.c"
)

add_library(${TARGET_NAME} STATIC
    ${TARGET_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PUBLIC "include" ${INCLUDE_DIRECTORIES_TO_PROPAGATE}
)

cmake_language(CALL ${PROJECT_NAME}_set_target_c_compiler_flags ${TARGET_NAME})
