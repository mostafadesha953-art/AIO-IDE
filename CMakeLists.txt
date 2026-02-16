cmake_minimum_required(VERSION 3.10)
project(AIO_Smart_IDE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
# تفعيل الربط الساكن للعمل على ويندوز 2000
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# البحث عن كافة ملفات cpp في المجلد الرئيسي وفي أي مجلد فرعي (مثل imgui)
file(GLOB_RECURSE SOURCES 
    "*.cpp"
    "*.h"
)

# التأكد من أننا وجدنا ملفات لنتجنب خطأ الـ Linker
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found! Please upload imgui.cpp and main.cpp")
endif()

add_executable(AIO_IDE ${SOURCES})

# إضافة كافة المجلدات التي قد تحتوي على ملفات Header
target_include_directories(AIO_IDE PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(AIO_IDE PRIVATE 
    CURL::libcurl 
    nlohmann_json::nlohmann_json
    d3d11 
    dwmapi
)
