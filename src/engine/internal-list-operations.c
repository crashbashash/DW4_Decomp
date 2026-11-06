/* Exact internal-list operations. PointerList/RefHeader are observed ABI views. Append physical
 * old-count return is a compiler-match signature hypothesis; no defined public return is claimed
 * by the behavioral oracle. */
/* Observed 16-byte ABI; no reflected public-list layout is substituted. */
typedef struct {int header[2];int *data;int count;} PointerList;
typedef struct {int vtable;unsigned refs;} RefHeader;
unsigned int Memory_GetBufferSize(void *);
void *FUN_00300e50(void *,void *,int);
void memset(void *,int,int);
void ObjectPointerList_EnsureIndex(PointerList *,int);
void ObjectPointerList_SetCount(PointerList *,int);
void ObjectPointerList_Destruct(PointerList *);
void InternalObjectList_SetCount(PointerList *,int);
void igObject_Destroy(void *);
int igStrCmp(const char *,const char *);

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

void InternalObjectList_Destruct(PointerList *list){InternalObjectList_SetCount(list,0);ObjectPointerList_Destruct(list);}

void InternalObjectList_SetCount(PointerList *list,int count){
    int i=list->count;
    if(count<i){
        i--;
        while(i>=count){
            RefHeader *item=(RefHeader *)list->data[i];
            if(item){--item->refs;if(!(item->refs&0x7fffff))igObject_Destroy(item);}
            i--;
        }
    }
    ObjectPointerList_SetCount(list,count);
}
