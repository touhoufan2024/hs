set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # 禁用 GNU 扩展，推荐使用标准 C++

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/lua
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/sol2/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/ocgcore
)

set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB TEST_SOURCES "${TEST_DIR}/*.cpp")
if(NOT TEST_SOURCES)
    message(WARNING "No .cpp files found in the test directory '${TEST_DIR}'.")
else()
    message(STATUS "Found test files: ${TEST_SOURCES}")
    foreach(TEST_FILE ${TEST_SOURCES})
        # 获取文件名（不带路径和扩展名），作为可执行文件的名称
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        message(STATUS "Adding test executable: ${TEST_NAME} from ${TEST_FILE}")
        # 添加可执行文件
        add_executable(${TEST_NAME} ${TEST_FILE})
        # 链接所需的库
        target_link_libraries(${TEST_NAME} PRIVATE
            lua::lua
            sol2::sol2
            ocgcore::ocgcore
        )
        # C++ 标准设置可以省略，因为它会继承全局的 CMAKE_CXX_STANDARD 17
        # 如果你想为测试文件强制不同于全局的标准 (不推荐，但可选):
        # set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 17)
        # 添加 CTest 测试，方便统一运行
        add_test(NAME ${TEST_NAME}_test COMMAND ${TEST_NAME})
    endforeach()
endif()