/* look up a reflected class (igMetaObject) by name in the engine's object system. The system
 * record lives behind the pointer at 0x00586dc8; this wrapper supplies it to
 * igObjectSystem_FindMetaByName (0x002d3070), which the allocator builder dispatch uses to resolve
 * pool class names. */
extern int igObjectSystem_FindMetaByName(void *objectSystem, const char *name);
extern void *g_objectSystem[4];
int igObjectSystem_FindMetaByNameDefault(const char *name){return igObjectSystem_FindMetaByName(g_objectSystem[0],name);}
