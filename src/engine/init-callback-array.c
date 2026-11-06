/* The growable callback array of the class-registration protocol (data pointer,
 * count, capacity): igArray_Construct 0x002d3400, igArray_Destruct 0x002d3420 and
 * igArray_Append 0x002d3480.  docs/engine/metadata-callback-services.md documents
 * the lifetime and the growth rule.
 *
 * The growth rule is retail's, not a conventional 1.5x: the first capacity is 4 and
 * every later growth multiplies the capacity by (capacity * 3) / 2, so ordinary
 * capacities advance 4 -> 24 -> 864.  Do not "fix" it. */
typedef struct {int *data;int count;int capacity;} CallbackArray;

/* Object system record: only the allocator it keeps at +52 is used here
 * (docs/engine/metadata-callback-services.md, "object system +52"). */
typedef struct ObjectSystemRecord {
    char unknown0[52];
    void *allocator;
} ObjectSystemRecord;
extern ObjectSystemRecord *g_objectSystem[4];

void *Memory_AllocateBufferDirect(int,void *);
/* Reallocate an existing buffer: allocates afresh when the buffer is null, otherwise
 * asks the owning allocator (Memory_FindOwningAllocator, virtual slot 232) to resize
 * it.  See docs/engine/metadata-callback-services.md. */
void *Memory_ReallocateBuffer(void *,int);
void Memory_FreeBuffer(void *);
/* Delete the array object itself (alias of Memory_FreeBuffer). */
void FUN_002ed5c0(void *);

CallbackArray *igArray_Construct(CallbackArray *array){array->data=0;array->capacity=0;array->count=0;return array;}

/* Free the data buffer, and the array object itself when `deleteFlag` is positive. */
CallbackArray *igArray_Destruct(CallbackArray *array,short deleteFlag){
    if(array){if(array->data)Memory_FreeBuffer(array->data);if(deleteFlag>0)FUN_002ed5c0(array);}
    return array;
}

/* Grow only when count equals capacity, then store `item` at the end. */
void igArray_Append(CallbackArray *array,int item){
    int capacity=array->capacity;
    if(array->count==capacity){
        if(capacity==0)array->capacity=4;
        else array->capacity*=((capacity*3)/2);
        if(array->data==0)array->data=Memory_AllocateBufferDirect(array->capacity*4,g_objectSystem[0]->allocator);
        else array->data=Memory_ReallocateBuffer(array->data,array->capacity*4);
    }
    array->data[array->count++]=item;
}
