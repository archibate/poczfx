//
// Created by admin on 2022/6/29.
//
//这是一个用来build字节码的
#include "../bc.h"
#include <string>
#include <variant>
#include <unordered_map>
namespace zfx {
    //一个纯虚类
    class BytecodeEncoder {
    public:
        virtual ~BytecodeEncoder();
        virtual std::uint32_t encodeOp() = 0;//
    };

    class BytecodeBuilder {
    public:
        BytecodeBuilder(BytecodeEncoder *encoder = nullptr);


        //接下来就是添加各类指令的方法


        void emit(OpCode op);

        const std::string& getByteCode() const {
            if (!bytecode.empty()) {
                return bytecode;
            } else {
                return "WRONG";
            }
        }

        int32_t addConstantNumber(double value);

        int32_t addConstantNumber(int value);

        int32_t addConstant(const ConstantKey &key, const Constant &value);

        void emitABC(Opcode op, uint8_t a, uint8_t b, uint8_t c);


    private:
        //这些都是zfx中的常量
        struct Constant {
            enum class Type {
                FLOAT,
                INT
            };

            Type type;
            std::variant<int, float> m;
        };
//在zfx中framid是当作常量来处理的嘛，用一个map来处理
        struct ConstantKey {
            Constant::Type type;

            uint32_t value;
            bool operator==(const ConstantKey& key) {
                return key.type == type && key.value == value;
            }
        };
        struct Jump {
            //跳转指令
        };

        std::unordered_map<> constantMap;
        std::string bytecode;
        std::vector<uint32_t> insn;
    };
}