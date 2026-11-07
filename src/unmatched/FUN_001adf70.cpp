#include "dw4/reflected.h"
class igPoolObject {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual int reset();
    unsigned int _refCount;
};
struct PoolObjectList { char pad[8]; int _count; int _capacity; igPoolObject **_data; };
struct BoneInfoSlot { char pad[8]; int _lastKeyframe; int _animationState; int _transformSource; float _q[4]; float _t[3]; int _priority; unsigned char _useTranslation; char pad53[3]; int _reflect; };
struct BoneInfoSlotList { char pad[8]; int _count; int _capacity; BoneInfoSlot **_data; };
struct BoneInfoRows { char pad[16]; BoneInfoSlotList **_data; };
struct CombinerResetView {
    char pad0[12];
    igPoolObject *_animHierarchy;
    char pad16[32];
    BoneInfoRows *_boneInfoListList;
    int pad52;
    PoolObjectList *_animationStateList;
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
int FUN_001adf70(CombinerResetView *c);
}
int FUN_001adf70(CombinerResetView *c) {
    PoolObjectList *states;
    int k;
    int count;
    int bones;
    int i;
    int n;
    states = c->_animationStateList;
    count = states->_count;
    bones = c->_animHierarchy->reset();
    if (count == 0) {
        return 0;
    }
    c->_cacheValid = 0;
    n = states->_count;
    for (i = 0; i < n; i++) {
        igPoolObject *s = states->_data[0];
        igPoolObject *o;
        s->reset();
        FUN_001dcb80(DAT_00562540, s);
        o = states->_data[0];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(states, 0);
        states->_data[states->_count] = 0;
    }
    for (k = 0; k < bones; k++) {
        BoneInfoSlotList *row = c->_boneInfoListList->_data[k];
        int rowCount = row->_count;
        BoneInfoSlot *b;
        int j;
        for (j = 0; j < rowCount; j++) {
            igPoolObject *o;
            b = row->_data[0];
            FUN_001ae250(&b->_animationState, 0);
            FUN_001ae1d0(&b->_transformSource, 0);
            FUN_001ae1b0(b->_q, 0.0f, 0.0f, 0.0f, 0.0f);
            FUN_001ae1a0(b->_t, 0.0f, 0.0f, 0.0f);
            b->_priority = 0;
            b->_useTranslation = 0;
            b->_lastKeyframe = 1;
            b->_reflect = -1;
            FUN_001dcb80(DAT_00562528, b);
            o = (igPoolObject *)row->_data[0];
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt(row, 0);
            row->_data[row->_count] = 0;
        }
    }
    return 1;
}
