/* 0x00204150 — FUN_00204150. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00490c70[4];
extern int DAT_00490c78[4];
extern int DAT_00490c80[4];
extern int DAT_00490cc0[4];
extern int DAT_00490cc4[4];
extern int DAT_00490cc8[4];
extern int DAT_00491628[4];
extern int DAT_00491630[4];
extern int DAT_00491638[4];
extern int DAT_00491640[4];
extern int DAT_00491648[4];
extern int DAT_00491650[4];
extern int DAT_00491658[4];
extern int DAT_00491660[4];
extern int DAT_0056ba90[4];
extern int DAT_0056ba94[4];
extern int DAT_0056ba98[4];
void FUN_00204150(unsigned int arg0, int arg1) {
    switch (arg0) {
    case 13:
        DAT_00491660[0] = arg1;
        return;
    case 11:
        DAT_00491650[0] = arg1;
        return;
    case 12:
        DAT_00491658[0] = arg1;
        return;
    case 3:
        DAT_00491628[0] = arg1;
        return;
    case 10:
        DAT_00491630[0] = arg1;
        return;
    case 7:
        DAT_00491640[0] = arg1;
        return;
    case 8:
        DAT_00491648[0] = arg1;
        return;
    case 9:
        DAT_00491638[0] = arg1;
        return;
    case 0:
        DAT_00490cc0[0] = arg1;
        DAT_0056ba90[0] = 0;
        return;
    case 1:
        DAT_00490cc4[0] = arg1;
        DAT_0056ba94[0] = 0;
        return;
    case 2:
        DAT_00490cc8[0] = arg1;
        DAT_0056ba98[0] = 0;
        return;
    case 4:
        DAT_00490c70[0] = arg1;
        return;
    case 5:
        DAT_00490c78[0] = arg1;
        return;
    case 6:
        DAT_00490c80[0] = arg1;
        
    default:
        return;
    }
}
