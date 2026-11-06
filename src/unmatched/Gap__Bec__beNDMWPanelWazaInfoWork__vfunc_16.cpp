#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int FUN_003cc3d0(...);
void *FUN_003cc480(...);
void *FUN_003cc540(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int igObject_Destroy(...);
extern int DAT_004c9220[4];
extern int DAT_00586f20[4];
void Gap__Bec__beNDMWPanelWazaInfoWork__vfunc_16(beNDMWPanelWazaInfoWork *arg0);
}
/* matching construct: dummy-virtual class; only slot 16 (vX) is called through the panel references */
class PanelVirtualShim { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual int vX(); };
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]). The constructor interns the text and the destructor releases the token on scope exit;
 * both are out of line. */
class StringRef {
public:
    char *p;
    StringRef(const char *text);
    ~StringRef();
};
extern "C" int FUN_003cc490(void *, StringRef *);
void Gap__Bec__beNDMWPanelWazaInfoWork__vfunc_16(beNDMWPanelWazaInfoWork *arg0) {
    int *temp_a1;
    int temp_v0;
    int var_v0;
    int *old;
    int *s1;
    igObject *t;

    arg0->_retIsFire = 0;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
    old = (int *)arg0->_retWazaLabel;
    if (old != 0) {
        temp_a1 = old - 2;
        temp_v0 = old[-1] - 1;
        old[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_retWazaLabel = (int)s1;
    t = (igObject *)arg0->_playerWork;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if ((t->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_playerWork = 0;
    {
        StringRef empty(0);
        FUN_003cc490(FUN_003cc540(arg0), &empty);
    }
    FUN_003cc3d0(FUN_003cc480(arg0), &DAT_004c9220[0]);
    ((PanelVirtualShim *)arg0->_panelWaza)->vX();
    ((PanelVirtualShim *)arg0->_panelItem)->vX();
    ((PanelVirtualShim *)arg0->_panelStat)->vX();
}
