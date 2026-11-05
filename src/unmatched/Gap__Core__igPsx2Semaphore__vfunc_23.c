struct S_arg1 { char pad0[12]; int f12; int f16; int f20; };
union U { int w[6]; char b[24]; };
int CreateSema();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Core__igPsx2Semaphore__vfunc_23(int *arg0, struct S_arg1 *arg1) {
    union U u;
    char *var_v1_2;
    unsigned int var_v0;
    if (arg1->f12 != -1) {
        *arg0 = DAT_004fb418[0];
    } else {
        var_v1_2 = u.b;
        var_v0 = 0x18;
        if (var_v1_2 != 0) {
            do {
                *var_v1_2 = 0;
                var_v0 -= 1;
                var_v1_2 += 1;
            } while (var_v0 != 0);
        }
        u.w[1] = arg1->f20;
        u.w[2] = arg1->f16;
        arg1->f12 = CreateSema(&u);
        if (arg1->f12 < 0) {
            arg1->f12 = -1;
            *arg0 = DAT_004fb418[0];
        } else {
            *arg0 = DAT_004fb410[0];
        }
    }
}
