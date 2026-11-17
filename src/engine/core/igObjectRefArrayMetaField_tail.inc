void igObjectRefArrayMetaField_SwapBytes(igObjectRefArrayMetaField *self, int passThrough, int perElement) {
    void **elementDescriptor;

    elementDescriptor = (void **)(((void **)igObjectRefMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementDescriptor))->SwapBytes((void *)(passThrough), (int)(perElement * self->_num));
}

void igObjectRefArrayMetaField_SetElement(igObjectRefArrayMetaField *self, int object, int index, igObject *value) {
    int byteOffset;
    igObject *old;

    byteOffset = index * 4;
    old = ((igObject **)(object + self->_offset))[index];
    if (self->_refCounted != 0) {
        if (value != 0) {
            value->_refCount = value->_refCount + 1;
        }
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
    }
    ((igObject **)(object + self->_offset))[index] = value;
}

int igObjectRefArrayMetaField_ReadRawFieldMem(igObjectRefArrayMetaField *self, int dst, char *src, int directory, int swapBytes) {
    int *p;
    int cur;
    int start;
    int i;
    p = (int *)dst;
    cur = (int)src;
    start = cur;
    for (i = 0; i < self->_num; i++) {
        cur += igObjectRefMetaField_ReadRawFieldMem((igObjectRefMetaField *)self, (igObject **)p, cur, directory, swapBytes);
        p++;
    }
    return cur - start;
}

void igObjectRefArrayMetaField_ConstructValue(igObjectRefArrayMetaField *self, int object) {
    igObject *element;
    int allocator;
    int i;
    char *poolName;

    if (self->_construct != 0) {
        poolName = (char *)self->_poolName;
        if ((poolName != 0) && (*poolName != 0)) {
            allocator = (int)Memory_GetAllocatorByName(poolName);
            if (allocator == 0) {
                allocator = ((int)igObject_GetAllocator((igObject *)object));
            }
        } else {
            allocator = ((int)igObject_GetAllocator((igObject *)object));
        }
        for (i = 0; i < self->_num; i++) {
            element = ((igObject *)igMetaObject_CreateInstance((igMetaObject *)self->_metaObject, (igMemoryPoolView *)allocator));
            igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)self, object, i, (igObject *)element);
            if (self->_refCounted != 0) {
                element->_refCount = element->_refCount - 1;
                if (((unsigned long long) ((long long)(int)element->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(element);
                }
            }
        }
    }
}

void igObjectRefArrayMetaField_DestructValue(igObjectRefArrayMetaField *self, int object) {
    int i;
    igObject *element;

    if (self->_destruct != 0) {
        for (i = 0; i < self->_num; i++) {
            element = *(igObject **)(object + self->_offset + (i * 4));
            if (element != 0) {
                element->_refCount = (int)((int) (element->_refCount - 1));
                if (((unsigned long long) ((long long)(int)element->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(element);
                }
            }
        }
    }
}

void igObjectRefArrayMetaField_ClearValue(igObjectRefArrayMetaField *self, int object) {
    int i;
    igObject *element;

    if (self->_persistent != 0) {
        if (self->_refCounted != 0) {
            for (i = 0; i < self->_num; i++) {
                element = *(igObject **)(object + self->_offset + (i * 4));
                if (element != 0) {
                    element->_refCount = element->_refCount - 1;
                    if (((unsigned long long)((long long)(int)element->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(element);
                    }
                }
            }
        }
        igRefMetaField_ClearValue((igMetaField *)self, (void *)object);
    }
}

void igObjectRefArrayMetaField_SetToDefault(igObjectRefArrayMetaField *self, int object) {
    int element;
    int i;

    for (i = 0; i < self->_num; i++) {
        element = *(int *)(object + self->_offset + (i * 4));
        if (element != 0) {
            igObject_ResetFields((igObjectDispatchView *)element);
        }
    }
}

void igObjectRefArrayMetaField_CopyDefaultToValue(igObjectRefArrayMetaField *self, int object) {
    int i;

    for (i = 0; i < self->_num; i++) {
        igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)self, object, i, (igObject *)((int *)self->_default)[i]);
    }
}

void igObjectRefArrayMetaField_CopyReference(igObjectRefArrayMetaField *self, int object, int source) {
    int i;

    for (i = 0; i < self->_num; i++) {
        igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)self, object, i, (igObject *)(*(int *)(source + self->_offset + (i * 4))));
    }
}

void igObjectRefArrayMetaField_DeepCopy(igObjectRefArrayMetaField *s, char *a1, char *a2) {
    int i = 0;
    while (i < s->_num) {
        int base = s->_offset;
        int off = i * 4;
        igObject *x = *(igObject **)(a1 + base + off);
        igObjectDispatchView *y = *(igObjectDispatchView **)(a2 + base + off);
        if (x == 0 && y == 0) break;
        if (x != 0 && y != 0) {
            igObject_DeepCopy((igObjectDispatchView *)x, (igObjectDispatchView *)y);
        } else if (x == 0) {
            igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)s, (int)a1, i, (igObject *)(y->CloneViaMetadata(1)));
        } else if (y == 0) {
            x->_refCount = x->_refCount - 1;
            if (((unsigned long long)((long long)(int)x->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(x);
            }
            igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)s, (int)a1, i, (igObject *)0);
        }
        i++;
    }
}

void igObjectRefArrayMetaField_ShallowCopy(igObjectRefArrayMetaField *self, int object, int source) {
    int i;
    int offset;
    int objectBase;
    int sourceBase;
    int byteOffset;
    igObject *element;
    igObjectDispatchView *sourceElement;

    i = 0;
    while (i < self->_num) {
        offset = self->_offset;
        byteOffset = i * 4;
        objectBase = object + offset;
        sourceBase = source + offset;
        element = *(igObject **)(objectBase + byteOffset);
        sourceElement = *(igObjectDispatchView **)(sourceBase + byteOffset);
        if (element != 0 || sourceElement != 0) {
            if (element != 0 && sourceElement != 0) {
                igObject_ShallowCopy((igObjectDispatchView *)element, (int)sourceElement);
            } else if (element == 0) {
                igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)self, object, i, (igObject *)(sourceElement->CloneViaMetadata(1)));
            } else if (sourceElement == 0) {
                element->_refCount = element->_refCount - 1;
                if ((element->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(element);
                }
                igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)self, object, i, (igObject *)0);
            }
            i += 1;
        } else {
            break;
        }
    }
}

void igObjectRefArrayMetaField_ResetValue(igObjectRefArrayMetaField *self, int object) {
    int i;
    for (i = 0; i < self->_num; i++) {
        int *p = (int *)(object + self->_offset + (i * 4));
        if (*p != 0) {
            igObject_ResetFields((igObjectDispatchView *)(*p));
        }
    }
}

int igObjectRefArrayMetaField_WriteRawFieldMem(igObjectRefArrayMetaField *self, int src, void *dst, int a3, int a4) {
    int s;
    int d;
    int start;
    int i;

    s = src;
    d = (int)dst;
    start = d;
    for (i = 0; i < self->_num; i++) {
        d += igMemoryRefMetaField_WriteRawFieldMem((igMetaFieldView *)self, (int *)s, (void *)d, a3, a4);
        s += 4;
    }
    return ((d - start) + 3) & ~3;
}

int igObjectRefArrayMetaField_GetSize(igObjectRefArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}

void igObjectRefArrayMetaField_ReleaseElements(igObjectRefArrayMetaField *self, int object, int visitor, int context) {
    int element;
    int i;

    for (i = 0; i < self->_num; i++) {
        element = *(int *)(object + self->_offset + (i * 4));
        if (element != 0) {
            igObject_VisitFields((igObjectDispatchView *)element, (int (*)(void *, void *, void *))visitor, (void *)context);
        }
    }
}

int igObjectRefArrayMetaField_IsAlikeExactly(igObjectRefArrayMetaField *self, int first, int second) {
    int i;
    int off;
    int a;
    int b;
    for (i = 0; i < self->_num; i++) {
        off = self->_offset;
        a = *(int *)(first + off + i * 4);
        b = *(int *)(second + off + i * 4);
        if (a != b) {
            if (a == 0 || b == 0) {
                return 0;
            }
            if (!(igObject_IsAlikeExactly((void *)a, (void *)b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}

int igObjectRefArrayMetaField_IsAlikeDeep(igObjectRefArrayMetaField *self, int first, int second) {
    int i;
    for (i = 0; i < self->_num; i++) {
        int a = *(int *)(first + self->_offset + i * 4);
        int b = *(int *)(second + self->_offset + i * 4);
        if (a != b) {
            if (a == 0 || b == 0) {
                return 0;
            }
            if (!(igObject_IsAlikeDeep((igObjectDispatchView *)a, (igObjectDispatchView *)b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}

int igObjectRefArrayMetaField_IsAlikeShallow(igObjectRefArrayMetaField *self, int first, int second) {
    int i;
    int a;
    int b;

    for (i = 0; i < self->_num; i++) {
        a = *(int *)(first + self->_offset + i * 4);
        b = *(int *)(second + self->_offset + i * 4);
        if (a != b) {
            if ((a == 0) || (b == 0)) {
                return 0;
            }
            if (!(igObject_IsAlikeShallow((igObjectDispatchView *)a, (igObjectDispatchView *)b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}

