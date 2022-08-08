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
#include <string>
#include <unordered_map>

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

    enum class KeyWordKind {
        Function = 200,//取一个大点的值防止枚举值冲突
        Break,
        Return,
        If,
        Else,
        For,
        While,
        Undefined
    };

    using Ident = std::string;
    //using Token = std::variant<Op, Ident, float, int>;

    //
    struct Position {
        std::uint32_t begin {1};//开始于哪一个字符, 默认为一
        std::uint32_t end {1};//结束于哪一个字符
        std::uint32_t line {1};//所在的行号， 默认为一
        std::uint32_t col {1}; //所在的列号

        Position(uint32_t begin, uint32_t end, uint32_t line, uint32_t col) :
        begin(begin), end(end), line(line), col(col) {

        }

        Position(const Position &other) {
            this->begin = other.begin;
            this->end = other.end;
            this->line = other.line;
            this->col = other.col;
        }

        Position& operator=(const Position &other) :
                begin(other.begin), end(other.end),
                line(other.line), col(other.col){
            return *this;
        }

        std::string toString() {
            return "(ln: " + std::to_string(this->line) + ", col: " + std::to_string(this->col) +
            ", pos: " + std::to_string(this->begin) + ")";
        }

    };

    struct Token {
       TokenKind kind;
       std::string text;
       std::any code;//其实也可以用std::variant,分别有Op string int float之类
       Position pos;

       Token(TokenKind kind, std::string &text, Position &pos, std::any code = std::any()):
       kind(kind), text(text), pos(pos), code(code) {

       }

       //伺候单个字符
       Token(TokenKind kind, char c, Position &pos, std::any code = std::any()) :
       kind(kind), text(std::string(1, c)), pos(pos), code(code){

       }

       //将token输出
       std::string toString() {
           // return "Token" + ":" = this->pos.toString() + "\t" + ;
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

        Position getPosition() {
            return Position(this->pos + 1, this->pos + 1, this->line, this->col);
        }
    };
    struct ZFXTokenizer {
        std::list<Token> tokens;//因为要频繁删除插入用vector可能效果不好
        CharStream stream;
        std::unordered_map<std::string, KeyWordKind> KeyWordMap;
        Position lastPos {0, 0, 0, 0};//这个类似于链表的虚拟头节点

        ZFXTokenizer(CharStream &stream) : st(stream) {}
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

            //特判一下如果push还是没有元素, 那就返回一个eof
            if (this->tokens.size() < 1) {
                //return Token{}
            }
            auto it = this->tokens.begin();
            std::advance(it, 1);
            return *it;
        }

        //获取下一个Token的位置
        Position getNextPos() {
            return this->peek.pos();
        }

        //获取前一个Token的位置
        Position getLastPos() {
            return lastPos;
        }
    private:
        Token getAToken() {
            this->skipWhiteSpaces();//先跳过空白
            auto pos = this->stream.getPosition(); //我们只需要更新一下pos中的end
            if (this->stream.eof()) {
                //如果到了字符串末尾,返回一个空Token
                return Token(TokenKind::Eof, "EOF", pos); //这里code是默认的
            } else {
                auto ch = this->stream.peek();
                if (isLetter(ch) || ch == '_') {
                    return this->parseIdentifer();
                } else if (ch == '"' || "'") {
                    //开始解析字符串
                    return this->parseStringLiteral(ch);
                } else if (this->isDigit(ch)) {
                    //解析数字字面量
                    this->stream.next();//再预读一个字符
                    auto ch1 = this->stream.peek();//取出字符
                    std::string literal = "";
                    if (ch == '0') {
                        //不支持八进制，二进制，十六进制
                        if (!(ch1 >= '1' && ch1 <= '9')) {
                            //先取零
                            literal += '0'
                        } else {
                            std::cout << "0 cannot be followed bu other digit now" << std::endl;
                            //暂时不支持十六进制, 八进制, 二进制
                            //先跳过去再解析token
                            this->stream.next();
                            return this->getAToken();
                        }
                    } else if(ch >= '1' && ch <= '9') {
                        literal += ch;
                        while(this->isDigit(ch1)) {
                            ch = this->stream.next();
                            literal += ch;
                            ch1 = this->stream.peek();//实数的情况
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
                        return Token(TokenKind::FloatLiteral, literal, pos);//浮点数字面零
                    } else {
                        return Token(TokenKind::IntegerLiteral, literal, pos);//返回一个整形字面零
                    }
                } else if (ch == '.') {
                    //如果直接以点开头，那么有两种情况一个是以点开头的浮点数，另一种就是点操作符
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (this->isDigit(ch1)) {
                        std string literal = ".";
                        while(this->isDigit(ch1)) {
                            ch = this->stream.next();
                            literal += ch;
                            ch1 = this->stream.peek();
                        }
                        return Token(TokenKind::FloatLiteral, literal, pos);
                    } else {
                        //返回.这一个Token
                        return Token();
                    }
                } else if (ch == '/') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "/=", pos,Op::kDivideAssign);
                    } else {
                        //如果都不是
                        return Token(TokenKind::Operator, "/", pos, Op::kDivide);
                    }
                } else if (ch == '+') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '+') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "++", pos, Op::);
                    } else if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "+=", pos, Op::kPlusAssign);
                    } else {
                        //如果都不是，那就返回+
                        return Token(TokenKind::Operator, "+", pos, Op::kPlus);
                    }
                } else if(ch == '-') {
                    this->stream.next();
                    auto ch1 = this->stream.peek();
                    if (ch1 == '-') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "--", pos, Op::);
                    } else if (ch1 == '=') {
                        this->stream.next();
                        return Token(TokenKind::Operator, "-=", pos, Op::kMinusAssign);
                    } else {
                        return Token(TokenKind::Operator, "-", pos, Op::kMinus);
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
                    return Token(TokenKind::Separator, ch, pos, Op::kRightBracket);
                } else if (ch == ':') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, pos, Op::kTernaryElse);
                } else if(ch == ';') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, pos, Op::kSemicolon);
                } else if(ch == ',') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, pos, Op::kComma);
                } else if(ch == '?') {
                    this->stream.next();
                    return Token(TokenKind::Separator, ch, pos, Op::kTernary);
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

        bool isLetter(char c) noexcept{
            return (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z');
            //我在这里不需要识别 $ 和 @ 这两个字符，因为这两个字符会单独成为两个独立的Token，Kind是属性
        }

        bool isDigit(char ch) {
            return (ch >= '0' && ch <= '9');
        }

        bool isLetterDigitOrUnderScope(char ch) {
            return (ch > = 'a' && ch <= 'z') ||
                    (ch >= 'A' && ch <= 'Z') ||
                    (ch >= '0' && ch <= '9') ||
                    (ch == '_');
        }

        Token parseStringLiteral() {
            //上面this->st.peek() = '"'时，就开始解析
            Token token();
            this->stream->next();
            while(!this->stream.eof() && this->stream.peek() != '"') {
                token.text += this->stream.next();
            }

            if(this->st.peek() == '"') {
                //消化掉最后一个'"'
                this->st.next();
            } else {
                //打印错误。出错了肯定
            }
            return token;
        }

        //解析标识符，并且从标识符中识别出关键字
        Token parseIdentifier() {
            //Identifier 目前是指clr, pos这种， 后续像if else for 之类
            Token token();

            //第一个字符不用判断了,因为在调用者那里已经判断过了
            while(!this->stream.eof() &&
            isLetterDigitOrUnderScope(this->stream.peek())) {
                token.text += this->stream.next();
            }

            auto it = KeyWords.find(token.text);
            if (it != KeyWords.end()) {
                //如果不为空则token的kind是关键字
                token.kind = TokenKind::KeyWord;
                token.code = it->second;
            }
            return token;
        }
    };


}