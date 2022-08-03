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
#include <set>
#include <any>

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
        Identifier,
        StringLiteral,
        IntegerLiteral,
        FloatLiteral,
        Operator,
        Separator,
        Eof,
    };

    using Ident = std::string;
    //using Token = std::variant<Op, Ident, float, int>;
    struct Token {
       TokenKind kind;
       std::string text;
       std::any code;//其实也可以用std::variant,分别有Op string int float之类
       Token(TokenKind kind, const std::string& text, std::any code = std::any()):
       kind(kind), text(text), code(code) {

       }

       //为了伺候单个字符的情况
       Token(TokenKind kind, char c, std::any code = std::any()) :
       kind(kind), text(std::string(1, c)), code(code) {

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
        std::list<Token> tokens;//因为要频繁删除插入用vector可能效果不好
        CharStream& stream
        static std::set<std::string> KeyWords;//一些常用的关键词，比如说for if else 之类，我在预读的时候就可以直接查表得到

        static bool isIdent(char c) {
            return std::isalnumc(c) || c == '_' || c == '$' || '@'
        }

        /*
         * 对运算符的一些判断操作,根据枚举值的大小去判断
         * */
        static bool isAssignOp(Op op) const {

        }

        static bool isRelationOp(Op op) const {

        }

        static bool isArithmeticOp(Op op) const {

        }

        static bool isLogicalOp(Op op) const {

        }
      Token next() {
            if (this->tokens.empty()) {
                auto t = this->getAToken();
                //不会插入到tokens中去
                return t;
            } else {
                auto t = this->tokens.front();
                this->tokens.pop_front();
                return t;
            }
        }

       Token peek() {
            //读取但是不移动
            if (this->tokens.empty()) {
                auto t = this->getAToken();
                this->tokens.push_back(t);
                return t;
            } else {
                auto t = this->tokens.front();
                return t;
            }
        }

        Token peek2() {
            while (this->tokens.size() < 2) {
                auto t = this->getAToken();
                this->tokens.push_back(t);
            }

            auto it = this->tokens.begin();
            std::advance(it, 1);
            return *it;
        }

    private:
        Token getAToken() {
            this->skipWhiteSpaces();//先跳过空白

            if (this->stream.eof()) {
                //如果到了字符串末尾,返回一个空Token
                return Token(TokenKind::Eof, "EOF");
            } else {
                auto ch = this->stream.peek();
                if (isident(ch)) {
                    return this->parseIdentifer();
                } else if (ch == '"') {
                    //开始解析字符串
                    return this->parseStringLiteral();
                } else if (this->isDigit(ch)) {
                    //解析数字字面量
                    this->stream.next();//再预读一个字符
                    auto ch1 = this->stream.peek();
                    std::string literal = "";
                    if (ch == '0') {
                        //不支持八进制，二进制，十六进制
                        if (!(ch1 >= '1' && ch1 <= '9')) {
                            //先取零
                            literal += '0'
                        } else {
                            std::cout << "0 cannot be followed bu other digit now" << std::endl;
                            //先跳过去再解析token
                            this->strem.next();
                            return this->getAToken();
                        }
                    } else if(ch >= '1' && ch <= '9') {
                        literal += ch;
                        while(this->isDigit(ch1)) {
                            ch = this->stream.next();
                            literal += ch;
                            ch1 = this->stream.peek();
                        }
                    }
                    if (ch1 == '.') {
                        //解析浮点数, 加上小数字面量
                        literal += '.';
                        this->strem.next();
                        ch1 = this->stream.peek();
                        while (this->isDigit(ch1)) {
                            ch = this->stream.next();
                            literal += ch;
                            ch1 = this->stream.peek();
                        }
                        return Token();//浮点数字面零
                    } else {
                        return Token();
                    }
                } else if (ch == '.') {
//我们也允许只以.开头的小数
                } else if (ch == '/') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "/=", Op::kDivideAssign);
                    } else {
                        //如果都不是
                        return Token(TokenKind::Operator, "/", Op::kDivide);
                    }
                } else if (ch == '+') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '+') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "++", Op::);
                    } else if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "+=", Op::kPlusAssign);
                    } else {
                        //如果都不是，那就返回+
                        return Token(TokenKind::Operator, "+", Op::kPlus);
                    }
                } else if(ch == '-') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '-') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "--", Op::);
                    } else if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "-=", Op::kMinusAssign);
                    } else {
                        return Token(TokenKind::Operator, "-", Op::kMinus);
                    }
                } else if (ch == '*') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "*=", Op::kMultiplyAssign);
                    } else {
                        return Token(TokenKind::Operator, "*", Op::kMultiply);
                    }
                } else if (ch == '%') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "%=", Op::kModulus);
                    } else {
                        return Token(TokenKind::Operator, "%", Op::kModulusAssign);
                    }
                } else if (ch == '>') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if(ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, ">=", Op::kCmpGreaterEqual);
                    } else if (ch1 == '>') {
                        this->stream.next();
                        return Token(TokenKind::Operator, ">>", Op::kBitShr);
                    } else {
                        return Token(TokenKind::Operator, ">", Op::kCmpGreaterThan);
                    }
                } else if (ch == '<') {
                 this->stream.next();
                 auto ch1 = this->stream.peek();
                 if (ch1 == '=') {
                     this->stream.next();
                     return Token(TokenKind::Operator, "<=", Op::kCmpLessEqual);
                 } else if(ch1 == '<') {
                     this->stream.next();
                     return Token(TokenKind::Operator, "<<", Op::kBitShl);
                 } else {
                    return Token(TokenKind::Operator, "<", Op::kCmpLessThan);
                 }
                } else if(ch == '=') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "==", Op::kCmpEqual);
                    } else {
                        return Token(TokenKind::Operator, "=", Op::kAssign);
                    }
                } else if(ch == '!') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "!=", Op::kLogicNot);
                    } else {
                        return Token(TokenKind::Operator, "!", Op::kCmpNotEqual);
                    }
                } else if (ch == '|'){
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '|') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "||", Op::kLogicOr);
                    } else if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "|=", Op::kBitOrAssign);
                    } else {
                        return Token(TokenKind::Operator, "|", Op::kBitOr);
                    }
                } else if(ch == '&') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '&') {
                         this->stream.next();
                         return Token(TokenKind::Operator, "&&", Op::kLogicAnd);
                    } else if(ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "&=", Op::kBitAndAssign);
                    } else {
                        return Token(TokenKind::Operator, "&", Op::kBitAnd);
                    }
                } else if(ch == '^') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator,"^=", Op::kBitXorAssign);
                    } else {
                        return Token(TokenKind::Operator, "^", Op::kBitXor);
                    }
                } else if (ch == '~') {
                    this->stream.next();
                    return Token(TokenKind::Operator, "~", Op::kBitInverse);
                } else if(ch == '(') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kLeftBrace);
                } else if(ch == ')') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kRightBrace);
                } else if(ch == '{') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kLeftBlock);
                } else if(ch == '}') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kRightBlock);
                } else if(ch == '[') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kLeftBracket);
                } else if(ch == ']') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kRightBracket);
                } else if (ch == ':') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kTernaryElse);
                } else if(ch == ';') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kSemicolon);
                } else if(ch == ',') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kComma);
                } else if(ch == '?') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, Op::kTernary);
                } else if(ch == '@') {
                    this->stream.next();
                    return Token();
                } else if(ch == '$') {
                    this->stream.next();
                    return Token();
                } else {
                    //识别到错误字符
                    std::cout << "Unrecognized pattern meeting" << std::endl;
                    this->stream.next();
                    return this->getAToken();
                }
            }
        }

        bool isident(char c) noexcept{
            return std::isalnum(c) || c == '_' || c == '$' || c == '@';
        }

        bool isDigit(char ch) {
            return (ch >= '0' && ch <= '9');
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

        Token parseIdentifier() {


        }
    };

    std::set<std::string> ZFXTokenizer::KeyWords {
        "if", "else", "for"
    };
}