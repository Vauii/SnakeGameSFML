cmake_minimum_required(VERSION 3.0)
project(lab_6)

set(CMAKE_CXX_STANDARD 17)


add_executable(lab_6 main.cpp game.cpp game.h controller.cpp controller.h view.cpp view.h model.cpp model.h)

set(SFML_DIR "lib\\sfml\\GCC 7.3.0 MinGW (DW2) - 32-bit\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(lab_6 sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)

if (MSVC)
    target_compile_options(lab_6
            PRIVATE /W4          # warnings level
            PRIVATE /WX          # treat all warnings as errors
            )
else()
    target_compile_options(lab_6
            PRIVATE -Wall        # basic set of warnings
            PRIVATE -pedantic    # modern C++ inspections
            PRIVATE -Werror      # treat all warnings as errors
            )
endif()
