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
struct CombinerHierarchyRec;
struct CombinerBlendView {
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
struct CombinerPool { char pad[8]; int _capacity; int pad12; igPoolObject **_data; int _used; };
struct CombinerBoneState { igPoolObject _base; igPoolObject *_animation; int _combineMode; int _transitionMode; int _status; int _baseState; unsigned char _new; char pad29[43]; long long _blendStartTime; char pad80[72]; long long _timeRequested; };
struct CombinerBitMask { char pad[16]; unsigned int *_data; };
struct CombinerTrack { igPoolObject _base; int _name; igPoolObject *_source; float _q[4]; float _t[3]; };
struct CombinerTrackList { char pad[16]; CombinerTrack **_data; };
struct CombinerAnimation { igPoolObject _base; int _name; int _priority; int _bindingList; CombinerTrackList *_trackList; char pad24[32]; CombinerBitMask *_useTrans; };
struct CombinerBinding { char pad[12]; int *_boneMap; };
struct CombinerHierarchyTrans { char pad[12]; float *_translations; };
extern "C" {
void FUN_001dca40(CombinerPool *, void *);
void FUN_001a6bb0(void);
void FUN_001a80b0(void);
void ObjectList_AppendRetained(CombinerStateList *, void *);
void FUN_001ad5c0(CombinerBlendView *, CombinerBoneInfo *, int);
long long FUN_001acb10(CombinerBlendView *);
int FUN_001abc20(CombinerBinding *, int);
int FUN_001ad990(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone, CombinerBinding *binding);
}
static inline igPoolObject *poolTake(CombinerPool *pool, void *ctor) {
    int i;
    if (pool->_used >= pool->_capacity) {
        FUN_001dca40(pool, ctor);
    }
    i = pool->_used;
    pool->_used = i + 1;
    return pool->_data[i];
}
static inline int useTranslation(CombinerAnimation *a, unsigned int i) {
    CombinerBitMask *m = a->_useTrans;
    if (m != 0) {
        return ((1 << (i & 31)) & m->_data[i >> 5]) != 0;
    }
    return 0;
}
static inline void retain(igPoolObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
}
static inline void setState(CombinerBoneInfo *b, igPoolObject *s) {
    retain(s);
    releaseWord((igPoolObject *)b->_animationState);
    b->_animationState = (igAnimationState *)s;
}
int FUN_001ad990(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone, CombinerBinding *binding) {

    int i;
    CombinerTrack *track;
    int bones;
    CombinerBoneState *state;
    int pi;
    igPoolObject *source;
    CombinerBoneInfo *b;
    pi = 0;
    c->_cacheValid = 0;
    bones = c->_animHierarchy->reset();
    if (c->_animationStateList->_count == 0) {
        combineMode = 0;
    }
    state = (CombinerBoneState *)poolTake(*(CombinerPool **)&DAT_00562540, (void *)FUN_001a6bb0);
    retain(&anim->_base);
    releaseWord(state->_animation);
    state->_animation = &anim->_base;
    state->_combineMode = combineMode;
    state->_transitionMode = transitionMode;
    state->_status = status;
    state->_new = 1;
    state->_base.slot21();
    state->_blendStartTime = 0;
    ObjectList_AppendRetained(c->_animationStateList, state);
    state->_timeRequested = FUN_001acb10(c);
    for (i = 0; i < bones; i++) {
        int t = binding->_boneMap[i];
        track = 0;
        if (t != -1) {
            track = anim->_trackList->_data[t];
        }
        if (track != 0) {
            b = (CombinerBoneInfo *)poolTake(*(CombinerPool **)&DAT_00562528, (void *)FUN_001a80b0);
            source = track->_source;
            if (source != 0) {
                int useT = useTranslation(anim, binding->_boneMap[i]);
                int priority = priorities[pi];
                int r;
                setState(b, &state->_base);
                retain(source);
                releaseWord((igPoolObject *)b->_transformSource);
                b->_transformSource = (int)source;
                b->_priority = priority;
                b->_useTranslation = useT;
                r = FUN_001abc20(binding, i);
                if (r != -1) {
                    b->_reflect = r;
                }
                if (!useT) {
                    float *v = *(float **)((char *)c->_animHierarchy + 12) + i * 3;
                    float y;
                    float z;
                    float x;
                    z = v[2];
                    y = v[1];
                    x = v[0];
                    b->_t[0] = x;
                    b->_t[1] = y;
                    b->_t[2] = z;
                }
            } else {
                unsigned int idx = binding->_boneMap[i];
                float *q = track->_q;
                float *v;
                float neg[4];
                int r;
                int priority;
                if (useTranslation(anim, idx)) {
                    v = anim->_trackList->_data[idx]->_t;
                } else {
                    v = *(float **)((char *)c->_animHierarchy + 12) + i * 3;
                }
                r = FUN_001abc20(binding, i);
                if (r != -1) {
                    neg[0] = q[0];
                    neg[1] = q[1];
                    neg[2] = q[2];
                    neg[3] = q[3];
                    q = neg;
                    neg[0] = -neg[0];
                    neg[1] = -neg[1];
                    neg[2] = -neg[2];
                    neg[r] = -neg[r];
                }
                priority = priorities[pi];
                setState(b, &state->_base);
                b->_q[0] = q[0];
                b->_q[1] = q[1];
                b->_q[2] = q[2];
                b->_q[3] = q[3];
                b->_t[0] = v[0];
                b->_t[1] = v[1];
                b->_t[2] = v[2];
                b->_priority = priority;
            }
            if (perBone) {
                pi++;
            }
            FUN_001ad5c0(c, b, i);
        }
    }
    return 1;
}
