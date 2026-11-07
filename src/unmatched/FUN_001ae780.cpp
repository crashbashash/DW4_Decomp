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
struct CombinerPool { char pad[8]; int _capacity; int pad12; igPoolObject **_data; int _used; };
struct CombinerNewState { igPoolObject _base; igPoolObject *_animation; int _combineMode; int _transitionMode; int _status; int _baseState; unsigned char _new; char pad29[43]; long long _blendStartTime; };
struct CombinerQuat { float x, y, z, w; };
extern CombinerPool *DAT_00562540p;
extern igPoolObject *DAT_00562558;
extern CombinerPool *DAT_00562528p;
extern "C" {
void FUN_001dca40(CombinerPool *, void *);
void FUN_001a6bb0(void);
void FUN_001a80b0(void);
void ObjectList_AppendRetained(CombinerStateList *, void *);
void FUN_001925f0(CombinerQuat *, float *);
void FUN_001ad5c0(CombinerStateView *, CombinerBoneInfo *, int);
int FUN_001adf70(CombinerStateView *);
int FUN_001ae780(CombinerStateView *c, CombinerStateView *from);
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
int FUN_001ae780(CombinerStateView *c, CombinerStateView *from) {
    CombinerStateView *src;
    int need;
    int bones;
    igPoolObject *anim;
    CombinerNewState *state;
    int i;
    if (!from) {
        from = c;
    }
    { CombinerStateView *const pick = from; src = pick; }
    need = c->_animHierarchy->reset();
    if (need > src->_animHierarchy->reset()) {
        return 0;
    }
    FUN_001adf70(c);
    c->_cacheValid = 0;
    bones = c->_animHierarchy->reset();
    state = (CombinerNewState *)poolTake(*(CombinerPool **)&DAT_00562540, (void *)FUN_001a6bb0);
    anim = DAT_00562558;
    if (anim != 0) {
        anim->_refCount = anim->_refCount + 1;
    }
    releaseWord(state->_animation);
    state->_animation = anim;
    state->_combineMode = 0;
    state->_transitionMode = 4;
    state->_status = 1;
    state->_new = 1;
    state->_base.slot21();
    state->_blendStartTime = 0;
    ObjectList_AppendRetained(c->_animationStateList, state);
    for (i = 0; i < bones; i++) {
        CombinerBoneInfo *info = (CombinerBoneInfo *)poolTake(*(CombinerPool **)&DAT_00562528, (void *)FUN_001a80b0);
        float *m;
        float tx, ty, tz;
        CombinerQuat q;
        releaseWord((igPoolObject *)info->_transformSource);
        info->_transformSource = 0;
        info->_reflect = -1;
        m = (float *)(*(int *)((char *)src + 64) + (i << 6));
        tz = m[14];
        ty = m[13];
        tx = m[12];
        FUN_001925f0(&q, m);
        if (state != 0) {
            state->_base._refCount = state->_base._refCount + 1;
        }
        releaseWord((igPoolObject *)info->_animationState);
        info->_animationState = (igAnimationState *)state;
        info->_q[0] = q.x;
        info->_q[1] = q.y;
        info->_q[2] = q.z;
        info->_q[3] = q.w;
        info->_t[0] = tx;
        info->_t[1] = ty;
        info->_t[2] = tz;
        info->_priority = 0;
        FUN_001ad5c0(c, info, i);
    }
    return 1;
}
