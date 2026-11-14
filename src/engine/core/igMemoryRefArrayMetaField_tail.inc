void igMemoryRefArrayMetaField_SwapBytes(igMemoryRefArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)igMemoryRefMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

int igMemoryRefArrayMetaField_ReadRawFieldMem(void *arg0, void *arg1, void *arg2, int arg3, int arg4) {
    void ** src;
    char * off;
    char * start;
    int i;
    src = (void **)arg1; off = (char *)arg2; start = off;
    for (i = 0; i < *(int *)((char *)(arg0) + 80); i++) {
        off += igMemoryRefMetaField_ReadRawFieldMem((igMemoryRefMetaField *)arg0, (int)src, (int *)off, (void *)arg3, arg4);
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
        off += igMemoryRefMetaField_WriteRawFieldMem((igMetaFieldView *)arg0, (int *)src, off, arg3, arg4);
        src++;
    }
    return ((off - start) + 3) & ~3;
}

int igMemoryRefArrayMetaField_GetSize(igMemoryRefArrayMetaField *arg0) {
    return (arg0->_num * 4) & 0xFFFF;
}

void igMemoryRefArrayMetaField_ReleaseElements(igMemoryRefArrayMetaField *arg0, int arg1, int arg2, int arg3) {
    int var_s3;
    if (igObject_IsKindOf((void *)arg0->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject[0]) != 0) {
        for (var_s3 = 0; var_s3 < arg0->_num; var_s3++) {
            int temp_s2 = *(int *)(arg1 + arg0->_offset + var_s3 * 4);
            if (temp_s2 != 0) {
                unsigned int temp_s8 = Memory_GetBufferSize((void *)temp_s2) >> 2;
                int var_s1;
                for (var_s1 = 0; var_s1 < (int)temp_s8; var_s1++) {
                    igObjectDispatchView **temp_s0 = (igObjectDispatchView **)(temp_s2 + var_s1 * 4);
                    if (*temp_s0 != 0) {
                        (*temp_s0)->vfunc_16();
                        igObject_VisitFields((igObjectDispatchView *)(*temp_s0), (int (*)(void *, void *, void *))arg2, (void *)arg3);
                    }
                }
            }
        }
    }
}

