cmake_minimum_required(VERSION 3.16)
project(sample)

# オプション
option(SAMPLE_WITH_TESTS "テストを有効にする" OFF)
option(SAMPLE_USE_CPPCHECK "cppcheckを使用する" OFF)
option(SAMPLE_USE_LIZARD "lizardを使用する" OFF)
option(SAMPLE_USE_GCOV "gcovを使用する" OFF)

if(SAMPLE_USE_GCOV)
    set(SAMPLE_WITH_TESTS ON CACHE BOOL "テストを有効にする" FORCE)
    message(STATUS "gcovを使用するため、テストを自動的に有効にしました。")
endif()

if(SAMPLE_WITH_TESTS)
    message(STATUS "Google Testを使用します。")

    # Google Testを外部から取り込む
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.x
        GIT_SHALLOW TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

if(SAMPLE_USE_CPPCHECK)
    # cppcheckを見つける
    find_program(CPPCHECK cppcheck)
    if(CPPCHECK)
        message(STATUS "cppcheckを使用します。")
        set(CMAKE_CXX_CPPCHECK
            ${CPPCHECK}
            --enable=all
            --inconclusive
            --suppress=unmatchedSuppression
            --suppress=unusedFunction
            --suppress=missingIncludeSystem
            --suppress=syntaxError
            --error-exitcode=1
        )
    else()
        message(WARNING "cppcheckが見つかりません。")
    endif()
endif()

if(SAMPLE_USE_LIZARD)
    # lizardを見つける
    find_program(LIZARD lizard)
    if(LIZARD)
        message(STATUS "lizardを使用します。")
        add_custom_target(
            lizard
            COMMAND ${LIZARD} --CCN 15 include src
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
    else()
        message(WARNING "lizardが見つかりません。")
    endif()
endif()

if(SAMPLE_USE_GCOV)
    message(STATUS "gcovを使用します。")
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

        # gcovrを見つける
        find_program(GCOVR_PATH gcovr REQUIRED)
        set(gcovr_options --exclude ".*googletest.*")
        add_custom_target(coverage
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
            COMMAND ${GCOVR_PATH} -r ${CMAKE_SOURCE_DIR} ${gcovr_options} --xml ${CMAKE_BINARY_DIR}/coverage/coverage.xml
            COMMAND ${GCOVR_PATH} -r ${CMAKE_SOURCE_DIR} ${gcovr_options} --html --html-details -o ${CMAKE_BINARY_DIR}/coverage/index.html
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "カバレッジレポートを生成中... 出力先: ${CMAKE_BINARY_DIR}/coverage"
        )
    else()
        message(WARNING "gcovはGCCでのみ使用できます。")
    endif()
endif()

# sample_libライブラリを作成
add_library(sample_lib
    src/fizzbuzz.cpp
)
target_include_directories(sample_lib PUBLIC include)
target_precompile_headers(sample_lib PRIVATE src/pch.h)

if(CMAKE_CXX_CPPCHECK)
    # cppcheckを使用する場合は、target_propertiesに追加する
    set_target_properties(sample_lib PROPERTIES
        CXX_CPPCHECK "${CMAKE_CXX_CPPCHECK}"
    )
endif()

if(SAMPLE_USE_LIZARD)
    # lizardを使用する場合は、sample_libのビルド時にlizardを実行する
    add_dependencies(sample_lib lizard)
endif()

if(SAMPLE_WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
