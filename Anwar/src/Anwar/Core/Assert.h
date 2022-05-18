#pragma once

#include "Anwar/Core/Base.h"
#include "Anwar/Core/Log.h"
#include <filesystem>

#ifdef ANW_ENABLE_ASSERTS
// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define ANW_INTERNAL_ASSERT_IMPL(type, check, msg, ...) {if(!(check)) {ANW##type##ERROR(msg, __VA_ARGS__); ANW_DEBUGBREAK();}}
#define ANW_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ANW_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define ANW_INTERNAL_ASSERT_NO_MSG(type, check) ANW_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ANW_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define ANW_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define ANW_INTERNAL_ASSERT_GET_MACRO(...) ANW_EXPAND_MACRO(ANW_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ANW_INTERNAL_ASSERT_WITH_MSG, ANW_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define ANW_ASSERT(...) ANW_EXPAND_MACRO(ANW_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_,__VA_ARGS__))
#define ANW_CORE_ASSERT(...) ANW_EXPAND_MACRO(ANW_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_,__VA_ARGS__))
#else
#define ANW_ASSERT(...)
#define ANW_CORE_ASSERT(...)
#endif