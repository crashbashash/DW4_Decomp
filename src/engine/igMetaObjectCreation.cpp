/* Reflection creation helpers. StaticInitCallbacks is a structural ABI view,
 * not an original type name. Byte verification preserves the physical callback
 * register flow; see docs/engine/object-creation.md. */
extern "C" void *Memory_GetDefaultAllocator();
extern "C" void *igMetaObject_CreateInstance(void *,void *);
extern "C" void *igMetaObject_CreateInstanceDefault(void *meta){return igMetaObject_CreateInstance(meta,Memory_GetDefaultAllocator());}

struct StaticInitCallbacks { void (**functions)(); int count; };
extern "C" void igArray_Destruct(StaticInitCallbacks *,short);
extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*initialize)()){
    int i; int count; StaticInitCallbacks *list=initialize();
    if(list){count=list->count;for(i=0;i<count;i++)list->functions[i]();igArray_Destruct(list,1);}
}
