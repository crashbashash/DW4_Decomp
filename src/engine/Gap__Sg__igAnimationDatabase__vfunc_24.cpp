#include "dw4/igSmartPointer.h"
typedef struct R : public igObject { int f8; int f12; int *f16; } R;
typedef struct O { char pad[8]; char *f8; char pad2[8]; void *f20; void *f24; void *f28; void *f32; void *f36; } O;
extern "C" {
extern char DAT_004e0858[];
extern char DAT_004e4130[];
extern char DAT_004e44f8[];
extern char DAT_004e4500[];
extern int DAT_00562370[4];
extern int DAT_00562428[4];
extern int *DAT_00562560[4];
extern int DAT_00585b20[4];
extern int DAT_00585be0[4];
int sscanf(char *, char *, char *, int *);
int strlen(char *);
int strncmp(char *, char *, int);
int igObject_IsKindOf(void *, int);
R *igMetaObject_FindFieldByName(int, char *);
R *igProperty_FindByName(void *, int, char *);
int strcmp(char *, char *);
}

extern "C" void *Gap__Sg__igAnimationDatabase__vfunc_24(O *arg0, char *arg1) {
    int sp106C;
    char sp50[4096];
    char *var_a1;
    R *var_s0;
    R *var_s1;

    var_a1 = arg0->f8;
    if (var_a1 != 0) {
        var_a1 = (char *)var_a1;
    } else {
        var_a1 = DAT_004e0858;
    }
    if (strcmp(arg1, var_a1) == 0) {
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
    if (strncmp(arg1, DAT_004e44f8, strlen(DAT_004e44f8)) == 0) {
        if (DAT_00562560[0] == 0) {
            var_s1 = igMetaObject_FindFieldByName(DAT_00562370[0], DAT_004e4130);
            if ((var_s1 != 0) && (igObject_IsKindOf(var_s1, DAT_00585b20[0]) != 0)) {
                var_s1 = (R *)var_s1;
            } else {
                var_s1 = 0;
            }
            DAT_00562560[0] = (int *)var_s1;
        }
        sscanf(arg1 + strlen(DAT_004e44f8), DAT_004e4500, sp50, &sp106C);
        igSmartPointer<R> record(igProperty_FindByName(arg0->f24, DAT_00585be0[0], sp50), kRetainReference);
        if (record.get() != 0) {
            var_s1 = *(R **)((char *)record.get() + DAT_00562560[0][2]);
            if ((var_s1 != 0) && (igObject_IsKindOf(var_s1, DAT_00562428[0]) != 0)) {
                var_s1 = (R *)var_s1;
            } else {
                var_s1 = 0;
            }
            igSmartPointer<R> list(var_s1, kRetainReference);
            if (list.get() != 0) {
                igSmartPointer<R> entry((R *)list.get()->f16[sp106C], kRetainReference);
                if (entry.get() != 0) {
                    var_s0 = (R *)entry.get()->f12;
                }
            }
        }
    }
    igSmartPointer<R> keep = igSmartPointer<R>(var_s0, kRetainReference);
    return var_s0;
}
