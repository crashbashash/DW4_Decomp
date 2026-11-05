#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int sprintf(char *, int *, int);
int strlen(char *);
int beMessenger_AppendString(int, char *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern int DAT_0051c6e0[4];
extern int DAT_0051c6e8[4];
extern int DAT_0051c6f0[4];
extern char DAT_0051c720[];
extern char DAT_0051c740[];
extern char DAT_0051c780[];
extern int DAT_0051c788[4];
extern char DAT_0051c790[];
extern int DAT_0051c798[4];
extern int DAT_0051c7a0[4];
extern int DAT_0051c7a8[4];
extern int DAT_0051c7b0[4];
extern int DAT_0051c7b8[4];
extern int DAT_0051c7c0[4];
void FUN_004402e0(beNDMWWindow *arg0, int arg1, unsigned int arg2, int *arg3) {
    char b70[16];
    char b80[12];
    char c[2];
    char *s1;
    int i, n;
    void *fmt;

    if (arg0->_entCode == 3) {
        s1 = &DAT_0051c720[0];
    } else {
        s1 = &DAT_0051c740[0];
    }
    i = 0;
    do {
        sprintf(b70, arg3, i);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c6e8[0]);
        beMessenger_AppendString(arg0->_messenger, s1);
        beMessenger_AppendString(arg0->_messenger, b70);
        beMessenger_AppendString(arg0->_messenger, &DAT_0051c780[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c788[0]);
        i++;
    } while (i < 7);
    switch (arg2) {
    case 0: return;
    case 1: sprintf(b80, &DAT_0051c6e0[0], arg1); break;
    case 2: sprintf(b80, &DAT_0051c798[0], arg1); break;
    case 3: sprintf(b80, &DAT_0051c7a0[0], arg1); break;
    case 4: sprintf(b80, &DAT_0051c7a8[0], arg1); break;
    case 5: sprintf(b80, &DAT_0051c7b0[0], arg1); break;
    case 6: sprintf(b80, &DAT_0051c7b8[0], arg1); break;
    case 7: sprintf(b80, &DAT_0051c7c0[0], arg1); break;
    default: return;
    }
    n = strlen(b80);
    i = n - 1;
    c[1] = 0;
    if (i > -1) {
        do {
            sprintf(b70, arg3, i);
            c[0] = b80[(n - 1) - i];
            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c6e8[0]);
            beMessenger_AppendString(arg0->_messenger, s1);
            beMessenger_AppendString(arg0->_messenger, b70);
            beMessenger_AppendString(arg0->_messenger, c);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c6f0[0]);
            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c6e8[0]);
            beMessenger_AppendString(arg0->_messenger, s1);
            beMessenger_AppendString(arg0->_messenger, b70);
            beMessenger_AppendString(arg0->_messenger, &DAT_0051c790[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c788[0]);
            i--;
        } while (i > -1);
    }
}
} /* extern "C" */
