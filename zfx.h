#pragma once

#include <vector>
#include <string>
#include <cctype>
#include <memory>
#include "span.h"
#include "overloaded.h"
#include "scope_exit.h"
#include <algorithm>
#include <string_view>
#include <optional>
#include <variant>
#include <array>
#include <map>

namespace zeno::zfx {

enum class Op {
    kAssign,
    kPlus,
    kMinus,
    kMultiply,
    kDivide,
    kModulus,
    kPlusAssign,
    kMinusAssign,
    kMultiplyAssign,
    kDivideAssign,
    kModulusAssign,
    kBitAndAssign,
    kBitOrAssign,
    kBitXorAssign,
    kMember,
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
    kLeftBrace,
    kRightBrace,
    kLeftBracket,
    kRightBracket,
    kLeftBlock,
    kRightBlock,
    kTernary,
    kTernaryElse,
    kComma,
    kSemicolon,
    kKeywordIf,
    kKeywordElse,
    kKeywordFor,
    kKeywordWhile,
    kKeywordReturn,
};

using Ident = std::string;
using Token = std::variant<Op, Ident, float, int>;


struct ZFXTokenizer {
    std::vector<Token> tokens;

    static inline std::map<char, Op> lut1{
        {'=', Op::kAssign},
        {'+', Op::kPlus},
        {'-', Op::kMinus},
        {'*', Op::kMultiply},
        {'/', Op::kDivide},
        {'%', Op::kModulus},
        {'.', Op::kMember},
        {'~', Op::kBitInverse},
        {'&', Op::kBitAnd},
        {'|', Op::kBitOr},
        {'^', Op::kBitXor},
        {'<', Op::kCmpLessThan},
        {'>', Op::kCmpGreaterThan},
        {'!', Op::kLogicNot},
        {'(', Op::kLeftBrace},
        {')', Op::kRightBrace},
        {'[', Op::kLeftBracket},
        {']', Op::kRightBracket},
        {'{', Op::kLeftBlock},
        {'}', Op::kRightBlock},
        {'?', Op::kTernary},
        {':', Op::kTernaryElse},
        {',', Op::kComma},
        {';', Op::kSemicolon},
    };

    static inline std::map<std::tuple<char, char>, Op> lut2{
        {{'&', '&'}, Op::kLogicAnd},
        {{'|', '|'}, Op::kLogicOr},
        {{'=', '='}, Op::kCmpEqual},
        {{'!', '='}, Op::kCmpNotEqual},
        {{'<', '='}, Op::kCmpLessEqual},
        {{'>', '='}, Op::kCmpGreaterEqual},
        {{'<', '<'}, Op::kBitShl},
        {{'>', '>'}, Op::kBitShr},
        {{'+', '='}, Op::kPlusAssign},
        {{'-', '='}, Op::kMinusAssign},
        {{'*', '='}, Op::kMultiplyAssign},
        {{'/', '='}, Op::kDivideAssign},
        {{'%', '='}, Op::kModulusAssign},
        {{'&', '='}, Op::kBitAndAssign},
        {{'^', '='}, Op::kBitXorAssign},
        {{'|', '='}, Op::kBitOrAssign},
    };

    //static inline std::map<std::tuple<char, char, char>, Op> lut3{
        //{{'<', '<', '='}, Op::kBitShlAssign},
        //{{'>', '>', '='}, Op::kBitShrAssign},
    //};

    static inline std::map<std::string, Op> lutkwd{
        {"if", Op::kKeywordIf},
        {"else", Op::kKeywordElse},
        {"for", Op::kKeywordFor},
        {"while", Op::kKeywordWhile},
        {"return", Op::kKeywordReturn},
    };

    static bool isident(char c) noexcept {
        return std::isalnum(c) || c == '_' || c == '$' || c == '@';
    }

    std::optional<Token> take(std::string_view &ins) noexcept {
        if (ins.size() >= 1) {
            if (std::isdigit(ins[0]) || (ins[0] == '.' && ins.size() >= 2 && std::isdigit(ins[1]))) {
                auto ep = std::find_if_not(ins.cbegin() + 1, ins.cend(), [] (char c) {
                    return std::isdigit(c) || c == '.';
                });
                std::string s(ins.cbegin(), ep);
                if (s.find_first_of('.') != std::string::npos) {
                    return std::stof(s);
                } else {
                    return std::stoi(s);
                }
            } else if (isident(ins[0])) {
                auto it = std::find_if_not(ins.cbegin() + 1, ins.cend(), [] (char c) {
                    return isident(c);
                });
                std::string id(ins.cbegin(), it);
                ins.remove_prefix(it - ins.cbegin());
                if (auto it = lutkwd.find(id); it != lutkwd.end()) {
                    return it->second;
                } else {
                    return id;
                }
            }
        }
        if (ins.size() >= 2) {
            auto it = lut2.find({ins[0], ins[1]});
            if (it != lut2.end()) {
                ins.remove_prefix(2);
                return it->second;
            }
        }
        if (ins.size() >= 1) {
            auto it = lut1.find(ins[0]);
            if (it != lut1.end()) {
                ins.remove_prefix(1);
                return it->second;
            }
        }
        return std::nullopt;
    }

    void tokenize(std::string_view ins) noexcept {
        while (!ins.empty()) {
            if (auto t = take(ins)) {
                tokens.push_back(std::move(*t));
            } else {
                break;
            }
        }
    }
};

struct AST {
    Token token;
    std::vector<std::unique_ptr<AST>> chs;
};

struct ZFXParser {
    std::unique_ptr<AST> root;
    AST *curr{};

    explicit ZFXParser(span<Token> a_tokens) noexcept : tokens(a_tokens) {
        root = std::make_unique<AST>();
        curr = root.get();
    }

    span<Token> tokens;

    Token next_token() noexcept {
        auto token = std::move(tokens.front());
        tokens.remove_prefix(1);
        return token;
    }

    bool token_eof() const noexcept {
        return tokens.empty();
    }

    std::optional<Op> next_op(std::initializer_list<Op> const &ops) noexcept {
        if (token_eof())
            return std::nullopt;
        scope_restore rst{tokens};
        auto token = next_token();
        if (auto *p_op = std::get_if<Op>(&token)) {
            auto &op = *p_op;
            if (std::find(ops.begin(), ops.end(), op) != ops.end()) {
                rst.release();
                return op;
            }
        }
        return std::nullopt;
    }

    std::unique_ptr<AST> expr_atom() noexcept {
        if (token_eof())
            return nullptr;
        scope_restore rst{tokens};
        auto token = next_token();
        return overloaded{
        [&] (Ident const &ident) {
            auto node = std::make_unique<AST>();
            node->token = ident;
            rst.release();
            return node;
        },
        [&] (float const &val) {
            auto node = std::make_unique<AST>();
            node->token = val;
            rst.release();
            return node;
        },
        [&] (int const &val) {
            auto node = std::make_unique<AST>();
            node->token = val;
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
        };
        return expr_template<std::size(lvs)>(std::data(lvs));
    }

    std::unique_ptr<AST> expr_assign() noexcept {
        if (auto lhs = expr_binary()) {
            auto rhs = expr_binary();
        }
    }
};


}
