#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <memory>
#include "span.h"
#include "enumtools.h"
#include <string_view>
#include "ZFXCode.h"
#include "Object.h"
#include "bc.h"
/*
 * zfx虚拟机字节码解释执行函数
 * */
namespace zeno::zfx {
/*
struct ZFXExec {
    span<std::uint32_t const> codes;
    std::vector<Object> regtab;
    std::vector<Object> symtab;
    std::uint32_t *ptrreg{};

    explicit ZFXExec(ZFXCode const &co) noexcept
        : codes{co.codes}
        , regtab(co.nregs)
        , symtab(co.syms.size())
    {}

    void execute() {
        int *const regi = reinterpret_cast<int *>(regtab.data());
        float *const regf = reinterpret_cast<float *>(regtab.data());

        std::uint32_t const *ip = codes.begin();
        while (ip != codes.end()) {
            Bc bc{*ip++};
            switch (bc) {

                case Bc::kLoadConstInt:
                {
                    std::uint32_t regid = *ip++;
                    std::uint32_t val = *ip++;
                    regtab[regid] = Object{bit_cast<int>(val)};
                } break;

                case Bc::kLoadConstFloat:
                {
                    std::uint32_t regid = *ip++;
                    std::uint32_t val = *ip++;
                    regtab[regid] = Object{bit_cast<float>(val)};
                } break;

                case Bc::kAssign:
                {
                    std::uint32_t reg1 = *ip++;
                    std::uint32_t reg2 = *ip++;
                    regtab[reg1] = regtab[reg2];
                } break;

                case Bc::kNegate:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    regtab[reg0] = -regtab[reg1];
                } break;

                case Bc::kPlus:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    std::uint32_t reg2 = *ip++;
                    regi[reg0] = regi[reg1] + regi[reg2];
                } break;

                case Bc::kMinus:
                {
                    std::uint32_t reg0 = *ip++;
                    std::uint32_t reg1 = *ip++;
                    std::uint32_t reg2 = *ip++;
                    regi[reg0] = regi[reg1] - regi[reg2];
                } break;

                default: break;
            }
        }
    }
};
*/

static void zfx_execute(zfx_State* l) {
    //接下来就是一串死循环

}

}
