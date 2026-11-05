extern "C" {
typedef struct E { char pad[20]; int f14; char pad2[52]; int f4c; } E;
typedef struct L { char pad[8]; int f8; char pad2[4]; E **f10; } L;
typedef struct O { char pad[16]; L *f10; } O;
int igStrCmp(int, int);

int Gap__igMovieManager__vfunc_30(O *arg0, int arg1) {
    L *var_v1;
    int temp_v0;
    int var_s1;
    int var_s0;
    E *temp_s4;

    var_v1 = arg0->f10;
    if (var_v1 == 0) {
        return 2;
    }
    temp_v0 = var_v1->f8;
    if (temp_v0 <= 0) {
        return 2;
    }
    var_s1 = 0;
    if (0 < temp_v0) {
        var_s0 = 0;
        do {
            temp_s4 = *(E **)((char *)var_v1->f10 + var_s0);
            if (igStrCmp(temp_s4->f14, arg1) == 0) {
                return temp_s4->f4c;
            }
            var_v1 = arg0->f10;
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < var_v1->f8);
    }
    return 2;
}
}
