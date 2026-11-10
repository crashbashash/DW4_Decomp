typedef struct ConvJob {
    int used;           /* 0x00 */
    int id;             /* 0x04 */
    int f8;             /* 0x08 */
    int stat;           /* 0x0c */
    int ret;            /* 0x10 */
    int mode;           /* 0x14 */
    int a0;             /* 0x18 */
    int a1;             /* 0x1c */
    int a2;             /* 0x20 */
    int a3;             /* 0x24 */
    int f40;            /* 0x28 */
    int f44;            /* 0x2c */
    short f48;          /* 0x30 */
    short f50;          /* 0x32 */
    short f52;          /* 0x34 */
    short f54;          /* 0x36 */
    short f56;          /* 0x38 */
    short pad58;
} ConvJob;

extern int DAT_004a8eb0[4];
extern ConvJob DAT_004a8eb8[16];

int memset();
void FUN_0025f300(int a, int b, short *first, short *second);
int FUN_0025fdf0(int a0, int a1, int a2, int *a3, int t0, int t1, short *t2, int t3, int s0);
int FUN_002606e0(int a0, int a1, int a2, int *a3, int t0, int *t1, int t2, int t3, short *s0,
                 int s1, int s2);

void FUN_0026ee48(void) {
    memset(&DAT_004a8eb8[0], 0, 0x3C0);
}

void FUN_0026ee70(void) {
    memset(&DAT_004a8eb8[0], 0, 0x3C0);
}

ConvJob *FUN_0026ee98(void)
{
    ConvJob *v;
    int i;
    for (i = 0; i < 16; i++) {
        if (DAT_004a8eb8[i].used == 0) {
            break;
        }
    }
    if (i == 16) {
        return 0;
    }
    v = &DAT_004a8eb8[i];
    memset(v, 0, sizeof(ConvJob));
    v->used = 1;
    v->id = i;
    v->f8 = 0;
    v->stat = 0;
    FUN_0025f300(500, 44100, &v->f48, &v->f50);
    memset(&v->f40, 0, 8);
    return v;
}

void FUN_0026ef68(ConvJob *object, int b, int a) {
    FUN_0025f300(a, b, &object->f48, &object->f50);
}

void FUN_0026ef90(void *arg0, void *arg1, void *arg2) {
    *(unsigned short *)((char *)(arg0) + 40) = (unsigned short) *(unsigned short *)((char *)(arg1) + 0);
    *(unsigned short *)((char *)(arg0) + 42) = (unsigned short) *(unsigned short *)((char *)(arg2) + 0);
    *(unsigned short *)((char *)(arg0) + 44) = (unsigned short) *(unsigned short *)((char *)(arg1) + 2);
    *(unsigned short *)((char *)(arg0) + 46) = (unsigned short) *(unsigned short *)((char *)(arg2) + 2);
}

void FUN_0026efb8(void *arg0, void *arg1, void *arg2) {
    *(unsigned short *)((char *)(arg1) + 0) = (unsigned short) *(unsigned short *)((char *)(arg0) + 40);
    *(unsigned short *)((char *)(arg2) + 0) = (unsigned short) *(unsigned short *)((char *)(arg0) + 42);
    *(unsigned short *)((char *)(arg1) + 2) = (unsigned short) *(unsigned short *)((char *)(arg0) + 44);
    *(unsigned short *)((char *)(arg2) + 2) = (unsigned short) *(unsigned short *)((char *)(arg0) + 46);
}

void FUN_0026efe0(void *arg0, short arg1, short arg2, short arg3) {
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    *(short *)((char *)(arg0) + 52) = arg1;
    *(short *)((char *)(arg0) + 54) = arg2;
    *(short *)((char *)(arg0) + 56) = arg3;
}

void FUN_0026eff0(void *arg0, unsigned short *arg1, unsigned short *arg2, unsigned short *arg3) {
    *arg1 = *(unsigned short *)((char *)(arg0) + 52);
    *arg2 = *(unsigned short *)((char *)(arg0) + 54);
    *arg3 = *(unsigned short *)((char *)(arg0) + 56);
}

void FUN_0026f010(int *entry)
{
    if (entry != 0) {
        entry[0] = 0;
        memset(entry, 0, 60);
    }
}

void FUN_0026f048(ConvJob *v, int value)
{
    v->f8 = value;
}

int FUN_0026f050(int *p)
{
    return *(int *)((char *)p + 12);
}

int FUN_0026f058(ConvJob *object, int f24, int f28, int f32, int f36) {
    if (object->stat == 0) {
        object->a3 = f36;
        object->a0 = f24;
        object->a1 = f28;
        object->a2 = f32;
        object->mode = 1;
        return 1;
    }
    return 0;
}

int FUN_0026f088(ConvJob *object, int f24, int f28, int f32, int f36) {
    if (object->stat == 0) {
        object->a3 = f36;
        object->a0 = f24;
        object->a1 = f28;
        object->a2 = f32;
        object->mode = 2;
        return 1;
    }
    return 0;
}

int FUN_0026f0b8(ConvJob *object, int f24, int f28, int f32, int f36) {
    if (object->stat == 0) {
        object->a3 = f36;
        object->a0 = f24;
        object->a1 = f28;
        object->a2 = f32;
        object->mode = 1;
        return 1;
    }
    return 0;
}

void FUN_0026f0e8(void *arg0) {
    if (*(int *)((char *)(arg0) + 12) == 0) {
        *(int *)((char *)(arg0) + 16) = 0;
        *(int *)((char *)(arg0) + 12) = 1;
    }
}

void FUN_0026f108(void *arg0) {
    *(int *)((char *)(arg0) + 12) = 0;
    memset((char *)arg0 + 0x28, 0, 8);
}

void FUN_0026f130(void *arg0) {
    if (*(int *)((char *)(arg0) + 12) == 3) {
        *(int *)((char *)(arg0) + 12) = 0;
    }
}

int FUN_0026f148(int *p)
{
    return *(int *)((char *)p + 16);
}

void FUN_0026f150(void) {
    DAT_004a8eb0[0] = 1;
}

void FUN_0026f160(ConvJob *c)
{
    if (c->stat == 1) {
        c->stat = 2;
    }
    if (c->stat != 2) {
        return;
    }
    if (c->mode == 1) {
        c->ret = FUN_0025fdf0(c->a0, c->a1, c->a2, &c->f40, c->f48, c->f50, &c->f52, c->f54, c->f56);
    } else {
        c->ret = FUN_002606e0(c->a0, c->a1, c->a2, &c->f40, c->a3, &c->f44, c->f48, c->f50, &c->f52,
                              c->f54, c->f56);
        if (c->ret % 2 == 1) {
            FUN_0026f150();
        }
    }
    c->stat = 3;
}

void FUN_0026f258(void) {
    int i;
    for (i = 0; i < 16; i++) {
        if (DAT_004a8eb8[i].used == 1) {
            FUN_0026f160(&DAT_004a8eb8[i]);
        }
    }
}
