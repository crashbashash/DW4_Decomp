extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int FUN_00463910(...);
int FUN_00100610(...);
}
struct Obj {
    int *vt; char p4[24]; T *m28; T *m32; T *m36; T *m40; char p44[4]; T *m48; T *m52; T *m56;
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
extern "C" Obj *FUN_0025a330(Obj *arg0, short arg1);
Obj *FUN_0025a330(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m48);
        arg0->rel(&arg0->m40);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        arg0->rel(&arg0->m28);
        FUN_00463910(arg0, -1);
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
