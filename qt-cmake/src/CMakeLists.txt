set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# 查找源文件
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

# 添加资源文件
file(GLOB RESOURCES "${CMAKE_SOURCE_DIR}/res/*.qrc")

# 添加可执行文件
add_executable(template  ${SOURCES} ${RESOURCES})

# 为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(template
PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
