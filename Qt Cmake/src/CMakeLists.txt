# 生成可执行文件
ADD_EXECUTABLE(main main.cpp)



add_subdirectory(MainWindow)

# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(main
PRIVATE
	${Qt5Widgets_LIBRARIES}
	MainWindow
)
