#include "ast.h"
#include "scanner.h"
#include "ZFXCode.h"
#include "bc.h"
#include <vector>
#include <string>
#include <cctype>
#include <memory>
#include "span.h"
#include "enumtools.h"
#include "overloaded.h"
#include "scope_exit.h"
#include <algorithm>
#include <string_view>
#include <optional>
#include <variant>
#include <array>
#include <map>
#include <typeinfo>
#include <any>
#include <unordered_map>
/*
 * variableDecl : '@'|'$' Identifier
 * */
namespace zeno::zfx {
namespace {


struct ZFXParser {
    ZFXTokenizer& tokenizer;
    ZFXParser(ZFXTokenizer &tokenizer) : tokenizer(tokenizer){

    }

    //解析程序入口
    std::shared_ptr<AST> parseProg() {
        auto beginPos = this->tokenizer.peek().pos;
        auto stmts = this->parseStatementList();//std::vector<Statement>
        return std::make_shared<Prog>(beginPos, this->tokenizer.getLastPos(), stmts);
    }

    std::vector<std::shared_ptr<AST>> parseStatementList() {
        std::vector<std::shared_ptr<AST>> stmts;
        auto t = this->tokenizer.peek();//预读一个Token
        while (t.kind != TokenKind::Eof) {
            //只要Token 的类型不等于 EOF 和 }
            auto stmt = this->parseStatement();//解析语句
            stmts.push_back(stmt);
            t = this->tokenizer.peek();
        }
        return stmts;
    }

    std::shared_ptr<AST> parseStatement() {


    }
private:
    static std::map<Op, int32_t> opRec;
};

}

std::map<Op, int32_t> ZFXTokenizer::opRec {
        {Op::kAssign,                     2}, //+
        {Op::kPlusAssign,                 2}, // +=
        {Op::kMinusAssign,                2},  // -=
        {Op::kMultiplyAssign,             2},  // *=
        {Op::kDivideAssign,               2},  // /=
        {Op::kModulusAssign,              2},  // %=
        {Op::kBitAndAssign,               2},  // &=
        {Op::kBitOrAssign,                2},  // |=
        {Op::kBitXorAssign,               2},  // ^=
        {Op::kLogicOr,                    4},  // ||
        {Op::kLogicAnd,                   5},  // &&
        {Op::kBitOr,                      6}, // |
        {Op::kBitXor,                     7}, // ^
        {Op::kBitAnd,                     8}, // &
        {Op::kCmpEqual,                   9},  // ==
        {Op::kCmpNotEqual,                9},  // !=
        {Op::kCmpGreaterThan,             10},  // >
        {Op::kCmpGreaterEqual,            10},  // >=
        {Op::kCmpLessThan,                10},  // <
        {Op::kCmpLessEqual,               10},  // <=
        {Op::kPlus,                       12},  //+
        {Op::kMinus,                      12},  // -
        {Op::kDivide,                     13},   // /
        {Op::kMultiply,                   13},   // *
        {Op::kModulus,                    13},   // %
};

}
