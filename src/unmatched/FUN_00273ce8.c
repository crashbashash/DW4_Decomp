int FUN_00274e30();
int FUN_002745c0();
int FUN_002725a0();
int sceCdSync();
int FUN_002739e8();
int FUN_002659a0();
extern char DAT_004ab300[];
extern char DAT_004f01e8[];
extern char DAT_004f0218[];
extern char DAT_004f0240[];
int FUN_002739b8();

typedef struct {
    int f0;
    int f4;
    char pad8[40];
} FileInfo;

int FUN_00273ce8(char *name)
{
    FileInfo info;

    if (name == 0) {
        FUN_002739b8(0, DAT_004f01e8);
        return 0;
    }
    FUN_00274e30(name, &info);
    if (info.f4 == 0) {
        FUN_002745c0(name, DAT_004ab300);
        FUN_002725a0(0x8200);
        sceCdSync(0);
        FUN_002725a0(0x8201);
        if (FUN_002739e8(&info, DAT_004ab300) == 0) {
            FUN_002659a0(DAT_004f0218, DAT_004ab300);
            FUN_002739b8(0, DAT_004f0240);
            return 0;
        }
    }
    return info.f4;
}
