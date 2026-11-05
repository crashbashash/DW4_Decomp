/* 0x002dc340 - FUN_002dc340. Object list destructor; element virtual (vptr at +8) via a class with two leading ints; typed first parameter keeps the parameter-copy order. Alternate -O3. */
extern "C" {
int Memory_FreeBufferAlias_002ed5c0(void *);
void igObject_Destroy(void *);
extern int DAT_005305f8[4];
extern int DAT_00530618[4];
struct S;
void *FUN_002dc340(S *arg0, long long arg1);
}
class E { public: int a0; int a4; virtual void d0(int); };
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; int count; int cap; E **data; };
struct S { int vt0; int vt; RO *l; RO *r; };
extern "C" {
void *FUN_002dc340(S *arg0, long long arg1) {
    int var_s0;
    int s3;
    RO *a0;
    RO *v1;
    int v0;
    E *e;
    if (arg0 != 0) {
        arg0->vt = (int)&DAT_005305f8[0];
        for (var_s0 = 0; var_s0 < arg0->l->count; var_s0++) {
            s3 = var_s0 * 4;
            e = arg0->l->data[var_s0];
            if (e != 0) {
                e->d0(1);
            }
            v1 = arg0->l;
            v0 = v1->count;
            if (v0 != 0 && var_s0 >= 0 && var_s0 < v0) {
                *(int *)((char *)v1->data + s3) = 0;
            }
        }
        a0 = arg0->l;
        a0->u.w = a0->u.w - 1;
        if (a0->u.b.cnt == 0) igObject_Destroy(a0);
        arg0->l = 0;
        a0 = arg0->r;
        a0->u.w = a0->u.w - 1;
        if (a0->u.b.cnt == 0) igObject_Destroy(a0);
        arg0->r = 0;
        if (arg0 != 0) {
            arg0->vt = (int)&DAT_00530618[0];
        }
        if ((short)arg1 > 0) {
            Memory_FreeBufferAlias_002ed5c0(arg0);
        }
    }
    return arg0;
}
}
