extern "C" {
int thunk_FUN_002ed460__002ff810(void *);
void igObject_Destroy(void *);
extern int DAT_00528250[4];
extern int DAT_005293c0[4];
}
struct T { int word0; int references; };
struct Obj {
    int *vt;
    char p4[24];
    T *m28;
    T *m32;
    T *m36;
    char p40[12];
    T *m52;
    T *m56;
    T *m60;
    T *m64;
    T *m68;
    T *m72;
    T *m76;
    T *m80;
    T *m84;
    T *m88;
    T *m92;
    T *m96;
    char p100[132];
    T *m232;
    T *m236;
    T *m240;
    T *m244;
    T *m248;
    T *m252;
    T *m256;
    T *m260;
    T *m264;
    T *m268;
    char p272[64];
    T *m336;
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
extern "C" Obj *FUN_001a0910(Obj *arg0, short arg1);
Obj *FUN_001a0910(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_005293c0;
        arg0->rel(&arg0->m336);
        arg0->rel(&arg0->m268);
        arg0->rel(&arg0->m264);
        arg0->rel(&arg0->m260);
        arg0->rel(&arg0->m256);
        arg0->rel(&arg0->m252);
        arg0->rel(&arg0->m248);
        arg0->rel(&arg0->m244);
        arg0->rel(&arg0->m240);
        arg0->rel(&arg0->m236);
        arg0->rel(&arg0->m232);
        arg0->rel(&arg0->m96);
        arg0->rel(&arg0->m92);
        arg0->rel(&arg0->m88);
        arg0->rel(&arg0->m84);
        arg0->rel(&arg0->m80);
        arg0->rel(&arg0->m76);
        arg0->rel(&arg0->m72);
        arg0->rel(&arg0->m68);
        arg0->rel(&arg0->m64);
        arg0->rel(&arg0->m60);
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        if (arg0) {
            arg0->vt = DAT_00528250;
            arg0->rel(&arg0->m28);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
