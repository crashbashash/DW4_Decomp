struct S { char pad[1276]; unsigned char b; };
int FUN_00174db0();
extern int DAT_005609b4[4];
void FUN_00174d70(struct S *arg0, int arg1) {
    if (arg0->b == (arg1 & 0xFF)) {
        DAT_005609b4[0] += 1;
    }
    arg0->b = arg1;
    FUN_00174db0();
}
