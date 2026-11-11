void Gap__Core__igStringArrayMetaField__vfunc_52(igStringArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)FUN_002b9c60()));
    ((DW4VC_208_2 *)(descriptor))->vX((int)(item), (int)(count * self->_num));
}

int Gap__Core__igStringArrayMetaField__vfunc_51(struct S_30a5c0 *arg0, void *parg1, void *parg2, int arg3, int arg4) {
    int arg1 = (int)parg1;
    int arg2 = (int)parg2;
    int start = arg2;
    int i;
    for (i = 0; i < arg0->n; i++) {
        arg2 = arg2 + igStringMetaField_ReadRawValue(arg0, arg1, arg2, arg3, arg4);
        arg1 += 4;
    }
    return arg2 - start;
}

int Gap__Core__igStringArrayMetaField__vfunc_50(struct S_30a660 *arg0, void *parg1, void *parg2, int arg3, int arg4) {
    int arg1 = (int)parg1;
    int arg2 = (int)parg2;
    int start = arg2;
    int i;
    for (i = 0; i < arg0->n; i++) {
        arg2 = arg2 + igStringMetaField_WriteRawValue((void *)arg0, (void *)arg1, (void *)arg2, arg3, arg4);
        arg1 += 4;
    }
    return ((arg2 - start) + 3) & ~3;
}

void Gap__Core__igStringArrayMetaField__vfunc_32(struct SS *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *var_s1;
    int var_s0;
    int temp_a0;
    int temp_s3;

    if (arg0->f53 != 0) {
        var_s1 = (int *)(arg1 + arg0->f8);
        for (var_s0 = 0; var_s0 < arg0->f60; var_s0++) {
            if (DAT_00586f20[0] == 0) {
                var_v0 = ((int)FUN_002eb010(0x10));
                if (var_v0 != 0) {
                    var_v0 = ((int)StringPool_Construct((struct S_2eadf0 *)var_v0));
                }
                DAT_00586f20[0] = var_v0;
            }
            temp_s3 = StringPool_Intern((StringPool *)DAT_00586f20[0], (const char *)0);
            temp_a0 = *var_s1;
            if (temp_a0 != 0) {
                temp_a1 = (int *)(temp_a0 - 8);
                temp_v1 = *(int *)(temp_a0 - 4) - 1;
                *(int *)(temp_a0 - 4) = temp_v1;
                if (temp_v1 == 0) {
                    StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
                }
            }
            *var_s1 = temp_s3;
            var_s1 += 1;
        }
    }
}

int Gap__Core__igStringArrayMetaField__vfunc_25(void *arg0) {
    return (*(int *)((char *)(arg0) + 60) * 4) & 0xFFFF;
}

