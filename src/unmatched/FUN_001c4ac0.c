#pragma opt_common_subs off
typedef struct CullMatrixEntry { char _pad0[12]; float _matrix[16]; } CullMatrixEntry;
typedef struct CullMatrixStack { int _pad0[2]; int _count; int _pad0c; CullMatrixEntry **_data; CullMatrixEntry *_default; int _current; } CullMatrixStack;
typedef struct CullStackList { int _pad0[4]; CullMatrixStack **_data; } CullStackList;
typedef struct CullAttrState { char _pad0[16]; CullStackList *_stacks; char _pad14[48]; int *_slotOfIndex; } CullAttrState;
typedef struct CullMeta { int _pad0[2]; int _index; } CullMeta;
static inline CullMatrixEntry *entryAt(CullMatrixStack *s, int i) { return s->_data[i]; }
static inline CullMatrixEntry *currentEntry(CullMatrixStack *s) {
    int cur = s->_current;
    int n;
    if (cur >= 0) return entryAt(s, cur);
    n = s->_count;
    if (n != 0) return entryAt(s, n - 1);
    return s->_default;
}
static inline CullMatrixStack *stackOf(CullAttrState *st, CullMeta *meta) {
    return st->_stacks->_data[st->_slotOfIndex[meta->_index]];
}
typedef struct CullFrustumView { char _pad0[52]; CullAttrState *_state; char _pad38[420]; char _frustum[64]; float *_lastWorld; float *_lastView; } CullFrustumView;
typedef struct CullBoundsView { char _pad0[8]; float _min[3]; float _max[3]; } CullBoundsView;
extern CullMeta *DAT_0055efe8[4];
extern CullMeta *DAT_0055ef50[4];
void FUN_001c47a0(CullFrustumView *, float *, float *);
void FUN_001c47f0(char *, float *, float *);
void FUN_001c4ac0(CullFrustumView *o, CullBoundsView *b) {
    CullAttrState *st = o->_state;
    float *world = currentEntry(stackOf(st, DAT_0055efe8[0]))->_matrix;
    float *view = currentEntry(stackOf(st, DAT_0055ef50[0]))->_matrix;
    int same = o->_lastWorld == world;
    if (same) {
        same = o->_lastView == view;
    }
    if (!same) {
        FUN_001c47a0(o, world, view);
    }
    FUN_001c47f0(o->_frustum, b->_min, b->_max);
}
