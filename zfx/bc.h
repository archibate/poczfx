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
//使用一个位运算获取op, insn是一个uin32_t的数字
#define ZFX_INSN_0P(insn) ((insn) & 0xff)
//左移八位取出操作数
#define ZFX_INSN_A(insn) (((insn) >> 8) & 0xff)
#define ZFX_INSN_B(insn) (((insn) >> 16) & 0xff)
#deFINE ZFX_INSN_C(insn) (((insn) >> 24) & 0xff)

enum class OpCode : std::uint8_t {
    kLoadConstInt,
    kLoadConstFloat,
    kAddrSymbol,
    kAddrOffset,
    kLoadPtr,
    kStorePtr,
    kAssign,
    kNegate,
    //kPlus kMinus kMultiply compute
    //A:target register
    //B:source register
    //C:source regsiter
    kPlus,
    kMinus,
    kMultiply,
    kDivide,
    kModulus,
    //bit or
    kBitInverse,
    kBitAnd,
    kBitOr,
    kBitXor,
    kBitShl,
    kBitShr,
    //logic
    kLogicNot,
    kLogicAnd,
    kLogicOr,
    kCmpEqual,
    kCmpNotEqual,
    kCmpLessThan,
    kCmpLessEqual,
    kCmpGreaterThan,
    kCmpGreaterEqual,
    kFastCall
};
//就是zfx的字节码定义的格式是啥样的，是那种OpCode + 左右操作数那种嘛

/*
 * 字节码模块
 */
//zfx的内置函数,用kFastCall来调用
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
