/* Start an empty list with 64 zeroed slots. */
RegistryList *igMemoryPoolInfoList_Init(RegistryList *list){
    list->capacity=64;list->count=0;
    list->data=(void **)((BootstrapSystem * *)g_objectSystem)[0]->allocator->Allocate((unsigned)list->capacity*4);
    memset(list->data,0,(unsigned)list->capacity*4);
    return list;
}

/* Free the slot storage; destroy the list object itself only when deleteFlag is positive. */
RegistryList *igMemoryPoolInfoList_Release(RegistryList *list,int deleteFlag){
    if(list){
        if(list->data)((BootstrapSystem * *)g_objectSystem)[0]->allocator->Free(list->data);
        if((short)deleteFlag>0)igMemoryPoolInfoList_Delete(list);
    }
    return list;
}

/* Index of `allocator` in the list, or -1 when absent. */
int igMemoryPoolInfoList_IndexOf(AllocatorRegistry *list,igMemoryPoolView *allocator){
    int count=list->count;
    for(int i=0;i<count;++i)if(list->data[i]==allocator)return i;
    return -1;
}

/* Add an entry at the end, growing the storage by four zeroed slots when full. */
void igMemoryPoolInfoList_Append(RegistryList *list,void *entry){
    if(list->count>=list->capacity){
        list->capacity+=4;
        list->data=(void **)((BootstrapSystem * *)g_objectSystem)[0]->allocator->Reallocate(list->data,(unsigned)list->capacity*4);
        memset(list->data+(list->capacity-4),0,16);
    }
    list->data[list->count++]=entry;
}

void *igMemoryPoolInfoList_Allocate(unsigned int size)
{
    return ((BootstrapSystem * *)g_objectSystem)[0]->allocator->Allocate(size);
}

void igMemoryPoolInfoList_Delete(void *block)
{
    ((BootstrapSystem * *)g_objectSystem)[0]->allocator->Free(block);
}

