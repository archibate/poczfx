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

    ZFXTokenizer &tokenizer;
    //span<Token> tokens;
    static std::unordered_map<std::string , int32_t> OpRec;//运算符优先级为了伺候表达式解析的左递归问题
    ZFXParser(ZFXTokenizer &tokenizer) : tokenizer(tokenizer) {

    }

    std::shared_ptr<AST> parseProg() {
        auto stmts = this->parseStatementList();//std::vector<std::shared_ptr<AST>>

        return std::make_share<Prog>();
    }

    std::vector<std::shared_ptr<AST>> parseStatementList() {
        std::vector<std::shared_ptr<AST>> stmts;
        auto t = this->tokenizer.peek();//先预读一个token;
        while(t.kind != TokenKind::Eof) {
            //只要我的token不是Eof
            auto stmt = this->parseStatement();
            stmts.push_back(stmt);//插入一个ast节点
            t = this->scanner.peek();
        }
        return stmts;
    }

    std::shared_ptr<AST> parseStatement() {
        auto t = this->scanner.peek();
        //取出Token的code
        auto code = t.code;
        if () {

        } else if() {

        } else if() {

        } else if() {

        } else {
            //解析出来一个无效的ast
        }
    }

    std::shared_ptr<AST> parseIfStatement() {
        auto beginPos = this->tokenizer.getNextPos();
        std::shared_ptr<> exp1{};
    }

    std::shared_ptr<AST> parseReturnStatement() {

    }
}
//拿解析变量说明一下,解析结果是Sym, Param两个节点
    std::unique_ptr<AST> parseVariableDecl() {
            //简单的伪代码描述一下
            this->tokenizer.next();//跳过$ 和 @因为在调用者那已经判断过了我们只需要取出变量名
            if () {

            } else {
                std::cout << "Error parsing type annotation in VariableDecl" << std::endl;
            }
            /*
            if (token == "$" || token == "@") {
                //在预读一个字符，把clr这种读出来赋值给name

                //再判断一下是否有等于好
                auto t = next_token();
                if (t == "=") {
                    //读出他的val 和type构造这一个节点
                    return std::make_shared<AST>();
                }
            }
             */
    }
// 解析二元表达式采用运算符优先级算法， 比如 @pos + $c * 5,那么 + 运算符优先级小于 * 所以先计算 $c * 5
//原理就是 :@pos 后面跟了个 + 号所以肯定是一个加法表达式 继续往后遍历， 遇到 $c ，我们再往后看一看后面的运算符如果优先级大于前面的就
//解析赋值表达式
//解析一元运算符号，注意是前缀还是后缀

    std::shared_ptr<AST> parseUnary() {
    //一元表达式有以下三种情况，一个是前缀一元表达式就是 +@a这种， 另外一种是后缀++ -- a++ a--这种
    //递归解析
    //先解析前置一元情况，伪代码，前端要改一下
    //
    }
    std::unique_ptr<AST> expr_atom() noexcept {
        if (token_eof())
            return nullptr;
        scope_restore rst{tokens};
        auto token = next_token();
        return overloaded{
        [&] (Ident const &ident) {
            auto node = std::make_unique<ASTSym>();
            node->token = ident;
            node->name = ident;
            rst.release();
            return node;
        },
        [&] (float const &val) {
            auto node = std::make_unique<ASTFloat>();
            node->token = val;
            node->value = val;
            rst.release();
            return node;
        },
        [&] (int const &val) {
            auto node = std::make_unique<ASTInt>();
            node->token = val;
            node->val = val;
            rst.release();
            return node;
        },
        [&] (auto const &) {
            return nullptr;
        },
        }.match<std::unique_ptr<AST>>(token);
    }

    template <std::size_t N>
    std::unique_ptr<AST> expr_template(std::initializer_list<Op> *p_ops) noexcept {
        if constexpr (N == 0) {
            return expr_atom();
        } else {
            scope_restore rst{tokens};
            if (auto lhs = expr_template<N - 1>(p_ops + 1)) {
                while (1) if (auto p_op = next_op(*p_ops)) {
                    auto &op = *p_op;
                    if (auto rhs = expr_template<N - 1>(p_ops + 1)) {
                        auto node = std::make_unique<AST>();
                        node->token = op;
                        node->chs.push_back(std::move(lhs));
                        node->chs.push_back(std::move(rhs));
                        lhs = std::move(node);
                    }
                } else break;
                rst.release();
                return lhs;
            }
            return nullptr;
        }
    }

    std::unique_ptr<AST> expr_binary() noexcept {
        std::initializer_list<Op> lvs[] = {
            { Op::kLogicOr, },
            { Op::kLogicAnd, },
            { Op::kBitOr, },
            { Op::kBitXor, },
            { Op::kBitAnd, },
            { Op::kCmpEqual, Op::kCmpNotEqual, },
            { Op::kCmpLessThan, Op::kCmpLessEqual, Op::kCmpGreaterThan, Op::kCmpGreaterEqual, },
            { Op::kBitShl, Op::kBitShr, },
            { Op::kPlus, Op::kMinus, },
            { Op::kMultiply, Op::kDivide, Op::kModulus, },
            { Op::kAssign, Op::kPlusAssign, Op::kMinusAssign, Op::kMultiplyAssign, Op::kDivideAssign, Op::kModulusAssign, Op::kBitAndAssign, Op::kBitOrAssign, Op::kBitXorAssign, },
            { Op::kComma, },
        };
        return expr_template<std::size(lvs)>(std::data(lvs));
    }

    std::unique_ptr<AST> expr_top() noexcept {
        scope_restore rst{tokens};
        auto node = std::make_unique<AST>();
        node->token = Op::kSemicolon;
        while (1) if (auto p_stm = expr_binary()) {
            if (!next_op({Op::kSemicolon})) {
                break;
            }
            node->chs.push_back(std::move(p_stm));
        } else break;
        rst.release();
        return node;
    }
private:
    static std::map<Op, int32_t> opRec;//为了伺候二元运算符左递归问题
};

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

struct ZFXLower {
    std::vector<IRNode> nodes;

    IRId visit(AST const *ast) noexcept {
        IRId currid{static_cast<std::uint32_t>(nodes.size())};
        auto node = overloaded{
            [&] (Ident const &name) {
                return IRSym{name};
            },
            [&] (Op const &op) {
                std::vector<IRId> chsid;
                chsid.reserve(ast->chs.size());
                for (auto const &chast: ast->chs) {
                    chsid.push_back(visit(chast.get()));
                }
                return IROp{op, std::move(chsid)};
            },
            [&] (float const &val) {
                return IRConstFloat{val};
            },
            [&] (int const &val) {
                return IRConstInt{val};
            },
            [&] (auto const &) {
                return IREmpty{};
            },
        }.match<IRNode>(ast->token);
        nodes.push_back(std::move(node));
        return currid;
    }
};


enum class RegId : std::uint32_t {};
enum class SymId : std::uint32_t {};


}
