#include "dw4/reflected.h"
extern "C" {
struct T { char pad[12]; igStringRefList *list; };
struct T *FUN_003a9310(int, int *);
int StringChunk_ReleaseHeader(int, int *);
int StringList_CopyRetained(char **, igStringRefList *, int);
int bePlayer_GetStruct(int);
extern int DAT_0050d960[4];
char *SYSgetWeaponName(int arg0, int arg1);
}

char *SYSgetWeaponName(int arg0, int arg1) {
    char *str;
    char *s;
    igStringRefList *list;
    int *hdr;
    int v;

    list = FUN_003a9310(bePlayer_GetStruct(arg0 + 1), &DAT_0050d960[0])->list;
    if (list->_count <= arg1) {
        return 0;
    }
    StringList_CopyRetained(&str, list, arg1);
    s = str;
    if (s != 0) {
        hdr = (int *)(s - 8);
        v = hdr[1] - 1;
        hdr[1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(hdr[0], hdr);
        }
    }
    return s;
}
