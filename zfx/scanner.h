//
// Created by admin on 2022/7/27.
//

#pragma once
#include <iostream>
#include <vector>
#include <cctype>
#include <variant>
#include <optional>
#include <string_view>


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

    enum class TokenKind {

    };

    using Ident = std::string;
    //using Token = std::variant<Op, Ident, float, int>;
    struct Token {
        std::variant<Op, Ident, float, int> code;//其实也可以搞成std::any
        std::string text;//获取字符串

        Token() {

        }
    };

    //包裹的一个字符串
    struct CharStream {
        std::string data; //注意坑爹的string_view是没有'\0'
        uint32_t pos = 0;
        uint32_t line = 1;//默认初始都是第一行
        uint32_t col = 0;//列数默认为一‘

        CharStream(const std::string &data) : data(data){

        }

        char peek() {
            return  this->data[this->pos];
            //只预断，不加加
        }

        char next() {
            return this->data[this->pos++];
            //判断一下是否已经换行了
            if (ch == '\n') {
                this->line++;
                this->col = 0;//列数清空
            } else {
                this->col++;
            }
            return ch;
        }

        bool eof() {

        }
    };
    struct ZFXTokenizer {
        std::vector<Token> tokens;
        CharStream& stream

        static bool isident(char c) {
            return std::isalnumc(c) || c == '_' || c == '$' || '@'
        }

      std::optional<Token> next() {
            if (this->tokens.empty()) {
                auto t = this->getAToken();

                return t;
            } else {
                auto t = this->tokens.front();
                this->tokens.pop_front();
                return t;
            }
        }

       std::optional<Token> peek() {
            //读取但是不移动
        }

        std::optional<Token> peek2() {
            //预读两个字符但是不移动
        }

    private:
        std::optional<Token> take() {
            this->skipWhiteSpaces();//先跳过空白

            if () {
                //如果到了字符串末尾，那么就要么返回一个std::nullopt,或者一个空Token

            } else {
                auto ch = this->stream.peek();
                if (isident(ch)) {
                    return this->parseIdentifer();
                } else if (ch == '"') {
                    //开始解析字符串
                    return this->parseStringLiteral();
                } else if () {
                    //解析数字字面量

                }
            }
        }

        bool isident(char c) noexcept{
            return std::isalnum(c) || c == '_' || c == '$' || c == '@';
        }

        Token parseStringLiteral() {
            //直接去掉第一个字符,因为上面已经判断了ch == '"'
            Token token();
            this->stream->next();
            while(!this->stream.eof() && this->stream.peek() != '"') {
                token.text += this->stream.next();
            }

            return token;
        }

        Token parseIdentifer() {

            Token token();

            return token;
        }
    };
}