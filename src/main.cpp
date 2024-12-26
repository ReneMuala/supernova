#include "jit/function.hpp"

bool test_return()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float>());
    asmjit::x86::Xmm arg0 = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->return_value(arg0);
    if (const auto func = builder->build<float(float)>())
    {
        float a = 90;
        fmt::println(__FUNCTION__": func({}) = {}",a, func(a));
        return true;
    }
    return false;
}

bool test_add_xmm()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float, float>());
    auto arg0 = builder->xmmss();
    asmjit::x86::Xmm arg1 = builder->xmmss();
    asmjit::x86::Xmm result = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->add(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<float(float, float)>())
    {
        float a = 90, b = 90, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a + b;
    }
    return false;
}

bool test_sub_xmm()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float, float>());
    asmjit::x86::Xmm arg0 = builder->xmmss();
    asmjit::x86::Xmm arg1 = builder->xmmss();
    asmjit::x86::Xmm result = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->sub(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<float(float, float)>())
    {
        float a = 90, b = 90, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a - b;
    }
    return false;
}

bool test_mul_xmm()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float, float>());
    asmjit::x86::Xmm arg0 = builder->xmmss();
    asmjit::x86::Xmm arg1 = builder->xmmss();
    asmjit::x86::Xmm result = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->mul(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<float(float, float)>())
    {
        float a = 90, b = 90, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a * b;
    }
    return false;
}

bool test_div_xmm()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float, float>());
    asmjit::x86::Xmm arg0 = builder->xmmss();
    asmjit::x86::Xmm arg1 = builder->xmmss();
    asmjit::x86::Xmm result = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->div(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<float(float, float)>())
    {
        float a = 90, b = 90, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a / b;
    }
    return false;
}

bool test_add_i32()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    asmjit::x86::Gp arg0 = builder->i32();
    asmjit::x86::Gp arg1 = builder->i32();
    asmjit::x86::Gp result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->add(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<int(int, int)>())
    {
        int a = 90, b = 90, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a + b;
    }
    return false;
}

bool test_sub_i32()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    asmjit::x86::Gp arg0 = builder->i32();
    asmjit::x86::Gp arg1 = builder->i32();
    asmjit::x86::Gp result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->sub(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<int(int, int)>())
    {
        int a = 90, b = 90, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a - b;
    }
    return false;
}

bool test_mul_i32()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    asmjit::x86::Gp arg0 = builder->i32();
    asmjit::x86::Gp arg1 = builder->i32();
    asmjit::x86::Gp result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->mul(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<int(int, int)>())
    {
        int a = 90, b = 90, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a * b;
    }
    return false;
}

bool test_div_i32()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    asmjit::x86::Gp arg0 = builder->i32();
    asmjit::x86::Gp arg1 = builder->i32();
    asmjit::x86::Gp result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->div(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<int(int, int)>())
    {
        int a = 90, b = 20, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a / b;
    }
    return false;
}

bool test_mod_i32()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    asmjit::x86::Gp arg0 = builder->i32();
    asmjit::x86::Gp arg1 = builder->i32();
    asmjit::x86::Gp result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->mod(result, arg0, arg1);
    builder->return_value(result);
    if (const auto func = builder->build<int(int, int)>())
    {
        int a = 90, b = 20, r = func(a, b);
        fmt::println(__FUNCTION__": func({}, {}) = {}",a, b, r);
        return r == a % b;
    }
    return false;
}

void native_function()
{
    fmt::println("\t\tnative_function()");
}

bool test_call()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<void>());
    builder->call(native_function, asmjit::FuncSignature::build<void>(),{},{});
    builder->return_void();
    if (const auto func = builder->build<void()>())
    {
        func();
        fmt::println(__FUNCTION__": func()");
        return true;
    }
    return false;
}

void native_function_args(int a, int b, int c, float d, float e, float f)
{
    fmt::println("\t\tnative_function_args({},{},{},{},{},{})", a, b, c, d, e, f);
}

bool test_call_args()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<void>());
    auto a = builder->i32(1);
    auto b = builder->i32(2);
    auto c = builder->i32(3);

    auto d = builder->xmmss(4.5);
    auto e = builder->xmmss(5.5);
    auto f = builder->xmmss(6.5);

    builder->call(native_function_args, asmjit::FuncSignature::build<void, int, int, int, float, float, float>(),{a, b, c, d, e, f},{});
    builder->return_void();
    if (const auto func = builder->build<void()>())
    {
        func();
        fmt::println(__FUNCTION__": func()");
        return true;
    }
    return false;
}

float native_function_args_return(int a, int b, int c, float d, float e, float f)
{
    fmt::println("\t\tnative_function_args_return({},{},{},{},{},{})", a, b, c, d, e, f);
    return a + b + c + d + e + f;
}

bool test_call_args_return()
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float>());
    auto a = builder->i32(1);
    auto b = builder->i32(2);
    auto c = builder->i32(3);

    auto d = builder->xmmss(4.5);
    auto e = builder->xmmss(5.5);
    auto f = builder->xmmss(6.5);

    auto r = builder->xmmss();
    builder->call(native_function_args_return, asmjit::FuncSignature::build<float, int, int, int, float, float, float>(),{a, b, c, d, e, f},{r});
    builder->return_value(r);
    if (const auto func = builder->build<float()>())
    {
        const float a = 1, b = 2, c = 3, d = 4.5, e = 5.5, f = 6.5, r = func();
        fmt::println(__FUNCTION__": func() = {}", r);
        return a + b + c + d + e + f == r;
    }
    return false;
}

void playground(bool sum)
{
    using namespace supernova::jit;

    auto rt = std::make_shared<asmjit::JitRuntime>();
    auto builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    auto a = builder->i32();
    auto b = builder->i32();
    auto c = builder->i32();
    builder->fetch_argument(0, a);
    builder->fetch_argument(1, b);
    if (sum)
        builder->add(c, a, b);
    else
        builder->sub(c, a, b);
    builder->return_value(c);

    auto func = builder->build<int(int, int)>();
    if (func)
    {
        int a = 40, b = 60;
        fmt::println("func({},{}) = {}", a,b, func(a,b));
    }
}




int main(int argc, char** argv)
try {
    // test_jump_equal();
    // playground(true);
    // playground(false);
    test_return();
    test_add_xmm();
    test_sub_xmm();
    test_mul_xmm();
    test_div_xmm();
    test_add_i32();
    test_sub_i32();
    test_mul_i32();
    test_div_i32();
    test_mod_i32();
    test_call();
    test_call_args();
    test_call_args_return();
} catch (std::exception& e)
{
    fmt::println(stderr, "Uncaught exception:\n{}", e.what());
}