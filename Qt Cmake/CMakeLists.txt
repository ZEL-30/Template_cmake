# 设置项目名称
set(PROJECT_NAME Template)
project(${PROJECT_NAME})

# 让cmake自动去寻找Qt5
FIND_PACKAGE(Qt5 COMPONENTS Widgets REQUIRED)

# 采用C++11标准
set(CMAKE_CXX_STANDARD 11)

# 指定编译32位程序
set(CMAKE_CXX_FLAGS "-m32")

# 添加所有的源文件
file(GLOB srcs ./src/*/*.cpp)
file(GLOB main ./src/*.cpp)
SET(Minesweeper_SOURCES 
	${srcs}
	${main}
)

# 添加所有的头文件
include_directories(./third_lib/public_lib/include 
    ./src/main_window
)


file(GLOB include ./src/*/*.h)
file(GLOB third_include ./third_lib/*/include/*.h)
SET(Minesweeper_HEADERS 
   ${include}
   ${third_include}
)

# 添加所有的.ui文件
file(GLOB ui ui/*)
SET(Minesweeper_FORMS 
	${ui}
)

# 添加资源文件
file(GLOB res res/*.qrc)
SET(Minesweeper_RESOURCES 
	${res}
)

# 添加所有的三方库
file(GLOB thirdlib third_lib/*/lib/*)
SET(Third_Library
	${thirdlib}
)

# 调用预编译器moc，需要使用 QT5_WRAP_CPP宏
QT5_WRAP_CPP(Minesweeper_HEADERS_MOC ${Minesweeper_HEADERS})

# 使用uic处理.ui文件
QT5_WRAP_UI(Minesweeper_FORMS_HEADERS ${Minesweeper_FORMS})

# 使用rcc处理.qrc文件
QT5_ADD_RESOURCES(Minesweeper_RESOURCES_RCC ${Minesweeper_RESOURCES})

# 这些生成的中间文件都会在build目录下，这样的话，编译器则不能定位由uic程序产生的诸如_ui_mainwindow.h等文件。所以，我们需要把build目录添加到包含目录中
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# 生成可执行文件
ADD_EXECUTABLE(${PROJECT_NAME}
	${Minesweeper_SOURCES} 
	${Minesweeper_HEADERS_MOC} 
    ${Minesweeper_FORMS_HEADERS}
	${Minesweeper_RESOURCES_RCC} 
)

# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
    ${Qt5Widgets_LIBRARIES}
	${Third_Library}
)



# 打印
# MESSAGE( STATUS "srcs = ${srcs}.")

