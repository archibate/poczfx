//
// Created by admin on 2022/8/2.
//
/*
 * 生成字节码其实大致思路和老版zfx EmitAssembly差不多都是采用visit模式
 * */
#pragma once
#include "ast.h"
#include <iostream>
#include <variant>
#include <any>
#include <vector>
namespace zeno::zfx {
    //字节码
    enum class OpCode {

    };

    class BCModule {
        //常量池
    public:
        std::vector<std::any> consts;
        //将内置函数,字符串浮点数等加入到常量池中去

        BCModule() {
            for () {
                //将内置函数加入到常量池中去
            }
        }

    };

    //打印字节码用来调试
    class BCModulesDumper {

    };

    //字节码生成程序。从AST中遍历即可
    class BCGenerator : public AstVisitor {
    public:
        std::shared_ptr<BCModule> m;

        BCGenerator() {
            this->m = std::make_shared<BCModule>();
        }

        std::vector<uint8_t> anyToCode() {

        }

        void concatCodeWithAny(std::vector<uint8_t> &code, std::any &val) {
            if() {

            }
        }
    };
}
