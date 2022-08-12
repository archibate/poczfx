//
// Created by admin on 2022/8/8.
//

#include "ast.h"

namespace zeno::zfx {
    //实现AstVisitor的方法
    std::any AstVisitor::visit(AST &node, std::string additional) {
       //调用node各自的accept方法
        return node.accept(*this);
    }

    std::any AstVisitor::visitProg(Prog &prog, std::string additional) {
        return this->visitBlock(prog);
    }

    std::any AstVisitor::visitVariableDecl(VariableDecl &variableDecl, std::string additional) {
        //首先判断init是否已经
        if (variableDecl.init != nullptr) {
            return this->visit(*variableDecl.init);
        }
        return std::any();
    }

    std::any AstVisitor::visitVariableStatement(VariableStatement &variableStmt, std::string additional) {
        return this->visit(*variableStmt.variableDecl);
        return std::any();
    }

    std::any AstVisitor::visitFunctionDecl(FunctionDecl &functionDecl, std::string additional) {

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
            retVal = this->visit(*x);
        }
        return retVal;
    }

    std::any AstVisitor::visitExpressionStatement(ExpressionStatement &expressionStatement, std::string additional) {

        return std::any();
    }

    std::any AstVisitor::visitReturnStatement(ReturnStatement &returnStatement, std::string additional) {


        return std::any();
    }

    std::any AstVisitor::visitIfStatement(IfStatement &ifStatement, std::string additional) {

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
        return node.value;
    }

    std::any AstVisitor::visitFloatLiteral(FloatLiteral &node, std::string additional) {
        return node.value;
    }

    std::any AstVisitor::visitStringLiteral(StringLiteral &node, std::string additional) {
        return node.value;
    }

    std::any AstVisitor::visitFunctionCall(FunctionCall &functionCall, std::string additional) {
        //依次访问函数调用的每一个参数
        for (auto param : functionCall.arguments) {
            this->visit(*param, additional);
        }
    }
}
