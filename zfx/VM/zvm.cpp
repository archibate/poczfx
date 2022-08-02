//
// Created by admin on 2022/7/7.
//
#include "zvm.h"

#define VM_CASE(op) CASE_##OP;
#define VM_NEXT()
//虚拟机解释执行的核心引擎

static void zfx_execute(zfx_State* l) {

    Object* base;

    const Instruction* pc;//using Instruction = std::uin32_t;
    base = l->base;

    {
        VM_CASE(kLoadConstInt) {
            Instruction insn = *pc++;
            Object ra ;
            setnilvalue(ra);
            VM_NEXT();//取下一条指令
        }

        VM_CASE(kLoadConstFloat) {
            Instruction insn = *pc++;

            VM_NEXT();
        }

        VM_CASE(kAddrSymbol) {
            Instruction insn = *pc++;

        }

        VM_CASE(kAddrOffest) {

        }

        VM_CASE(kLoadPtr) {

        }

        VM_CASE(kStorePtr) {

        }

        VM_CASE(Assign) {

        }

        VM_CASE(kPlus) {

        }

        VM_CASE(kMinus) {
            
        }
        //接下来还有一些
    }
}