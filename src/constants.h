#pragma once

#define GRID_ROWS 23
#define GRID_COLS 10
#define GRID_SIZE 32

#define SCREEN_WIDTH GRID_SIZE * GRID_COLS
#define SCREEN_HEIGHT GRID_SIZE * GRID_ROWS

#define HOR_MOVE_DELAY 0.03f
#define VER_MOVE_DELAY 0.02f
#define TRIGGER_DELAY 0.14f

#define SPAWN_X 3
#define SPAWN_Y 0

// Super Rotation System
int MINO_O_0[4][4] = {
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_O_1[4][4] = {
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_O_2[4][4] = {
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_O_3[4][4] = {
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int (*MINO_O[4])[4] = {MINO_O_0, MINO_O_1, MINO_O_2, MINO_O_3};
Color MINO_O_COLOR = {255, 255, 0, 255};

int MINO_I_0[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_I_1[4][4] = {
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0}
};
int MINO_I_2[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0}
};
int MINO_I_3[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}
};
int (*MINO_I[4])[4] = {MINO_I_0, MINO_I_1, MINO_I_2, MINO_I_3};
Color MINO_I_COLOR = {0, 255, 255, 255};

int MINO_J_0[4][4] = {
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_J_1[4][4] = {
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}
};
int MINO_J_2[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0}
};
int MINO_J_3[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};
int (*MINO_J[4])[4] = {MINO_J_0, MINO_J_1, MINO_J_2, MINO_J_3};
Color MINO_J_COLOR = {50, 50, 255, 255};

int MINO_L_0[4][4] = {
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_L_1[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};
int MINO_L_2[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_L_3[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}
};
int (*MINO_L[4])[4] = {MINO_L_0, MINO_L_1, MINO_L_2, MINO_L_3};
Color MINO_L_COLOR = {255, 165, 0, 255};

int MINO_S_0[4][4] = {
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_S_1[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 0}
};
int MINO_S_2[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};
int MINO_S_3[4][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}
};
int (*MINO_S[4])[4] = {MINO_S_0, MINO_S_1, MINO_S_2, MINO_S_3};
Color MINO_S_COLOR = {50, 255, 50, 255};

int MINO_Z_0[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_Z_1[4][4] = {
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}
};
int MINO_Z_2[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};
int MINO_Z_3[4][4] = {
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}
};
int (*MINO_Z[4])[4] = {MINO_Z_0, MINO_Z_1, MINO_Z_2, MINO_Z_3};
Color MINO_Z_COLOR = {255, 0, 0, 255};

int MINO_T_0[4][4] = {
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
int MINO_T_1[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}
};
int MINO_T_2[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}
};
int MINO_T_3[4][4] = {
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0}
};
int (*MINO_T[4])[4] = {MINO_T_0, MINO_T_1, MINO_T_2, MINO_T_3};
Color MINO_T_COLOR = {200, 50, 200, 255};

int (**MINOS[7])[4] = {MINO_O, MINO_I, MINO_J, MINO_L, MINO_S, MINO_Z, MINO_T};
Color *MINO_COLORS[7] = {&MINO_O_COLOR, &MINO_I_COLOR, &MINO_J_COLOR, &MINO_L_COLOR, &MINO_S_COLOR, &MINO_Z_COLOR, &MINO_T_COLOR};

// Wall kicks: [rotate direction][current rotation][test list][x, y]
int I_WALLKICKS[2][4][5][2] = {
    { // CW
        {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
        {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
        {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
        {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}
    },
    { // CCW
        {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
        {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
        {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},
        {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}}
    }
};
int JLSTZ_WALL_KICKS[2][4][5][2] = {
    { // CW
        {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
        {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
        {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
        {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}
    },
    { // CCW
        {{0, 0}, {+1, 0}, {1, 1}, {0, -2}, {1, -2}},
        {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
        {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
        {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}
    }
};

// Reference: https://harddrop.com/wiki/SRS