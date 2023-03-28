# 添加预处理宏
add_definitions(-D DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)


add_executable(test test.cpp)
target_include_directories(test 
PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor
)