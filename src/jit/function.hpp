//
// Created by ReneMuala on 12/26/2024.
//
#pragma once
#include <memory>
#include <asmjit/asmjit.h>
#include <unordered_map>
#include <fmt/core.h>
#include <vector>
#include <optional>
namespace supernova::jit
{
    struct function_builder
    {
        std::unordered_map<long long, asmjit::x86::Mem> i64_consts;
        std::unordered_map<int, asmjit::x86::Mem> i32_consts;
        std::unordered_map<short, asmjit::x86::Mem> i16_consts;
        std::unordered_map<char, asmjit::x86::Mem> i8_consts;
        std::unordered_map<float, asmjit::x86::Mem> xmms_consts;
        std::shared_ptr<asmjit::JitRuntime> rt;
        std::shared_ptr<asmjit::CodeHolder> code;
        std::shared_ptr<asmjit::x86::Compiler> co;
        asmjit::FuncSignature signature;
        asmjit::FileLogger logger{stdout};
        asmjit::FuncNode * node{nullptr};
        void *function{nullptr};

        static std::shared_ptr<function_builder> create(const std::shared_ptr<asmjit::JitRuntime>& rt, const bool& logger = false);
        static std::shared_ptr<function_builder> create(const std::shared_ptr<asmjit::JitRuntime>& rt, const asmjit::FuncSignature& signature, const bool& logger = false);

        [[nodiscard]] asmjit::x86::Gp i8() const
        {
            return co->newInt8();
        }

        [[nodiscard]] asmjit::x86::Gp i8(const char val)
        {
            asmjit::x86::Gp initialized_gp = i8();
            move(initialized_gp, i8_const(val), true);
            return initialized_gp;
        }

        [[nodiscard]] asmjit::x86::Mem i8_const(const char val)
        {
            if (not i8_consts.contains(val))
                i8_consts[val] = co->newByteConst(asmjit::ConstPoolScope::kLocal, val);
            return i8_consts[val];
        }

        [[nodiscard]] asmjit::x86::Gp i16() const
        {
            return co->newInt16();
        }

        [[nodiscard]] asmjit::x86::Gp i16(const short val)
        {
            asmjit::x86::Gp initialized_gp = i16();
            move(initialized_gp, i16_const(val), true);
            return initialized_gp;
        }

        [[nodiscard]] asmjit::x86::Mem i16_const(const short val)
        {
            if (not i16_consts.contains(val))
                i16_consts[val] = co->newInt16Const(asmjit::ConstPoolScope::kLocal, val);
            return i16_consts[val];
        }


        [[nodiscard]] asmjit::x86::Xmm xmmss() const
        {
            return co->newXmmSs();
        }

        [[nodiscard]] asmjit::x86::Xmm xmmss(const float val)
        {
            asmjit::x86::Xmm initialized_xmms = xmmss();
            move(initialized_xmms, xmmss_const(val));
            return initialized_xmms;
        }

        [[nodiscard]] asmjit::x86::Mem xmmss_const(const float val)
        {
            if (not xmms_consts.contains(val))
                xmms_consts[val] = co->newFloatConst(asmjit::ConstPoolScope::kLocal, val);
            return xmms_consts[val];
        }

        [[nodiscard]] asmjit::x86::Gp i32() const
        {
            return co->newInt32();
        }

        [[nodiscard]] asmjit::x86::Gp i32(const int val)
        {
            asmjit::x86::Gp initialized_gp = i32();
            move(initialized_gp, i32_const(val));
            return initialized_gp;
        }

        [[nodiscard]] asmjit::x86::Mem i32_const(const int val)
        {
            if (not i32_consts.contains(val))
                i32_consts[val] = co->newInt32Const(asmjit::ConstPoolScope::kLocal, val);
            return i32_consts[val];
        }

        [[nodiscard]] asmjit::x86::Gp i64() const
        {
            return co->newInt64();
        }

        [[nodiscard]] asmjit::x86::Gp i64(const long long val)
        {
            asmjit::x86::Gp initialized_gp = i64();
            move(initialized_gp, i64_const(val));
            return initialized_gp;
        }

        [[nodiscard]] asmjit::x86::Mem i64_const(const long long val)
        {
            if (not i64_consts.contains(val))
                i64_consts[val] = co->newInt64Const(asmjit::ConstPoolScope::kLocal, val);
            return i64_consts[val];
        }

        [[nodiscard]] asmjit::Label label() const
        {
            return co->newLabel();
        }

        void bind(const asmjit::Label& label) const
        {
            co->bind(label);
        }

        void fetch_argument(const size_t index, const asmjit::x86::Reg & r) const
        {
            if (signature.arg(index) == asmjit::TypeId::kFloat32 and not r.isXmm())
                throw std::runtime_error("Argument not a floating point type");
            if (signature.arg(index) == asmjit::TypeId::kInt32 and not r.isGp32())
                throw std::runtime_error("Argument not a int type");
            if (index < signature.argCount())
                node->setArg(index, r);
            else
                throw std::runtime_error("arg out of range");
        }

        void add(const asmjit::x86::Xmm & r, const asmjit::x86::Xmm & lhs,const asmjit::x86::Xmm & rhs) const
        {
            co->movss(r, lhs);
            co->addss(r, rhs);
        }

        void sub(const asmjit::x86::Xmm & r, const asmjit::x86::Xmm & lhs,const asmjit::x86::Xmm & rhs) const
        {
            co->movss(r, lhs);
            co->subss(r, rhs);
        }

        void mul(const asmjit::x86::Xmm & r, const asmjit::x86::Xmm & lhs,const asmjit::x86::Xmm & rhs) const
        {
            co->movss(r, lhs);
            co->mulss(r, rhs);
        }

        void div(const asmjit::x86::Xmm & r, const asmjit::x86::Xmm & lhs,const asmjit::x86::Xmm & rhs) const
        {
            co->movss(r, lhs);
            co->divss(r, rhs);
        }

        void add(const asmjit::x86::Gp & r, const asmjit::x86::Gp & lhs,const asmjit::x86::Gp & rhs) const
        {
            co->mov(r, lhs);
            co->add(r, rhs);
        }

        void sub(const asmjit::x86::Gp & r, const asmjit::x86::Gp & lhs,const asmjit::x86::Gp & rhs) const
        {
            co->mov(r, lhs);
            co->sub(r, rhs);
        }

        void mul(const asmjit::x86::Gp & r, const asmjit::x86::Gp & lhs,const asmjit::x86::Gp & rhs) const // NOLINT
        {
            // use i32(lhs)*i32(rhs) -> (i8)r for byte or word
            if (r.isGpb() or rhs.isGpw())
            {
                const auto _lhs = i32();
                const auto _rhs = i32();
                const auto _r = i32();

                co->movzx(_lhs, lhs);
                co->movzx(_rhs, rhs);
                mul(_r, _lhs, _rhs);
                co->movzx(r, _r);
            } else
            {
            co->mov(r, lhs);
            co->imul(r, rhs);
            }
        }

        void div(const asmjit::x86::Gp & r, const asmjit::x86::Gp & lhs,const asmjit::x86::Gp & rhs) const // NOLINT
        {
            // use i32(lhs)/i32(rhs) -> (i8)r for byte or word
            if (r.isGpb() or rhs.isGpw())
            {
                const auto _lhs = i32();
                const auto _rhs = i32();
                const auto _r = i32();

                co->movzx(_lhs, lhs);
                co->movzx(_rhs, rhs);
                div(_r, _lhs, _rhs);
                co->movzx(r, _r);
            } else
            {
                co->xor_(r, r);
                co->idiv(r, lhs, rhs);

                if (r.isGp64())
                    co->mov(r, asmjit::x86::rax);
                else
                    co->mov(r, asmjit::x86::eax);
            }
           }

        void mod(const asmjit::x86::Gp & r, const asmjit::x86::Gp & lhs,const asmjit::x86::Gp & rhs) const // NOLINT
        {
            // use i32(lhs)%i32(rhs) -> (i8)r for byte or word
            if (r.isGpb() or rhs.isGpw())
            {
                const auto _lhs = i32();
                const auto _rhs = i32();
                const auto _r = i32();

                co->movzx(_lhs, lhs);
                co->movzx(_rhs, rhs);
                mod(_r, _lhs, _rhs); // NOLINT
                co->movzx(r, _r);
            } else
            {
                co->xor_(r, r);
                co->idiv(r, lhs, rhs);
            }
        }

        void increment(const asmjit::x86::Gp & r) const
        {
            co->inc(r);
        }

        void increment(const asmjit::x86::Xmm & r)
        {
            add(r, r, xmmss(1.0f));
        }

        void decrement(const asmjit::x86::Gp & r) const
        {
            co->dec(r);
        }

        void decrement(const asmjit::x86::Xmm & r)
        {
            sub(r, r, xmmss(1.0f));
        }

        void return_value(const asmjit::x86::Gp & r) const
        {
            if (signature.ret() != asmjit::TypeId::kInt64 and signature.ret() != asmjit::TypeId::kInt32 and signature.ret() != asmjit::TypeId::kInt16 and signature.ret() != asmjit::TypeId::kInt8)
                throw std::runtime_error(fmt::format("Return type, does not match function signature or inst supported {}", static_cast<int>(signature.ret())));
            co->ret(r);
        }

        void return_value(const asmjit::x86::Xmm & r) const
        {
            if (signature.ret() != asmjit::TypeId::kFloat64 and signature.ret() != asmjit::TypeId::kFloat32)
                throw std::runtime_error(fmt::format("Return type, does not match function signature or inst supported {}", static_cast<int>(signature.ret())));
            co->ret(r);
        }

        void return_void() const
        {
            if (signature.ret() != asmjit::TypeId::kVoid)
                throw std::runtime_error("Return type, does not match function signature");
            co->ret();
        }

        /// TODO: TEST[]
        void compare(const asmjit::x86::Gp & lhs,const asmjit::x86::Gp & rhs) const
        {
            co->cmp(lhs, rhs);
        }

        /// TODO: TEST[]
        void compare(const asmjit::x86::Xmm & lhs,const asmjit::x86::Xmm & rhs, const bool possible_equal = false) const
        {
            if(possible_equal)
               co->ucomiss(lhs, rhs);
            else
               co->comiss(lhs, rhs);
        }

        /// TODO: TEST[]
        void jump(const asmjit::Label& l) const
        {
            co->jmp(l);
        }

        /// TODO: TEST[X]
        void jump_equal(const asmjit::x86::Gp& t1, const asmjit::x86::Gp& t2, const asmjit::Label& l) const
        {
            compare(t1, t2);
            co->je(l);
        }

        /// TODO: TEST[]
        void jump_equal(const asmjit::x86::Xmm& t1, const asmjit::x86::Xmm& t2, const asmjit::Label& l) const
        {
            compare(t1, t2, true);
            co->je(l);
        }

        /// TODO: TEST[]
        void jump_not_equal(const asmjit::x86::Gp& t1, const asmjit::x86::Gp& t2, const asmjit::Label& l) const
        {
            compare(t1, t2);
            co->jne(l);
        }

        /// TODO: TEST[]
        void jump_not_equal(const asmjit::x86::Xmm& t1, const asmjit::x86::Xmm& t2, const asmjit::Label& l) const
        {
            compare(t1, t2, true);
            co->jne(l);
        }

        /// TODO: TEST[]
        void jump_lower(const asmjit::x86::Gp& t1, const asmjit::x86::Gp& t2, const asmjit::Label& l) const
        {
            compare(t1, t2);
            co->jl(l);
        }

        /// TODO: TEST[]
        void jump_lower(const asmjit::x86::Xmm& t1, const asmjit::x86::Xmm& t2, const asmjit::Label& l) const
        {
            compare(t2, t1);
            co->ja(l); // t2 > t1 -> t1 < t2
        }

        /// TODO: TEST[]
        void jump_lower_equal(const asmjit::x86::Gp& t1, const asmjit::x86::Gp& t2, const asmjit::Label& l) const
        {
            compare(t1, t2);
            co->jle(l);
        }

        /// TODO: TEST[]
        void jump_lower_equal(const asmjit::x86::Xmm& t1, const asmjit::x86::Xmm& t2, const asmjit::Label& l) const
        {
            compare(t2, t1);
            co->jnb(l); // !(t2 < t1) => !(t1 > t2) => t1 <= t2
        }

        /// TODO: TEST[]
        void jump_greater(const asmjit::x86::Gp& t1, const asmjit::x86::Gp& t2, const asmjit::Label& l) const
        {
            compare(t1, t2);
            co->jg(l);
        }

        /// TODO: TEST[]
        void jump_greater(const asmjit::x86::Xmm& t1, const asmjit::x86::Xmm& t2, const asmjit::Label& l) const
        {
            compare(t1, t2);
            co->ja(l);
        }

        /// TODO: TEST[]
        void jump_greater_equal(const asmjit::x86::Gp& t1, const asmjit::x86::Gp& t2, const asmjit::Label& l) const
        {
            compare(t1, t2);
            co->jge(l);
        }

        /// TODO: TEST[]
        void jump_greater_equal(const asmjit::x86::Xmm& t1, const asmjit::x86::Xmm& t2, const asmjit::Label& l) const
        {
            compare(t1, t2);
            co->jnb(l); // !(t1 < t2) => t1 >= t2
        }

        /// TODO: TEST[x]
        void move(const asmjit::x86::Gp& to, const asmjit::x86::Gp& from, const bool is_char = false) const
        {
            if(is_char)
                co->movzx(to, from);
            else
                co->mov(to, from);
        }

        /// TODO: TEST[x]
        void move(const asmjit::x86::Gp& to, const asmjit::x86::Mem& from, const bool is_char = false) const
        {
            if(is_char)
                co->movzx(to, from);
            else
                co->mov(to, from);
        }

        /// TODO: TEST[x]
        void move(const asmjit::x86::Xmm& to, const asmjit::x86::Xmm& from) const
        {
            co->movss(to, from);
        }

        /// TODO: TEST[x]
        void move(const asmjit::x86::Xmm& to, const asmjit::x86::Mem& from) const
        {
            co->movss(to, from);
        }

        /// TODO: TEST[x]
        void call(const asmjit::Imm& func, const asmjit::FuncSignature & signature, const std::vector<asmjit::x86::Reg> & args, const std::optional<asmjit::x86::Reg> & return_to) const
        {
            asmjit::InvokeNode * node = nullptr;
            if (args.size() != signature.argCount())
                throw std::invalid_argument("incorrect number of arguments");
            co->invoke(&node, func, signature);
            for (int i = 0; i < args.size(); i++)
            {
                if (not (args[i].isGp64() or args[i].isGp32()  or args[i].isGpb() or args[i].isXmm()))
                    throw std::invalid_argument(fmt::format("unsupported callee argument type for arg[{}]: {}", i, static_cast<int>(asmjit::x86::Reg::typeIdOf(args[i].type()))));
                if (args[i].isGpb() and signature.arg(i) != asmjit::TypeId::kInt8 or args[i].isGp64() and signature.arg(i) != asmjit::TypeId::kInt64 or args[i].isGp32() and signature.arg(i) != asmjit::TypeId::kInt32 or args[i].isXmm() and signature.arg(i) != asmjit::TypeId::kFloat32)
                    throw std::invalid_argument(fmt::format("incorrect callee argument type for arg[{}]: {}, expected: {}", i,static_cast<int>(asmjit::x86::Reg::typeIdOf(args[i].type())),static_cast<int>(signature.arg(i))));
                node->setArg(i, args[i]);
            }
            if (return_to)
            {
                if (not (return_to->isGp32() or return_to->isXmm()))
                    throw std::invalid_argument("unsupported callee return type");
                if (return_to->isGp32() and signature.ret() != asmjit::TypeId::kInt32 or return_to->isXmm() and signature.ret() != asmjit::TypeId::kFloat32)
                    throw std::invalid_argument(fmt::format("incorrect callee return type for {}, expected: {}", static_cast<int>(asmjit::x86::Reg::typeIdOf(return_to->type())),static_cast<int>(signature.ret())));
                node->setRet(0, *return_to);
            }
        }

        template <typename FT>
        FT* build()
        {
            if (function)
                throw std::runtime_error("Function already built");
            co->endFunc();
            co->finalize();
            if (const asmjit::Error e = rt->add(&function, &*code))
            {
                throw std::runtime_error(fmt::format("Error {}", asmjit::DebugUtils::errorAsString(e)));
            }
            return static_cast<FT*>(function);
        }
    };

    inline std::shared_ptr<function_builder> function_builder::create(const std::shared_ptr<asmjit::JitRuntime> & rt, const bool & logger)
    {
        return create(rt, asmjit::FuncSignature::build<void>(), logger);
    }

    inline std::shared_ptr<function_builder> function_builder::create(const std::shared_ptr<asmjit::JitRuntime> & rt, const asmjit::FuncSignature & signature, const bool & logger)
    {
        auto func = std::make_shared<struct function_builder>();
        func->rt = rt;
        func->signature = signature;
        func->code = std::make_shared<asmjit::CodeHolder>();

        func->code->init(rt->environment(), rt->cpuFeatures());

        func->co = std::make_unique<asmjit::x86::Compiler>(&*func->code);
        if (logger)
            func->code->setLogger(&func->logger);
        func->node = func->co->addFunc(func->signature);
        return func;
    }

}
