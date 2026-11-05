#include "dw4/reflected.h"
extern "C" {
igPluginRepository *FUN_002bc930(...);
int FUN_002eb010(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int igNamedObject_SetName(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00586f20[4];
void FUN_00304720(igPluginHelper *arg0, int arg1, int arg2, int arg3);
}
void FUN_00304720(igPluginHelper *arg0, int arg1, int arg2, int arg3) {
    igPluginRepository *volatile sp5C;
    int var_v0;
    char *str;
    igPluginRepository *nm;
    char *old;
    sp5C = FUN_002bc930(igObject_GetAllocator(arg0));
    igNamedObject_SetName(sp5C, arg1);
    nm = sp5C;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    str = StringPool_Intern(DAT_00586f20[0], arg2);
    old = (char *)nm->_location;
    if (old != 0) {
        int *hdr = (int *)(old - 8);
        int c = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    nm->_location = (int)str;
    sp5C->_locationType = arg3;
    ObjectList_AppendRetained(arg0->_repositoryList, sp5C);
    {
        igPluginRepository *q = sp5C;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if ((q->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(q);
            }
        }
    }
}
