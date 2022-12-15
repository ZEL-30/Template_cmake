#  编译静态库
add_library(Mode "")


target_sources(Mode
PRIVATE
    mode.cpp
PUBLIC
    mode.h
)

# 添加头文件
target_include_directories(Mode
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)


# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(Mode

)