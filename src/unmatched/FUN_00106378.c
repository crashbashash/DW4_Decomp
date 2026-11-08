int FUN_001054e8();
void FUN_00106150();
int FUN_001067e8();
int FUN_00106c88();

void FUN_00106378(ld, PMV, dmvector, h_r_size, v_r_size, dmv, mvscale, full_pel_vector)
char *ld;
int *PMV;
int *dmvector;
int h_r_size, v_r_size, dmv, mvscale, full_pel_vector;
{
    int motion_code, motion_residual;

    motion_code = FUN_001067e8(ld, 2);
    motion_residual = (h_r_size != 0 && motion_code != 0) ? FUN_00106c88(ld, h_r_size) : 0;
    FUN_00106150(&PMV[0], h_r_size, motion_code, motion_residual, full_pel_vector);

    if (dmv)
        dmvector[0] = FUN_001054e8(ld);

    motion_code = FUN_001067e8(ld, 2);
    motion_residual = (v_r_size != 0 && motion_code != 0) ? FUN_00106c88(ld, v_r_size) : 0;

    if (mvscale)
        PMV[1] >>= 1;

    FUN_00106150(&PMV[1], v_r_size, motion_code, motion_residual, full_pel_vector);

    if (mvscale)
        PMV[1] <<= 1;

    if (dmv)
        dmvector[1] = FUN_001054e8(ld);
}
