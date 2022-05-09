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
    kKeywordIf,
    kKeywordElse,
    kKeywordFor,
    kKeywordWhile,
    kKeywordReturn,
    kComma,
    kSemicolon,
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
        {',', Op::kComma},
        {';', Op::kSemicolon},
    };

    static inline std::map<std::pair<char, char>, Op> lut2{
        {{'&', '&'}, Op::kLogicAnd},
        {{'|', '|'}, Op::kLogicOr},
        {{'=', '='}, Op::kCmpEqual},
        {{'!', '='}, Op::kCmpNotEqual},
        {{'<', '='}, Op::kCmpLessEqual},
        {{'>', '='}, Op::kCmpGreaterEqual},
        {{'<', '<'}, Op::kBitShl},
        {{'>', '>'}, Op::kBitShr},
    };

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

    ZFXParser() {
        root = std::make_unique<AST>();
        curr = root.get();
    }

    span<Token> tokens;

    Token next_token() {
        auto token = std::move(tokens.front());
        tokens.remove_suffix(1);
        return token;
    }

    bool token_eof() const {
        return tokens.empty();
    }

    std::optional<Op> next_op(std::initializer_list<Op> const &ops) {
        if (token_eof())
            return std::nullopt;
        auto token = next_token();
        if (auto *p_op = std::get_if<Op>(&token)) {
            auto &&op = *p_op;
            if (std::find(ops.begin(), ops.end(), op) == ops.end()) {
            }
            return op;
        }
        return std::nullopt;
    }

    std::unique_ptr<AST> expr_atom() {
        if (token_eof())
            return nullptr;
        auto token = next_token();
        return overloaded{
        [&] (Ident const &ident) -> std::unique_ptr<AST> {
            auto node = std::make_unique<AST>();
            node->token = ident;
            return node;
        },
        [&] (float const &val) -> std::unique_ptr<AST> {
            auto node = std::make_unique<AST>();
            node->token = val;
            return node;
        },
        [&] (int const &val) -> std::unique_ptr<AST> {
            auto node = std::make_unique<AST>();
            node->token = val;
            return node;
        },
        [&] (auto const &) -> std::unique_ptr<AST> {
            return nullptr;
        },
        }.match(token);
    }

    std::unique_ptr<AST> expr_plus() {
        scope_restore rst{tokens};
        if (auto lhs = expr_atom()) {
            if (auto p_op = next_op({Op::kPlus, Op::kMinus})) {
                auto &&op = *p_op;
                if (auto rhs = expr_atom()) {
                    auto node = std::make_unique<AST>();
                    node->token = op;
                    node->chs = {std::move(lhs), std::move(rhs)};
                    rst.release();
                    return node;
                }
            }
        }
        return nullptr;
    }
};


}
