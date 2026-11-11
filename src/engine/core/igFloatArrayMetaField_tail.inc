/* Storage size in bytes of the field's array: `_num` elements of 4 bytes (float), truncated to the
 * 16-bit size the meta field system uses. */

int igFloatArrayMetaField_GetSize(igFloatArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}

void igFloatArrayMetaField_SwapBytes(igFloatArrayMetaField *arg0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)FUN_002c4870()));
    ((DW4VC_208_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 * arg0->_num));
}

int Gap__Core__igFloatArrayMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &DAT_004f9a68[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igFloatArrayMetaField__vfunc_57(int *arg0, int arg1, float *arg2) {
    char sp20[1024];
    int var_v0;
    int var_v1;

    sprintf(sp20, &DAT_004f9a70[0], fptodp(*arg2));
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0 = ((int)FUN_002eb010(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            DAT_00586f20[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)DAT_00586f20[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

