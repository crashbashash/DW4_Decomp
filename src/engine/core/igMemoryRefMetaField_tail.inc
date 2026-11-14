int igMemoryRefMetaField_GetSize(void) {
    return 4;
}

void igMemoryRefMetaField_SetDefaultWord(void **self, int defaultWord) {
    int defaultCell;

    defaultCell = defaultWord;
    ((igMetaFieldView *)(self))->SetDefault(&defaultCell);
}

/* Allocates the array a memory-reference field points at, if the field is constructed
 * (_construct). The element count is memSize rounded up to whole elements of the element type's
 * size (element-size virtual, low 16 bits); the pool name picks a named allocator, falling back to
 * the owning object's allocator when the name is empty or unknown. */
void igMemoryRefMetaField_ConstructValue(igMemoryRefMetaField *self, int object) {
    int status;
    int allocator;
    char *poolName;
    unsigned int elementCount;
    unsigned int elementSize;
    void **memType;

    if (self->_construct != 0) {
        memType = (void **)(self->_memType);
        elementSize = ((igMetaFieldView *)(memType))->GetSize() & 0xFFFF;
        poolName = (char *)(self->_poolName);
        elementCount = (int)((unsigned int) ((self->_memSize + elementSize) - 1) / elementSize);
        if ((poolName != 0) && (*poolName != 0)) {
            allocator = ((int)Memory_GetAllocatorByName((int)poolName));
            if (allocator == 0) {
                allocator = ((int)igObject_GetAllocator(object));
            }
        } else {
            allocator = ((int)igObject_GetAllocator(object));
        }
        igMetaField_AllocateArray(&status, self, (void *)object, elementCount, (igMemoryPoolView *)allocator);
    }
}

void igMemoryRefMetaField_DestructValue(igMemoryRefMetaField *field,void *object, int extra2){
    if(field->_destruct){
        igMemoryRefMetaField_ReleaseElementRefs(field, object, extra2);
        Memory_FreeBuffer(*(void **)((char *)object+field->_offset));
        *(void **)((char *)object+field->_offset)=0;
    }
}

void igMemoryRefMetaField_AddElementRefs(igMemoryRefMetaField *field,void *object){
    igObject **data;
    int n;
    int i;
    igObject *value;
    if(!field->_refCounted)return;
    if(!field->_memType)return;
    if(!igObject_IsKindOf((void *)field->_memType, (igMetaObject *)(((int *)g_igObjectRefMetaField_metaObject)[0])))return;
    data=*(igObject ***)((char *)object+field->_offset);
    if(!data)return;
    n=Memory_GetBufferSize(data)>>2;
    for(i=0;i<n;i++){value=data[i];if(value)++value->_refCount;}
}

void igMemoryRefMetaField_ReleaseElementRefs(igMemoryRefMetaField *field,void *object, int extra2){
    igObject **data;
    int n;
    int i;
    igObject *value;
    if(!field->_refCounted)return;
    if(!field->_memType)return;
    if(!igObject_IsKindOf((void *)field->_memType, (igMetaObject *)(((int *)g_igObjectRefMetaField_metaObject)[0])))return;
    data=*(igObject ***)((char *)object+field->_offset);
    if(!data)return;
    n=Memory_GetBufferSize(data)>>2;
    for(i=0;i<n;i++){
        value=data[i];
        if(value){--value->_refCount;if(!(value->_refCount&0x7fffff))igObject_Destroy(value);}
    }
}

void igMemoryRefMetaField_SetToDefault(igMemoryRefMetaField *field,void *object, int extra2){
    void *value,*result;
    igMemoryRefMetaField_ReleaseElementRefs(field, object, extra2);
    if(field->_releaseOnReset){value=*(void **)((char *)object+field->_offset);if(value)Memory_FreeOwnedBufferUnchecked(value);}
    value=*(void **)field->_default;
    result=value?Memory_DuplicateBuffer(value):0;
    *(void **)((char *)object+field->_offset)=result;
    igMemoryRefMetaField_AddElementRefs(field,object);
}

void igMemoryRefMetaField_DeepCopy(igMemoryRefMetaField *m, int arg1, int arg2) {
    int a;
    igMemoryRefMetaField_ReleaseElementRefs(m, (void *)arg1, arg2);
    if (m->_releaseOnCopy != 0) {
        int p = *(int *)(arg1 + m->_offset);
        if (p != 0) Memory_FreeOwnedBufferUnchecked((void *)p);
    }
    {
        int s = *(int *)(arg2 + m->_offset);
        if (s != 0) a = ((int)Memory_DuplicateBuffer((void *)s)); else a = 0;
        *(int *)(arg1 + m->_offset) = a;
    }
    if (m->_memType != 0) {
        if (igObject_IsKindOf((void *)m->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject[0]) != 0) {
            int src = *(int *)(arg2 + m->_offset);
            int dst = *(int *)(arg1 + m->_offset);
            if (src != 0 && dst != 0) {
                unsigned n = Memory_GetBufferSize((void *)src) >> 2;
                int i;
                for (i = 0; i < (int)n; i++) {
                    igObjectDispatchView *e = *(igObjectDispatchView **)(src + i * 4);
                    int r = 0;
                    if (e != 0) r = (int)e->cloneViaMetadata(1);
                    *(int *)(dst + i * 4) = r;
                }
            }
        } else if (igObject_IsKindOf((void *)m->_memType, (igMetaObject *)(((int *)g_igMemoryRefMetaField_metaObject)[0])) != 0) {
            int src = *(int *)(arg2 + m->_offset);
            int dst = *(int *)(arg1 + m->_offset);
            unsigned n = Memory_GetBufferSize((void *)src) >> 2;
            int i;
            for (i = 0; i < (int)n; i++) {
                int e = *(int *)(src + i * 4);
                int r;
                if (e != 0) r = ((int)Memory_DuplicateBuffer((void *)e)); else r = 0;
                *(int *)(dst + i * 4) = r;
            }
        }
    }
}

void igMemoryRefMetaField_ShallowCopy(igMemoryRefMetaField *field,void *dest,void *source){
    igMemoryRefMetaField_ReleaseElementRefs(field, dest, (int)source);
    if(field->_releaseOnCopy){void *old=*(void **)((char *)dest+field->_offset);if(old)Memory_FreeOwnedBufferUnchecked(old);}
    void *value=*(void **)((char *)source+field->_offset);
    void *copy=value?Memory_DuplicateBuffer(value):0;
    *(void **)((char *)dest+field->_offset)=copy;
    igMemoryRefMetaField_AddElementRefs(field,dest);
}

void igMemoryRefMetaField_Print(igMemoryRefMetaField *arg0, int arg1, int arg2, int arg3) {
    unsigned int n;
    unsigned int sz;
    int base;
    int i;
    base = *(int *)(arg1 + arg0->_offset);
    igReport_Printf(DAT_004faef0, arg3, arg0->_fieldName, base);
    igReport_Flush();
    if (arg2 != 0 && base != 0) {
        sz = ((igMetaFieldView *)arg0->_memType)->vfunc_26();
        n = Memory_GetBufferSize((void *)base) / sz;
        if (igObject_IsKindOf((void *)arg0->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject[0]) != 0) {
            for (i = 0; i < (int)n; i++) {
                int e = *(int *)(base + i * 4);
                if (e != 0) {
                    igObject_Print((void **)e, arg2, arg3);
                }
            }
        }
    }
}

void igMemoryRefMetaField_ReleaseElements(igMemoryRefMetaField *arg0, int arg1, int arg2, int arg3) {
    igObjectDispatchView **arr;
    unsigned int n;
    int i;
    igObjectDispatchView *e;
    if (igObject_IsKindOf((void *)arg0->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject[0]) != 0) {
        arr = *(igObjectDispatchView ***)(arg1 + arg0->_offset);
        if (arr != 0) {
            n = Memory_GetBufferSize((void *)arr) >> 2;
            for (i = 0; i < (int)n; i++) {
                e = arr[i];
                if (e != 0) {
                    e->vfunc_16();
                    igObject_VisitFields((igObjectDispatchView *)arr[i], (Visitor)arg2, (void *)arg3);
                }
            }
        }
    }
}

