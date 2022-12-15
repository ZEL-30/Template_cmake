# 添加源文件
SET(Minesweeper_SOURCES main_window.cpp)

# 添加头文件
SET(Minesweeper_HEADERS main_window.h)

# 添加所有的.ui文件
file(GLOB ui ${CMAKE_SOURCE_DIR}/ui/*)
SET(Minesweeper_FORMS 
	${ui}
)

# 添加资源文件
file(GLOB res ${CMAKE_SOURCE_DIR}/res/*.qrc)
SET(Minesweeper_RESOURCES 
	${res}
)

# 调用预编译器moc，需要使用 QT5_WRAP_CPP宏
QT5_WRAP_CPP(Minesweeper_HEADERS_MOC ${Minesweeper_HEADERS})

# 使用uic处理.ui文件
QT5_WRAP_UI(Minesweeper_FORMS_HEADERS ${Minesweeper_FORMS})

# 使用rcc处理.qrc文件
QT5_ADD_RESOURCES(Minesweeper_RESOURCES_RCC ${Minesweeper_RESOURCES})

# 这些生成的中间文件都会在build目录下，这样的话，编译器则不能定位由uic程序产生的诸如_ui_mainwindow.h等文件。所以，我们需要把build目录添加到包含目录中
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

#  编译静态库
add_library(MainWindow "")


target_sources(MainWindow
PRIVATE
    ${Minesweeper_SOURCES} 
PUBLIC
	${Minesweeper_HEADERS_MOC} 
    ${Minesweeper_FORMS_HEADERS}
	${Minesweeper_RESOURCES_RCC} 
)


# 添加头文件
target_include_directories(MainWindow
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(MainWindow
PRIVATE
    ${Qt5Widgets_LIBRARIES}
)

