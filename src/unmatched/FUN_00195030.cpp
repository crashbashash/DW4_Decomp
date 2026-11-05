extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_005283e0[4];
}
struct Obj {
    int *vt; char p4[4]; T *m8; T *m12; T *m16; T *m20;
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
};
extern "C" Obj *FUN_00195030(Obj *arg0, short arg1);
Obj *FUN_00195030(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_005283e0[0];
        arg0->rel(&arg0->m20);
        arg0->rel(&arg0->m16);
        arg0->rel(&arg0->m12);
        arg0->rel(&arg0->m8);
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
