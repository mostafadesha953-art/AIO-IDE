cmake_minimum_required(VERSION 3.10)
project(AIO_Smart_IDE)

set(CMAKE_CXX_STANDARD 17)
add_compile_options("/utf-8")

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

if(DEFINED ENV{VCPKG_INSTALLATION_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE SOURCES ".cpp" "${IMGUI_DIR}/.cpp")

add_executable(AIO_IDE ${SOURCES})

target_include_directories(AIO_IDE PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
)

target_link_libraries(AIO_IDE PRIVATE CURL::libcurl nlohmann_json::nlohmann_json d3d11 dwmapi)