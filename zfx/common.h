//
// Created by admin on 2022/8/12.
//

#pragma once

#include <iostream>
#include <type_traits>
#include <string>
#include <any>
#include <typeinfo>

namespace zeno::zfx {
    template<typename T>
    bool isType(const std::any &a) {
        return typeid(T) == a.type();
    }


}
