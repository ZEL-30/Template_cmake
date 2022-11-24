# 设置项目名称
set(PROJECT_NAME SmartCard)
project(${PROJECT_NAME})

# 采用C++11标准
set(CMAKE_CXX_STANDARD 11)

# 添加所有的源文件
file(GLOB srcs ./src/*/*.cpp)
file(GLOB main ./src/*.cpp)
SET(Minesweeper_SOURCES 
	${srcs}
	${main}
)

# 添加所有的头文件
include_directories(./third_lib/public_lib/include 
	# ./src/
)


# 添加所有的三方库
file(GLOB thirdlib third_lib/*/lib/*)
SET(Third_Library
	${thirdlib}
)


# 生成可执行文件
ADD_EXECUTABLE(${PROJECT_NAME}
	${Minesweeper_SOURCES} 
	${Minesweeper_HEADERS} 
)


# 打印
# MESSAGE( STATUS "third_include = ${Minesweeper_SOURCES}.")


# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	${Third_Library}
)
