extern "C" {
void FUN_001354b0(void *, int);
void FUN_00198190(void *, int);
void ObjectRef_Destruct_001c6460(void *, int);
void FUN_00229350(void *, int);
void FUN_0034c1b0(void *, int);
void FUN_00350b10(void *, int);
void FUN_00350b90(void *, int);
void FUN_00350c10(void *, int);
void FUN_00350c90(void *, int);
void FUN_00350d10(void *, int);
void FUN_00350d90(void *, int);
void FUN_00350e10(void *, int);
void FUN_00350e90(void *, int);
void ObjectRef_Destruct_00150eb0(void *, int);
void StringRef_Destruct_00130720(void *, int);
void igObject_Destroy(void *);
int thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00537ee0[4];
extern int DAT_00540520[4];
}
struct T { int word0; int references; };
struct Obj {
    int *vt; char p4[236]; T *m240; T *m244; T *m248; T *m252; char p256[8]; T *m264; T *m268;
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
extern "C" Obj *FUN_003bfde0(Obj *arg0, short arg1);
Obj *FUN_003bfde0(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_00540520;
        arg0->rel(&arg0->m268);
        arg0->rel(&arg0->m264);
        arg0->rel(&arg0->m252);
        arg0->rel(&arg0->m248);
        arg0->rel(&arg0->m244);
        arg0->rel(&arg0->m240);
        if (arg0) {
            arg0->vt = DAT_00537ee0;
            FUN_00198190((char *)arg0 + 232, -1);
            FUN_00350e90((char *)arg0 + 228, -1);
            StringRef_Destruct_00130720((char *)arg0 + 220, -1);
            FUN_00350e10((char *)arg0 + 212, -1);
            FUN_00229350((char *)arg0 + 208, -1);
            FUN_00350d90((char *)arg0 + 204, -1);
            FUN_00350d10((char *)arg0 + 200, -1);
            StringRef_Destruct_00130720((char *)arg0 + 184, -1);
            StringRef_Destruct_00130720((char *)arg0 + 180, -1);
            FUN_00350c90((char *)arg0 + 176, -1);
            FUN_0034c1b0((char *)arg0 + 172, -1);
            StringRef_Destruct_00130720((char *)arg0 + 116, -1);
            StringRef_Destruct_00130720((char *)arg0 + 96, -1);
            StringRef_Destruct_00130720((char *)arg0 + 92, -1);
            StringRef_Destruct_00130720((char *)arg0 + 88, -1);
            FUN_00350c10((char *)arg0 + 80, -1);
            StringRef_Destruct_00130720((char *)arg0 + 76, -1);
            FUN_001354b0((char *)arg0 + 72, -1);
            StringRef_Destruct_00130720((char *)arg0 + 56, -1);
            StringRef_Destruct_00130720((char *)arg0 + 52, -1);
            StringRef_Destruct_00130720((char *)arg0 + 48, -1);
            ObjectRef_Destruct_00150eb0((char *)arg0 + 44, -1);
            ObjectRef_Destruct_001c6460((char *)arg0 + 40, -1);
            ObjectRef_Destruct_001c6460((char *)arg0 + 36, -1);
            FUN_00350b90((char *)arg0 + 24, -1);
            StringRef_Destruct_00130720((char *)arg0 + 20, -1);
            FUN_00350b10((char *)arg0 + 12, -1);
            FUN_00350b10((char *)arg0 + 8, -1);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
