int igObject_IsKindOf();
extern int DAT_00560f68[4];

typedef struct Q { char pad[8]; int f8; } Q;

int FUN_0022d050(Q *arg0, int arg1, Q *arg2, int arg3) {
    unsigned char *dst;
    unsigned char *src;
    Q *var_s3;
    Q *var_s1;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00560f68[0]) != 0)) {
        var_s3 = arg0;
    } else {
        var_s3 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00560f68[0]) != 0)) {
        var_s1 = arg2;
    } else {
        var_s1 = 0;
    }
    if ((var_s3 != 0) && (var_s1 != 0)) {
        src = (unsigned char *)(arg1 + var_s3->f8);
        dst = (unsigned char *)(arg3 + var_s1->f8);
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        return 1;
    }
    return 0;
}
