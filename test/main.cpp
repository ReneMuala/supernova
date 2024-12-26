#include <gtest/gtest.h>
#include "jit/function.hpp"
//
// Created by dte on 11/24/2024.
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

int main()
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}