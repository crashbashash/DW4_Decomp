/* Update state machine of the status-screen flag (important item) page. State 0 collects the owned
 * important items, registers the close text type/name, sends the row text groups, opens the list
 * window (one row per item, at least one) with its own close texts and message script, and queues
 * the model; state 1 waits for the window and reacts to the cursor; state 2 closes everything;
 * state 3 waits for the close and clears _isRun. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
beNDMWWindowSelect *FUN_003b51b0(int);
int FUN_003f5410(...);
int FUN_0041aaa0(...);
int List_Resize(...);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, void *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int *);
int beMessenger_GetObject(...);
int beMessenger_SendGroup(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_RunMessageScript(...);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
int *igProperty_GetRecordArray(...);
extern int *DAT_004cf670[4];
extern int *DAT_004cf674[4];
extern int DAT_00519a58[4];
extern int DAT_00519b50[4];
extern int DAT_00519b60[4];
extern int DAT_00519b68[4];
extern int DAT_00519b90[4];
extern int DAT_00519ba0[4];
extern int DAT_00519d98[4];
extern int DAT_0051a040[4];
extern int DAT_0051a060[4];
extern int DAT_0051a080[4];
extern int DAT_0051a098[4];
extern int DAT_0051a0a8[4];
extern int DAT_0051a0f8[4];
extern int DAT_0051a108[4];
extern int DAT_0051a118[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
typedef struct PropertyRecordList { int p0, p4; int cnt; int cap; unsigned char *data; } PropertyRecordList;
typedef struct PropertyRecord { char p[12]; PropertyRecordList *f12; } PropertyRecord;
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
/* Owning stack reference to the list window created here, released on scope exit (reference count
 * in the low 23 bits of _refCount). */
class WindowRef {
public:
    beNDMWWindowSelect *p;
    WindowRef(beNDMWWindowSelect *w) : p(w) {}
    ~WindowRef() { beNDMWWindowSelect *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy(w); } }
};
struct Str { static inline int *intern(int *s) {
    int *ref;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = (int *)StringPool_Intern(DAT_00586f20[0], s);
    }
    return ref;
} };
/* intern `text` and append it to the string list `field`; the list takes its own share, the temporary's
 * share is released at the end of the statement */
#define INTERN_APPEND(field, text) { int *tok = Str::intern(text); StringList_AppendRetained(field, StringRef(tok)); }
extern "C" void Gap__Bec__beNDMWStatusCtrlFlag__vfunc_21(beNDMWStatusCtrlFlag *arg0);
void Gap__Bec__beNDMWStatusCtrlFlag__vfunc_21(beNDMWStatusCtrlFlag *arg0) {
    PropertyRecordList *lst;
    int s2;
    int s1;
    int a;
    int al;
    igIntList *l4;
    int *src;
    int k;
    int **p;
    switch (arg0->_st0) {
    case 0:
        beMessenger_SendGroup(arg0->_messenger, DAT_00519ba0, DAT_0051a0f8);
        lst = ((PropertyRecord *)igProperty_GetRecordArray(beMessenger_GetObject(arg0->_messenger, 0), DAT_0051a108))->f12;
        s2 = 0;
        if (0 < lst->cnt) {
            do {
                if (lst->data[s2] != 0) {
                    l4 = (igIntList *)arg0->_impItems;
                    s1 = l4->_count;
                    if (s1 < l4->_capacity) {
                        /* matching construct: const re-read of the count */
                        l4->_count = ((const igIntList *)l4)->_count + 1;
                    } else {
                        List_Resize(l4, s1 + 1, 4);
                    }
                    ((int *)l4->_data)[s1] = s2;
                }
                s2 += 1;
            } while (s2 < lst->cnt);
        }
        INTERN_APPEND(arg0->_textCloseTypeList, &DAT_0051a040[0])
        src = DAT_004cf670[0];
        INTERN_APPEND(arg0->_textCloseNameList, src)
        beNDMWWindow_RunMessageScript(arg0, DAT_00519b90, 0x47);
        k = 0;
        p = &DAT_004cf670[0];
        do {
            FUN_003f5410(arg0, DAT_0051a060, *p, DAT_00519b60, DAT_00519b68);
            k += 1;
            p += 1;
        } while (k < 12);
        FUN_003f5410(arg0, DAT_0051a098, DAT_004cf670[0], DAT_00519b60, DAT_0051a080);
        FUN_003f5410(arg0, DAT_0051a098, DAT_004cf674[0], DAT_00519b60, DAT_0051a080);
        FUN_003f5410(arg0, DAT_00519b50, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
        al = igObject_GetAllocator(arg0);
        al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        {
        /* the list window is owned by the stack reference while it is bound, listed and set up; its
         * share is released at the block end */
        WindowRef win(FUN_003b51b0(al));
        beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        /* matching construct: (unsigned) cast on the reference steers retail operand order */
        ObjectList_AppendRetained((unsigned)arg0->_subWindow, win.p);
        a = ((igIntList *)arg0->_impItems)->_count;
        if (a == 0) {
            win.p->_selectMax = 1;
        } else {
            win.p->_selectMax = a;
        }
        {
            beNDMWWindowSelect *t = win.p;
            t->_offsetPos[0] = -121.0f;
            t->_offsetPos[1] = 128.0f;
            t->_offsetPos[2] = 0.0f;
        }
        win.p->_startPoint = 0;
        INTERN_APPEND(win.p->_textCloseTypeList, &DAT_00519b50[0])
        INTERN_APPEND(win.p->_textCloseNameList, &DAT_00519d98[0])
        beNDMWWindow_RunMessageScript(win.p, DAT_00519b90, 0x87);
        }
        arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
        beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051a0a8, 0, DAT_0051a118, DAT_00519a58);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            FUN_0041aaa0(arg0, 1, 1);
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
        case 1:
            if (((beNDMWWindowList *)(arg0->_subWindow))->_count == arg0->_nowProcKazu) {
                a = arg0->_retCode;
                if (a != -1 && arg0->_st2 != a) {
                    FUN_0041aaa0(arg0, 0, 1);
                    arg0->_st2 = arg0->_retCode;
                    arg0->_st3 = 0;
                }
            } else {
                arg0->_st0 = arg0->_st0 + 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}
