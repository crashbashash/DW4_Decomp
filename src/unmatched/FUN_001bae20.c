typedef struct MatrixFrame { char _pad0[12]; char *_matrices; unsigned int _count; unsigned int _capacity; } MatrixFrame;
typedef struct MatrixFramePool { int _pad0[2]; int _capacity; int _pad0c; MatrixFrame **_data; int _used; } MatrixFramePool;
typedef struct MatrixArrayList { int _pad0[2]; int _count; int _pad0c; char **_data; } MatrixArrayList;
typedef struct BoneIndexList { int _pad0[2]; int _count; int _pad0c; int *_data; } BoneIndexList;
typedef struct BlendNodeView { char _pad0[40]; BoneIndexList *_boneIndices; } BlendNodeView;
typedef struct CompileTraversalHead { char _pad0[52]; int _state; char _pad38[196]; MatrixArrayList *_palettes; char _pad100[12]; MatrixFramePool *_frames; } CompileTraversalHead;
void FUN_00139c10(void);
void FUN_001dca40(MatrixFramePool *, void (*)(void));
void FUN_001b1030(int, MatrixFrame *);
void FUN_001b1100(int, MatrixFrame *);
int FUN_001b9320(CompileTraversalHead *, BlendNodeView *);
void FUN_00300f50(MatrixFrame *, char *);
char *FUN_00300db0(MatrixFrame *, int, int);
void Matrix44_Copy(char *, char *);
static inline char *paletteAt(MatrixArrayList *l, int i) { return l->_data[i]; }
int FUN_001bae20(CompileTraversalHead *o, BlendNodeView *node) {
    char *out;
    char *palette;
    int slot;
    MatrixArrayList *l;
    int i;
    int state;
    MatrixFrame *frame;
    unsigned int n;
    int r;
    MatrixFramePool *pool;
    pool = o->_frames;
    state = o->_state;
    if (!(pool->_used < pool->_capacity)) {
        FUN_001dca40(pool, FUN_00139c10);
    }
    slot = pool->_used;
    pool->_used = slot + 1;
    frame = pool->_data[slot];
    l = o->_palettes;
    palette = 0;
    if (l->_count > 0) {
        palette = paletteAt(l, l->_count - 1);
    }
    n = node->_boneIndices->_count;
    if (frame->_capacity < n) {
        if (frame->_matrices != 0) {
            FUN_00300f50(frame, frame->_matrices);
        }
        frame->_matrices = FUN_00300db0(frame, n << 6, 16);
        frame->_capacity = n;
    }
    frame->_count = n;
    out = frame->_matrices;
    for (i = 0; i < node->_boneIndices->_count; i++, out += 64) {
        Matrix44_Copy(out, palette + (node->_boneIndices->_data[i] << 6));
    }
    FUN_001b1030(state, frame);
    r = FUN_001b9320(o, node);
    FUN_001b1100(state, frame);
    if (r == 2) {
        return 2;
    }
    return 0;
}
