//
// Created by admin on 2022/8/23.
//
#pragma once
#include "ast.h"
#include <any>
#include <memory>
#include <map>
#include <vector>

//暂时没有IR，但是我在汇编之上封装了一层抽象例如:Inst Oprand之类
//汇编操作码
enum class AsmOpCode {

};

//操作数的种类
enum class OprandKind {

};

//操作数
class Oprand {
    OprandKind kind;
    std::any value;
};

//寄存器
class Register : public Oprand {

};

//条件语句产生的Oprand
class CmpOrand : public Oprand {

};

//指令的基本块，块内都是线性序列
class BasicBlock {

};

class AsmModule {

};

class AsmGenerator : public AstVisitor {
    std::shared_ptr<AsmModule> asmModule;//编译后的模型

    std::shared_ptr<BasicBlock> getCurrentBlock() {

    }

    std::shared_ptr<BasicBlock> newBlock() {
        auto bb = std::make_shared<BasicBlock>();

    }

    //接下来就是重写AstVisitor中所有的visit方法
    std::any visitProg() {
        //设置一些状态变量
        this->asmModule = std::make_shared<AsmModule>();

    }

    std::any visitReturnStatement(ReturnStatement &rtStmt) {
        if(rtStmt.exp != nullptr) {

        }
    }

    std::any visitIfStatement(IfStatement &ifStmt) {
        //初始化if和for要注意BasicBlock的构建
    }

    std::any visitForStatement(ForStatement &forStmt) {
        if(forStmt.init != nullptr) {
            //访问
        }
    }

    std::any visitVariableDecl(VariableDecl &variableDecl) {

    }

    std::any visitBinary(Binary &bi) {

    }

    std::any visitUnary(Unary &u) {

    }

    std::any visitVariable(Variable &variable) {

    }

    std::any visitIntegerLiteral(IntegerLiteral &integerLiteral) {

    }

    std::any visitFloatLiteral(FloatLiteral &floatLiteral) {

    }

    std::any visitStringLiteral(StringLiteral &stringLiteral) {

    }

    std::any visitFunctionCall() {

    }
};

//lower
/*对AsmModule做lower处理
 * 1.把虚拟寄存器转换成物理寄存器
 * 2.把本地变量换算成具体的物理寄存器
 * 3.把抽象的指令转换成具体的指令
 * 4.计算标签名称
 * 5.内存对齐
 * */
class Lower {
public:
    //前一步生成的
    std::shared_ptr<AsmModule> asmModule;

    size_t numParams {0};//当前函数的参数

    //可以通过寄存器传递的参数的最大数量
    size_t MaxXmmRegParams = 8;//
};

/*
 * 控制流图
 * */
class CFG{
public:
    //基本快的列表，第一个和最后一个是图的root
    std::vector<std::shared_ptr<BasicBlock>> bbs;

    //每一个基本块输出的边
    std::map<std::shared_ptr<BasicBlock>, std::vector<std::shared_ptr<BasicBlock>>> edgesOut;
    //每一个基本快输入的边
    std::map<std::shared_ptr<BasicBlock>, std::vector<std::shared_ptr<BasicBlock>>> edgesIn;

    CFG(std::vector<std::shared_ptr<BasicBlock>> &bbs) : bbs(bbs) {
        this->buildCFG();
    }


private:
    void buildCFG() {
        //先开始构建edgesOut
        for (int i = 0; i < ) {

        }
    }

    //构建edgesIn

    //打印基本快的信息
    std::string toString() {
        std::string str;

        for (auto &item : this->edgesOut) {

        }

        for (auto &item : this->edgesIn) {
            auto &bb = item.first;
            auto &fromBBS = item.second;

        }
        return str;
    }
};

//变量活跃性分析
class LivenessAnalyzer {
public:
    std::shared_ptr<AsmModule> asmModule;


    //注意我们主要是对函数和基本块做分析

};