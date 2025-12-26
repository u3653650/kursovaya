cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Загрузка SFML
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# Загрузка GoogleTest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Включение тестов
enable_testing()

# Основной исполняемый файл
add_executable(main
        src/main.cpp
        src/WordCloud.cpp
        src/WordCloud.h
        src/ImageSaver.cpp
        src/ImageSaver.h
        src/MaskApplier.cpp
        src/MaskApplier.h
)

target_link_libraries(main
        PRIVATE
        sfml-graphics
)

# Линковка с SFML и другими библиотеками
target_compile_features(main PRIVATE cxx_std_17)

# Копирование OpenAL DLL для Windows
if(WIN32)
    add_custom_command(
            TARGET main
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
            VERBATIM)
endif()

# Настройка GoogleTest для тестов
include(GoogleTest)

# Тесты (исполняемый файл для тестов)
add_executable(runTests
        test/test_main.cpp  # Ваш файл с тестами
        src/WordCloud.cpp
        src/WordCloud.h
        src/ImageSaver.cpp
        src/ImageSaver.h
        src/MaskApplier.cpp
        src/MaskApplier.h
)

# Добавляем директорию с исходными файлами (если не добавлена)
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(runTests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        sfml-graphics
)

# Компиляция с GoogleTest
target_compile_features(runTests PRIVATE cxx_std_17)

# Добавляем тесты в CTest
add_test(NAME WordCloudTests COMMAND runTests)
