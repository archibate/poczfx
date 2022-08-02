//
// Created by admin on 2022/7/7.
//
#include <cmath>


static int math_abs() {

    return 1;
}

static int math_sin(zfx_State* l) {
//默认都是对栈顶的值求sin

    zfx_pushnumber(l, sin());
    //checknumber(L,1)得逻辑是
    //zfx_tonumberx(l, narg, &isnum)
    return 1;
}

//双曲正弦
static int math_sinh(zfx_State* l) {
    zfx_pushnumber(l, sinh());
    return 1;
}

static int math_cos(zfx_State* l) {
    zfx_pushnumber(l, cos());
    return 1;
}

//
static int math_cosh(zfx_State* l) {
    zfx_pushnumber(l, cosh());
}

static int math_tan(zfx_State* l) {
    zfx_pushnumber(l, tan());
    return 1;
}

static int math_tanh() {

}

static int math_asin() {

    return 1;
}

static int math_acos() {
    return 1;
}

static int math_atan() {
    return 1;
}

static int math_atan2() {

}

static int math_ceil() {
    return 1;
}

static int math_floor() {
    return 1;
}

static int math_sqrt() {
    return 1;
}

static int math_pow() {
    return 1;
}