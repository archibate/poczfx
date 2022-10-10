//
// Created by admin on 2022/7/7.
//
#include "../bc.h"
#include "Builtin.h"

namespace zfx {
    namespace Compile {

        Builtin getBuiltin() {

        }
        int getBuiltinFunctionId(const Builtin& builtin) {
            if (builtin.empty()) {
                return -1;
            }
//zfx不需要global函数
            if (builtin.object == "math") {
                if ()
            }
            return -1;
        }
    }
}