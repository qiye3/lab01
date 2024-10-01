cmake_minimum_required(VERSION 3.10)
project(lab01 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)  # 可以选择 C++17 或者保持为 C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_PREFIX_PATH "E:/Qt/6.7.2/mingw_64/lib/cmake/")

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# # 添加子目录
# add_subdirectory(src/Utils)
# add_subdirectory(src/Task)
# add_subdirectory(src/Task_Manager)
# add_subdirectory(src/Qt_Interface)

# 指定源文件
file(GLOB_RECURSE SRC_FILES "src/**/*.cpp")  # 递归查找所有 cpp 文件
file(GLOB_RECURSE UI_HEADERS "src/**/*.ui")   # 递归查找所有 ui 文件
file(GLOB_RECURSE HEADERS "src/**/*.hpp")     # 递归查找所有头文件

# 创建可执行文件
add_executable(main main.cpp ${SRC_FILES} ${UI_HEADERS} ${HEADERS})

# 链接库
target_link_libraries(main PRIVATE
    # Utils
    # Task
    # Task_Manager
    Qt6::Core
    Qt6::Widgets
    # QtInterface
)

# 设置可执行文件的属性
set_target_properties(main PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS main
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
