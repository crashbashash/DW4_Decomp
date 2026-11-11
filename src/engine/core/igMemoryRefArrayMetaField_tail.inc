void Gap__Core__igMemoryRefArrayMetaField__vfunc_52(igMemoryRefArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)FUN_002bfa60()));
    ((MetaFieldSwapBytesSlot *)(elementField))->SwapBytes((int)(buffer), (int)(count * self->_num));
}

int igMemoryRefArrayMetaField_ReadRawFieldMem(void *arg0, void *arg1, void *arg2, int arg3, int arg4) {
    void ** src;
    char * off;
    char * start;
    int i;
    src = (void **)arg1; off = (char *)arg2; start = off;
    for (i = 0; i < *(int *)((char *)(arg0) + 80); i++) {
        off += igMemoryRefMetaField_ReadRawFieldMem((Fld_2fb690 *)arg0, (int)src, (int *)off, (void *)arg3, arg4);
        src++;
    }
    return off - start;
}

int igMemoryRefArrayMetaField_WriteRawFieldMem(void *arg0, void *arg1, void *arg2, int arg3, int arg4) {
    void ** src;
    char * off;
    char * start;
    int i;
    src = (void **)arg1; off = (char *)arg2; start = off;
    for (i = 0; i < *(int *)((char *)(arg0) + 80); i++) {
        off += igMemoryRefMetaField_WriteRawFieldMem(arg0, src, off, arg3, arg4);
        src++;
    }
    return ((off - start) + 3) & ~3;
}

int igMemoryRefArrayMetaField_GetSize(igMemoryRefArrayMetaField *arg0) {
    return (arg0->_num * 4) & 0xFFFF;
}

void igMemoryRefArrayMetaField_ReleaseElements(M_2fa8c0 *arg0, int arg1, int arg2, int arg3) {
    int var_s3;
    if (igObject_IsKindOf((void *)arg0->f60, (igMetaObject *)DAT_00585b20[0]) != 0) {
        for (var_s3 = 0; var_s3 < arg0->f80; var_s3++) {
            int temp_s2 = *(int *)(arg1 + arg0->f8 + var_s3 * 4);
            if (temp_s2 != 0) {
                unsigned int temp_s8 = Memory_GetBufferSize((void *)temp_s2) >> 2;
                int var_s1;
                for (var_s1 = 0; var_s1 < (int)temp_s8; var_s1++) {
                    V_2fa8c0 **temp_s0 = (V_2fa8c0 **)(temp_s2 + var_s1 * 4);
                    if (*temp_s0 != 0) {
                        (*temp_s0)->v72();
                        igObject_VisitFields((VisitorObjectView *)(*temp_s0), (int (*)(void *, void *, void *))arg2, (void *)arg3);
                    }
                }
            }
        }
    }
}

