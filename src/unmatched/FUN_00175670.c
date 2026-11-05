extern int DAT_005609f4[4];
int FUN_001e83e0(unsigned char);
struct O { char pad[1537]; unsigned char f; };
void FUN_00175670(struct O *arg0, int arg1) {
    if (arg0->f == (unsigned char)arg1) {
        DAT_005609f4[0] += 1;
    }
    arg0->f = arg1;
    FUN_001e83e0(arg1);
}
