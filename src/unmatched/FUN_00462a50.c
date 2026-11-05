int FUN_004578c0();
int FUN_00464110();
int FUN_004643a0();
extern int DAT_0058cad8[4];
typedef struct { int p0[3]; } Q;
typedef struct { char p[12]; int f12; char q[196]; int f212; } T;
typedef struct { char p[20]; T *f20; char q[112]; int f136; } S;
void FUN_00462a50(S *arg0) {
    int buf[3];
    arg0->f20->f212 = 1;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cad8[0];
    FUN_004578c0(arg0->f20, buf, 1);
    FUN_00464110(arg0->f136, (int)arg0->f20 + 0x10);
    FUN_004643a0(arg0->f136, arg0->f20->f12);
}
