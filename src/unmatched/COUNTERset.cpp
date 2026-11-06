/* Padding nop after the guarded store (asm nop) reproduces the retail block end. */
#include "dw4/reflected.h"
extern "C" {
void *FUN_003a9250(int, int *);
int beMessenger_GetObject(int, int);
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int DAT_0050d8f0[4];
extern int DAT_0050d940[4];
extern int DAT_0050daf8[4];
extern int DAT_0058a1c0[4];
void COUNTERset(int arg0, int arg1);
}

void COUNTERset(int arg0, int arg1) {
    int temp_v1;
    igIntList *temp_a1;
    beMessenger_SendNamed(DAT_0058a1c0[0], &DAT_0050d940[0], 0, 0, &DAT_0050d8f0[0]);
    temp_a1 = (igIntList *)(*(int *)((char *)(FUN_003a9250(beMessenger_GetObject(DAT_0058a1c0[0], 0), &DAT_0050daf8[0])) + 12));
    temp_v1 = temp_a1->_count;
    if ((temp_v1 != 0) && (arg0 >= 0) && (arg0 < temp_v1)) {
        *(int *)(temp_a1->_data + (arg0 * 4)) = arg1;
        asm { nop }
    }
}
