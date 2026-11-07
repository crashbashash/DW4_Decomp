#include "dw4/reflected.h"
extern int DAT_0048acd0[];
int FUN_0017a2b0();
int p2LoadTexture(int a, int b, int c, int d, int e);
void FUN_002094c0(int a, int b);
void FUN_00209cf0(int a, int b, int c, int d, int e, int f, int g);
void FUN_0020a590(int a, int b, int c, int d, int e, int f, int g, int h);
void FUN_0020a990(int a, int b, int c, int d, int e, int f, int g, int h);

int Gap__Gfx__igPsx2VisualContext__vfunc_171(igPsx2VisualContext *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8) {
    int temp_a1;
    int temp_a2;
    int temp_v1;
    char *temp_a3;
    char *temp_s0;
    char *temp_s7;

    temp_a2 = (arg1 * 3) << 4;
    temp_a3 = (char *)arg0->_pBufList;
    temp_a1 = *(int *)(temp_a3 + 16);
    temp_s7 = (char *)(temp_a1 + temp_a2);
    temp_s0 = (char *)(*(int *)((char *)arg0->_pTexList + 16) + (arg2 * 0x88));
    if (**(int **)(temp_s0 + 72) == 0) {
        **(int **)(temp_s0 + 72) = p2LoadTexture(0, *(int *)(temp_s0 + 32), *(int *)(temp_s0 + 36), FUN_0017a2b0(*(int *)(temp_s0 + 0)), 0);
    }
    if ((arg7 == -1) || (arg8 == -1)) {
        if (arg0->_textureStateFilter != 0) {
            temp_v1 = (arg0->_textureMagFilter << 0x10) | arg0->_textureMinFilter;
            if (arg0->_currentTextureFilter[0] != temp_v1) {
                arg0->_currentTextureFilter[0] = temp_v1;
                FUN_002094c0(DAT_0048acd0[arg0->_textureMagFilter], DAT_0048acd0[arg0->_textureMinFilter]);
            }
        }
        FUN_00209cf0(*(int *)(temp_s7 + 40), **(int **)(temp_s0 + 72), arg3, arg4, arg5, arg6, 0);
    } else if (*(int *)(temp_s7 + 28) == 2) {
        FUN_0020a990(*(int *)(temp_s7 + 40), arg3, arg4, **(int **)(temp_s0 + 72), arg7, arg8, arg5, arg6);
    } else {
        FUN_0020a590(**(int **)(temp_s0 + 72), arg3, arg4, arg7, arg8, arg5, arg6, 0);
    }
    *(int *)(temp_s0 + 132) = 3;
    return 1;
}
