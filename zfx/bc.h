#pragma once

#include <cstdint>

namespace zeno::zfx {

enum class Bc : std::uint32_t {
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

}
