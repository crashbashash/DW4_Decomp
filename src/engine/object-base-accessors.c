extern int g_igObject_metaObject[4];
void *igObject_GetMetaObject_ParentAccessor(void){return (void *)g_igObject_metaObject[0];}
void *igObject_GetMetaObject_Virtual(void){return (void *)g_igObject_metaObject[0];}
void *igObject_GetMetaObject(void){return (void *)g_igObject_metaObject[0];}
void *igObject_GetNoParentMetaObject(void){return 0;}
