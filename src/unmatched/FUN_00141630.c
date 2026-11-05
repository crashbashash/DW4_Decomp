typedef struct S { char p0[12]; unsigned char b; char pad[3]; int f16; } S;
int FUN_00174030(int, int, unsigned char);
void FUN_00141630(S *arg0, int arg1) {
    FUN_00174030(arg1, arg0->f16, arg0->b);
}
