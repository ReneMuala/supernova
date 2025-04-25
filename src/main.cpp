#include "jit/function.hpp"

void playground3()
{
    using namespace supernova::jit;

    auto rt = std::make_shared<asmjit::JitRuntime>();
    auto builder = function_builder::create(rt, asmjit::FuncSignature::build<bool,int,int>());

    auto func = builder->build<long long(long long*)>();
    if (func)
    {
        long long a = 40;
        fmt::println("func({}) = {}", a, func(&a));
    }
}

void playground2()
{
    using namespace supernova::jit;

    auto rt = std::make_shared<asmjit::JitRuntime>();
    auto builder = function_builder::create(rt, asmjit::FuncSignature::build<long long, long long*>());
    auto a = builder->i64();
    auto b = builder->i64();
    auto r = builder->i64();
    builder->fetch_argument(0, a);
    builder->move(b, asmjit::x86::dword_ptr(a));
    builder->increment(b);
    builder->move(r,b);
    builder->decrement(b);
    builder->move(asmjit::x86::dword_ptr(a),b);
    builder->return_value(r);
    auto func = builder->build<long long(long long*)>();
    if (func)
    {
        long long a = 40;
        fmt::println("func({}) = {}", a, func(&a));
    }
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
        fmt::println("{}({},{}) = {}", sum ? "sum" : "sub", a,b, func(a,b));
    }
}

int main(int argc, char** argv)
try {
    playground(true);
    // playground(false);
    // playground2();
} catch (std::exception& e)
{
    fmt::println(stderr, "Uncaught exception:\n{}", e.what());
}