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
                        //return
                    } else {
                        //return 一个整形字面量
                    }
                } else if (ch == '.') {

                } else if (ch == '/') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();

                        //return /= 这样一个 token
                    } else {
                        //如果都不是
                        //return 这 / 个Token
                    }
                } else if (ch == '+') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '+') {
                        this->stream.next();

                        //return token ++;
                    } else if (ch1 == '=') {
                        this->stream.next();
                        //return token +=;
                    } else {
                        //如果都不是，那就返回+
                        //return token +;
                    }
                } else if(ch == '-') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '-') {
                        this->stream.next();
                        //return token ++;
                    } else if (ch1 == '=') {
                        this->stream.next();
                        //return token -=;
                    } else {
                        //return token -;
                    }
                } else if (ch == '*') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        //return token *=
                    } else {
                        //return *
                    }
                } else if (ch == '%') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        //return token %=
                    } else {
                        //return token %
                    }
                } else if (ch == '>') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '>') {
                        this->stream.next();
                        ch1 = this->stream.peek();
                    } else if (ch1 == '=') {
                        this->stream.next();

                    }
                } else if (ch == '<') {
                 this->stream.next();
                 auto ch1 = this->stream.peek();
                 if (ch1 == '=') {
                     this->stream.next();
                     //return token <=;
                 } else if(ch1 == '<') {
                     this->stream.next();
                     ch1 = this->stream.peek();
                     if (ch1 == '=') {
                         this->stream.next();
                         //return token <<=
                     } else {
                         //return token <<
                     }
                 }
                } else if(ch == '=') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        ch1 = this->stream.peek();

                    }
                } else if(ch == '!') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        ch1 = this->stream.peek();
                        if (ch1 == '=') {
                            this->stream.next();
                            //return token !==
                        } else {
                            //return ！=
                        }
                    } else {
                        //return token !;
                    }
                } else if (ch == '|'){
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '|') {
                        this->stream.next();
                        //return  ||
                    } else if (ch1 == '=') {
                        this->stream.next();
                        //return |=
                    } else {
                        //return token |
                    }
                } else if(ch == '&') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '&') {
                         this->stream.next();
                         //return &&；
                    } else if(ch1 == '=') {
                        this->stream.next();
                        //return &=;
                    } else {
                        //return token &
                    }
                } else if(ch == '^') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        //return token ^=
                    } else {
                        //return token ^
                    }
                } else if (ch == '~') {
                    this->stream.next();
                    //return token ~
                } else if(ch == '(') {
                    this->stream.next();
                    //return token (
                } else if(ch == ')') {
                    this->stream.next();
                    //return token )
                } else if(ch == '{') {
                    this->stream.next();
                    //return token {
                } else if(ch == '}') {
                    this->stream.next();
                    //return }
                } else if(ch == '[') {
                    this->stream.next();
                    //return token [
                } else if(ch == ']') {
                    this->stream.next();
                    //return token [
                } else if (ch == ':') {
                    this->stream.next();
                    //return token :
                } else if(ch == ';') {
                    this->stream.next();
                    //return token ;
                } else if(ch == ',') {
                    this->stream.next();
                    //return token ,
                } else if(ch == '?') {
                    this->stream.next();
                    //return token ?
                } else if(ch == '@') {
                    this->stream.next();
                    //return token @
                } else if(ch == '$') {
                    this->stream.next();
                    //return token $
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

        Token parseIdentifer() {

            Token token();

            return token;
        }
    };
}