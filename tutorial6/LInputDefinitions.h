

#pragma once

#include "../Config.h"

#define L_KEY_PRESS 1
#define L_KEY_RELEASE 0

#ifdef GLFW_SUPPORT_ENABLED

#define L_MAX_KEYS 1024
#define L_MAX_BUTTONS 32

#include <GLFW/glfw3.h>

#define L_MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_1
#define L_MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_2
#define L_MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_3

#define L_KEY_UNKNOWN -1
#define L_KEY_SPACE GLFW_KEY_SPACE
#define L_KEY_0 GLFW_KEY_0
#define L_KEY_1 GLFW_KEY_1
#define L_KEY_2 GLFW_KEY_2
#define L_KEY_3 GLFW_KEY_3
#define L_KEY_4 GLFW_KEY_4
#define L_KEY_5 GLFW_KEY_5
#define L_KEY_6 GLFW_KEY_6
#define L_KEY_7 GLFW_KEY_7
#define L_KEY_8 GLFW_KEY_8
#define L_KEY_9 GLFW_KEY_9
#define L_KEY_A GLFW_KEY_A
#define L_KEY_B GLFW_KEY_B
#define L_KEY_C GLFW_KEY_C
#define L_KEY_D GLFW_KEY_D
#define L_KEY_E GLFW_KEY_E
#define L_KEY_F GLFW_KEY_F
#define L_KEY_G GLFW_KEY_G
#define L_KEY_H GLFW_KEY_H
#define L_KEY_I GLFW_KEY_I
#define L_KEY_J GLFW_KEY_J
#define L_KEY_K GLFW_KEY_K
#define L_KEY_L GLFW_KEY_L
#define L_KEY_M GLFW_KEY_M
#define L_KEY_N GLFW_KEY_N
#define L_KEY_O GLFW_KEY_O
#define L_KEY_P GLFW_KEY_P
#define L_KEY_Q GLFW_KEY_Q
#define L_KEY_R GLFW_KEY_R
#define L_KEY_S GLFW_KEY_S
#define L_KEY_T GLFW_KEY_T
#define L_KEY_U GLFW_KEY_U
#define L_KEY_V GLFW_KEY_V
#define L_KEY_W GLFW_KEY_W
#define L_KEY_X GLFW_KEY_X
#define L_KEY_Y GLFW_KEY_Y
#define L_KEY_Z GLFW_KEY_Z
#define L_KEY_ESCAPE GLFW_KEY_ESCAPE
#define L_KEY_ENTER GLFW_KEY_ENTER
#define L_KEY_TAB GLFW_KEY_TAB
#define L_KEY_BACKSPACE GLFW_KEY_BACKSPACE
#define L_KEY_RIGHT GLFW_KEY_RIGHT
#define L_KEY_LEFT GLFW_KEY_LEFT
#define L_KEY_DOWN GLFW_KEY_DOWN
#define L_KEY_UP GLFW_KEY_UP
#define L_KEY_F1 GLFW_KEY_F1
#define L_KEY_F2 GLFW_KEY_F2
#define L_KEY_F3 GLFW_KEY_F3
#define L_KEY_F4 GLFW_KEY_F4
#define L_KEY_F5 GLFW_KEY_F5
#define L_KEY_F6 GLFW_KEY_F6
#define L_KEY_F7 GLFW_KEY_F7
#define L_KEY_F8 GLFW_KEY_F8
#define L_KEY_F9 GLFW_KEY_F9
#define L_KEY_F10 GLFW_KEY_F10
#define L_KEY_F11 GLFW_KEY_F11
#define L_KEY_F12 GLFW_KEY_F12

#elif GLUT_SUPPORT_ENABLED

#include <GL/glut.h>

#define L_MOUSE_BUTTON_LEFT 0
#define L_MOUSE_BUTTON_MIDDLE 1
#define L_MOUSE_BUTTON_RIGHT 2

#define L_KEY_UNKNOWN -1
#define L_KEY_0 48
#define L_KEY_1 49
#define L_KEY_2 50
#define L_KEY_3 51
#define L_KEY_4 52
#define L_KEY_5 53
#define L_KEY_6 54
#define L_KEY_7 55
#define L_KEY_8 56
#define L_KEY_9 57
#define L_KEY_A 65
#define L_KEY_B 66
#define L_KEY_C 67
#define L_KEY_D 68
#define L_KEY_E 69
#define L_KEY_F 70
#define L_KEY_G 71
#define L_KEY_H 72
#define L_KEY_I 73
#define L_KEY_J 74
#define L_KEY_K 75
#define L_KEY_L 108
#define L_KEY_M 77
#define L_KEY_N 78
#define L_KEY_O 79
#define L_KEY_P 80
#define L_KEY_Q 81
#define L_KEY_R 114
#define L_KEY_S 115
#define L_KEY_T 84
#define L_KEY_U 85
#define L_KEY_V 86
#define L_KEY_W 119
#define L_KEY_X 120
#define L_KEY_X_MAYUS 88
#define L_KEY_Y 121
#define L_KEY_Y_MAYUS 89
#define L_KEY_Z 122
#define L_KEY_Z_MAYUS 90
#define L_KEY_SPACE 32
#define L_KEY_ESCAPE 27
#define L_KEY_ENTER 13
#define L_KEY_TAB 9
#define L_KEY_BACKSPACE 8
#define L_KEY_RIGHT GLUT_KEY_RIGHT
#define L_KEY_LEFT GLUT_KEY_LEFT
#define L_KEY_DOWN GLUT_KEY_DOWN
#define L_KEY_UP GLUT_KEY_UP
#define L_KEY_F1 GLUT_KEY_F1
#define L_KEY_F2 GLUT_KEY_F2
#define L_KEY_F3 GLUT_KEY_F3
#define L_KEY_F4 GLUT_KEY_F4
#define L_KEY_F5 GLUT_KEY_F5
#define L_KEY_F6 GLUT_KEY_F6
#define L_KEY_F7 GLUT_KEY_F7
#define L_KEY_F8 GLUT_KEY_F8
#define L_KEY_F9 GLUT_KEY_F9
#define L_KEY_F10 GLUT_KEY_F10
#define L_KEY_F11 GLUT_KEY_F11
#define L_KEY_F12 GLUT_KEY_F12

#else

#error WINDOWING SYSTEM NOT DEFINED CORRECTLY

#endif