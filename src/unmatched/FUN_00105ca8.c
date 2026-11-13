extern char DAT_004d2090[];
void _motionVectors(char *d, int PMV[2][2][2], int *dmvector, int mv_field_sel[2][2], int s,
                  int motion_vector_count, int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale);
void FUN_00106378(char *d, int *pmv, int *dmvector, int h_r_size, int v_r_size, int dmv, int mvscale, int full_pel);
void FUN_001064c8(char *d, unsigned int cmd);
void FUN_001064f8(char *d);
int _ipuVdec(char *d, int type);
void _ipuFlushBits(char *d, int n);
unsigned int FUN_00106c88(char *d, int n);
void FUN_001084b0(unsigned int addr, int size);
void _sceMpegMessage(char *d, const char *msg, ...);

#define LD(o) (*(int *)(ld + (o)))
#define picture_coding_type LD(360)
#define picture_structure LD(396)
#define frame_pred_frame_dct LD(404)
#define concealment_motion_vectors LD(408)
#define Fault_Flag LD(308)

int FUN_00105ca8(char *ld, int *pmacroblock_type, int *pmotion_type, int *pdct_type, int PMV[2][2][2],
                 int motion_vertical_field_select[2][2], int *dmvector) {
    int macroblock_type;
    int motion_vector_count, mv_format, dmv, mvscale, dct_type;

    *(volatile unsigned int *)0x10002010 = (*(volatile unsigned int *)0x10002010 & ~0x07000000) | (picture_coding_type << 24);
    macroblock_type = *pmacroblock_type = _ipuVdec(ld, 1);
    if (macroblock_type == 0) {
        _sceMpegMessage(ld, DAT_004d2090);
        Fault_Flag = 1;
        return 0;
    }

    if (macroblock_type & 0xC) {
        if (picture_structure == 3 && frame_pred_frame_dct)
            *pmotion_type = 2;
        else
            *pmotion_type = FUN_00106c88(ld, 2);
    } else if ((macroblock_type & 1) && concealment_motion_vectors) {
        *pmotion_type = (picture_structure == 3) ? 2 : 1;
    }

    if (picture_structure == 3) {
        motion_vector_count = (*pmotion_type == 1) ? 2 : 1;
        mv_format = (*pmotion_type == 2);
    } else {
        mv_format = 0;
        motion_vector_count = (*pmotion_type == 2) ? 2 : 1;
    }
    dmv = (*pmotion_type == 3);
    mvscale = (mv_format == 0 && picture_structure == 3);
    dct_type = (picture_structure == 3) && (!frame_pred_frame_dct) && (*pmacroblock_type & 3) ? FUN_00106c88(ld, 1) : 0;
    *pdct_type = dct_type;

    if (*pmacroblock_type & 0x10)
        LD(460) = FUN_00106c88(ld, 5);

    if ((*pmacroblock_type & 8) || ((*pmacroblock_type & 1) && concealment_motion_vectors)) {
        if (LD(2144))
            _motionVectors(ld, PMV, dmvector, motion_vertical_field_select, 0, motion_vector_count, mv_format,
                         LD(380) - 1, LD(384) - 1, dmv, mvscale);
        else
            FUN_00106378(ld, PMV[0][0], dmvector, LD(368) - 1, LD(368) - 1, 0, 0, LD(364));
    }
    if (Fault_Flag)
        return 0;

    if (*pmacroblock_type & 4) {
        if (LD(2144))
            _motionVectors(ld, PMV, dmvector, motion_vertical_field_select, 1, motion_vector_count, mv_format,
                         LD(388) - 1, LD(392) - 1, 0, mvscale);
        else
            FUN_00106378(ld, PMV[0][1], dmvector, LD(376) - 1, LD(376) - 1, 0, 0, LD(372));
    }
    if (Fault_Flag)
        return 0;

    if ((*pmacroblock_type & 1) && concealment_motion_vectors)
        _ipuFlushBits(ld, 1);

    if (*pmacroblock_type & 3) {
        FUN_001084b0(*(unsigned int *)(ld + LD(2088) * 320 + 1452), 0x300);
        FUN_001064f8(ld);
        FUN_001064c8(ld, 0x20000000 | ((*pmacroblock_type & 1) << 27) | (LD(456) << 26) | (*pdct_type << 25) |
                             (LD(460) << 16));
    } else {
        *(int *)(ld + LD(2088) * 320 + 1764) = 1;
    }
    LD(456) = 0;
    if (Fault_Flag)
        return 0;

    if (!(*pmacroblock_type & 1))
        LD(456) = 1;

    if ((*pmacroblock_type & 1) && !concealment_motion_vectors) {
        PMV[0][0][0] = PMV[0][0][1] = PMV[1][0][0] = PMV[1][0][1] = 0;
        PMV[0][1][0] = PMV[0][1][1] = PMV[1][1][0] = PMV[1][1][1] = 0;
    }

    if (picture_coding_type == 2 && !(*pmacroblock_type & 9)) {
        PMV[0][0][0] = PMV[0][0][1] = PMV[1][0][0] = PMV[1][0][1] = 0;
        if (picture_structure == 3)
            *pmotion_type = 2;
        else {
            *pmotion_type = 1;
            motion_vertical_field_select[0][0] = (picture_structure == 2);
        }
    }
    return 1;
}
