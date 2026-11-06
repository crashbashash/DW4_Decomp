/* Lifecycle of the engine-internal pointer lists: construction, resizing,
 * indexed store, and the "retained" variants that keep a reference count on
 * the stored object.
 *
 * Every function is byte-matched; the shapes below are exactly the retail ones
 * (a duplicated capacity computation in each resizing function, the release
 * of the old entry written out inline).  The reflected lists in
 * include/dw4/reflected.h are 20 bytes; these internal lists use the exact
 * 16-byte layout below, so they are not the reflected public classes. */

/* Exact 16-byte list ABI projection: object header, element block, count. */
typedef struct PointerList {
    int header[2];  /* +0 vtable, +4 reference count (see RefHeader) */
    int *data;      /* +8  element block, sized by Memory_GetBufferSize */
    int count;      /* +12 number of elements in use */
} PointerList;

/* Head of every reference-counted object: vtable, then a reference count whose
 * low 23 bits are the count (the release below tests `refs & 0x7fffff`,
 * the same test as the inlined release in igObject-derived destructors). */
typedef struct RefHeader {
    int vtable;
    unsigned refs;
} RefHeader;

/* Mask of the reference-count bits within RefHeader::refs. */
#define REF_COUNT_MASK 0x7fffff

void *igObject_InitHeader(void *);
void *ObjectPointerList_Construct(void *);
void *ObjectPointerList_CopyConstruct(void *, void *);
void ObjectPointerList_EnsureIndex(PointerList *, int);
void ObjectPointerList_Insert(PointerList *, int, int);
int ObjectPointerList_Append(PointerList *, int); /* physical return candidate */
unsigned int Memory_GetBufferSize(void *);
void igObject_Destroy(void *);

/* Vtables stored into offset 0: the plain pointer list and the derived internal object list that
 * the InternalObjectList_* functions below install over it. */
extern int g_ObjectPointerList_vtable[4];
extern int g_InternalObjectList_vtable[4];

PointerList *ObjectPointerList_Init(PointerList *list) {
    igObject_InitHeader(list);
    *(int *)list = (int)g_ObjectPointerList_vtable;
    list->data = 0;
    list->count = 0;
    return list;
}

/* Set the element count, growing the block first when it cannot hold `count`
 * entries (capacity is the buffer size in words). */
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

/* Store `value` at `index`, growing the block first when the index is past
 * its capacity.  The count is not changed. */
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

void *InternalObjectList_Construct(PointerList *list) {
    ObjectPointerList_Construct(list);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

void *InternalObjectList_Init(PointerList *list) {
    ObjectPointerList_Init(list);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

void *InternalObjectList_CopyConstruct(PointerList *list, PointerList *source) {
    ObjectPointerList_CopyConstruct(list, source);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

/* Insert `value` at `index`, taking a reference on it for the list. */
void InternalObjectList_InsertRetained(PointerList *list, int index, RefHeader *value) {
    if (value)
        ++value->refs;
    ObjectPointerList_Insert(list, index, (int)value);
}

/* Append `value`, taking a reference on it for the list. */
void MetaRefList_AppendRetained(PointerList *list, RefHeader *value) {
    if (value)
        ++value->refs;
    ObjectPointerList_Append(list, (int)value);
}

/* Replace the entry at `index` with `value`: reference the new object, release
 * the old one (destroying it when its count reaches zero), then store. */
void InternalObjectList_SetAtRetained(PointerList *list, int index, RefHeader *value) {
    RefHeader *old;
    if (value)
        ++value->refs;
    old = (RefHeader *)list->data[index];
    if (old) {
        --old->refs;
        if (!(old->refs & REF_COUNT_MASK))
            igObject_Destroy(old);
    }
    ObjectPointerList_SetAt(list, index, (int)value);
}
