extern char DAT_004d2040[];
int FUN_001034e0(char *d, int MBA, int MBAinc, int macroblock_type, int motion_type, int PMV[2][2][2],
                 int mv_field_sel[2][2], int dmvector[2]);
void FUN_00104258(char *d, int buf);
int FUN_00105250(char *d);
int _getMacroblockAddressIncrement(char *d);
int FUN_001058b8(char *d, int MBAmax, int *MBA, int *MBAinc, int PMV[2][2][2]);
int FUN_00105be8(char *d, int PMV[2][2][2], int *motion_type, int mv_field_sel[2][2], int *macroblock_type);
int FUN_00105ca8(char *d, int *macroblock_type, int *motion_type, int *dct_type, int PMV[2][2][2],
                 int mv_field_sel[2][2], int dmvector[2]);
unsigned int _ipuShowBits(char *d, int n);
void _sceMpegMessage(char *d, const char *msg, ...);

int FUN_001059e8(char *d, int MBAmax) {
    int PMV[2][2][2];
    int motion_vertical_field_select[2][2];
    int dmvector[4];
    int MBA, MBAinc, macroblock_type, motion_type, dct_type;
    int ret;

    MBA = 0;
    MBAinc = 0;

    if ((ret = FUN_001058b8(d, MBAmax, &MBA, &MBAinc, PMV)) != 0)
        return ret;
    *(int *)(d + 308) = 0;

    for (;;) {
        if (MBA >= MBAmax)
            return 0;

        *(int *)(d + *(int *)(d + 2088) * 320 + 1764) = 0;
        if (!FUN_00105250(d))
            return *(int *)(d + 4256) == 0 ? 2 : 4;

        if (MBAinc == 0) {
            if (!_ipuShowBits(d, 23) || *(int *)(d + 308)) {
                *(int *)(d + 308) = 0;
                return 3;
            } else {
                MBAinc = _getMacroblockAddressIncrement(d);
                if (*(int *)(d + 308))
                    goto resync;
            }
        }

        if (MBA >= MBAmax) {
            _sceMpegMessage(d, DAT_004d2040);
            return 2;
        }

        if (MBAinc == 1) {
            if (!FUN_00105ca8(d, &macroblock_type, &motion_type, &dct_type, PMV,
                              motion_vertical_field_select, dmvector)) {
resync:
                *(int *)(d + 308) = 0;
                return 1;
            }
        } else {
            if (!FUN_00105be8(d, PMV, &motion_type, motion_vertical_field_select, &macroblock_type))
                goto fail;
        }

        if (!FUN_001034e0(d, MBA, MBAinc, macroblock_type, motion_type, PMV,
                          motion_vertical_field_select, dmvector)) {
fail:
            *(int *)(d + 308) = 0;
            return 2;
        }

        if (MBA)
            FUN_00104258(d, *(int *)(d + 2088) ^ 1);
        MBA++;
        *(int *)(d + 2088) ^= 1;
        MBAinc--;
    }
}
