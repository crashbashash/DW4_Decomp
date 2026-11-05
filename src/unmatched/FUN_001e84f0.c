struct O { char pad[328]; unsigned char b0 : 1; };
extern int DAT_00491478[4];
extern struct O * DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_001e84f0(int arg0) {
    DAT_0056ad80[0]->b0 = arg0;
    DAT_00491478[0] |= 0x40;
    DAT_0056ae48[0] |= (long long)0x200 << 0x20;
}
