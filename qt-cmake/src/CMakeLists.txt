# 生成可执行文件
ADD_EXECUTABLE(run main.cpp)

add_subdirectory(windows)

# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(run
PRIVATE
	${Qt5Widgets_LIBRARIES}
	Windows
)
