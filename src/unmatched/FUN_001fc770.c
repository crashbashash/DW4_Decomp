extern int DAT_00491330[4];
extern int DAT_00491334[4];
extern int DAT_00491338[4];
extern int DAT_0049133c[4];
extern int DAT_00491340[4];
extern int DAT_00491344[4];
extern int DAT_00491348[4];
extern int DAT_00491350[4];
extern int DAT_00491358[4];
extern int DAT_00569340[4];
void FUN_001fc770(int **pp, int arg1, int arg2) {
    int *w, *t_;
    int idx;
    char *rec;
    if (arg2 != 0) {
        w = *pp;
        *pp = w + 4;
        w[0] = DAT_00491330[0];
        w[1] = DAT_00491334[0];
        w[2] = DAT_00491338[0];
        w[3] = DAT_0049133c[0];
    }
    { t_ = *pp; *pp = t_ + 1; *t_ = (DAT_00491350[0]); }
    { t_ = *pp; *pp = t_ + 1; *t_ = (arg1); }
    if (arg1 > 0) *(*pp)++ = arg1; else *(*pp)++ = 0x1234;
    { t_ = *pp; *pp = t_ + 1; *t_ = (arg1); }
    if (arg1 > 1) idx = arg1 - 1; else idx = 0;
    rec = (char *)&DAT_00569340[0] + idx * 0x1C0;
    *(*pp)++ = DAT_00491340[0];
    *(*pp)++ = DAT_00491344[0];
    *(*pp)++ = DAT_00491348[0];
    if (arg1 > 0) {
        *(*pp)++ = *(int *)(rec + 280);
        *(*pp)++ = *(int *)(rec + 284);
        *(*pp)++ = 0x43;
        *(*pp)++ = *(int *)(rec + 56);
        *(*pp)++ = *(int *)(rec + 60);
        *(*pp)++ = 7;
        *(*pp)++ = *(int *)(rec + 112);
        *(*pp)++ = *(int *)(rec + 116);
        *(*pp)++ = 0x15;
    } else {
        *(*pp)++ = *(int *)(rec + 272);
        *(*pp)++ = *(int *)(rec + 276);
        *(*pp)++ = 0x42;
        *(*pp)++ = *(int *)(rec + 48);
        *(*pp)++ = *(int *)(rec + 52);
        *(*pp)++ = 6;
        *(*pp)++ = *(int *)(rec + 104);
        *(*pp)++ = *(int *)(rec + 108);
        *(*pp)++ = 0x14;
    }
    { t_ = *pp; *pp = t_ + 1; *t_ = (0); }
    { t_ = *pp; *pp = t_ + 1; *t_ = (0); }
    *(*pp)++ = 0x3F;
    { t_ = *pp; *pp = t_ + 1; *t_ = (DAT_00491358[0]); }
}
