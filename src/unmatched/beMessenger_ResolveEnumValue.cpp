#include "dw4/reflected.h"
extern "C" {
extern int strcpy(int *, int);
extern int igMetaEnum_GetValueByName(int *, int, int, int *);
extern int igStrCmp(int *, int);
extern int DAT_004fb410[4];
extern int DAT_0058a4e0[4];
extern int DAT_0058a4f0[4];
extern int DAT_0058a530[4];
int beMessenger_ResolveEnumValue(beMessenger *self, int arg1, int arg2);
}

int beMessenger_ResolveEnumValue(beMessenger *self, int arg1, int arg2) {
    int value;
    int found;
    if ((DAT_0058a4e0[0] == arg1) && (igStrCmp(&DAT_0058a4f0[0], arg2) == 0)) {
        return DAT_0058a530[0];
    }
    igMetaEnum_GetValueByName(&found, arg1, arg2, &value);
    if (*(int *)(unsigned)&found == DAT_004fb410[0]) {
        DAT_0058a4e0[0] = arg1;
        strcpy(&DAT_0058a4f0[0], arg2);
        DAT_0058a530[0] = value;
        return value;
    }
    return -1;
}
