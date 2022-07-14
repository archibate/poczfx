//
// Created by admin on 2022/7/7.
//
#include <cmath>


static int math_abs() {

    return 1;
}

static int math_sin(zfx_State* l) {
//默认都是对栈顶的值求sin
    lua_pushnumber(l, sin())
    //checknumber(L,1)得逻辑是
    //zfx_tonumberx(l, narg, &isnum)
    return 1;
}

static int math_cos() {

}

static int math_tan() {

}