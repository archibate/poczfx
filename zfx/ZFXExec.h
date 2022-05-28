#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <memory>
#include "span.h"
#include <string_view>
#include "ZFXCode.h"
#include "bc.h"

namespace zeno::zfx {

struct ZFXExec {
    span<std::uint32_t const> codes;
    std::vector<std::uint32_t> regtab;
    span<std::uint32_t *const> symtab;
    std::uint32_t *ptrreg{};

    explicit ZFXExec(ZFXCode const &co) noexcept
        : codes{co.codes}
        , regtab(co.nregs)
        , symtab{co.symtab}
    {}

    void execute() {
        auto regi = reinterpret_cast<int *>(regtab.data());
        auto regf = reinterpret_cast<float *>(regtab.data());

        auto ip = codes.begin();
        while (ip != codes.end()) {
            Bc bc{*ip++};
            switch (bc) {

                case Bc::kLoadConst:
                {
                    std::uint32_t regid = *ip++;
                    std::uint32_t val = *ip++;
                    regtab[regid] = val;
                } break;

                case Bc::kAddrSymbol:
                {
                    std::uint32_t symid = *ip++;
                    ptrreg = symtab[symid];
                } break;

                case Bc::kAddrOffset:
                {
                    std::uint32_t regid = *ip++;
                    ptrreg += regtab[regid];
                } break;

                case Bc::kLoadPtr:
                {
                    std::uint32_t regid = *ip++;
                    regtab[regid] = *ptrreg;
                } break;

                case Bc::kStorePtr:
                {
                    std::uint32_t regid = *ip++;
                    *ptrreg = regtab[regid];
                } break;

                case Bc::kAssign:
                {
                    std::uint32_t reg1 = *ip++;
                    std::uint32_t reg2 = *ip++;
                    regtab[reg1] = regtab[reg2];
                } break;

                case Bc::kNegateInt:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    regi[reg0] = -regi[reg1];
                } break;

                case Bc::kNegateFloat:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    regf[reg0] = -regf[reg1];
                } break;

                case Bc::kPlusInt:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    std::uint32_t reg2 = *ip++;
                    regi[reg0] = regi[reg1] + regi[reg2];
                } break;

                case Bc::kPlusFloat:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    std::uint32_t reg2 = *ip++;
                    regf[reg0] = regf[reg1] + regf[reg2];
                } break;

                case Bc::kMinusInt:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    std::uint32_t reg2 = *ip++;
                    regi[reg0] = regi[reg1] - regi[reg2];
                } break;

                case Bc::kMinusFloat:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    std::uint32_t reg2 = *ip++;
                    regf[reg0] = regf[reg1] - regf[reg2];
                } break;

                default: break;
            }
        }
    }
};

}
