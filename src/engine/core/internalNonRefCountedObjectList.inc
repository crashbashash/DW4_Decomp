void *ObjectPointerList_Construct(__internalNonRefCountedObjectList *self, int extra1) {
    void **allocator;

    igObject_ConstructHeader(self);
    self->_vtable = (int)(&g_ObjectPointerList_vtable[0]);
    if (self != 0) {
        ObjectPointerList_Init((PointerList *)self);
    }
    allocator = (void **)(((void **)igObject_GetAllocator((int)self)));
    self->_data = (int)((igMemoryPoolView *)allocator)->Allocate(0x10);
    return self;
}

PointerList *ObjectPointerList_Init(PointerList *list) {
    igObject_InitHeader((struct ObjectHeader *)list);
    *(int *)list = (int)g_ObjectPointerList_vtable;
    list->data = 0;
    list->count = 0;
    return list;
}

__internalNonRefCountedObjectList *ObjectPointerList_CopyConstruct(__internalNonRefCountedObjectList *self, __internalNonRefCountedObjectList *source) {
    int bytes;
    igObject_CopyConstructHeader((CopyHeader *)self, (CopyHeader *)source);
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

static inline unsigned int pointerListCapacity(PointerList *list) {
    return list->data == 0 ? 0 : Memory_GetBufferSize(list->data) >> 2;
}

void ObjectPointerList_EnsureIndex(PointerList *list, int index) {
    if (index >= (int)pointerListCapacity(list)) {
        unsigned int old = pointerListCapacity(list);
        unsigned int n = old;
        if (old == 0) {
            n = 4;
        }
        while (!(index < (int)n)) {
            if ((int)n < 512) n *= 2; else n += 512;
        }
        list->data = (int *)FUN_00300e50((int)list, (int)list->data, n * 4);
        char *p = (char *)list->data;
        p += old * 4;
        memset(p, 0, (n - old) * 4);
    }
}

void *ObjectPointerList_FindByStringField(FieldPointerList *list,igMetaField *selector,const char *name){
    int i;int byteOffset;
    for(i=0;i<list->count;i++){
        byteOffset=i*4;
        if(strcmp(*(char **)((char *)*(void **)((char *)list->data+byteOffset)+selector->_offset),name)==0)
            return *(void **)((char *)list->data+byteOffset);
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

void ObjectPointerList_ClearUnused(PointerList *list){
    int i=list->count;
    while(i<(int)(list->data?Memory_GetBufferSize(list->data)>>2:0)){list->data[i]=0;i++;}
}

void ObjectPointerList_Insert(PointerList *list,int index,int value){
    int i;int count=list->count;
    unsigned capacity;void *buffer=list->data;
    if(buffer==0){capacity=0;}else{capacity=Memory_GetBufferSize(buffer)>>2;}
    if(count>=(int)capacity)ObjectPointerList_EnsureIndex(list,count);
    i=list->count;
    while(i>index){list->data[i]=list->data[i-1];i--;}
    list->data[index]=value;
    list->count++;
}

void ObjectPointerList_SetCount(PointerList *list, int count) {
    void *buffer = list->data;
    unsigned capacity;
    if (buffer == 0) {
        capacity = 0;
    } else {
        capacity = Memory_GetBufferSize(buffer) >> 2;
    }
    if (count >= (int)capacity)
        ObjectPointerList_EnsureIndex(list, count);
    list->count = count;
}

int ObjectPointerList_EraseAt(PointerList *list,int index){
    int i;
    if(index<list->count){
        for(i=index;i<list->count-1;i++)list->data[i]=list->data[i+1];
        list->count--;
        return index;
    }
    return -1;
}

int ObjectPointerList_Append(PointerList *list,int value){
    int count=list->count;
    unsigned capacity;void *buffer=list->data;
    if(buffer==0){capacity=0;}else{capacity=Memory_GetBufferSize(buffer)>>2;}
    if(count>=(int)capacity)ObjectPointerList_EnsureIndex(list,count);
    list->data[list->count]=value;
    return list->count++;
}

void ObjectPointerList_SetAt(PointerList *list, int index, int value) {
    void *buffer = list->data;
    unsigned capacity;
    if (buffer == 0) {
        capacity = 0;
    } else {
        capacity = Memory_GetBufferSize(buffer) >> 2;
    }
    if (index >= (int)capacity)
        ObjectPointerList_EnsureIndex(list, index);
    list->data[index] = value;
}

