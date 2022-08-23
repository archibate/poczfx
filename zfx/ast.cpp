//
// Created by admin on 2022/8/8.
//

#include "ast.h"

namespace zeno::zfx {
    //实现AstVisitor的方法
    std::any AstVisitor::visit(AST &node, std::string additional) {
       //根据node本身调用各自的accept方法
        return node.accept(*this, additional);
    }

    std::any AstVisitor::visitProg(Prog &prog, std::string additional) {
        //访问prog就是调用visitBlock()
        return this->visitBlock(prog, additional);
    }

    std::any AstVisitor::visitVariableDecl(VariableDecl &variableDecl, std::string additional) {
        //首先判断init是否已经
        if (variableDecl.init != nullptr) {
            return this->visit(*variableDecl.init, additional);
        }
        return std::any();
    }

    std::any AstVisitor::visitVariableStatement(VariableStatement &variableStmt, std::string additional) {
        return this->visit(*variableStmt.variableDecl, additional);
    }

    std::any AstVisitor::visitFunctionDecl(FunctionDecl &functionDecl, std::string additional) {
        for () {

        }
        return std::any();
    }

    std::any AstVisitor::visitCallSignature(CallSignature &callSignature, std::string additional) {

        return std::any();
    }

    std::any AstVisitor::visitParameterList(ParameterList &parameterList, std::string additional) {

        return std::any();
    }

    std::any AstVisitor::visitBlock(Block &block, std::string additional) {
        std::any retVal;
        for (auto x : block.stmts) {
            retVal = this->visit(*x, additional);
        }
        return retVal;
    }

    std::any AstVisitor::visitExpressionStatement(ExpressionStatement &stmt, std::string additional) {
        return this->visit()
        return std::any();
    }

    std::any AstVisitor::visitReturnStatement(ReturnStatement &returnStatement, std::string additional) {


        return std::any();
    }

    std::any AstVisitor::visitIfStatement(IfStatement &ifStatement, std::string additional) {

        if ()
        return std::any();
    }

    std::any AstVisitor::visitForStatement(ForStatement &forStatement, std::string additional) {

        return std::any();
    }

    std::any AstVisitor::visitBinary(Binary &binary, std::string additional) {
        this->visit(*binary.exp1, additional);
        this->visit(*binary.exp2, additional);
        return std::any();
    }

    std::any AstVisitor::visitUnary(Unary &unary, std::string additional) {
        this->visit(*unary.exp, additional);
        return std::any();
    }

    std::any AstVisitor::visitIntegerLiteral(IntegerLiteral &node, std::string additional) {
        return std::get<int>(node.value);
    }

    std::any AstVisitor::visitFloatLiteral(FloatLiteral &node, std::string additional) {
        return std::get<float >(node.value);
    }

    std::any AstVisitor::visitStringLiteral(StringLiteral &node, std::string additional) {
        return std::get<std::string>(node.value);
    }

    std::any AstVisitor::visitFunctionCall(FunctionCall &functionCall, std::string additional) {
        //依次访问函数调用的每一个参数
        for (auto param : functionCall.arguments) {
            this->visit(*param, additional);
        }
    }
}
