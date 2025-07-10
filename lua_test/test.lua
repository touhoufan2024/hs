-- script.lua

print("[Lua] Script loaded!")

-- Lua 代码调用 C++ 实现的 add_numbers 函数
local result = add_numbers(10, 20)
print("[Lua] Result of add_numbers(10, 20): " .. result)

local result2 = add_numbers(5, 7)
print("[Lua] Result of add_numbers(5, 7): " .. result2)

-- Lua 代码调用 C++ 实现的 print_message 函数
print_message("This is a message from Lua!")

-- 定义一个 Lua 函数，稍后会被 C++ 调用
function greet(name)
    print("[Lua] Hello, " .. name .. "! This is from a Lua function.")
end

-- 调用 C++ 函数 call_lua_from_cpp，并传递一个 Lua 匿名函数
print("[Lua] Calling C++ function to make C++ call back to Lua...")
call_lua_from_cpp(function(cpp_msg)
    print("[Lua] Recieved message from C++ in anonymous function: " .. cpp_msg)
    return "Lua acknowledged: " .. cpp_msg
end)

print("[Lua] Script finished!")
