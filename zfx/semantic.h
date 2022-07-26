//
// Created by admin on 2022/7/26.
//
//语义分析主要做这些功能比如最基本的引用消解， 类型检查
//比如我在开头定义了一个@a，那么我在parser的时候会将a : value作为一个map加入到全局的符号表中去，后续有运算的话载更新一下map


#pragma once
#include "scope.h"
#include "parser.h"
#include <memory>

namespace zfx {

    class Enter {
    public:
        std::shared_ptr<Scope> scope;//目前zfx只有一个作用域,后续如果有{}，那每进一个{}就创建一个作用域
        /*
         * 把所有@和$声明都加入到符号表中去
         * */
        std::any visitVariableDecl() {
            //先查找当前作用域是否有这一个符号
            auto currentScope = this->scope;
            if () {

            }
            //没有就加入当前符号表

            return std::any();
        }
    };


}