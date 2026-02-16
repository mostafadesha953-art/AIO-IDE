cmake_minimum_required(VERSION 3.10)
project(AIO_Smart_IDE LANGUAGES CXX) # تأكيد لغة C++

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# تحديد الملفات يدوياً لضمان رؤيتها (تأكد من مطابقة الأسماء تماماً)
set(MY_SOURCES
    main.cpp
    ui_manager.cpp
    imgui.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_tables.cpp
    imgui_demo.cpp
    imgui_impl_dx11.cpp
    imgui_impl_win32.cpp
)

# أمر إضافي لضمان لغة التجميع
set_source_files_properties(${MY_SOURCES} PROPERTIES LANGUAGE CXX)

add_executable(AIO_IDE ${MY_SOURCES})

target_include_directories(AIO_IDE PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(AIO_IDE PRIVATE 
    CURL::libcurl 
    nlohmann_json::nlohmann_json
    d3d11 
    dwmapi
)
