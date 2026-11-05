extern int DAT_00491478[4];
extern int DAT_00569330[4];
typedef struct { char pad[313]; unsigned char lo : 7; unsigned char hi : 1; char pad2[7]; unsigned char lo2 : 7; unsigned char hi2 : 1; } S;
extern S * DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056b058[4];
void FUN_001e8730(int arg0) {
    int t;
    if (DAT_00569330[0] == 0) {
        t = arg0;
        DAT_0056ad80[0]->hi = arg0;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= (long long)0x80 << 0x20;
        if (DAT_0056b058[0] != 0) {
            DAT_0056ad80[0]->hi2 = arg0;
            DAT_00491478[0] |= 0x40;
            DAT_0056ae48[0] |= (long long)0x100 << 0x20;
        }
    } else {
        DAT_0056ad80[0]->hi2 = arg0;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= (long long)0x100 << 0x20;
    }
}
