//
// Created by admin on 2022/7/7.
//
#include "../bc.h"
#include "Builtin.h"

namespace zfx {
    namespace Compile {
        int getBuiltinFunctionId(const Builtin& builtin) {
            if (builtin.empty()) {
                return -1;
            }
//zfx不需要global函数
            if()
        }
    }
}