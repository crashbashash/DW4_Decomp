#include "dw4/reflected.h"
class igPoolObject {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual void slot21();
    virtual int reset();
    unsigned int _refCount;
};
struct CombinerBoneInfo { char pad[8]; int _lastKeyframe; igAnimationState *_animationState; int _transformSource; float _q[4]; float _t[3]; int _priority; unsigned char _useTranslation; char pad53[3]; int _reflect; };
struct CombinerBoneRow { char pad[8]; int _count; int _capacity; CombinerBoneInfo **_data; };
struct CombinerBoneRows { char pad[16]; CombinerBoneRow **_data; };
struct CombinerIntList { char pad[8]; int _count; int _capacity; int *_data; };
struct CombinerStateList { char pad[8]; int _count; int _capacity; igPoolObject **_data; };
struct CombinerStateRec { int _vtable; unsigned int _refCount; int pad8; int _combineMode; char pad16[108]; unsigned char _isCycleMatchTarget; };
struct CombinerStateView {
    char pad0[12];
    igPoolObject *_animHierarchy;
    char pad16[32];
    CombinerBoneRows *_boneInfoListList;
    CombinerIntList *_boneInfoListBase;
    CombinerStateList *_animationStateList;
    char pad60[20];
    unsigned char _cacheValid;
};
extern int DAT_00562540;
extern int DAT_00562528;
extern "C" {
void FUN_001dcb80(int, void *);
int igObject_Destroy(void *);
void List_RemoveWordAt(void *, int);
void FUN_001ae250(void *, int);
void FUN_001ae1d0(void *, int);
void FUN_001ae1b0(void *, float, float, float, float);
void FUN_001ae1a0(void *, float, float, float);
}
static inline void releaseWord(igPoolObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
}
static inline void clearBoneInfo(CombinerBoneInfo *b) {
    FUN_001ae250(&b->_animationState, 0);
    FUN_001ae1d0(&b->_transformSource, 0);
    FUN_001ae1b0(b->_q, 0.0f, 0.0f, 0.0f, 0.0f);
    FUN_001ae1a0(b->_t, 0.0f, 0.0f, 0.0f);
    b->_priority = 0;
    b->_useTranslation = 0;
    b->_lastKeyframe = 1;
    b->_reflect = -1;
}
extern "C" {
void FUN_001ad860(CombinerStateView *, igPoolObject *);
int FUN_001ae2d0(CombinerStateView *c, igPoolObject *state);
}
static inline void setBase(CombinerStateView *c, int bone, int value) {
    CombinerIntList *s = c->_boneInfoListBase;
    int n = s->_count;
    if (n != 0 && bone >= 0 && bone < n) {
        s->_data[bone] = value;
    }
    c->_cacheValid = 0;
}
int FUN_001ae2d0(CombinerStateView *c, igPoolObject *state) {
    igPoolObject *found;
    int bones;
    bool have;
    int si;
    int i;
    int count;
    CombinerStateList *states;
    states = c->_animationStateList;
    count = states->_count;
    found = 0;
    bones = c->_animHierarchy->reset();
    have = 0;
    for (si = 0; si < count; si++) {
        found = states->_data[si];
        if (found == state) {
            have = 1;
            break;
        }
    }
    if (!have) {
        return 0;
    }
    if (((CombinerStateRec *)found)->_isCycleMatchTarget) {
        FUN_001ad860(c, found);
    }
    c->_cacheValid = 0;
    for (i = 0; i < bones; i++) {
        CombinerBoneRow *row = c->_boneInfoListList->_data[i];
        int n = row->_count;
        int j;
        for (j = 0; j < n; j++) {
            CombinerBoneInfo *b = row->_data[j];
            if ((igPoolObject *)b->_animationState == state) {
                clearBoneInfo(b);
                FUN_001dcb80(DAT_00562528, b);
                releaseWord((igPoolObject *)row->_data[j]);
                List_RemoveWordAt(row, j);
                row->_data[row->_count] = 0;
                if (n - 1 > 0) {
                    bool set;
                    int k;
                    k = n - 2;
                    set = 0;
                    for (; k >= 0; k--) {
                        if (row->_data[k]->_animationState->_combineMode == 0) {
                            set = 1;
                            setBase(c, i, k);
                            break;
                        }
                    }
                    if (!set) {
                        setBase(c, i, 0);
                    }
                }
                break;
            }
        }
    }
    found->reset();
    FUN_001dcb80(DAT_00562540, found);
    releaseWord(states->_data[si]);
    List_RemoveWordAt(states, si);
    states->_data[states->_count] = 0;
    if (c->_animationStateList->_count == 1) {
        ((igAnimationState *)states->_data[0])->_combineMode = 0;
    }
    return 1;
}
