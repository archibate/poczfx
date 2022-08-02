//
// Created by admin on 2022/8/2.
//
#pragma once
#include "ast.h"
#include <iostream>
#include <variant>
#include <any>

namespace zeno::zfx {
    //字节码
    enum class OpCode {

    };

    class BCModule {
        //常量池
    public:
        std::vector<std::any> consts;

        //将内置函数加入到常量池

    };

    class BCModulesDumper {

    };

    //字节码生成程序。从AST中遍历即可
    class BCGenerator : public AstVisitor {
    public:
        std::shared_ptr<BCModule> m;

    };
}
