#include <gtest/gtest.h>
#include "jit/function.hpp"
//
// Created by ReneMuala on 11/24/2024.
//

TEST(JIT, jump_equal)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(40);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 1);
    }
}

TEST(JIT, jump_equal_case_different_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(-40);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 0);
    }
}

TEST(JIT, jump_not_equal)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(4);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_not_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 1);
    }
}

TEST(JIT, jump_not_equal_case_equal_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(40);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_not_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 0);
    }
}

TEST(JIT, jump_lower)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(39);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_lower(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 1);
    }
}

TEST(JIT, jump_lower_case_greeter_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(91);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_lower(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 0);
    }
}

TEST(JIT, jump_lower_equal)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(40);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_lower_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 1);
    }
}

TEST(JIT, jump_lower_equal_case_lower_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(7);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_lower_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 1);
    }
}


TEST(JIT, jump_lower_equal_case_greater_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(41);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_lower_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 0);
    }
}


TEST(JIT, jump_greater)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(40);
    asmjit::x86::Gp arg1 = builder->i32(4);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_greater(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 1);
    }
}

TEST(JIT, jump_greater_case_lower_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(0);
    asmjit::x86::Gp arg1 = builder->i32(1);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_greater(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 0);
    }
}

TEST(JIT, jump_greater_case_equal_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(40);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_greater(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 0);
    }
}

TEST(JIT, jump_greater_equal)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(40);
    asmjit::x86::Gp arg1 = builder->i32(10);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_greater_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 1);
    }
}

TEST(JIT, jump_greater_equal_case_equal_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(40);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_greater_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 1);
    }
}

TEST(JIT, jump_greater_equal_case_lower_value)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int>());
    asmjit::x86::Gp arg0 = builder->i32(4);
    asmjit::x86::Gp arg1 = builder->i32(40);
    asmjit::x86::Gp result = builder->i32(1);

    const auto end = builder->label();
    builder->jump_greater_equal(arg0, arg1, end);
    builder->move(result, builder->i32_const(0));
    builder->bind(end);
    builder->return_value(result);
    const auto func = builder->build<int()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int  r = func();
        ASSERT_EQ(r, 0);
    }
}

TEST(JIT, add_xmm)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float, float>());
    auto arg0 = builder->xmmss();
    auto arg1 = builder->xmmss();
    auto result = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->add(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<float(float, float)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        float a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a+b);
    }
}

TEST(JIT, sub_xmm)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float, float>());
    auto arg0 = builder->xmmss();
    auto arg1 = builder->xmmss();
    auto result = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->sub(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<float(float, float)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        float a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a-b);
    }
}

TEST(JIT, mul_xmm)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float, float>());
    auto arg0 = builder->xmmss();
    auto arg1 = builder->xmmss();
    auto result = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->mul(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<float(float, float)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        float a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a*b);
    }
}

TEST(JIT, div_xmm)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float, float, float>());
    auto arg0 = builder->xmmss();
    auto arg1 = builder->xmmss();
    auto result = builder->xmmss();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->div(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<float(float, float)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        float a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a/b);
    }
}

TEST(JIT, add_i32)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    auto arg0 = builder->i32();
    auto arg1 = builder->i32();
    auto result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->add(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<int(int, int)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a+b);
    }
}

TEST(JIT, sub_i32)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    auto arg0 = builder->i32();
    auto arg1 = builder->i32();
    auto result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->sub(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<int(int, int)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a-b);
    }
}

TEST(JIT, mul_i32)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    auto arg0 = builder->i32();
    auto arg1 = builder->i32();
    auto result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->mul(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<int(int, int)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a*b);
    }
}

TEST(JIT, div_i32)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    auto arg0 = builder->i32();
    auto arg1 = builder->i32();
    auto result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->div(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<int(int, int)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a/b);
    }
}

TEST(JIT, mod_i32)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<int, int, int>());
    auto arg0 = builder->i32();
    auto arg1 = builder->i32();
    auto result = builder->i32();
    builder->fetch_argument(0, arg0);
    builder->fetch_argument(1, arg1);
    builder->mod(result, arg0, arg1);
    builder->return_value(result);
    const auto func = builder->build<int(int, int)>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        int a = 90, b = 90, r = func(a, b);
        ASSERT_EQ(r, a%b);
    }
}

bool native_function_called = false;
void native_function()
{
    native_function_called = true;
}

TEST(JIT, native_call)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<void>());
    builder->call(native_function, asmjit::FuncSignature::build<void>(),{},{});
    builder->return_void();
    const auto func = builder->build<void()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        func();
        ASSERT_TRUE(native_function_called);
    }
}

bool native_function_args_called = false;
int native_function_args_a, native_function_args_b, native_function_args_c;
float native_function_args_d, native_function_args_e, native_function_args_f;
void native_function_args(int a, int b, int c, float d, float e, float f)
{
    native_function_args_called = true;
    native_function_args_a = a;
    native_function_args_b = b;
    native_function_args_c = c;
    native_function_args_d = d;
    native_function_args_e = e;
    native_function_args_f = f;
}

TEST(JIT, native_call_args)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<void>());
    int _a = 1, _b = 2, _c = 3;
    float _d = 4.5, _e = 5.5, _f = 6.5;

    auto a = builder->i32(_a);
    auto b = builder->i32(_b);
    auto c = builder->i32(_c);

    auto d = builder->xmmss(_d);
    auto e = builder->xmmss(_e);
    auto f = builder->xmmss(_f);

    builder->call(native_function_args, asmjit::FuncSignature::build<void, int, int, int, float, float, float>(),{a, b, c, d, e, f},{});
    builder->return_void();
    const auto func = builder->build<void()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        func();
        ASSERT_TRUE(native_function_args_called);
        ASSERT_EQ(native_function_args_a, _a);
        ASSERT_EQ(native_function_args_b, _b);
        ASSERT_EQ(native_function_args_c, _c);
        ASSERT_EQ(native_function_args_d, _d);
        ASSERT_EQ(native_function_args_e, _e);
        ASSERT_EQ(native_function_args_f, _f);
    }
}

bool native_function_args_return_called = false;
int native_function_args_return_a, native_function_args_return_b, native_function_args_return_c;
float native_function_args_return_d, native_function_args_return_e, native_function_args_return_f;
float native_function_args_return(int a, int b, int c, float d, float e, float f)
{
    native_function_args_return_called = true;
    native_function_args_return_a = a;
    native_function_args_return_b = b;
    native_function_args_return_c = c;
    native_function_args_return_d = d;
    native_function_args_return_e = e;
    native_function_args_return_f = f;
    return a + b + c + d + e + f;
}

TEST(JIT, native_call_args_return)
{
    using namespace supernova::jit;
    const auto rt = std::make_shared<asmjit::JitRuntime>();
    const std::shared_ptr<function_builder> builder = function_builder::create(rt, asmjit::FuncSignature::build<float>());
    int _a = 1, _b = 2, _c = 3;
    float _d = 4.5, _e = 5.5, _f = 6.5;

    auto a = builder->i32(_a);
    auto b = builder->i32(_b);
    auto c = builder->i32(_c);

    auto d = builder->xmmss(_d);
    auto e = builder->xmmss(_e);
    auto f = builder->xmmss(_f);
    auto r = builder->xmmss();

    builder->call(native_function_args_return, asmjit::FuncSignature::build<float, int, int, int, float, float, float>(),{a, b, c, d, e, f},{r});
    builder->return_value(r);
    const auto func = builder->build<float()>();
    ASSERT_NE(func, nullptr);
    if (func)
    {
        auto _r = func();
        ASSERT_TRUE(native_function_args_return_called);
        ASSERT_EQ(native_function_args_return_a, _a);
        ASSERT_EQ(native_function_args_return_b, _b);
        ASSERT_EQ(native_function_args_return_c, _c);
        ASSERT_EQ(native_function_args_return_d, _d);
        ASSERT_EQ(native_function_args_return_e, _e);
        ASSERT_EQ(native_function_args_return_f, _f);
        ASSERT_EQ(_a+_b+_c+_d+_e+_f, _r);
    }
}

int main()
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}