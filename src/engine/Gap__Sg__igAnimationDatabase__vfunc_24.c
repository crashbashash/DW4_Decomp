typedef struct R { int pad0; int refs; int f8; int f12; int *f16; } R;
typedef struct O { char pad[8]; char *f8; char pad2[8]; void *f20; void *f24; void *f28; void *f32; void *f36; } O;
extern char DAT_004e0858[];
extern char DAT_004e4130[];
extern char DAT_004e44f8[];
extern char DAT_004e4500[];
extern int DAT_00562370[4];
extern int DAT_00562428[4];
extern int *DAT_00562560[4];
extern int DAT_00585b20[4];
extern int DAT_00585be0[4];
int FUN_00129ef8(char *, char *, char *, int *);
int strlen(char *);
int FUN_0012aba0(char *, char *, int);
int igObject_IsKindOf(void *, int);
void *igMetaObject_FindFieldByName(int, char *);
int igObject_Destroy(void *);
void *igProperty_FindByName(void *, int, char *);
int igStrCmp(char *, char *);
void *Gap__Sg__igAnimationDatabase__vfunc_24(O *arg0, char *arg1) {
    int sp106C;
    R *volatile sp1068;
    R *volatile sp1064;
    R *volatile sp1060;
    R *volatile sp105C;
    char sp50[4096];
    char *var_a1;
    R *var_s0;
    R *var_s1;
    R *t;

    var_a1 = arg0->f8;
    if (var_a1 != 0) {
        var_a1 = (char *)var_a1;
    } else {
        var_a1 = DAT_004e0858;
    }
    if (igStrCmp(arg1, var_a1) == 0) {
        return arg0;
    }
    var_s0 = igProperty_FindByName(arg0->f20, DAT_00585be0[0], arg1);
    if (var_s0 == 0) {
        var_s0 = igProperty_FindByName(arg0->f28, DAT_00585be0[0], arg1);
    }
    if (var_s0 == 0) {
        var_s0 = igProperty_FindByName(arg0->f24, DAT_00585be0[0], arg1);
    }
    if (var_s0 == 0) {
        var_s0 = igProperty_FindByName(arg0->f32, DAT_00585be0[0], arg1);
    }
    if (var_s0 == 0) {
        var_s0 = igProperty_FindByName(arg0->f36, DAT_00585be0[0], arg1);
    }
    if (FUN_0012aba0(arg1, DAT_004e44f8, strlen(DAT_004e44f8)) == 0) {
        if (DAT_00562560[0] == 0) {
            var_s1 = igMetaObject_FindFieldByName(DAT_00562370[0], DAT_004e4130);
            if ((var_s1 != 0) && (igObject_IsKindOf(var_s1, DAT_00585b20[0]) != 0)) {
                var_s1 = (R *)var_s1;
            } else {
                var_s1 = 0;
            }
            DAT_00562560[0] = (int *)var_s1;
        }
        FUN_00129ef8(arg1 + strlen(DAT_004e44f8), DAT_004e4500, sp50, &sp106C);
        sp1068 = igProperty_FindByName(arg0->f24, DAT_00585be0[0], sp50);
        t = sp1068;
        if (t != 0) {
            t->refs = t->refs + 1;
        }
        t = sp1068;
        if (t != 0) {
            var_s1 = *(R **)((char *)t + DAT_00562560[0][2]);
            if ((var_s1 != 0) && (igObject_IsKindOf(var_s1, DAT_00562428[0]) != 0)) {
                var_s1 = (R *)var_s1;
            } else {
                var_s1 = 0;
            }
            sp1064 = var_s1;
            t = sp1064;
            if (t != 0) {
                t->refs = t->refs + 1;
            }
            t = sp1064;
            if (t != 0) {
                sp1060 = (R *)t->f16[sp106C];
                t = sp1060;
                if (t != 0) {
                    t->refs = t->refs + 1;
                }
                t = sp1060;
                if (t != 0) {
                    var_s0 = (R *)t->f12;
                }
                if (t != 0) {
                    t->refs = t->refs - 1;
                    if (((unsigned long long) ((long long) t->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
            }
            t = sp1064;
            if (t != 0) {
                t->refs = t->refs - 1;
                if (((unsigned long long) ((long long) t->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        t = sp1068;
        if (t != 0) {
            t->refs = t->refs - 1;
            if (((unsigned long long) ((long long) t->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    sp105C = var_s0;
    t = sp105C;
    if (t != 0) {
        t->refs = t->refs + 1;
    }
    t = sp105C;
    if (t != 0) {
        t->refs = t->refs - 1;
        t = sp105C;
        if (((unsigned long long) ((long long) t->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    return var_s0;
}
