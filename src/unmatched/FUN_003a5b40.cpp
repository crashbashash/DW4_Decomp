#include "dw4/reflected.h"
/* arg1 is the position list (12-byte elements, igVec3fList) and arg2 the optional per-element int list (igIntList); both read at _count +8, _capacity +12, _data +16.
 * Arena refs stay 4-byte handles in the reflected structs, so _data is cast to its element pointer on use.
 * matching construct: the second list's count is reloaded after the call, spelled *(volatile int *)&arg2->_count. */
extern "C" {
int List_Resize(void *, int, int);
int Matrix44_GetTranslation(void *, float *);
int beMessenger_GetInt(int, int);
int beMessenger_GetMatrix(void *, int, int);
int beMessenger_GetMatrixCount(int);
int beMessenger_SendGroup(int, int, int);
extern int DAT_0058a578[4];
void FUN_003a5b40(void *arg0, igVec3fList *arg1, igIntList *arg2, int arg3, int arg4);
}
void FUN_003a5b40(void *arg0, igVec3fList *arg1, igIntList *arg2, int arg3, int arg4) {
    float v[3];
    int mat[16];
    int cnt, i, s0, s1;
    float *e;
    beMessenger_SendGroup(DAT_0058a578[0], arg3, arg4);
    cnt = beMessenger_GetMatrixCount(DAT_0058a578[0]);
    i = 0;
    if (0 < cnt) {
        do {
            beMessenger_GetMatrix(mat, DAT_0058a578[0], i);
            Matrix44_GetTranslation(mat, v);
            s0 = arg1->_count;
            if (s0 < arg1->_capacity) {
                arg1->_count = s0 + 1;
            } else {
                List_Resize(arg1, s0 + 1, 12);
            }
            e = (float *)(arg1->_data + s0 * 12);
            e[0] = v[0];
            e[1] = v[1];
            e[2] = v[2];
            if (arg2 != 0) {
                s1 = beMessenger_GetInt(DAT_0058a578[0], i);
                s0 = *(volatile int *)&arg2->_count;
                if (s0 < arg2->_capacity) {
                    arg2->_count = arg2->_count + 1;
                } else {
                    List_Resize(arg2, s0 + 1, 4);
                }
                ((int *)arg2->_data)[s0] = s1;
            }
            i++;
        } while (i < cnt);
    }
}
