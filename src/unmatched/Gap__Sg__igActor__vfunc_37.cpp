struct ActorMatrixEntry { char _pad0[12]; float _matrix[16]; };
struct ActorMatrixStack { int _pad0[2]; int _count; int _pad0c; ActorMatrixEntry **_data; };
struct ActorStackList { int _pad0[4]; ActorMatrixStack **_data; };
struct ActorAttrState { char _pad0[16]; ActorStackList *_stacks; char _pad14[48]; int *_slotOfIndex; };
struct ActorMeta { int _pad0[2]; int _offset; };
struct ActorCountedList { int _pad0[2]; int _count; };
struct ActorTraversal { char _pad0[52]; ActorAttrState *_state; char _pad38[108]; float _view[16]; };
class ActorAnimationHolder {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void updateNodes(void *t, void *actor, int status, float *bones, float *blend, void *list);
};
class ActorAnimationStateSlots {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual int update(void *t, void *actor);
    virtual int isReady();
    virtual void setReady(int v);
    virtual float *bones();
    virtual void slot26();
    virtual float *blends();
};
struct ActorAnimationState : ActorAnimationStateSlots { int _pad4[2]; ActorAnimationHolder *_holder; };
struct ActorChildren { char _pad[8]; };
struct ActorView {
    char _pad0[32]; ActorAnimationState *_animationState; float *_bones; float *_blends; ActorChildren _children; ActorCountedList *_nodes;
    char _pad38[64]; unsigned char _forced; unsigned char _useCached; char _pad7a[2]; float _world[16]; float _view[16];     unsigned char _animate; unsigned char _traverse;
};
extern ActorMeta *DAT_0055efe8[4];
extern ActorMeta *DAT_005624c0[4];
extern "C" {
void Matrix44_Copy(float *, float *);
void FUN_001904f0(float *, char *, float *);
void FUN_001b8a20(ActorView *, ActorTraversal *);
int FUN_001b8a10(ActorChildren *);
void *FUN_001b8a00(ActorChildren *);
int FUN_001af620(void *, ActorTraversal *);
void FUN_001b89b0(ActorView *, ActorTraversal *);
}
static inline ActorMatrixEntry *entryAt(ActorMatrixStack *s, int i) { return s->_data[i]; }
static inline ActorMatrixEntry *lastEntry(ActorMatrixStack *s) {
    int n = s->_count;
    if (n == 0) return 0;
    return entryAt(s, n - 1);
}
static inline float *bonesOf(ActorView *o) {
    if (o->_useCached) return o->_bones;
    return o->_animationState->bones();
}
static inline float *blendsOf(ActorView *o) {
    if (o->_useCached) return o->_blends;
    return o->_animationState->blends();
}
extern "C" int Gap__Sg__igActor__vfunc_37(ActorView *o0, ActorTraversal *t0) {
    ActorAnimationHolder *holder;
    int r;
    ActorCountedList *nodes;
    float *world;
    float *bones;
    ActorView *o;
    ActorTraversal *t;
    int status;
    char *rootBone;
    o = (ActorView *)(int)o0;
    t = (ActorTraversal *)(int)t0;
    if (o->_animate) {
        ActorAttrState *st = t->_state;
        Matrix44_Copy(o->_world, lastEntry(st->_stacks->_data[st->_slotOfIndex[DAT_0055efe8[0]->_offset]])->_matrix);
        Matrix44_Copy(o->_view, t->_view);
        if (o->_nodes->_count == 0 && o->_forced == 0) {
            o->_useCached = 0;
        } else {
            o->_useCached = 1;
        }
        {
            world = o->_world;
            rootBone = (char *)o + DAT_005624c0[0]->_offset;
            FUN_001904f0(bonesOf(o), rootBone, world);
        }
        status = o->_animationState->update(t, o);
        if (o->_useCached == 0) {
            if (o->_animationState->isReady() != 0) {
                goto skip;
            }
            o->_animationState->setReady(1);
        }
        {
            holder = o->_animationState->_holder;
            nodes = o->_nodes;
            bones = bonesOf(o);
            holder->updateNodes(t, o, status, bones, blendsOf(o), nodes);
        }
    }
skip:
    if (o->_traverse) {
        FUN_001b8a20(o, t);
        if (FUN_001b8a10(&o->_children) != 0) {
            r = FUN_001af620(FUN_001b8a00(&o->_children), t);
        } else {
            r = 0;
        }
        FUN_001b89b0(o, t);
        return r;
    }
    return 0;
}
