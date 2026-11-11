#include "dw4/reflected.h"

typedef struct PointerList {
    int header[2];
    int *data;
    int count;
} PointerList;

typedef struct FieldPointerList {
    int header[2];
    void **data;
    int count;
} FieldPointerList;

extern "C" {
int igObject_ConstructHeader(...);
void *igObject_CopyConstructHeader(void *, void *);
void *igObject_InitHeader(void *);
void **igObject_GetAllocator(...);
int Gap__Core__igObject__vfunc_00__002ff0a0(...);
unsigned int Memory_GetBufferSize(void *);
void *FUN_00300e50(void *, void *, int);
void memcpy(void *, void *, int);
void memset(void *, int, int);
int strcmp(const char *, const char *);
extern int g_ObjectPointerList_vtable[4];
PointerList *ObjectPointerList_Init(PointerList *list);
}

struct List {
    char pad[8]; char *data;
    inline unsigned int Cap() {
        return data == 0 ? 0 : Memory_GetBufferSize(data) >> 2;
    }
};

extern "C" void ObjectPointerList_EnsureIndex(List *arg0, int arg1);

class AllocatorSlot216View { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
class AllocatorView { public: virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();virtual void d30();virtual void d31();virtual void d32();virtual void d33();virtual void d34();virtual void d35();virtual void d36();virtual void d37();virtual void d38();virtual void d39();virtual void d40();virtual void d41();virtual void d42();virtual void d43();virtual void d44();virtual void d45();virtual void d46();virtual void d47();virtual void d48();virtual void d49();virtual void d50();virtual void d51();virtual void *Allocate(int); };
class AllocatorSlot264View { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };

extern "C" {

void *ObjectPointerList_Construct(__internalNonRefCountedObjectList *self) {
    void **allocator;

    igObject_ConstructHeader(self);
    self->_vtable = (int)(&g_ObjectPointerList_vtable[0]);
    if (self != 0) {
        ObjectPointerList_Init((PointerList *)self);
    }
    allocator = (void **)(igObject_GetAllocator(self));
    self->_data = ((AllocatorSlot216View *)(allocator))->vX((int)(0x10));
    return self;
}

PointerList *ObjectPointerList_Init(PointerList *list) {
    igObject_InitHeader(list);
    *(int *)list = (int)g_ObjectPointerList_vtable;
    list->data = 0;
    list->count = 0;
    return list;
}

__internalNonRefCountedObjectList *ObjectPointerList_CopyConstruct(__internalNonRefCountedObjectList *self, __internalNonRefCountedObjectList *source) {
    int bytes;
    igObject_CopyConstructHeader(self, source);
    self->_vtable = (int)g_ObjectPointerList_vtable;
    self->_count = source->_count;
    if (source->_data) {
        bytes = self->_count * 4;
        AllocatorView *allocator = (AllocatorView *)igObject_GetAllocator(self);
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
        allocator = (void **)(igObject_GetAllocator(self));
        ((AllocatorSlot264View *)(allocator))->vX((int)(buffer));
    }
    Gap__Core__igObject__vfunc_00__002ff0a0(self);
}

void ObjectPointerList_EnsureIndex(List *arg0, int arg1) {
    if (arg1 >= (int)arg0->Cap()) {
        unsigned int old = arg0->Cap();
        unsigned int n = old;
        if (old == 0) {
            n = 4;
        }
        while (!(arg1 < (int)n)) {
            if ((int)n < 512) n *= 2; else n += 512;
        }
        arg0->data = (char *)FUN_00300e50(arg0, arg0->data, n * 4);
        char *p = arg0->data;
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
    if(count>=(int)capacity)ObjectPointerList_EnsureIndex((List *)list,count);
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
        ObjectPointerList_EnsureIndex((List *)list, count);
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
    if(count>=(int)capacity)ObjectPointerList_EnsureIndex((List *)list,count);
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
        ObjectPointerList_EnsureIndex((List *)list, index);
    list->data[index] = value;
}
}
