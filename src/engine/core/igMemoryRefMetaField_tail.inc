int igMemoryRefMetaField_GetSize(void) {
    return 4;
}

void igMemoryRefMetaField_SetDefaultWord(igMetaField *self, int defaultWord) {
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
            allocator = (int)Memory_GetAllocatorByName(poolName);
            if (allocator == 0) {
                allocator = ((int)igObject_GetAllocator((igObject *)object));
            }
        } else {
            allocator = ((int)igObject_GetAllocator((igObject *)object));
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
    if(!igObject_IsKindOf((igObject *)field->_memType, (igMetaObject *)((int)g_igObjectRefMetaField_metaObject)))return;
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
    if(!igObject_IsKindOf((igObject *)field->_memType, (igMetaObject *)((int)g_igObjectRefMetaField_metaObject)))return;
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

void igMemoryRefMetaField_DeepCopy(igMemoryRefMetaField *self, int destination, int source) {
    int copy;
    igMemoryRefMetaField_ReleaseElementRefs(self, (void *)destination, source);
    if (self->_releaseOnCopy != 0) {
        int owned = *(int *)(destination + self->_offset);
        if (owned != 0) Memory_FreeOwnedBufferUnchecked((void *)owned);
    }
    {
        int buffer = *(int *)(source + self->_offset);
        if (buffer != 0) copy = ((int)Memory_DuplicateBuffer((void *)buffer)); else copy = 0;
        *(int *)(destination + self->_offset) = copy;
    }
    if (self->_memType != 0) {
        if (igObject_IsKindOf((igObject *)self->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject) != 0) {
            int src = *(int *)(source + self->_offset);
            int dst = *(int *)(destination + self->_offset);
            if (src != 0 && dst != 0) {
                unsigned n = Memory_GetBufferSize((void *)src) >> 2;
                int i;
                for (i = 0; i < (int)n; i++) {
                    igObjectDispatchView *e = *(igObjectDispatchView **)(src + i * 4);
                    int clone = 0;
                    if (e != 0) clone = (int)e->CloneViaMetadata(1);
                    *(int *)(dst + i * 4) = clone;
                }
            }
        } else if (igObject_IsKindOf((igObject *)self->_memType, (igMetaObject *)((int)g_igMemoryRefMetaField_metaObject)) != 0) {
            int src = *(int *)(source + self->_offset);
            int dst = *(int *)(destination + self->_offset);
            unsigned n = Memory_GetBufferSize((void *)src) >> 2;
            int i;
            for (i = 0; i < (int)n; i++) {
                int e = *(int *)(src + i * 4);
                int clone;
                if (e != 0) clone = ((int)Memory_DuplicateBuffer((void *)e)); else clone = 0;
                *(int *)(dst + i * 4) = clone;
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

void igMemoryRefMetaField_Print(igMemoryRefMetaField *self, int object, int depth, int indent) {
    unsigned int count;
    unsigned int elementSize;
    int buffer;
    int i;
    buffer = *(int *)(object + self->_offset);
    igReport_Printf("%s%s = 0x%x\n", indent, self->_fieldName, buffer);
    igReport_Flush();
    if (depth != 0 && buffer != 0) {
        elementSize = ((igMetaFieldView *)self->_memType)->GetElementSize();
        count = Memory_GetBufferSize((void *)buffer) / elementSize;
        if (igObject_IsKindOf((igObject *)self->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject) != 0) {
            for (i = 0; i < (int)count; i++) {
                int e = *(int *)(buffer + i * 4);
                if (e != 0) {
                    igObject_Print((void **)e, depth, indent);
                }
            }
        }
    }
}

void igMemoryRefMetaField_ReleaseElements(igMemoryRefMetaField *self, int object, int visitor, int context) {
    igObjectDispatchView **elements;
    unsigned int count;
    int i;
    igObjectDispatchView *element;
    if (igObject_IsKindOf((igObject *)self->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject) != 0) {
        elements = *(igObjectDispatchView ***)(object + self->_offset);
        if (elements != 0) {
            count = Memory_GetBufferSize((void *)elements) >> 2;
            for (i = 0; i < (int)count; i++) {
                element = elements[i];
                if (element != 0) {
                    element->TrimCapacity();
                    igObject_VisitFields((igObjectDispatchView *)elements[i], (Visitor)visitor, (void *)context);
                }
            }
        }
    }
}

