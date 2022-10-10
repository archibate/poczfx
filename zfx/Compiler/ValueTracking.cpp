//
// Created by admin on 2022/7/5.
//

#include "ValueTracking.h"
#include <unordered_map>
namespace zfx {
    namespace Compile {
        struct ValueVisitor {
            std::unordered_map<> globals;
            std::unordered_map<> variables;
            ValueVisitor() : {

            }

            //然后就是各种visit函数
        };
    }
}
