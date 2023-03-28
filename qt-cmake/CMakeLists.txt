# 最低版本
cmake_minimum_required(VERSION 3.24.2) 

# 设置项目名称
project(Template)

# 采用C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
    # Specify MSVC UTF-8 encoding   
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")    
endif()


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


# 链接Qt静态库/动态库
set(LINK_QT_STATIC TRUE)
set(QT_VERSION_MAJOR 5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# version
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "current systenm windows, program version: ${VER}")
    set(VERSIONINFO_RC "${CMAKE_CURRENT_SOURCE_DIR}/QReaderTools.rc")
    
else()
    message(STATUS "current systenm linux, program version: ${VER}")
endif()

# 查找Qt库
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets Network OpenGL Xml PrintSupport WinExtras Sql LinguistTools)
if(Qt5_FOUND)
    set(QT_INCLUDE ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS}
        ${Qt5PrintSupport_INCLUDE_DIRS} ${Qt5WinExtras_INCLUDE_DIRS} 
        ${Qt5Sql_INCLUDE_DIRS} ${Qt5Core_PRIVATE_INCLUDE_DIRS} ${Qt5Sql_PRIVATE_INCLUDE_DIRS} 
        )
        include_directories(${QT_INCLUDE})    
    # 定义QT_LIBRARIES
    set(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES}  
        ${Qt5Network_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${Qt5Xml_LIBRARIES} 
        ${Qt5PrintSupport_LIBRARIES} ${Qt5WinExtras_LIBRARIES} 
        ${Qt5Sql_LIBRARIES} ${Qt5Sql_PLUGINS}
        )
        #target_link_libraries(${CMAKE_PREFIX_PATH} ${QT_LIBRARIES})
endif(Qt5_FOUND)

# 添加子工程
add_subdirectory(vendor)
add_subdirectory(src)
add_subdirectory(tests)



# 打印
# MESSAGE( STATUS "目录 = ${CMAKE_CURRENT_SOURCE_DIR}/public_lib/lib/public.lib")

