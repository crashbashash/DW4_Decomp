extern "C" {
void FUN_00100390(void *, void *, int, int);
void *FUN_00137360(void *, short);
void igObject_Destroy(void *);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00525e50[4];
extern int DAT_00530a10[4];
}
struct T { int word0; int references; };
struct Obj {
    int *vt; T *m4; T *m8; T *m12; T *m16; T *m20; T *m24; T *m28; T *m32; T *m36; T *m40; T *m44; T *m48; T *m52; T *m56;
    char p60[244]; T *m304; T *m308;
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
extern "C" Obj *FUN_00150af0(Obj *arg0, short arg1);
Obj *FUN_00150af0(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_00525e50;
        arg0->rel(&arg0->m308);
        arg0->rel(&arg0->m304);
        FUN_00100390((char *)arg0 + 240, (void *)&FUN_00137360, 4, 16);
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m48);
        arg0->rel(&arg0->m44);
        arg0->rel(&arg0->m40);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        arg0->rel(&arg0->m28);
        arg0->rel(&arg0->m24);
        if (arg0) {
            arg0->vt = DAT_00530a10;
            arg0->rel(&arg0->m16);
            arg0->rel(&arg0->m8);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
