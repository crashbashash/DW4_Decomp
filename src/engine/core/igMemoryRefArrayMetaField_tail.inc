void igMemoryRefArrayMetaField_SwapBytes(igMemoryRefArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)igMemoryRefMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

int igMemoryRefArrayMetaField_ReadRawFieldMem(void *self, void *object, void *data, int directory, int swap) {
    void ** src;
    char * off;
    char * start;
    int i;
    src = (void **)object; off = (char *)data; start = off;
    for (i = 0; i < ((igMemoryRefArrayMetaField *)self)->_num; i++) {
        off += igMemoryRefMetaField_ReadRawFieldMem((igMemoryRefMetaField *)self, (int)src, (int *)off, (void *)directory, swap);
        src++;
    }
    return off - start;
}

int igMemoryRefArrayMetaField_WriteRawFieldMem(void *self, void *object, void *data, int directory, int swap) {
    void ** src;
    char * off;
    char * start;
    int i;
    src = (void **)object; off = (char *)data; start = off;
    for (i = 0; i < ((igMemoryRefArrayMetaField *)self)->_num; i++) {
        off += igMemoryRefMetaField_WriteRawFieldMem((igMetaFieldView *)self, (int *)src, off, directory, swap);
        src++;
    }
    return ((off - start) + 3) & ~3;
}

int igMemoryRefArrayMetaField_GetSize(igMemoryRefArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}

void igMemoryRefArrayMetaField_ReleaseElements(igMemoryRefArrayMetaField *self, int object, int visitor, int context) {
    int i;
    if (((Gap::Core::igObject *)self->_memType)->isOfType((igMetaObject *)g_igObjectRefMetaField_metaObject) != 0) {
        for (i = 0; i < self->_num; i++) {
            int block = *(int *)(object + self->_offset + i * 4);
            if (block != 0) {
                unsigned int count = Memory_GetBufferSize((void *)block) >> 2;
                int j;
                for (j = 0; j < (int)count; j++) {
                    igObjectDispatchView **slot = (igObjectDispatchView **)(block + j * 4);
                    if (*slot != 0) {
                        (*slot)->TrimCapacity();
                        ((Gap::Core::igObject *)(*slot))->traverseFields((int (*)(void *, void *, void *))visitor, (void *)context);
                    }
                }
            }
        }
    }
}

