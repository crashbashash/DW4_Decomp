#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beNDMWWindow_RunMessageScript(...);
extern int DAT_0051c488[4];
extern int DAT_0051c498[4];
extern int DAT_0051c4a0[4];
extern int DAT_0051c4b0[4];
extern int DAT_00586f20[4];
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit; the second constructor takes a new share of an existing token.
 * The out-of-line copy the exception table names is the retail body StringRef_Destruct_00130720
 * (config/SLUS-20836/unit-objects.json, duplicate __dt__9StringRefFv). */
class StringRef {
public:
    char *p;
    StringRef(int s) : p((char *)s) {}
    StringRef(int s, int retain) : p((char *)s) { char *t = p; if (t) ((int *)t)[-1] = ((int *)t)[-1] + 1; }
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
/* string-pool intern (the pool singleton is created on first use) and the release of a stored token */
struct Str { static inline int intern(int *s) {
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool)
                pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = StringPool_Intern(DAT_00586f20[0], s);
    }
    return ref;
}
static inline void release(int ref) {
    int *header;
    int count;
    if (ref) {
        header = (int *)(ref - 8);
        count = *(int *)(ref - 4) - 1;
        *(int *)(ref - 4) = count;
        if (!count)
            StringChunk_ReleaseHeader(*header, header);
    }
} };
extern "C" void Gap__Bec__beNDMWShopSelect00__vfunc_22(beNDMWShopSelect00 *arg0);
void Gap__Bec__beNDMWShopSelect00__vfunc_22(beNDMWShopSelect00 *arg0) {
    int pool;
    int ref;
    int old;
    int obj;
    if (arg0->_entCode > 0) {
        { int tok = Str::intern(&DAT_0051c488[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
        obj = arg0->_panelName;
        if (obj == 0) {
            { int tok = Str::intern(&DAT_0051c498[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
        } else {
            StringList_AppendRetained(arg0->_textCloseNameList, StringRef(obj, 1));
        }
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], arg0->_entCode);
    }
    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool)
            pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    ref = StringPool_Intern(DAT_00586f20[0], &DAT_0051c4b0[0]);
    old = arg0->_infoName;
    Str::release(old);
    arg0->_infoName = ref;
    arg0->_selectMax = 1;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}
