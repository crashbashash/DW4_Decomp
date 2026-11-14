void *ObjectPointerList_Construct(__internalNonRefCountedObjectList *self, int extra1) {
    void **allocator;

    igObject_ConstructHeader(self);
    self->_vtable = (int)(&g_ObjectPointerList_vtable[0]);
    if (self != 0) {
        ObjectPointerList_Init(self);
    }
    allocator = (void **)(((void **)igObject_GetAllocator((int)self)));
    self->_data = (int)((igMemoryPoolView *)allocator)->Allocate(0x10);
    return self;
}

__internalNonRefCountedObjectList *ObjectPointerList_Init(__internalNonRefCountedObjectList *list) {
    igObject_InitHeader((igObject *)list);
    list->_vtable = (int)g_ObjectPointerList_vtable;
    list->_data = 0;
    list->_count = 0;
    return list;
}

__internalNonRefCountedObjectList *ObjectPointerList_CopyConstruct(__internalNonRefCountedObjectList *self, __internalNonRefCountedObjectList *source) {
    int bytes;
    igObject_CopyConstructHeader((igObject *)self, (igObject *)source);
    self->_vtable = (int)g_ObjectPointerList_vtable;
    self->_count = source->_count;
    if (source->_data) {
        bytes = self->_count * 4;
        igMemoryPoolView *allocator = (igMemoryPoolView *)igObject_GetAllocator((int)self);
        self->_data = (int)allocator->Allocate(bytes);
        memcpy((void *)self->_data, (void *)source->_data, bytes);
    } else {
        self->_data = 0;
    }
    return self;
}

void ObjectPointerList_Destruct(__internalNonRefCountedObjectList *self) {
    int buffer;
    void **allocator;

    buffer = self->_data;
    if (buffer != 0) {
        allocator = (void **)(((void **)igObject_GetAllocator((int)self)));
        ((igMemoryPoolView *)allocator)->Free((void *)buffer);
    }
    Gap__Core__igObject__vfunc_00__002ff0a0((int)self);
}

static inline unsigned int pointerListCapacity(__internalNonRefCountedObjectList *list) {
    return list->_data == 0 ? 0 : Memory_GetBufferSize((void *)list->_data) >> 2;
}

void ObjectPointerList_EnsureIndex(__internalNonRefCountedObjectList *list, int index) {
    if (index >= (int)pointerListCapacity(list)) {
        unsigned int old = pointerListCapacity(list);
        unsigned int n = old;
        if (old == 0) {
            n = 4;
        }
        while (!(index < (int)n)) {
            if ((int)n < 512) n *= 2; else n += 512;
        }
        list->_data = FUN_00300e50((int)list, list->_data, n * 4);
        char *p = (char *)list->_data;
        p += old * 4;
        memset(p, 0, (n - old) * 4);
    }
}

void *ObjectPointerList_FindByStringField(__internalNonRefCountedObjectList *list,igMetaField *selector,const char *name){
    int i;int byteOffset;
    for(i=0;i<list->_count;i++){
        byteOffset=i*4;
        if(strcmp(*(char **)((char *)*(void **)((char *)list->_data+byteOffset)+selector->_offset),name)==0)
            return *(void **)((char *)list->_data+byteOffset);
    }
    return 0;
}

int ObjectPointerList_FindIndex(char *arg0, int arg1) {
    int *d = *(int **)(arg0 + 8);
    int n = *(int *)(arg0 + 12);
    int i;
    int v;
    for (i = 0; i < n; i++) {
        v = d[i];
        if (v == arg1) {
            return i;
        }
    }
    return -1;
}

void ObjectPointerList_ClearUnused(__internalNonRefCountedObjectList *list){
    int i=list->_count;
    while(i<(int)(list->_data?Memory_GetBufferSize((void *)list->_data)>>2:0)){((int *)list->_data)[i]=0;i++;}
}

void ObjectPointerList_Insert(__internalNonRefCountedObjectList *list,int index,int value){
    int i;int count=list->_count;
    unsigned capacity;void *buffer=(void *)list->_data;
    if(buffer==0){capacity=0;}else{capacity=Memory_GetBufferSize(buffer)>>2;}
    if(count>=(int)capacity)ObjectPointerList_EnsureIndex(list,count);
    i=list->_count;
    while(i>index){((int *)list->_data)[i]=((int *)list->_data)[i-1];i--;}
    ((int *)list->_data)[index]=value;
    list->_count++;
}

void ObjectPointerList_SetCount(__internalNonRefCountedObjectList *list, int count) {
    void *buffer = (void *)list->_data;
    unsigned capacity;
    if (buffer == 0) {
        capacity = 0;
    } else {
        capacity = Memory_GetBufferSize(buffer) >> 2;
    }
    if (count >= (int)capacity)
        ObjectPointerList_EnsureIndex(list, count);
    list->_count = count;
}

int ObjectPointerList_EraseAt(__internalNonRefCountedObjectList *list,int index){
    int i;
    if(index<list->_count){
        for(i=index;i<list->_count-1;i++)((int *)list->_data)[i]=((int *)list->_data)[i+1];
        list->_count--;
        return index;
    }
    return -1;
}

int ObjectPointerList_Append(__internalNonRefCountedObjectList *list,int value){
    int count=list->_count;
    unsigned capacity;void *buffer=(void *)list->_data;
    if(buffer==0){capacity=0;}else{capacity=Memory_GetBufferSize(buffer)>>2;}
    if(count>=(int)capacity)ObjectPointerList_EnsureIndex(list,count);
    ((int *)list->_data)[list->_count]=value;
    return list->_count++;
}

void ObjectPointerList_SetAt(__internalNonRefCountedObjectList *list, int index, int value) {
    void *buffer = (void *)list->_data;
    unsigned capacity;
    if (buffer == 0) {
        capacity = 0;
    } else {
        capacity = Memory_GetBufferSize(buffer) >> 2;
    }
    if (index >= (int)capacity)
        ObjectPointerList_EnsureIndex(list, index);
    ((int *)list->_data)[index] = value;
}

