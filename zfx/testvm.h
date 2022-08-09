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
#include <memory>

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

        FunctionSymbol functionSym;

        BCGenerator() {
            this->m = std::make_shared<BCModule>();
        }

        std::vector<uint8_t> anyToCode(const std::any &val) {
            if (val.has_value()) {
                //需要加一个判断条件val是否转成uint8_t类型
                return std::any_cast<std::vector<uint8_t>(val)>;
            }

            return {}
        }

        void concatCodeWithAny(std::vector<uint8_t> &code, std::any &val) {
            if() {

            }
        }

        /*
         * @param 主函数prog
         * */
        std::any visit(Prog &prog) {
            this->functionSym = prog.sym;//设置函数符号
            if (this->functionSym != nullptr) {
                this->m.consts.push_back(this->functionSym);
                //设置主函数
            }

            return this->m;
        }

        std::any visitBlock(Block &block) {
            std::vector<uint8_t> ret;
            //开始遍历Block中的每一条statement
            for (auto &x : ) {

            }

            return ret;
        }

        std::any visitFunctionDecl(FunctionDecl &decl) {
            //1.设置当前函数符号

            //
        }

        std::any visitVariableDecl(VariableDecl &decl) {
            std::vector<uint8_t> code;


            return code;
        }

        //为返回语句生成
        std::any visitReturnStatement(RetuanStatement returnStatement) {

        }

        std::any visitFunctionCall(FunctionCall &functionCall) {
            std::vector<uint8_t> code;
        }

        /*
         * 为if语句生成字节码,难点在于分支语句的跳转需要修改
         * */
        std::any visitIfStatement(IfStatement &ifStatement) {
            std::vector<uint8_t> code;


            return code;
        }

        std::any visitForStatement(ForStatement &forStatement) {
            std::vector<uint8_t> code;

            return code;
        }

        /*
         * 在跳转地址上添加偏移量
         * @param code
         * @param offset
         * */
        void addOfferSetToJump(std::vector<uint8_t> &code, uint32_t offset) {
            if (offset == 0) {
                return;
                //如果便宜量为0，那就直接短路
            }
        }

        /*
         *生成获取本地变量值的指令
        */
        std::any getVariableValue(VarSymbol &varSymbol) {
            std::vector<uint8_t> code;


            return code;
        }

        std::any setVariableValue(VarSymbol &symbol) {

        }

         /*
          * 简单的生成常量入栈的指令
          * */
        std::any visitIntegerLiteral(IntegerLiteral &literal) {
            std::vector<uint8_t> code;
            return code;
        }

        /*
         * 生成将字符串压入常量池中的指令
         * */
        std::any visitStringLiteral(StringLiteral &stringLiteral) {
            std::vector<uint8_t> code;
            //this->m.consts.push_back(stringLiteral.value)
            //code.push_back(OpCode::sldc);
            return code;
        }
        //遇到浮点数加入到常量池中去
        std::any visitBinary(Binary &bi) {
            std::vector<uint8_t> code;


            return code;
        }

        std::any visitUnary(Unary &u) {
            std::vector<uint8_t> code;


            return code;
        }
    };


    class VM {
    public:

    };

    //函数栈帧
    class StackFrame {
    public:
        //对应函数
        FunctionSymbol functionSymbol;

        std::uint32_t returnIndex;

        //函数的本地变量
        std::vector<uint32_t> localVars;

        //函数的操作数栈
    };

    //从bcModule生成字节码
    class BCModuleWriter {
    public:


        /*
         * 从BCModule生成字节码
         * */

    private:
        
    };
}
