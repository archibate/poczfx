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

    std::any AstVisitor::visitVariableStatement(VariableStatement &variableStmt, std::string additional) {
        return this->visit(*variableStmt.variableDecl, additional);
    }

    std::any AstVisitor::visitVariableDecl(VariableDecl &variableDecl, std::string additional) {
        //有一个纠结的点
        //首先判断init是否为空，如果不为空则visit访问
        if (variableDecl.init != nullptr) {
            return this->visit(*variableDecl.init, additional);
        }
        return std::any();
    }


    std::any AstVisitor::visitFunctionDecl(FunctionDecl &functionDecl, std::string additional) {
        this->visit(*functionDecl.callSignature, additional);
        return this->visit(*functionDecl.body, additional);
    }

    std::any AstVisitor::visitCallSignature(CallSignature &callSignature, std::string additional) {
//判断函数调用签名的参数列表是否为空
        if (callSignature.paramList != nullptr) {
            return this->visit(*callSignature.paramList, additional);
        }
        return std::any();
    }

    //遍历参数列表
    std::any AstVisitor::visitParameterList(ParameterList &parameterList, std::string additional) {
        std::any retVal;
        for (auto x : parameterList.params) {
            retVal = this->visit(*x, additional);
        }
        return retVal;
    }

    std::any AstVisitor::visitBlock(Block &block, std::string additional) {
        std::any retVal;
        for (auto x : block.stmts) {
            retVal = this->visit(*x, additional);
        }
        return retVal;
    }

    std::any AstVisitor::visitExpressionStatement(ExpressionStatement &stmt, std::string additional) {
        return this->visit(*stmt.exp, additional);
        return std::any();
    }

    std::any AstVisitor::visitReturnStatement(ReturnStatement &returnStatement, std::string additional) {
       //需要判断一下是否有返回值语句
        if (returnStatement.exp != nullptr) {
            return this->visit();
        }
        return std::any();
    }

    std::any AstVisitor::visitIfStatement(IfStatement &ifStatement, std::string additional) {
        //分别遍历condition stmt, 如果有else部分加上else部分
        this->visit(*ifStatement.conditional, additional);
        this->visit(*ifStatement.stmt, additional);
        if (ifStatement.elseStmt != nullptr) {
            this->visit(*ifStatemen.elseStmt, additional);
        }
        return std::any();
    }

    std::any AstVisitor::visitForStatement(ForStatement &forStatement, std::string additional) {
        if(forStatement.init != nullptr){
            this->visit(*forStatement.init, additional);
        }

        if (forStatement.condition != nullptr) {
            this->visit(*forStatement.condition, additional);
        }

        if(forStatement.increment != nullptr) {
            this->visit(*forStatement.increment, additional);
        }
        //visit stmt
        this.visit(*forStatement.stmt, additional);
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
