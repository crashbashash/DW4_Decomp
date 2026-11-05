extern int DAT_00491478[4];
extern int DAT_00569330[4];
typedef struct Obj { char pad[336]; unsigned char b336 : 1; unsigned char r336 : 7; char pad2[7]; unsigned char b344 : 1; unsigned char r344 : 7; } Obj;
extern Obj *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056b058[4];
void FUN_001e83e0(int arg0) {
    int t;
    long long v;

    if (DAT_00569330[0] == 0) {
        t = arg0;
        DAT_0056ad80[0]->b336 = t;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= (long long)0x400 << 0x20;
        if (DAT_0056b058[0] != 0) {
            DAT_0056ad80[0]->b344 = t;
            DAT_00491478[0] |= 0x40;
            v = DAT_0056ae48[0] | ((long long)0x800 << 0x20);
            DAT_0056ae48[0] = v;
        }
    } else {
        DAT_0056ad80[0]->b344 = arg0;
        DAT_00491478[0] |= 0x40;
        v = DAT_0056ae48[0] | ((long long)0x800 << 0x20);
        DAT_0056ae48[0] = v;
    }
}
