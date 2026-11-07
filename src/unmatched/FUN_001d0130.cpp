struct SceneMatrix { float m[16]; };
class SceneDrawItem {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();    virtual void d23();    virtual void d24();    virtual void d25();    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();
    virtual void setMatrix(SceneMatrix *);
};
struct SceneDrawItemPool { char pad0[8]; int capacity; char pad1[4]; SceneDrawItem **data; int used; };
struct SceneRenderer { char pad0[52]; void *state; char pad1[16]; SceneDrawItemPool *pool; };
class SceneTransformNode;
struct SceneChildList { char pad0[8]; int count; char pad1[4]; SceneTransformNode **data; };
struct SceneFieldInfo { char pad0[8]; int offset; };
class SceneTransformNode {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();
    virtual int getMeta();
    virtual void d21();    virtual void d22();    virtual void d23();    virtual void d24();    virtual void d25();    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();    virtual void d36();
    virtual void setContext(int);
    char pad0[24];
    SceneChildList *children;
    SceneMatrix local;
    char pad1[12];
    SceneMatrix bind;
    char *block;
};
extern "C" {
void FUN_001904f0(void *, SceneMatrix *, SceneMatrix *);
void FUN_001b1030(void *, SceneDrawItem *);
void FUN_001b1100(void *, SceneDrawItem *);
void FUN_001dca40(SceneDrawItemPool *, void *);
void FUN_001e04c0(SceneRenderer *, SceneTransformNode *);
void igMatrix44f_SetIdentity(SceneMatrix *);
void FUN_001356b0();
extern SceneFieldInfo *DAT_00562bc8;
extern int DAT_005618f8[4];
void FUN_001d0130(SceneTransformNode *self, SceneRenderer *renderer, SceneMatrix *parent, int context) {
    SceneMatrix world;
    int i;
    int count;
    SceneDrawItem *item;
    SceneDrawItemPool *pool;
    void *state;
    int meta;
    int got;
    SceneTransformNode *child;
    self->setContext(context);
    igMatrix44f_SetIdentity(&world);
    FUN_001904f0(&world, &self->local, parent);
    FUN_001904f0(self->block + DAT_00562bc8->offset, &self->bind, &world);
    count = 0;
    if (self->children != 0) {
        count = self->children->count;
    }
    for (i = 0; i < count; i++) {
        child = self->children->data[i];
        meta = DAT_005618f8[0];
        got = child->getMeta();
        if (meta == got) {
            FUN_001d0130(child, renderer, &world, context);
        } else {
            pool = renderer->pool;
            if (!(pool->used < pool->capacity)) {
                FUN_001dca40(pool, (void *)FUN_001356b0);
            }
            item = pool->data[pool->used++];
            item->setMatrix(&world);
            state = renderer->state;
            FUN_001b1030(state, item);
            FUN_001e04c0(renderer, child);
            FUN_001b1100(state, item);
        }
    }
}
}
