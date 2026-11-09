typedef struct CountedHeader { int w0; int refs; } CountedHeader;
#include "dw4/igTDataList.h"
typedef igTDataList<int> NameList;
typedef struct NamedLists { char pad[36]; NameList *_names; void *_name; } NamedLists;
extern "C" {
CountedHeader *FUN_002b90e0(int);
NameList *FUN_002caa70(int);
int FUN_002eb010(int);
int FUN_0025a550(NamedLists *, int);
int FUN_00463c70(NamedLists *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int igObject_Destroy(void *);
extern int DAT_00498728[4];
extern int DAT_00586f20[4];
void FUN_00259dc0(NamedLists *arg0, int arg1, int arg2);
}
struct AdoptReference {};
static inline void releaseRef(CountedHeader *t) {
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
}
static inline void resetName(NamedLists *o, AdoptReference) { releaseRef((CountedHeader *)o->_name); o->_name = FUN_002b90e0(0); }
static inline void resetList(NamedLists *o, AdoptReference) { releaseRef((CountedHeader *)o->_names); o->_names = FUN_002caa70(0); }
class StringRef {
public:
    int p;
    StringRef(int s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int FUN_001ca620(void *, StringRef *);
void FUN_00259dc0(NamedLists *arg0, int arg1, int arg2) {
    int var_v0;
    int obj;
    int n;
    NameList *l;
    int *hd;
    int cnt;
    int dv;
    resetName(arg0, AdoptReference());
    if (arg1 == 0) {
        var_v0 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            obj = FUN_002eb010(0x10);
            if (obj != 0) {
                obj = StringPool_Construct(obj);
            }
            DAT_00586f20[0] = obj;
        }
        var_v0 = StringPool_Intern(DAT_00586f20[0], arg1);
    }
    {
        StringRef name(var_v0);
        FUN_001ca620(arg0->_name, &name);
    }
    resetList(arg0, AdoptReference());
    l = arg0->_names;
    n = l->_count;
    if (n < l->_capacity) {
        l->_count = l->count() + 1;
    } else {
        List_Resize(l, n + 1, 4);
    }
    dv = DAT_00498728[0];
    l->_data[n] = dv;
    FUN_0025a550(arg0, dv);
    if (arg2 != 0) {
        FUN_00463c70(arg0);
    }
}
