void igStringArrayMetaField_SwapBytes(igStringArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)igStringMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(descriptor))->SwapBytes((void *)(item), (int)(count * self->_num));
}

int igStringArrayMetaField_ReadRawFieldMem(igStringArrayMetaField *self, void *values, void *buffer, int directory, int swapBytes) {
    int value = (int)values;
    int cursor = (int)buffer;
    int start = cursor;
    int i;
    for (i = 0; i < self->_num; i++) {
        cursor = cursor + igStringMetaField_ReadRawValue((void *)self, (void *)value, (void *)cursor, directory, swapBytes);
        value += 4;
    }
    return cursor - start;
}

int igStringArrayMetaField_WriteRawFieldMem(igStringArrayMetaField *self, void *values, void *buffer, int directory, int swapBytes) {
    int value = (int)values;
    int cursor = (int)buffer;
    int start = cursor;
    int i;
    for (i = 0; i < self->_num; i++) {
        cursor = cursor + igStringMetaField_WriteRawValue((void *)self, (void *)value, (void *)cursor, directory, swapBytes);
        value += 4;
    }
    return ((cursor - start) + 3) & ~3;
}

void igStringArrayMetaField_DestructValue(igStringArrayMetaField *self, int object) {
    int *header;
    int references;
    int pool;
    int *slot;
    int i;
    int previous;
    int empty;

    if (self->_destruct != 0) {
        slot = (int *)(object + self->_offset);
        for (i = 0; i < self->_num; i++) {
            if (g_stringPool == 0) {
                pool = ((int)StringPool_Allocate(0x10));
                if (pool != 0) {
                    pool = ((int)StringPool_Construct((StringPool *)pool));
                }
                g_stringPool = pool;
            }
            empty = StringPool_Intern((StringPool *)g_stringPool, (const char *)0);
            previous = *slot;
            if (previous != 0) {
                header = (int *)(previous - 8);
                references = *(int *)(previous - 4) - 1;
                *(int *)(previous - 4) = references;
                if (references == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
                }
            }
            *slot = empty;
            slot += 1;
        }
    }
}

int igStringArrayMetaField_GetSize(void *field) {
    return (((igStringArrayMetaField *)field)->_num * 4) & 0xFFFF;
}

