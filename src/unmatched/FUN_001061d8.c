int FUN_00106c88(char *d, int n);
void FUN_00106378(char *d, int *pmv, int *dmvector, int h_r_size, int v_r_size, int dmv, int mvscale, int full_pel);
void FUN_001061d8(char *d, int PMV[2][2][2], int *dmvector, int mv_field_sel[2][2], int s,
                  int motion_vector_count, int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale) {
    if (motion_vector_count == 1) {
        if (mv_format == 0 && !dmv) {
            mv_field_sel[1][s] = mv_field_sel[0][s] = FUN_00106c88(d, 1);
        }
        FUN_00106378(d, PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        PMV[1][s][0] = PMV[0][s][0];
        PMV[1][s][1] = PMV[0][s][1];
    } else {
        mv_field_sel[0][s] = FUN_00106c88(d, 1);
        FUN_00106378(d, PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        mv_field_sel[1][s] = FUN_00106c88(d, 1);
        FUN_00106378(d, PMV[1][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
    }
}
