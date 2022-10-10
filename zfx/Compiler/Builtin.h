//
// Created by admin on 2022/7/7.
//

#pragma once
#include <string_view>
namespace zfx {
    namespace Compile {
        struct Builtin {
            std::string_view object;
            std::string_view method;//内置对象方法

            bool empty() const {
                return object.empty() && method.empty();
            }

            //留下几个方法去判断
        };

        //需要传一个ast节点，一个变量map
        Builtin getBuiltin() ;

    }
}
