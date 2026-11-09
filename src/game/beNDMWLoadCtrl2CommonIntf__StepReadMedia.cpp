/* One step of the "read save media" sub-state for the player slot idx (mode selects which of the
 * control record's st0..st3 drives it). State 0 starts the memory card read; state 1 waits for the
 * result and, on success (result 2), builds a slot player (FUN_003c6360) with four empty Digimon
 * records (beNDMWDegiData_Create), fills it from the read save data (FUN_003f0e30), appends it to
 * _slotSaveData and copies each used Digimon's name (up to 8 UTF-16 chars, zero padded) from its
 * unicode text through FUN_00382eb0. The slot player and the Digimon records live on the stack in
 * owning references. */
#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(...);
int FUN_00382eb0(...);
void *FUN_003c6360(...);
void *beNDMWDegiData_Create(...);
int FUN_003f0e30(...);
int FUN_003f1460(...);
int List_Resize(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
extern int DAT_00587110[4];
extern int DAT_00589678[4];
extern unsigned char GPR_00554c14;

typedef igObject Rc;
/* matching construct: the code reads the reference count as a signed int (igObject._refCount is reflected unsigned) */
#define REFS(o) (*(int *)&(o)->_refCount)
struct Node { int p[8]; int f32; int st0; int st1; int st2; int st3; };
struct Meta { int p[2]; int f8; };
#define NODE(s, i) (((Node **)((igObjectList *)(s)->_flagWork)->_data)[i])
#define CFG(s) ((beNDMWMcUtilCtrl *)(s)->_mcUtilCtrl)
#define GRP(p) ((beNDMWLoadSlotPlayer *)(p))
#define DD(p) ((beNDMWDegiData *)(p))
/* beNDMWDegiData._dmNameUni is reflected as int[5] but the code reads it as 16-bit units (id marker at +8, name chars from +10) */
#define DNAME(d) ((unsigned short *)(d)->_dmNameUni)
#define REL(o) { Rc *rr = (o); if (rr != 0) { REFS(rr) = REFS(rr) - 1; if (((unsigned long long)((long long)REFS(rr) << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define ALLOC(a, self) { a = igObject_GetAllocator(self); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }

int beNDMWLoadCtrl2CommonIntf__StepReadMedia(beNDMWLoadCtrl2CommonIntf *self, int idx, int unused, int val, int mode);
}
/* Owning stack reference to the new slot player: constructed from the creating call and released
 * on scope exit (reference count in the low 23 bits of _refCount). Its destructor is emitted out
 * of line. */
static inline int countOf(const igIntList *list) { return list->_count; }
class SlotPlayerRef {
public:
    Rc *p;
    SlotPlayerRef(Rc *o) : p(o) {}
    ~SlotPlayerRef() { Rc *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to one Digimon record (a new one appended to the slot player, then each
 * one re-read from its list): released at the end of each loop pass. Its destructor is emitted out
 * of line. */
class DegiDataRef {
public:
    Rc *p;
    DegiDataRef(Rc *o) : p(o) {}
    ~DegiDataRef() { Rc *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

int beNDMWLoadCtrl2CommonIntf__StepReadMedia(beNDMWLoadCtrl2CommonIntf *self, int idx, int unused, int val, int mode) {
    int ret;
    int state;
    void *alloc;
    int n;
    igIntList *accessList;
    int i;
    int j;
    Node *node;
    unsigned short *unicodeText;
    int charIndex;
    int nextState;
    unsigned short *digimonName;

    ret = 0;
    state = 0;
    switch (mode) {
    case 0: state = NODE(self, idx)->st0; break;
    case 1: state = NODE(self, idx)->st1; break;
    case 2: state = NODE(self, idx)->st2; break;
    case 3: state = NODE(self, idx)->st3; break;
    }
    switch (state) {
    case 0:
        FUN_003f1460(self->_mcUtilCtrl, 4, val);
        nextState = state + 1;
        goto storeState;
    case 1:
        if (CFG(self)->_isResult == 1) {
            ret = 2;
            switch (CFG(self)->_result) {
            case 2: {
                ret = 1;
                ALLOC(alloc, self);
                SlotPlayerRef grp((Rc *)FUN_003c6360(alloc));
                for (i = 0; i < 4; i++) {
                    ALLOC(alloc, self);
                    DegiDataRef tmp((Rc *)beNDMWDegiData_Create(alloc));
                    ObjectList_AppendRetained(GRP(grp.p)->_saveDataList, tmp.p);
                }
                FUN_003f0e30(grp.p, ((Meta *)CFG(self)->_svData)->f8);
                GRP(grp.p)->_connectNO = val;
                accessList = (igIntList *)GRP(grp.p)->_accessPlList;
                n = accessList->_count;
                if (n < accessList->_capacity) accessList->_count = countOf(accessList) + 1;
                else List_Resize(accessList, n + 1, 4);
                ((int *)accessList->_data)[n] = idx;
                ObjectList_AppendRetained(self->_slotSaveData, grp.p);
                for (j = 0; j < 4; j++) {
                    DegiDataRef el((Rc *)((beNDMWDegiData **)((igObjectList *)GRP(grp.p)->_saveDataList)->_data)[j]);
                    if (el.p != 0) REFS(el.p) = REFS(el.p) + 1;
                    if (DD(el.p)->_isUse == 1 && DNAME(DD(el.p))[0] != 0xFFFF) {
                        Rc *str; /* the unicode text FUN_00382eb0 hands back (declared here: its slot sits below the record reference) */
                        digimonName = (unsigned short *)DD(el.p)->_dmName;
                        {
                            int insightEntry = FUN_00236f80(self->_insight, DAT_00589678[0]);
                            FUN_00382eb0(&str, insightEntry, digimonName);
                        }
                        unicodeText = (unsigned short *)((beUnicodeObj *)str)->_buffer;
                        for (charIndex = 0; ; ) {
                            ((unsigned short *)DD(el.p) + 5)[charIndex] /* matching construct: object-based index keeps the addu operand order */ = unicodeText[charIndex];
                            if (unicodeText[charIndex] == 0) break;
                            charIndex++;
                            if (charIndex >= 8) break;
                        }
                        for (; charIndex < 8; charIndex++) {
                            ((unsigned short *)DD(el.p) + 5)[charIndex] = 0;
                        }
                        DNAME(DD(el.p))[0] = 0xFFFF;
                        REL(str);
                    }
                }
                NODE(self, idx)->f32 = (int)grp.p;
                /* matching construct: leaving the block through this jump to the state store releases the slot
                 * player on the jump path, which keeps retail's branch after the release; falling out of the
                 * switch folds it away */
                nextState = state;
                goto storeState;
            }
            }
        }
        break;
    }
    nextState = state;
storeState:
    state = nextState;
    switch (mode) {
    case 0:
        node = NODE(self, idx);
        node->st0 = state;
        node->st3 = 0;
        node->st2 = 0;
        node->st1 = 0;
        break;
    case 1:
        node = NODE(self, idx);
        node->st1 = state;
        node->st3 = 0;
        node->st2 = 0;
        break;
    case 2:
        node = NODE(self, idx);
        node->st2 = state;
        node->st3 = 0;
        break;
    case 3:
        NODE(self, idx)->st3 = state;
        break;
    }
    return ret;
}
