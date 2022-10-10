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

        std::shared_ptr<FunctionSymbol> main_;//入口函数也是主函数
        BCModule() {
            for () {
                //在symbol.h中有一个built_ins的内置函数符号，将他加入到consts常量池中去
            }
        }

    };

    //打印字节码用来调试
    class BCModulesDumper {
    public:
        void dump(BCModule &bcModule) {
            //new 一个SymbolDumper
            //从常量池中循环取出内容,并且判断类型调用相应的visit
        }
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
            for (auto &x : block.stmts) {
                //调用visit方法
            }

            return ret;
        }

        std::any visitFunctionDecl(FunctionDecl &decl) {
            //1.设置当前函数符号
            //std::shared_ptr<lastFunctionSym> = this->functionSym;
            //this->functionSym = decl.sym;更新
            //this->consts.push_back(this->functionSym);

            //为函数体生成代码
            //std::vector<uint8_t> code ;

            //恢复当前函数
            //this->functionSym = lastFunctionSym;
        }

        std::any visitVariableDecl(VariableDecl &decl) {
            std::vector<uint8_t> code;

            //首先判断变量声明是否有初始化部分，
            /*
             * if (variableDecl.init != nullptr) {
             *      code = this->visit(variableDecl.init);
             * }
             * //再生成变量赋值的指令
             * */
            return code;
        }

        /*
         * 根据变量是否是左值,如果是左值那就返回变量符号,否则生成iload指令
         * */
        std::any visitVariable(Variable &v) {
            if (v.isLeftValue()) {
                return v.sym;
            } else {
                return this->getVariableValue(v.sym);
            }
        }
        //为返回语句生成
        std::any visitReturnStatement(RetuanStatement returnStatement) {
            std::vector<uint8_t> code;
            //首先判断return后面是否有表达式子
            if (returnStatement.exp != nullptr) {
                //为return 后面的表达式exp生成字节码
            } else {
                //生成return 代码，返回值是void
            }

            return code;
        }

        std::any visitFunctionCall(FunctionCall &functionCall) {
            std::vector<uint8_t> code;
        }

        /*
         * 为if语句生成字节码,难点在于分支语句的跳转需要修改
         * */
        std::any visitIfStatement(IfStatement &ifStatement) {
            std::vector<uint8_t> code;
            //std::vector<uint8_t> code_condition = this->visit(ifStatement.condition);
            //std::vector<uint8_t> code_ifBlock ;
            //std::vector<uint8_t> code_elseBlock;
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
        std::vector<uint8_t> addOfferSetToJump(std::vector<uint8_t> &code, uint32_t offset) {
            if (offset == 0) {
                return;
                //如果便宜量为0，那就直接短路
            }
        }

        /*
         *生成获取本地变量值的指令,类似与将数加载到寄存器中
        */
        std::any getVariableValue(VarSymbol &varSymbol) {
            std::vector<uint8_t> code;
            //首先判断以下varSymbol的init是否为空
            if() {
                //获取本地变量的下标
                switch() {

                }
            }
            return code;
        }

        /*
         * 和上面函数功能相反，是写回本地变量
         * */
        std::any setVariableValue(VarSymbol &varSymbol) {
            std::vector<uint8_t> code;
            if (varSymbol.sym != nullpty) {
                //获取本地变量的下标
                switch() {

                }
            }
            return code;
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

        /*
         * 生成二元表达式的时候注意，可以先为左右子树代码，再把运算指令放在最后
         * 赋值指令有一点不一样,他需要生成store指令
         * */
        std::any visitBinary(Binary &bi) {
            std::vector<uint8_t> code;


            //特判一下是否是为赋值
            if (bi.op = Op::Assign) {

            } else {
                //处理其他运算
                //加入左子树代码
                //加入右子树代码
                //加入二元运算符
            }
            return code;
        }

        std::any visitUnary(Unary &u) {
            std::vector<uint8_t> code;


            return code;
        }
    };


    class VM {
    public:
        //调用栈
         std::vector<std::shared_ptr<StackFrame>> callStack;

        int32_t execute(const BCModule &module) {
            //返回的int32_t是运行的状态消息
            //先找出入口函数
            std::shared_ptr<FunctionSymbol> functionSym;
            if (module.main_ == nullptr) {
                //输出错误语句
                return -1;
            } else {
              functionSym = module.main_;
            }

            //创建一个栈帧
            auto frame = std::make_shared<StackFrame>(functionSym);
            this->callStack.push_back(frame);


            //当前运行的代码
            std::vector<uint8_t> code;
            if() {

            } else {

            }

            //当前代码的位置
            std::uint32_t  codeIndex = 0;

            //一直执行代码，直到遇到return 语句

            //设置一些临时变量
            int8_t byte1 = 0;
            int8_t byte2 = 0;
            std::any vleft;
            std::any vright;

            //执行就是一个大循环
            while (true) {

            }
        }
    };

    //函数栈帧
    class StackFrame {
    public:
        //对应的函数,用来找到代码
        std::shared_ptr<FunctionSymbol> functionSym;

        uint32_t returnIndex {0};

        //函数的本地变量
        std::vector<uint32_t> localVars;

        //函数的操作数栈
        std::vector<std::any> oprandStack;

        StackFrame(std::shared_ptr<FunctionSymbol> &functionSymbol) : functionSymbol(functionSymbol){

        }

        //可能需要把StackFrame做成一个链表保存一下保存上一个栈帧，下一个栈帧
    };

    //从bcModule生成字节码,其实是一个序列化和反序列化的过程
    class BCModuleWriter {
    public:
        std::vector<const std::shared_ptr<Type>> types; //保存该模块涉及的类型

        /*
         * 从BCModule生成字节码
         * */
        std::vector<uint8_t> write(const BCModule &module) {

        }

        std::vector<uint8_t> writeVarSymbol() {

        }

        std::vector<uint8_t> writeFunctionSymbol() {

        }

        //把字符串添加到字节码数组中
        void writeString(std::vector<uint8_t> &code, const std::string &str) {

        }
    private:

    };

    //从字节码生成BCModule
    class BCModuleReader {
    private:
        //读取字节码时的下标
        uint32_t index = 0;

        //解析出来的所有类型
        std::map<std::string, Type> types;

        std::map<std::string, std::any> typeInfos;
    public:
        std::shared_ptr<BCModule> read(const std::vector<int>& bc) {

        }

    };
}
