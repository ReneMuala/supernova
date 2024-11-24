# Super Nova
A generic language VM based on [Caracol](https://github.com/renemuala), with a focus on multithreading and stability.

## How it looks

> Simple program

```c++
#include <caracol.hpp>

using namespace caracol;
int main(){
    int a = 5;
    int b;
    int c;

    caracol::vm<20> vm;
    int64_t insn[] = {
        // b = 10
        SET, addr(b),10,
        // c = a + b
        ADD32I, addr(c), addr(a), addr(b),
        HALT
    };
    vm.set_pc(vm.size-sizeof(insn)/sizeof(int64_t));
    vm.write(vm.size-sizeof(insn)/sizeof(int64_t), (void*)&insn, sizeof(insn));
    vm.start();
    // c is now: 15
    std::cout << "c is now: " << c << std::endl;
}

```


## Getting started

### Prerequisites

Depending on your operating system, you'll need the following tools to build and run Super Nova:

|   OS    |           Tools            |
|:-------:|:--------------------------:|
| Windows |    Visual Studio, XMAKE    |
|  *nix   | XMAKE and a c++23 compiler |

### Building 

To build the Super Nova VM and its associated tests, follow these steps:

1. Install the necessary prerequisites for your operating system.
2. Run `xmake build` in the project directory.
3. The compiled binaries, `snova` (the VM) and `snova-tests` (the tests), will be located in the `build/OS/ARCH/release` directory.
