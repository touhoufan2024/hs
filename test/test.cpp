#include <iostream>
#include <string>
#include <filesystem> // C++17 文件系统库

// 引入 sol2 库
#define SOL_ALL_SAFETIES_ON 1 // 建议开启所有安全检查
#include <sol/sol.hpp>

// ===========================================
// C++ 实现的函数 (与之前相同)
// ===========================================

// 一个简单的 C++ 函数，接受两个整数并返回它们的和
int cpp_add_numbers(int a, int b) {
    std::cout << "[C++] cpp_add_numbers called with: " << a << ", " << b << std::endl;
    return a + b;
}

// 一个 C++ 函数，接受一个字符串并打印它
void cpp_print_message(const std::string& msg) {
    std::cout << "[C++] Message from Lua: " << msg << std::endl;
}

// 一个 C++ 函数，接受一个 Lua 函数并调用它
void cpp_call_lua_function(sol::function lua_func) {
    std::cout << "[C++] Calling Lua function from C++..." << std::endl;
    try {
        sol::stack_object result = lua_func("Hello from C++!");
        if (result.valid() && result.is<std::string>()) {
            std::cout << "[C++] Lua function returned: " << result.as<std::string>() << std::endl;
        } else {
            std::cout << "[C++] Lua function returned nothing or unexpected type." << std::endl;
        }
    } catch (const sol::error& err) {
        std::cerr << "[C++] Error calling Lua function: " << err.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // 1. 处理命令行参数
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_lua_script.lua>" << std::endl;
        return 1; // 参数不足，退出
    }

    // 获取 Lua 脚本文件路径
    const std::string lua_filename = argv[1];

    // 2. 使用 C++17 的 filesystem 检查文件是否存在
    std::filesystem::path script_path(lua_filename);
    if (!std::filesystem::exists(script_path)) {
        std::cerr << "[Error] Lua script file not found: " << lua_filename << std::endl;
        return 1; // 文件不存在，退出
    }
    if (!std::filesystem::is_regular_file(script_path)) {
        std::cerr << "[Error] Provided path is not a regular file: " << lua_filename << std::endl;
        return 1; // 不是常规文件，退出
    }

    // 3. 创建一个 Lua 状态 (Lua 虚拟机)
    sol::state lua;

    // 4. 开启所有 Lua 默认库 (例如 `print`, `math`, `string` 等)
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string);

    // 5. 将 C++ 函数绑定到 Lua 环境中 (与之前相同)
    lua.set_function("add_numbers", cpp_add_numbers);
    std::cout << "[C++] 'add_numbers' C++ function bound to Lua." << std::endl;
    
    lua.set_function("print_message", &cpp_print_message);
    std::cout << "[C++] 'print_message' C++ function bound to Lua." << std::endl;

    lua.set_function("call_lua_from_cpp", cpp_call_lua_function);
    std::cout << "[C++] 'call_lua_from_cpp' C++ function bound to Lua." << std::endl;

    // 6. 读取并执行 Lua 脚本文件 (使用命令行参数传入的路径)
    try {
        std::cout << "\n[C++] Loading and executing Lua script: " << lua_filename << std::endl;
        lua.script_file(script_path.string()); // script_path.string() 确保是 std::string
        std::cout << "[C++] Lua script executed successfully." << std::endl;
    } catch (const sol::error& err) {
        std::cerr << "[C++] Error executing Lua script: " << err.what() << std::endl;
        return 1; // 脚本执行失败，退出
    }

    // 7. (可选) 从 C++ 调用 Lua 定义的函数 (与之前相同)
    sol::function lua_greet = lua["greet"];
    if (lua_greet.valid()) {
        std::cout << "\n[C++] Calling Lua function 'greet' from C++..." << std::endl;
        try {
            lua_greet("C++");
        } catch (const sol::error& err) {
            std::cerr << "[C++] Error calling Lua function 'greet': " << err.what() << std::endl;
        }
    } else {
        std::cout << "[C++] Lua function 'greet' not found or invalid." << std::endl;
    }

    std::cout << "\n[C++] Program finished." << std::endl;

    return 0;
}
