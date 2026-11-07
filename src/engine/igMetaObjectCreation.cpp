/* Reflection creation helpers. StaticInitCallbacks is a structural ABI view, not an original type
 * name. */
extern "C" void *Memory_GetDefaultAllocator();
extern "C" void *igMetaObject_CreateInstance(void *,void *);
extern "C" void *igMetaObject_CreateInstanceDefault(void *meta){return igMetaObject_CreateInstance(meta,Memory_GetDefaultAllocator());}

struct StaticInitCallbacks { void (**functions)(); int count; };
extern "C" void igArray_Destruct(StaticInitCallbacks *,short);
