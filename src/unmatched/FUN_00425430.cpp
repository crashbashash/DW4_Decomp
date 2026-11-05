/* 0x00425430 - FUN_00425430. Model-window reset: clears the two close-info string lists and the ram-number list,
 * selects a model-name string by the player's record field (16 arms) and presents the model at the fixed window
 * origin.  The selected name lives on the stack in a StringRef that each arm reassigns; the retail exception table
 * records its release.  alternate compiler -O3,p. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
void StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, const char *);
void beMessenger_AppendInt(int, int);
void beMessenger_DispatchSelected(int, int *);
int beMessenger_GetObject(int, int);
void beMessenger_SelectGroup(int, int *);
void beNDMWWindow_PlayQueuedModelClose(beNDMWWindow *);
int beNDMWWindow_PresentModel(beNDMWWindow *, int *, int, int *, int *, float *);
void *igProperty_GetRecord(int, int *);
extern int DAT_0051ac10[4], DAT_0051ad70[4], DAT_0051ad78[4], DAT_0051ad80[4], DAT_0051ad88[4], DAT_0051ad98[4], DAT_0051aec0[4];
extern int DAT_0051ada8[4];
extern int DAT_0051adb8[4];
extern int DAT_0051adc8[4];
extern int DAT_0051add8[4];
extern int DAT_0051adf0[4];
extern int DAT_0051ae00[4];
extern int DAT_0051ae10[4];
extern int DAT_0051ae20[4];
extern int DAT_0051ae30[4];
extern int DAT_0051ae40[4];
extern int DAT_0051ae50[4];
extern int DAT_0051ae60[4];
extern int DAT_0051ae70[4];
extern int DAT_0051ae80[4];
extern int DAT_0051aea0[4];
extern int DAT_0051aeb0[4];
extern int DAT_00586f20[4];
}
struct Rec { char pad[12]; unsigned int sel; };
/* create the shared string pool on first use (open-coded in the two clear loops: the inline Str::intern there
 * swaps the s0/s1 colouring of the first loop's counter and token) */
#define ENSURE_POOL() if (DAT_00586f20[0] == 0) { v = FUN_002eb010(0x10); if (v != 0) { v = StringPool_Construct(v); } DAT_00586f20[0] = v; }
/* string-pool intern of one of the model names (the pool singleton is created on first use) and the release of a
 * stored token */
struct Str {
    static inline int *intern(const char *s) {
        if (DAT_00586f20[0] == 0) {
            int v = FUN_002eb010(0x10);
            if (v != 0) v = StringPool_Construct(v);
            DAT_00586f20[0] = v;
        }
        return (int *)StringPool_Intern(DAT_00586f20[0], s);
    }
    static inline void release(int *p) {
        if (p != 0) {
            int *header = p - 2;
            int r = p[-1] - 1;
            p[-1] = r;
            if (r == 0) StringChunk_ReleaseHeader(*header, header);
        }
    }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at p[-2]):
 * releases the token on scope exit; set() drops the held token for a new one.  The out-of-line copy the
 * exception table names is the retail body StringRef_Destruct_00130720 (config/SLUS-20836/unit-objects.json,
 * duplicate __dt__9StringRefFv). */
class StringRef {
public:
    int *p;
    StringRef(int *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    void set(int *t) { int *cur = p; Str::release(cur); p = t; }
};
extern "C" void FUN_00425430(beNDMWWindow *arg0) {
    float sp80[3];
    igStringRefList *l1;
    igStringRefList *l3;
    int n1, n3, i3, v, off3;
    int *t, *a2;
    int i1;
    int **e1;
    int *a2b;
    int off1;
    int **e;
    unsigned int sel;
    int obj;

    beNDMWWindow_PlayQueuedModelClose(arg0);
    l1 = (igStringRefList *)arg0->_modelCloseInfoNameList;
    n1 = l1->_count;
    i1 = 0;
    if (i1 < n1) {
        off1 = 0;
        do {
            e1 = (int **)((char *)l1->_data + off1);
            ENSURE_POOL();
            a2b = (int *)StringPool_Intern(DAT_00586f20[0], 0);
            t = *e1;
            Str::release(t);
            i1 += 1;
            *e1 = a2b;
            off1 += 4;
        } while (i1 < n1);
    }
    l1->_count = 0;
    ((igIntList *)arg0->_modelCloseRamNoList)->_count = 0;
    l3 = (igStringRefList *)arg0->_modelCloseSeqNameList;
    n3 = l3->_count;
    i3 = 0;
    if (i3 < n3) {
        off3 = 0;
        do {
            e = (int **)((char *)l3->_data + off3);
            ENSURE_POOL();
            a2 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
            t = *e;
            Str::release(t);
            i3 += 1;
            *e = a2;
            off3 += 4;
        } while (i3 < n3);
    }
    l3->_count = 0;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051ad70[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051ad78[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051ad80[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051ad88[0]);
    obj = beMessenger_GetObject(arg0->_messenger, 0);
    {
        StringRef modelName(0);
        sel = ((struct Rec *)igProperty_GetRecord(obj, &DAT_0051ad98[0]))->sel;
        switch (sel) {
        default: modelName.set(Str::intern((const char *)&DAT_0051ada8[0])); break;
        case 1:  modelName.set(Str::intern((const char *)&DAT_0051adb8[0])); break;
        case 2:  modelName.set(Str::intern((const char *)&DAT_0051adc8[0])); break;
        case 3:  modelName.set(Str::intern((const char *)&DAT_0051add8[0])); break;
        case 4:  modelName.set(Str::intern((const char *)&DAT_0051adf0[0])); break;
        case 5:  modelName.set(Str::intern((const char *)&DAT_0051ae00[0])); break;
        case 6:  modelName.set(Str::intern((const char *)&DAT_0051ae10[0])); break;
        case 7:  modelName.set(Str::intern((const char *)&DAT_0051ae20[0])); break;
        case 8:  modelName.set(Str::intern((const char *)&DAT_0051ae30[0])); break;
        case 9:  modelName.set(Str::intern((const char *)&DAT_0051ae40[0])); break;
        case 10: modelName.set(Str::intern((const char *)&DAT_0051ae50[0])); break;
        case 11: modelName.set(Str::intern((const char *)&DAT_0051ae60[0])); break;
        case 12: modelName.set(Str::intern((const char *)&DAT_0051ae70[0])); break;
        case 13: modelName.set(Str::intern((const char *)&DAT_0051ae80[0])); break;
        case 14: modelName.set(Str::intern((const char *)&DAT_0051aea0[0])); break;
        case 15: modelName.set(Str::intern((const char *)&DAT_0051aeb0[0])); break;
        }
        sp80[2] = 0.0f;
        sp80[0] = -410.0f;
        sp80[1] = 240.0f;
        beNDMWWindow_PresentModel(arg0, &DAT_0051aec0[0], arg0->_playerNo, modelName.p, &DAT_0051ac10[0], &sp80[0]);
    }
}
