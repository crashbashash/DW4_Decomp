extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(...);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00524950[4];
extern int DAT_00526410[4];
}
struct Obj {
    int *vt; char p4[4]; char *m8; T *m12; T *m16; T *m20;
    inline void rel(T **self) {
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void relS(char **self) {
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" Obj *FUN_0014a910(Obj *arg0, short arg1);
Obj *FUN_0014a910(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00526410[0];
        arg0->rel(&arg0->m20);
        arg0->rel(&arg0->m16);
        arg0->rel(&arg0->m12);
        if (arg0) {
            arg0->vt = &DAT_00524950[0];
            arg0->relS(&arg0->m8);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
