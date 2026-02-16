cmake_minimum_required(VERSION 3.10)
project(AIO_Smart_IDE LANGUAGES CXX)

# تفعيل الربط الساكن (Static Linking) لدمج المكتبات داخل الـ EXE
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# تحديد المسارات بدقة
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

# البحث عن مكتبات vcpkg (CURL و JSON)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# تجميع كافة ملفات الـ CPP من الخارج ومن داخل مجلد imgui ومجلد backends
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${IMGUI_DIR}/*.cpp"
    "${IMGUI_DIR}/backends/*.cpp"
)

# التأكد من وجود ملفات (للحماية من الفشل)
if(NOT SOURCES)
    message(FATAL_ERROR "Could not find any .cpp files! Make sure main.cpp is in the root folder.")
endif()

add_executable(AIO_IDE ${SOURCES})

# إخبار المترجم بمكان ملفات الـ .h (Headers)
target_include_directories(AIO_IDE PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
)

# ربط المكتبات الخارجية والرسوميات
target_link_libraries(AIO_IDE PRIVATE 
    CURL::libcurl 
    nlohmann_json::nlohmann_json
    d3d11 
    dwmapi
)
