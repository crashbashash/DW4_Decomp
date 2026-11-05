int FUN_001e84f0(unsigned char);
extern int DAT_005609f0[4];
struct S { char p[1536]; unsigned char v; };
void FUN_00175640(struct S *arg0, int arg1) {
    if (arg0->v == (unsigned char)arg1) {
        DAT_005609f0[0] += 1;
    }
    arg0->v = arg1;
    FUN_001e84f0(arg1);
}
