# 生成可执行文件
ADD_EXECUTABLE(PCSC main.cpp)


add_subdirectory(DesOpenSSL)
add_subdirectory(SmartCard)
add_subdirectory(Globle)
add_subdirectory(MainWindow)
add_subdirectory(ParseData)
add_subdirectory(ParseScript)
add_subdirectory(SplitFunc)
add_subdirectory(Thread)


# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(PCSC
PRIVATE
	${Qt5Widgets_LIBRARIES}
	MainWindow
	ParseScript
	Thread
)
