#include <caracol.hpp>
#include <gtest/gtest.h>
//
// Created by dte on 11/24/2024.
//

TEST(VM, SET)
{
    using namespace caracol;

    int a = 5;

    caracol::vm<20> vm;
    int64_t insn[] = {
        SET, addr(a),10,
        SET, vm(0), 100,
        HALT
    };
    vm.set_pc(vm.size-sizeof(insn)/sizeof(int64_t));
    vm.write(vm.size-sizeof(insn)/sizeof(int64_t), (void*)&insn, sizeof(insn));
    vm.start();
    ASSERT_EQ(a, 10);
    ASSERT_EQ(*vm.fetch(0), 100);
}


int main()
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}