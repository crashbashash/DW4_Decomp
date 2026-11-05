struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" {
int Memory_GetAllocatorBySelector(...);
int ObjectList_ResizeRetained(...);
void *igAnimationState_GetMetaObject(...);
void *igEnbayaContextPool_Create(...);
int igObject_Destroy(...);
}
struct List {
    char p0[8]; volatile int count; char p12[4]; Ref **data;
    void clear() {
        int n = count;
        for (int i = 0; i < n; i++) {
            Ref *r = data[i];
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
        }
        int n2 = count;
        for (int i = 0; i < n2; i++) data[i] = 0;
        count = 0;
    }
};
struct Meta { char p0[60]; void *f60; };
extern "C" void FUN_001c10e0(void);
extern List *DAT_00562540[4];
extern Ref *DAT_00562718[4];
extern void *DAT_00562728[4];
extern int DAT_00587038[4];
extern unsigned char GPR_00554b90;
extern char DAT_00560000[];
extern "C" void FUN_001c0f00(int mode) {
    if ((mode & 0xFF) != GPR_00554b90) {
        int saved = 0;
        List *list = DAT_00562540[0];
        if (list != 0) {
            saved = list->count;
            list->clear();
        }
        if (mode != 0) {
            DAT_00562728[0] = ((Meta *)igAnimationState_GetMetaObject())->f60;
            Meta *m2 = (Meta *)igAnimationState_GetMetaObject();
            m2->f60 = (void *)FUN_001c10e0;
            int a = Memory_GetAllocatorBySelector(DAT_00587038[0]);
            Ref *p = DAT_00562718[0];
            if (p != 0) {
                p->u.w = p->u.w - 1;
                if (p->u.b.cnt == 0) igObject_Destroy(p);
            }
            DAT_00562718[0] = (Ref *)igEnbayaContextPool_Create(a);
        } else {
            ((Meta *)igAnimationState_GetMetaObject())->f60 = DAT_00562728[0];
            Ref *p = DAT_00562718[0];
            if (p != 0) {
                p->u.w = p->u.w - 1;
                if (p->u.b.cnt == 0) igObject_Destroy(p);
            }
            DAT_00562718[0] = 0;
        }
        if (DAT_00562540[0] != 0) ObjectList_ResizeRetained(DAT_00562540[0], saved);
        GPR_00554b90 = mode;
    }
}
