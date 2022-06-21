#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <any>

namespace zeno::zfx {

enum class OpCode : std::uint32_t {
    kLoadConstInt,
    kLoadConstFloat,
    kAddrSymbol,
    kAddrOffset,
    kLoadPtr,
    kStorePtr,
    kAssign,
    kNegate,
    kPlus,
    kMinus,
    kMultiply,
    kDivide,
    kModulus,
    kBitInverse,
    kBitAnd,
    kBitOr,
    kBitXor,
    kBitShl,
    kBitShr,
    kLogicNot,
    kLogicAnd,
    kLogicOr,
    kCmpEqual,
    kCmpNotEqual,
    kCmpLessThan,
    kCmpLessEqual,
    kCmpGreaterThan,
    kCmpGreaterEqual,
};
/*
 * 字节码模块
 */

    class BCModule {
    public:
        std::vector<std::any> consts;//常量将基本的浮点数和自定义函数设置为常量
//存放常量池内容


    };
    /*
     * 用来打印调试信息
     * */
    class BCModule {

    };
    /*
     * 字节码生成程序，先直接遍历ast或者IR生成字节码,我想增加一个AstVisitor，BCGenerator直接继承AstVisitor
     * */
    class BCGenerator {
    public:
        std::shared_ptr<BCModule> module;

        BCGenerator() {
            this->m = std::make_shared<BCModule>();
        }

        /*
         * 用于zfx中变量的声明，但是新版zfx到底支持几种变量
         *声明前判断一下是否带有初始化，如果有则要多一个赋值指令KAssign
         * @param VariableDecl (变量声明)
         * */
        std::any visitVariableDecl() {
            std::vector<std::uint32_t> code;


            return code;
        }

        /*
         *@param
         * */
        std::any visitBinary() {
            std::vector<std::uint32_t> code;
             /*
              * 如果是赋值操作
              * */

        }

        std::any visitUnary() {
            std::vector<std::uint32_t> code;

            return code;
        }

        std::any visitTernary() {

        }

        std::any visitInter
    };

    /*
     *
     * */

    class OprandStack {

    };

    class StackFrame {

    };

    /*
     * 从BCModule 生成字节码
     * */
}
