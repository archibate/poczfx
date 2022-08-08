//
// Created by admin on 2022/7/26.
//
//语义分析主要做这些功能比如最基本的引用消解， 类型检查
//比如我在开头定义了一个@a，那么我在parser的时候会将a : value作为一个map加入到全局的符号表中去，后续有运算的话载更新一下map


#pragma once
#include "scope.h"
#include "parser.h"
#include "ast.h"
#include "Symbol.h"
#include <memory>
#include <map>

namespace zeno::zfx {

    class SemanticAstVisitor : AstVisitor {
    public:
        //添加编译错误
        //添加警告
    };

    //消解类型， 后续再施工
    class TypeResolver : public SemanticAstVisitor {

    };


    /*
     * 从这里开始我们创建符号表, 将符号加入到符号表中去， 查找符号， 更新符号
     * */
    class Enter : public SemanticAstVisitor{
    public:
        std::shared_ptr<Scope> scope;//目前zfx只有一个作用域,后续如果有{}，那每进一个{}就创建一个作用域
        std::shared_ptr<FunctionSymbol> functionSym;

        /*
         * 返回最顶级的Scope对象
        */

        //
        std::any visitProg(Prog &prog) {
            //做一些初始化的工作
            //设置主程序的返回类型
        }

        /*
         * 把所有@和$声明都加入到符号表中去，
         * */
        std::any visitVariableDecl(Variable &) {
            //先查找当前作用域是否有这一个符号
            auto currentScope = this->scope;
            if () {

            }
            //没有就加入当前符号表

            return std::any();
        }

        //把函数声明加入到符号表中去
        std::any visitFunctionDecl(FunctionDecl &decl) {
            //设置作用域

        }
    };

    /* 引用消解
     * 遍历ast的时候,如果发现函数调用和变量引用，就去找他的定义
     *
     */
    class RefResolver : public SemanticAstVisitor {
    public:
      std::shared_ptr<Scope> scope;

      //每一个Scope作用域已经声明了变量的列表
      std::map<>
    };

    class TypeChecker : public SemanticAstVisitor {

    };
}