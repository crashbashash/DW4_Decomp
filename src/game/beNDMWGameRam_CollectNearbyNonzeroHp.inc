/* Complete nearby-query object and its emitted deleting destructor.
 * The class/vector/list names project the recovered ABI and operation order;
 * original C++ template and qualifier spellings are not established.
 * config/SLUS-20836/unit-objects.json owns both code bodies and their external alias.
 * This file is included by src/unmatched/FUN_003fab90.cpp (extension .inc so the
 * unit scanner does not treat it as a second owner): the stat recompute uses the
 * same stack-resident reference class, so both functions and its single emitted
 * destructor form one compiler unit.
 */
#include "dw4/reflected.h"
struct Vec3 { float x,y,z; };
struct Mat44 { float m[16]; };
/* Growable int array object: vtable word, reference word, then count/capacity/data.
 * The count reloads are observable in the original instructions. */
struct IntList { int vtable_word, reference_word; volatile int count; int capacity; int *data; };
/* Squared radius of the query: members closer than 30 units to the centre qualify. */
#define NEARBY_RADIUS_SQUARED 900.0f
/* Low 23 bits of igObject::_refCount hold the count. */
#define REFERENCE_COUNT_MASK 0x7fffffULL
extern "C" {
int igObject_GetAllocator(beNDMWGameRam *);
int Memory_GetAllocatorBySelector(int);
IntList *FUN_002caa70(int);
void igObject_Destroy(void *);
void List_Resize(IntList *,int,int);
void beMessenger_SendGroup(int,const char *,const char *);
int beMessenger_GetIntCount(int);
int beMessenger_GetInt(int,int);
void beMessenger_GetMatrix(Mat44 *,int,int);
void Matrix44_GetTranslation(const Mat44 *,Vec3 *);
void beMessenger_PushArgContext(int);
void beMessenger_SelectReceivers(int,const char *,const char *,int);
void beMessenger_SetRunCheck(int,unsigned char);
void beMessenger_DispatchSelected(int,const char *);
void beMessenger_PopArgContext(int);
extern char GETMATRIX[],GETHP[];
/* Default allocator selector (docs/engine/subwindow-preparation.md). */
extern int g_defaultAllocatorSelector[4];
extern unsigned char GPR_00554c14;
}
/* Stack-resident counted reference to an IntList (the low 23 bits of the reference
 * word are the count; the object is destroyed when the last reference goes). */
class NearbyListRef;
class IntListRef {
public:
    IntList *value;
    IntListRef(IntList *p):value(p) {}
    IntListRef(const NearbyListRef &p);
    IntListRef(const IntListRef &p):value(p.value) { if(value) ++value->reference_word; }
    ~IntListRef() {
        IntList *object=value;
        if(object) {
            --object->reference_word;
            if (((unsigned long long)(long long)object->reference_word & REFERENCE_COUNT_MASK)==0)
                igObject_Destroy(object);
        }
    }
};
/* The query's own working reference: its destructor is a separate retail copy (0x00150eb0, config/SLUS-20836/unit-objects.json
 * duplicates), while the by-value result handed back to the caller is the IntListRef whose destructor is 0x003fc670. */
class NearbyListRef {
public:
    IntList *value;
    NearbyListRef(IntList *p):value(p) {}
    ~NearbyListRef() {
        IntList *object=value;
        if(object) {
            --object->reference_word;
            if (((unsigned long long)(long long)object->reference_word & REFERENCE_COUNT_MASK)==0)
                igObject_Destroy(object);
        }
    }
};
inline IntListRef::IntListRef(const NearbyListRef &p):value(p.value) { if(value) ++value->reference_word; }
/* 0x003fc780
 * Collect the ids of the members of messenger group `group` that are within
 * 30 units of `center` (compared on GETMATRIX translations), skip `excluded`,
 * and keep those whose GETHP reply is nonzero (GETHP: docs/engine/property-system.md).
 * The result list comes from the
 * object's own allocator when the global byte flag is set, otherwise from the
 * allocator selected by g_defaultAllocatorSelector[0]. */
extern "C" IntListRef beNDMWGameRam_CollectNearbyNonzeroHp(beNDMWGameRam *self,const char *group,int excluded,const Vec3 *center) {
    int entry_index;
    int member_id;
    int append_index;
    IntList *list;
    int selfAllocator=igObject_GetAllocator(self);
    NearbyListRef result(FUN_002caa70(GPR_00554c14 ? selfAllocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
    beMessenger_SendGroup(self->_messenger,group,GETMATRIX);
    int count=beMessenger_GetIntCount(self->_messenger);
    Vec3 delta;
    Mat44 matrix;
    for(entry_index=0;entry_index<count;++entry_index) {
        member_id=beMessenger_GetInt(self->_messenger,entry_index);
        if(member_id!=excluded) {
            beMessenger_GetMatrix(&matrix,self->_messenger,entry_index);
            Matrix44_GetTranslation(&matrix,&delta);
            delta.x-=center->x;
            delta.y-=center->y;
            delta.z-=center->z;
            if((delta.x*delta.x+delta.y*delta.y+delta.z*delta.z)<NEARBY_RADIUS_SQUARED) {
                beMessenger_PushArgContext(self->_messenger);
                beMessenger_SelectReceivers(self->_messenger,group,0,member_id);
                beMessenger_SetRunCheck(self->_messenger,1);
                beMessenger_DispatchSelected(self->_messenger,GETHP);
                if(beMessenger_GetInt(self->_messenger,0)) {
                    list=result.value;
                    append_index=list->count;
                    if(append_index<list->capacity) ++list->count;
                    else List_Resize(list,append_index+1,4);
                    list->data[append_index]=member_id;
                }
                beMessenger_PopArgContext(self->_messenger);
            }
        }
    }
    return result;
}
