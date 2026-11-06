/* Look up a reflected class (igMetaObject) by name in the engine's object system. This wrapper
 * supplies the system record to igObjectSystem_FindMetaByName, which the allocator builder
 * dispatch uses to resolve pool class names. */
extern int igObjectSystem_FindMetaByName(void *objectSystem, const char *name);
extern void *g_objectSystem[4];
int igObjectSystem_FindMetaByNameDefault(const char *name){return igObjectSystem_FindMetaByName(g_objectSystem[0],name);}
