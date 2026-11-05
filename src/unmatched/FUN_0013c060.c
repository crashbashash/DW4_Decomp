struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
void *FUN_0013a640();
int Memory_GetAllocatorBySelector();
int igObject_Destroy(void *);
extern struct Ref *DAT_0055f4b8[4];
extern int DAT_00587028[4];
extern int DAT_005870f8[4];
extern unsigned char GPR_00554c14;
struct Ref *FUN_0013c060(void) {
    int a;
    struct Ref *p;
    if (DAT_0055f4b8[0] == 0) {
        if (GPR_00554c14 != 0) { int x = Memory_GetAllocatorBySelector(DAT_00587028[0]); a = x; } else { int y = Memory_GetAllocatorBySelector(DAT_005870f8[0]); a = y; }
        p = DAT_0055f4b8[0];
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        DAT_0055f4b8[0] = (struct Ref *)FUN_0013a640(a);
    }
    return DAT_0055f4b8[0];
}
