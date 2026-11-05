#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beNDMWWindow_RunMessageScript(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int FUN_003f5410(...);
int beMessenger_AppendBool(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_SelectGroup(...);
int beNDMWShopSelect11_RefreshStatCosts(...);
extern int DAT_0051c488[4];
extern int DAT_0051c498[4];
extern int DAT_0051c4a0[4];
extern int DAT_0051c4c0[4];
extern int DAT_0051c4c8[4];
extern int DAT_0051c500[4];
extern int DAT_0051c540[4];
extern int DAT_0051c5c0[4];
extern int DAT_0051c5d0[4];
extern int DAT_0051c5e8[4];
extern int DAT_0051c5f8[4];
extern int DAT_0051c600[4];
extern int DAT_0051c610[4];
extern int DAT_0051c620[4];
extern int DAT_0051c630[4];
extern int DAT_0051c638[4];
extern int DAT_0051c640[4];
extern int DAT_0051c648[4];
extern int DAT_0051c650[4];
extern int DAT_0051c660[4];
extern int DAT_0051c668[4];
extern int DAT_0051c670[4];
extern int DAT_0051c680[4];
extern int DAT_00586f20[4];
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit.  The out-of-line copy the exception table names is the retail
 * body StringRef_Destruct_00130720 (config/SLUS-20836/unit-objects.json, duplicate __dt__9StringRefFv). */
class StringRef {
public:
    char *p;
    StringRef(int s) : p((char *)s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
/* string-pool intern (the pool singleton is created on first use) and the release of a stored token */
struct StringRefHelpers { static inline int intern(int *s) {
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
extern "C" void Gap__Bec__beNDMWShopSelect11__vfunc_22(beNDMWShopSelect11 *arg0);
void Gap__Bec__beNDMWShopSelect11__vfunc_22(beNDMWShopSelect11 *arg0) {
    int pool;
    int ref;
    int old;
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051c5c0[0], 0, &DAT_0051c5d0[0], &DAT_0051c5e8[0]);
    { int tok = StringRefHelpers::intern(&DAT_0051c488[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c5f8[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x481);
    { int tok = StringRefHelpers::intern(&DAT_0051c600[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c498[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c610[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c4c0[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x44D);
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c498[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c4c0[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c4c8[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c630[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c638[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c640[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c648[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x44F);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c498[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c4c0[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c4c8[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c630[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c638[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c640[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c648[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c488[0], &DAT_0051c498[0], &DAT_0051c660[0], &DAT_0051c540[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c500[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_AppendBool(arg0->_messenger, 0);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c670[0]);
    beNDMWShopSelect11_RefreshStatCosts(arg0);
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], arg0->_entCode + 0x482);
    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool)
            pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    ref = StringPool_Intern(DAT_00586f20[0], &DAT_0051c680[0]);
    old = arg0->_infoName;
    StringRefHelpers::release(old);
    arg0->_infoName = ref;
    arg0->_selectMax = 7;
    arg0->_offsetPos[0] = -121.0f;
    arg0->_offsetPos[1] = 128.0f;
    arg0->_offsetPos[2] = 0.0f;
    arg0->_startPoint = arg0->_entCode;
    arg0->_isNoCancel = 0;
}
