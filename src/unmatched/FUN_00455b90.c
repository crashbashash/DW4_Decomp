struct A { char pad[8]; int x; int y; };
struct T { char pad[12]; float w; float h; };
int FUN_00191860(void *, float, float, float, float, float, float);
int FUN_004578c0();
extern int DAT_0058c3d0[4];
extern int DAT_0058c3f0[4];
void FUN_00455b90(void *arg0, int *arg1) {
    int sp30[3];
    struct T *temp_s0;
    if ((arg1[2] == DAT_0058c3d0[0]) || (arg1[0] == 0)) {
        temp_s0 = *(struct T **)((char *)arg0 + 8);
        FUN_00191860((char *)temp_s0 + 0x60, 0.0f, temp_s0->w, temp_s0->h, 0.0f, 0.0f, 2.0f);
        sp30[0] = 2;
        sp30[1] = (int)arg0;
        sp30[2] = DAT_0058c3f0[0];
        FUN_004578c0(temp_s0, sp30);
    }
}
