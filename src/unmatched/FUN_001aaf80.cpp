extern "C" {
int FUN_001958f0(void *, int);
int FUN_00195970(void *, int);
void igObject_Destroy(void *);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00528dd0[4];
extern int DAT_00528fa0[4];
}
struct T { int word0; int references; };
struct Obj {
    int *vt;
    char p4[28];
    T *m32;
    T *m36;
    char p40[12];
    T *m52;
    char p56[8];
    T *m64;
    T *m68;
    char p72[4];
    T *m76;
    T *m80;
    T *m84;
    T *m88;
    T *m92;
    T *m96;
    T *m100;
    T *m104;
    T *m108;
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
extern "C" Obj *FUN_001aaf80(Obj *arg0, short arg1);
Obj *FUN_001aaf80(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_00528fa0;
        arg0->rel(&arg0->m108);
        arg0->rel(&arg0->m104);
        arg0->rel(&arg0->m100);
        arg0->rel(&arg0->m96);
        arg0->rel(&arg0->m92);
        arg0->rel(&arg0->m88);
        arg0->rel(&arg0->m84);
        arg0->rel(&arg0->m80);
        arg0->rel(&arg0->m76);
        arg0->rel(&arg0->m68);
        arg0->rel(&arg0->m64);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        if (arg0) {
            arg0->vt = DAT_00528dd0;
            FUN_001958f0((char *)arg0 + 28, -1);
            FUN_00195970(arg0, 0);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
