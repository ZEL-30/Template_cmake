# 查找源文件
file(GLOB_RECURSE Minesweeper_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

# 查找头文件
file(GLOB_RECURSE Minesweeper_HEADERS ${CMAKE_CURRENT_LIST_DIR}/*.h)

# 添加所有的.ui文件
file(GLOB ui ${CMAKE_SOURCE_DIR}/ui/*.ui)
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


#  编译静态库
add_library(Windows "")

target_sources(Windows
PRIVATE
    ${Minesweeper_SOURCES} 
PUBLIC
	${Minesweeper_HEADERS_MOC} 
    ${Minesweeper_FORMS_HEADERS}
	${Minesweeper_RESOURCES_RCC} 
)


# 添加头文件
target_include_directories(Windows
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(Windows
PRIVATE
    ${Qt5Widgets_LIBRARIES}
)

