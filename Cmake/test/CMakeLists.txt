# 添加 doctest 预处理宏
add_definitions(-D DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)

# 添加 fmt 预处理宏
add_definitions(-D FMT_HEADER_ONLY)


add_executable(test test.cpp)
target_include_directories(test 
PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor
)

add_executable(test_fmt test_fmt.cpp)
target_include_directories(test_fmt 
PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor
)

add_executable(test_spdlog test_spdlog.cpp)
target_include_directories(test_spdlog 
PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor
)
