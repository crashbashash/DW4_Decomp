/* DVCI file-cache probe: looks up each name of a packed list on the device and
 * records its 8-byte location; strings "DVCI: \"%s\" found." etc. */
typedef struct DvciList {
    int w0, w4;
    int count;      /* 8: number of entries (location records come first) */
    int nameLen;    /* 12: bytes per name, excluding the terminator */
} DvciList;
typedef struct DvciLoc { int a, b; } DvciLoc;
typedef struct DvciInfo { int a, b; char pad[40]; } DvciInfo;

extern DvciList D_004ab430;
extern char D_004ab558[];
extern const char D_004f03e8[], D_004f0400[], D_004f0418[], D_004f0430[];
extern void FUN_002745c0(const char *, char *);
extern void FUN_002725a0(int);
extern int FUN_00116c80(int);
extern int FUN_002739e8(DvciInfo *, char *);
extern void FUN_00265928(const char *, ...);
extern void FUN_002659a0(const char *, ...);

int FUN_00274ab0(char *tab, int n)
{
    DvciInfo loc;
    int missing;
    int found = 0;
    int i;
    DvciLoc *out = (DvciLoc *)tab;
    char *name;

    missing = 0;
    for (i = 0; i < n; i++) {
        name = tab + ((D_004ab430.count << 3) + (D_004ab430.nameLen * i + i));
        if (*name == 0)
            continue;
        FUN_002745c0(name, D_004ab558);
        FUN_002725a0(0x9400);
        while (FUN_00116c80(1) == 1)
            ;
        FUN_002725a0(0x9401);
        FUN_002725a0(0x9500);
        if (FUN_002739e8(&loc, D_004ab558) == 1) {
            FUN_002725a0(0x9501);
            found++;
            out[i].a = loc.a;
            out[i].b = loc.b;
            FUN_00265928(D_004f03e8, name);
        } else {
            FUN_002725a0(0x9502);
            missing++;
            FUN_00265928(D_004f0400, name);
        }
    }
    FUN_00265928(D_004f0418, found);
    if (missing > 0)
        FUN_002659a0(D_004f0430, 10);
    return found;
}
