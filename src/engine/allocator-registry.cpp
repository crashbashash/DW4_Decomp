/* Allocator registry index lookup (0x002fa5c0) and encoded-index publication (0x002f0670). An
 * allocator is identified in saved data by "registry index << 1 | which-registry": the primary
 * list (0x586f58) gives an even code, the secondary list (0x586f60) an odd one. The class below is
 * an observed ABI view that projects the original virtual slots by number (a0.. are unnamed
 * padding); it must not be instantiated. */
class AllocatorLookupView {public:
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
virtual int Kind();
virtual void a120();virtual void a124();virtual void a128();virtual int Available();
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual void b7();
virtual void b8();
virtual void b9();
virtual void b10();
virtual void b11();
virtual void b12();
virtual void b13();
virtual void b14();
virtual void b15();
virtual void b16();
virtual void b17();
virtual void b18();
virtual void b19();
virtual void b20();
virtual void b21();
virtual void b22();
virtual void b23();
virtual void b24();
virtual void b25();
virtual void b26();
virtual void b27();
virtual void b28();
virtual void b29();
virtual void b30();
virtual void b31();
virtual void b32();
virtual void b33();
virtual void b34();
virtual void b35();
virtual void b36();
virtual void b37();
virtual void b38();
virtual void b39();
virtual void b40();
virtual void b41();
virtual void b42();
virtual void b43();
virtual void b44();
virtual void b45();
virtual void b46();
virtual void b47();
virtual void b48();
virtual void b49();
virtual void b50();
virtual int Owns(void *);};
/* Growable pointer list of allocators: data, signed count, capacity (same layout as igMemoryPoolInfoList). */
struct AllocatorRegistry {AllocatorLookupView **data;int count;int capacity;};
extern "C" AllocatorRegistry *g_primaryAllocatorList[4],*g_secondaryAllocatorList[4];
/* Object-system runtime pointer; byte 0 is the "object system active" flag. */
extern "C" unsigned char *g_objectSystem[4];
extern "C" int igMemoryPoolInfoList_IndexOf(AllocatorRegistry *,AllocatorLookupView *);
/* Index of `allocator` in the list, or -1 when absent. */
extern "C" int igMemoryPoolInfoList_IndexOf(AllocatorRegistry *list,AllocatorLookupView *allocator){
    int count=list->count;
    for(int i=0;i<count;++i)if(list->data[i]==allocator)return i;
    return -1;
}
/* Encode an allocator as its registry index: Kind() == 0 allocators live in the
 * primary list (code = index << 1), the rest in the secondary one (code =
 * index << 1 | 1); 0 when the object system is inactive.  An absent allocator
 * is not rejected, it encodes the -1 from IndexOf. */
extern "C" int igAllocator_EncodeIndex(AllocatorLookupView *allocator){
    if(*g_objectSystem[0]&&!allocator->Kind())return (unsigned)igMemoryPoolInfoList_IndexOf(g_primaryAllocatorList[0],allocator)<<1;
    unsigned char result=0;
    if(*g_objectSystem[0])return ((unsigned)igMemoryPoolInfoList_IndexOf(g_secondaryAllocatorList[0],allocator)<<1)|1;
    return result;
}
