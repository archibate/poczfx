#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <any>
/*
 *这里是zfx字节码的定义，builder 字节码的在另一个文件ByteCodeBuilder.h文件中
 * */
namespace zeno::zfx {
/*
 * zfx 虚拟机的指令格式就暂时先参考lua op(指令) A B C(操作数)
 * */
//我想把OpCode大小设置为uin8_t，那这样指令Op A B C 总共为32字节
enum class OpCode : std::uint8_t {
    kLoadConstInt,
    kLoadConstFloat,
    kAddrSymbol,
    kAddrOffset,
    kLoadPtr,
    kStorePtr,
    kAssign,
    kNegate,
    kPlus,
    kMinus,
    kMultiply,
    kDivide,
    kModulus,
    kBitInverse,
    kBitAnd,
    kBitOr,
    kBitXor,
    kBitShl,
    kBitShr,
    kLogicNot,
    kLogicAnd,
    kLogicOr,
    kCmpEqual,
    kCmpNotEqual,
    kCmpLessThan,
    kCmpLessEqual,
    kCmpGreaterThan,
    kCmpGreaterEqual,
};
//就是zfx的字节码定义的格式是啥样的，是那种OpCode + 左右操作数那种嘛

/*
 * 字节码模块
 */
//zfx的内置函数
    enum class BuiltinFunction {
        ZFX_MATH_SIN,
        ZFX_MATH_COS,
        ZFX_MATH_TAN,
        ZFX_MATH_ASIN,
        ZFX_MATH_ACOS,
        ZFX_MATH_ATAN,
        ZFX_MATH_EXP,
        ZFX_MATH_LOG,
        ZFX_MATH_FLOOR,
        ZFX_MATH_CEIL,
        ZFX_MATH_ATAN2,
        ZFX_MATH_POW
    };

    //定义一些有用的宏，用来获取op a, b, c
    #define ZFX_INSN_0P(insn)

    #define ZFX_INSN_A(insn)
    #define ZFX_INSN_B(insn)
    #deFINE ZFX_INSN_C(insn)
}
