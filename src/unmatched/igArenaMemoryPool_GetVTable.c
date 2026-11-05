typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
int FUN_0031eb90();
extern int DAT_00531030[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[208]; };
int igArenaMemoryPool_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p;
    S_ref *r;

    FUN_0031eb90(u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00531030[0];
    p = (S_ref *)&u.b[176];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    r = (S_ref *)&u.b[120];
    if (r != 0) {
        r = *(S_ref **)r;
        if (r != 0) {
            r->f4 = (int)((int) (r->f4 - 1));
            if (((unsigned long long) ((long long) r->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    return temp_s0;
}
