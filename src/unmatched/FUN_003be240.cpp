extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_0053d560[4];
}
struct Obj {
    int *vt; char p4[32]; T *m36; char p40[4]; T *m44; T *m48;
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
extern "C" Obj *FUN_003be240(Obj *arg0, short arg1);
Obj *FUN_003be240(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_0053d560[0];
        arg0->rel(&arg0->m48);
        arg0->rel(&arg0->m44);
        arg0->rel(&arg0->m36);
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
