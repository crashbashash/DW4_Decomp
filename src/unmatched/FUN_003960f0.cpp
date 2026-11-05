#include "dw4/reflected.h"

extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int igStrCmp(int *, int);
extern int DAT_004e0858[4];
extern int DAT_00586f20[4];
extern int DAT_00588e20[4];
int FUN_003960f0(int arg0, beModelCtrlInfoWork *self);
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit.  The out-of-line copy the exception table names is the retail
 * body StringRef_Destruct_00130720 (config/SLUS-20836/unit-objects.json, duplicate __dt__9StringRefFv). */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int FUN_001cafc0(int list, StringRef *key, int);
/* retail hands the copied token back by hidden return pointer */
extern "C" StringRef StringList_CopyRetained(int list, int index);


struct Obj { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad; int nm; };

int FUN_003960f0(int arg0, beModelCtrlInfoWork *self) {
    int result = 0;
    if (self->_labelSeqList != 0) {
        int name = self->_seqCodeName;
        int v;
        int idx;
        if (name == 0) {
            v = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int al = FUN_002eb010(16);
                if (al != 0) al = StringPool_Construct(al);
                DAT_00586f20[0] = al;
            }
            v = StringPool_Intern(DAT_00586f20[0], name);
        }
        {
            StringRef key((char *)v);
            idx = FUN_001cafc0(self->_labelSeqList, &key, 0);
        }
        if (idx != -1) {
            result = ((int *)((igIntList *)self->_labelOffsetList)->_data)[idx];
            if (result == -1) {
                int s2;
                beModelCtrlData *lst;
                int n, j;
                /* the copied token is a temporary: only the pointer outlives it (the list keeps its share) */
                s2 = (int)StringList_CopyRetained(self->_labelNameList, idx).p;
                lst = (beModelCtrlData *)self->_comData;
                n = ((igObjectList *)lst->_comList)->_count;
                for (j = 0; j < n; j++) {
                    Obj *o = (Obj *)((int *)((igObjectList *)lst->_comList)->_data)[j];
                    if (DAT_00588e20[0] == o->vX()) {
                        if (igStrCmp(o->nm != 0 ? (int *)o->nm : &DAT_004e0858[0], s2) == 0) {
                            igIntList *ia = (igIntList *)self->_labelOffsetList;
                            result = j;
                            if (ia->_count != 0 && idx >= 0 && idx < ia->_count) {
                                ((int *)ia->_data)[idx] = j;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return result;
}
