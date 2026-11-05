extern int DAT_00491478[4];
extern int DAT_00569330[4];
typedef struct Obj {
    char pad[312];
    unsigned char x0 : 1; unsigned char a0 : 3; unsigned short b0 : 8; unsigned char c0 : 2;
    char pad2[6];
    unsigned char x1 : 1; unsigned char a1 : 3; unsigned short b1 : 8; unsigned char c1 : 2;
} Obj;
extern Obj *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056b058[4];
void FUN_001e8550(int arg0, int arg1, int arg2) {
    long long v;

    if (DAT_00569330[0] == 0) {
        DAT_0056ad80[0]->a0 = arg0;
        DAT_0056ad80[0]->b0 = arg1;
        DAT_0056ad80[0]->c0 = arg2;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= (long long)0x80 << 0x20;
        if (DAT_0056b058[0] != 0) {
            DAT_0056ad80[0]->a1 = arg0;
            DAT_0056ad80[0]->b1 = arg1;
            DAT_0056ad80[0]->c1 = arg2;
            DAT_00491478[0] |= 0x40;
            v = DAT_0056ae48[0] | ((long long)0x100 << 0x20);
            DAT_0056ae48[0] = v;
        }
    } else {
        DAT_0056ad80[0]->a1 = arg0;
        DAT_0056ad80[0]->b1 = arg1;
        DAT_0056ad80[0]->c1 = arg2;
        DAT_00491478[0] |= 0x40;
        v = DAT_0056ae48[0] | ((long long)0x100 << 0x20);
        DAT_0056ae48[0] = v;
    }
}
