#pragma once

#include <cstring>
#include <iostream>
#include <ostream>
#include <math.h>
namespace caracol {
/// @brief Enumeration of instructions supported by the virtual machine
enum Instruction {
  /// 0 <- 1 = 2
  EQ32I,
  /// 0 <- 1 = 2
  EQ32F,
  /// 0 <- 1 > 2
  GT32I,
  /// 0 <- 1 > 2
  GT32F,
  /// 0 <- 1 < 2
  LT32I,
  /// 0 <- 1 < 2
  LT32F,
  /// 0 <- 1 >= 2
  GE32I,
  /// 0 <- 1 >= 2
  GE32F,
  /// 0 <- 1 <= 2
  LE32I,
  /// 0 <- 1 <= 2
  LE32F,

  /// 0 <- 1 && 2
  AND,
  /// 0 <- 1 || 2
  OR,
  /// 0 <- 1 + 2
  ADD32F,
  /// 0 <- 1 - 2
  SUB32F,
  /// 0 <- 1 * 2
  MUL32F,
  /// 0 <- 1 / 2
  DIV32F,

  /// 0 <- 1 + 2
  ADD32I,
  /// 0 <- 1 - 2
  SUB32I,
  /// 0 <- 1 * 2
  MUL32I,
  /// 0 <- 1 / 2
  DIV32I,
  SET,
  PRINT32I,
  PRINT32F,
  PRINTC,
  PRINTB,
  PRINTS,

  // $PC = 0
  JUMP,
  // IF(1) $PC = 0
  JUMP_IF,
  // $PC += 0
  JUMP_REL,
  // IF(1) $PC += 0
  JUMP_REL_IF,

  PUSH,
  PUSHP,
  POP,
  POPP,
  //
  // INCR,
  // DECR,
  //
  // MODE,
  HALT,
};

  /**
  * @brief Returns the address of a variable
  *
  * @param var the variable to get the address from
  *
  * @warning for arrays and cstr pass the first value (by prefix an *)
*/
  template<typename T>
  constexpr inline int64_t addr(T & var)
  {
    return int64_t(&var);
  }

/**
 * @brief Template class representing a virtual machine
 *
 * @tparam int64_t The data type for the memory blocks and instructions
 * @tparam memory_size The size of the memory in terms of the number of
 * `int64_t` elements
 * @tparam integer_type The data type for integer operations (default is
 * `int64_t`)
 */
template <unsigned long long memory_size>
class vm {
private:
  int64_t memory[memory_size] = {};
  int64_t $PC{0}, $SP{memory_size-1}, SP_LIMIT{0};

public:
  const int64_t size = memory_size;
  [[nodiscard]] int64_t operator()(const unsigned long long & index) const
  {
    return (int64_t)&memory[index];
  };
  /**
   * @brief Set the program counter
   *
   * @param pc The new value for the program counter
   */
  inline void set_pc(const int & pc) { $PC = pc; }

  /**
   * @brief Set the stack pointer
   *
   * @param sp The new value for the stack pointer
   */
  inline void set_sp(const int & sp) { $SP = sp; }

  /**
   * @brief Verify if there is enough space on the stack for a push operation
   *
   * @param size The size of the data to be pushed (default is
   * `sizeof(int64_t)`)
   */
  inline void verify_sp_for_push(const int &size = sizeof(int64_t)) const
  {
    if ($SP <= SP_LIMIT) {
      std::cerr
          << "[stack overflow]:\n- descr: the process exceed the upper stack "
             "limit, this means that there is no memory available to push (L = "
          << SP_LIMIT << ")\nMachine registers:\n- $PC = " << $PC
          << "\n- $SP = " << $SP << "\n";
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Verify if there is enough data on the stack for a pop operation
   *
   * @param size The size of the data to be popped (default is
   * `sizeof(int64_t)`)
   */
  inline void verify_sp_for_pop(const int &size = sizeof(int64_t)) const
  {

    if ($SP+1 >= memory_size) {
      std::cerr
          << "[stack underflow]:\n- descr: the process exceed the lower stack "
             "limit (L = "
          << memory_size
          << "), this means that more pops than pushes where "
             "done\nMachine registers:\n- $PC = "
          << $PC << "\n- $SP = " << $SP << "\n";
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Get a pointer to the memory location at the given address
   *
   * @param addr The memory address
   * @return int64_t* A pointer to the memory location
   */
  inline constexpr int64_t *fetch(const unsigned long long addr) {
    if (addr < memory_size) {
      return &memory[addr];
    } else {
      std::cerr << "[invalid address]:\n- descr: the process tried to access "
                   "an invalid "
                   "memory address "
                << addr << "\nMachine registers:\n- $PC = " << $PC
                << "\n- $SP = " << $SP << "\n";
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Write a block of data to the memory
   *
   * @param index The starting index in the memory
   * @param val The value to be written
   */
  inline void write(const int & index, const int64_t & val) {
    if (index + sizeof(int64_t) <= memory_size) {
      if (index + 1 > SP_LIMIT)
        SP_LIMIT = index;
      *fetch(index) = val;
    } else {
      perror("No enough memory to write_block");
      exit(EXIT_FAILURE);
    }
  }

//   /**
//    * @brief Write an array of blocks to the memory
//    *
//    * @param index The starting index in the memory
//    * @param data A pointer to the array of blocks
//    * @param size The size of the array
//    */
//   inline void constexpr write(int index, int64_t *data,
//                                           int size) {
//     if (index + size <= memory_size) {
//       if (index + size > SP_LIMIT)
//         SP_LIMIT = index + size;
//       memcpy(memory + index, data, size * sizeof(int64_t));
//     } else {
//       perror("No enough memory to write");
//       exit(EXIT_FAILURE);
//     }
//   }

  /**
   * @brief Write raw data to the memory
   *
   * @param index The starting index in the memory
   * @param data A pointer to the raw data
   * @param size The size of the data
   */
  inline void constexpr write(int index, const void *data, const int size) {
    if (size <= (memory_size - index) * sizeof(int64_t)) {
      if (index + size > SP_LIMIT)
        SP_LIMIT = index + size;
      memcpy(memory + index, data, size);
    } else {
      perror("No enough memory to write");
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Start executing the instructions in the memory
   */
  inline constexpr void start() {
    // constexpr int memblock_size = sizeof(int64_t);
    while (true) {
      switch ((Instruction)*fetch($PC)) {
      case HALT:
        return;
      case EQ32I:
        *(bool*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) == *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case EQ32F:
        *(bool*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) == *(float*)*fetch($PC + 3);
        $PC += 4;
        break;
      case GT32I:
        *(bool*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) > *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case GT32F:
        *(bool*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) > *(float*)*fetch($PC + 3);
        $PC += 4;
        break;
      case LT32I:
        *(bool*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) < *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case LT32F:
        *(bool*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) < *(float*)*fetch($PC + 3);
        $PC += 4;
        break;
      case GE32I:
        *(bool*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) >= *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case GE32F:
        *(bool*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) >= *(float*)*fetch($PC + 3);
        $PC += 4;
        break;
      case LE32F:
        *(bool*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) <= *(float*)*fetch($PC + 3);
        $PC += 4;
        break;
      case LE32I:
        *(bool*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) <= *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case ADD32I:
        *(int32_t*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) + *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case SUB32I:
        *(int32_t*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) - *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case MUL32I:
        *(int32_t*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) * *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case DIV32I:
        *(int32_t*)*fetch($PC + 1) =
          *(int32_t*)*fetch($PC + 2) / *(int32_t*)*fetch($PC + 3);
        $PC += 4;
        break;
      case AND:
        *(bool*)*fetch($PC + 1) =
          *(bool*)*fetch($PC + 2) and *(bool*)*fetch($PC + 3);
        $PC += 4;
        break;
      case OR:
        *(bool*)*fetch($PC + 1) =
          *(bool*)*fetch($PC + 2) or *(bool*)*fetch($PC + 3);
        $PC += 4;
        break;
      case ADD32F:
        *(float*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) + *(float*)*fetch($PC + 3);
        $PC += 4;
        break;
      case SUB32F:
        *(float*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) - *(float*)*fetch($PC + 3);
        $PC += 4;
        break;
      case MUL32F:
        *(float*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) * *(float*)*fetch($PC + 3);
        $PC += 4;
        break;
      case DIV32F:
        *(float*)*fetch($PC + 1) =
          *(float*)*fetch($PC + 2) / *(float*)*fetch($PC + 3);;
        $PC += 4;
        break;
      case SET:
        *(int64_t*)*fetch($PC + 1) = *fetch($PC + 2);
        $PC += 3;
        break;
       case PRINT32I:
         std::cout << *(int32_t*)*fetch($PC + 1);
         $PC += 2;
         break;
       case PRINT32F:
         std::cout << *(float*)*fetch($PC + 1);
         $PC += 2;
         break;
      case PRINTS:
        std::cout << (char*)*fetch($PC + 1);
        $PC += 2;
        break;
      case PRINTC:
        std::cout << *(char*)(*fetch($PC + 1));
        $PC += 2;
        break;
      case PRINTB:
        std::cout << (*(bool*)(*fetch($PC + 1)) ? "true" : "false");
        $PC += 2;
        break;
      case JUMP:
        $PC = *fetch($PC + 1);
        break;
      case JUMP_IF:
        if(*(bool*)*fetch($PC + 2))
          $PC = *fetch($PC + 1);
        else
          $PC += 3;
        break;
      case JUMP_REL:
        $PC += *fetch($PC + 1);
        break;
      case JUMP_REL_IF:
        if(*(bool*)*fetch($PC + 2))
          $PC += *fetch($PC + 1);
        else
          $PC += 3;
        break;
      case PUSH:
        verify_sp_for_push();
        *fetch($SP--) = *fetch($PC + 1);
        $PC += 2;
        break;
      case POP:
        verify_sp_for_pop();
        *fetch($PC+1) = *fetch(++$SP);
        $PC += 2;
        break;
      case PUSHP:
        verify_sp_for_push();
        *fetch($SP--) = *(int64_t*)*fetch($PC + 1);
        $PC += 2;
        break;
      case POPP:
        verify_sp_for_pop();
        *(int64_t*)*fetch($PC+1) = *fetch(++$SP);
        $PC += 2;
        break;
        /*
       case JLT:
         if (*fetch($PC + 1) < *fetch($PC + 2))
           $PC = (int64_t)*fetch($PC + 3);
         else
           $PC += 4;
         break;
       case JLE:
         if (*fetch($PC + 1) <= *fetch($PC + 2))
           $PC = (int64_t)*fetch($PC + 3);
         else
           $PC += 4;
         break;
       case JGE:
         if (*fetch($PC + 1) >= *fetch($PC + 2))
           $PC = (int64_t)*fetch($PC + 3);
         else
           $PC += 4;
         break;
       case JGT:
         if (*fetch($PC + 1) > *fetch($PC + 2))
           $PC = (int64_t)*fetch($PC + 3);
         else
           $PC += 4;
         break;
       case JMP:
         $PC = (int64_t)*fetch($PC + 3);
         break;
       case RJLT:
         if (*fetch($PC + 1) < *fetch($PC + 2))
           $PC += (int64_t)*fetch($PC + 3);
         else
           $PC += 4;
         break;
       case RJLE:
         if (*fetch($PC + 1) <= *fetch($PC + 2))
           $PC += (int64_t)*fetch($PC + 3);
         else
           $PC += 4;
         break;
       case RJGE:
         if (*fetch($PC + 1) >= *fetch($PC + 2))
           $PC += (int64_t)*fetch($PC + 3);
         else
           $PC += 4;
         break;
       case RJGT:
         if (*fetch($PC + 1) > *fetch($PC + 2))
           $PC += (int64_t)*fetch($PC + 3);
         else
           $PC += 4;
         break;
       case RJMP:
         $PC += (int64_t)*fetch($PC + 3);
         break;

       case INCR:
         *fetch($PC + 1) += 1;
         $PC += 2;
         break;
       case DECR:
         *fetch($PC + 1) -= 1;
         $PC += 2;
         break;
       case PUSH:
         verify_sp_for_push();
         *fetch($SP) = *fetch($PC + 1);
         $SP -= memblock_size;
         $PC += 2;
         break;
       case PUSHP:
         verify_sp_for_push();
         *fetch($SP) = *fetch(*fetch($PC + 1));
         $SP -= memblock_size;
         $PC += 2;
         break;
       case POP:
         verify_sp_for_pop();
         $SP += memblock_size;
         *fetch($PC + 1) = *fetch($SP);
         $PC += 2;
         break;
       case POPP:
         verify_sp_for_pop();
         $SP += memblock_size;
         *fetch(*fetch($PC + 1)) = *fetch($SP);
         $PC += 2;
         break;
       case Instruction::MODE:
         this->MODE = *fetch($PC + 1);
         $PC += 2;
         break;
         */
      default:
        std::cerr << "[illegal instruction at: " << $PC << " ]" << std::endl;
        return;
      }
    }
  }
};

} // namespace caracol
