cmake_minimum_required(VERSION 3.10)
project(AIO_Smart_IDE LANGUAGES CXX)

# دمج كل المكتبات داخل الـ EXE ليعمل على ويندوز 2000 (Static Linking)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# البحث عن مكتبات vcpkg (الإنترنت والذكاء الاصطناعي)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# تجميع كل ملفات الـ CPP والـ H الموجودة في الخارج مباشرة
file(GLOB SOURCES ".cpp" ".h")

# إنشاء البرنامج النهائي
add_executable(AIO_IDE ${SOURCES})

# إخبار المترجم أن كل شيء موجود في المجلد الحالي
target_include_directories(AIO_IDE PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# ربط المكتبات والرسوميات (DirectX 11)
target_link_libraries(AIO_IDE PRIVATE 
    CURL::libcurl 
    nlohmann_json::nlohmann_json
    d3d11 
    dwmapi
)
