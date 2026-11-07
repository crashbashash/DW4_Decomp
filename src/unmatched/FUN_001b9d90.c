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
typedef struct { float x, y, z; } LightVec3;
typedef struct LightView { char _pad0[12]; int _type; char _pad10[100]; LightVec3 _worldPosition; LightVec3 _worldDirection; } LightView;
typedef struct LightListView { int _pad0[2]; int _count; int _pad0c; LightView **_data; } LightListView;
typedef struct LightSceneView { char _pad0[28]; LightListView *_lights; } LightSceneView;
typedef struct LightFieldMeta { int _pad0[2]; int _offset; } LightFieldMeta;
typedef struct LightTraversalView { char _pad0[52]; CullAttrState *_state; char _pad38[12]; int _collector; char _pad48[92]; float _view[16]; } LightTraversalView;
extern CullMeta *DAT_0055efe8[4];
extern LightFieldMeta *DAT_0055f0a0[4];
extern LightFieldMeta *DAT_0055f0c0[4];
void FUN_001dc400(int, LightSceneView *, CullAttrState *);
void FUN_001904f0(float *, float *, float *);
void FUN_00192fc0(LightVec3 *, char *, float *);
void FUN_00192f50(LightVec3 *, char *, float *);
int FUN_001b9d90(LightTraversalView *o, LightSceneView *scene) {
    LightVec3 position;
    LightVec3 direction;
    float matrix[16];
    int i;
    FUN_001dc400(o->_collector, scene, o->_state);
    FUN_001904f0(matrix, currentEntry(stackOf(o->_state, DAT_0055efe8[0]))->_matrix, o->_view);
    for (i = 0; i < scene->_lights->_count; i++) {
        LightView *light = scene->_lights->_data[i];
        FUN_00192fc0(&position, (char *)light + DAT_0055f0a0[0]->_offset, matrix);
        light->_worldPosition.x = position.x;
        light->_worldPosition.y = position.y;
        light->_worldPosition.z = position.z;
        if (light->_type == 0 || light->_type == 2) {
            FUN_00192f50(&direction, (char *)light + DAT_0055f0c0[0]->_offset, matrix);
            light->_worldDirection.x = direction.x;
            light->_worldDirection.y = direction.y;
            light->_worldDirection.z = direction.z;
        }
    }
    return 0;
}
