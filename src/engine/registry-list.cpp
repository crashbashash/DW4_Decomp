/* The growable pointer list shared by the allocator registries (igMemoryPoolInfoList): data,
 * signed count, capacity. Initial capacity 64 entries, growing four at a time. The allocator used
 * for the storage is the one the object system keeps at +48 (g_objectSystem). The classes are
 * observed ABI projections of the allocator's virtual slots (a0.. are padding). */
struct RegistryList {void **data;int count,capacity;};
class RegistryAllocatorView {public:
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
virtual void a22();
virtual void a23();
virtual void a24();
virtual void a25();
virtual void a26();
virtual void a27();
virtual void a28();
virtual void a29();
virtual void a30();
virtual void a31();
virtual void a32();
virtual void a33();
virtual void a34();
virtual void a35();
virtual void a36();
virtual void a37();
virtual void a38();
virtual void a39();
virtual void a40();
virtual void a41();
virtual void a42();
virtual void a43();
virtual void a44();
virtual void a45();
virtual void a46();
virtual void a47();
virtual void a48();
virtual void a49();
virtual void a50();
virtual void a51();
virtual void *Allocate(unsigned);
virtual void a220();virtual void a224();virtual void a228();
virtual void *Reallocate(void *,unsigned);
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual void Free(void *);};
/* Object system as seen from here: only its allocator reference (+48) is used. */
struct BootstrapSystem {char prefix[48];RegistryAllocatorView *allocator;};
extern "C" BootstrapSystem *g_objectSystem[4];
extern "C" void memset(void *,int,unsigned);
extern "C" void igMemoryPoolInfoList_Delete(void *);
/* Start an empty list with 64 zeroed slots. */
extern "C" RegistryList *igMemoryPoolInfoList_Init(RegistryList *list){
    list->capacity=64;list->count=0;
    list->data=(void **)g_objectSystem[0]->allocator->Allocate((unsigned)list->capacity*4);
    memset(list->data,0,(unsigned)list->capacity*4);
    return list;
}
/* Free the slot storage; destroy the list object itself only when deleteFlag is positive. */
extern "C" RegistryList *igMemoryPoolInfoList_Release(RegistryList *list,int deleteFlag){
    if(list){
        if(list->data)g_objectSystem[0]->allocator->Free(list->data);
        if((short)deleteFlag>0)igMemoryPoolInfoList_Delete(list);
    }
    return list;
}
/* Add an entry at the end, growing the storage by four zeroed slots when full. */
extern "C" void igMemoryPoolInfoList_Append(RegistryList *list,void *entry){
    if(list->count>=list->capacity){
        list->capacity+=4;
        list->data=(void **)g_objectSystem[0]->allocator->Reallocate(list->data,(unsigned)list->capacity*4);
        memset(list->data+(list->capacity-4),0,16);
    }
    list->data[list->count++]=entry;
}
