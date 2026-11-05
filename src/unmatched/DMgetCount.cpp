extern "C" {
int beMessenger_GetBool(int, int);
int beMessenger_GetBoolCount(int);
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int DAT_0050dae8[4];
extern int DAT_0050daf0[4];
extern int DAT_0058a1c0[4];
typedef struct { char pad[28]; struct { char pad[8]; int f8; } *f1c; } O;
extern O *DAT_0058a1d0[4];
int DMgetCount(void);
}

int DMgetCount(void) {
    int temp_v0;
    temp_v0 = DAT_0058a1d0[0]->f1c->f8;
    if (temp_v0 != 0) { return temp_v0; }
    beMessenger_SendNamed(DAT_0058a1c0[0], &DAT_0050dae8[0], 0, 0, &DAT_0050daf0[0]);
    if (beMessenger_GetBoolCount(DAT_0058a1c0[0]) == 0) { return 0; }
    temp_v0 = beMessenger_GetBool(DAT_0058a1c0[0], 0);
    temp_v0 = (temp_v0 & 0xFF) != 0;
    return -temp_v0;
}