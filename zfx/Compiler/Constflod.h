//
// Created by admin on 2022/7/3.
//
#pragma once
#include "ValueTracking.h"
namespace zfx {
    namespace Compile {
        struct Constant {
            enum class Type {
                Type_Unknown,
                Type_Nil,
                Type_Number
            };

            Type type;
            union {

            };
        };

        void foldConstants() {

        }
    }
}
