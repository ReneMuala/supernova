#include <cstdint>
#include "caracol.hpp"
using namespace caracol;



int main(int argc, char** argv) {
    int8_t end = 10;
    int a = 20;
    int b = 10;
    int c;
    bool x = true;
    bool y = false;
    bool z;
    auto val = 3.14159265358979323846;
    caracol::vm<3000> vm;
    /* clang-format off */
    int64_t insn[] = {
        AND, addr(z), addr(x), addr(y),
        PRINTB, addr(z),
        OR, addr(z), addr(x), addr(y),
        PRINTB, addr(z),
        ADD32I, addr(c), addr(a), addr(b),
        PRINT32I, addr(c),
        PRINT32I, addr(a),
        PRINT32I, vm(1),
        SUB32I, vm(2), vm(1), addr(a),
        PRINT32I, vm(2),
        // PRINTS, addr(*name),
        // PRINT32I, vm(2),
        // LOAD, 8, 10,
        // PRINT32F, 0,
        // PRINTC, 8,
        // PRINT32F, 4,
        // DIV32F, 0,4,
        // PRINTC, 8,
        // PRINT32F, 0,
        // LOAD, 0, 0,
        // LOAD, 1, end,
        // PRINTi32, 0,
        // INCR, 0,
        // RJLE, 0, 1, -4,
        HALT,
    };
    /* clang-format on */
    vm.set_pc(vm.size-sizeof(insn)/sizeof(int64_t));
    // float a = 3.14159;
    // float b = 2.71828;
    // vm.write(0, (void*)&a, sizeof(a));
    // vm.write(4, (void*)&b, sizeof(b));
    vm.write(vm.size-sizeof(insn)/sizeof(int64_t), (void*)&insn, sizeof(insn));
    vm.start();

    // std::cout << "\na: " << a << std::endl;
    return 0;
}
