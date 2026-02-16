cmake_minimum_required(VERSION 3.10)
project(AIO_Smart_IDE LANGUAGES CXX)

# تفعيل الربط الساكن ليعمل على ويندوز 2000 بدون DLLs
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 17)

# البحث عن المكتبات الخارجية (vcpkg)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# تجميع كل ملفات المشروع الموجودة في الخارج مباشرة
file(GLOB SOURCES ".cpp" ".h")

add_executable(AIO_IDE ${SOURCES})

# إخبار المترجم أن يبحث عن الـ Headers في المجلد الحالي
target_include_directories(AIO_IDE PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# ربط المكتبات والرسوميات
target_link_libraries(AIO_IDE PRIVATE 
    CURL::libcurl 
    nlohmann_json::nlohmann_json
    d3d11 
    dwmapi
)
