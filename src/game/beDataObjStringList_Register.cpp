struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
void *igMetaObject_RegisterClass(
        int abstractState,
        igMetaObject **slot,
        void *(*baseRegister)(void),
        igMetaObject *(*baseMetaObject)(void),
        igMetaObject *(*getMetaObject)(void),
        const char *className,
        int instanceSize,
        int (*getVTable)(void),
        void (*initFields)(void),
        void (*callbackItem)(void),
        void *callbackList);
extern igMetaObject *g_beDataObjStringList_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beDataObjStringList_GetMetaObject(void);
extern const char beDataObjStringList_className[];
int beDataObjStringList_GetVTable(void);
void beDataObjStringList_InitFields(void);
extern char g_beDataObjStringList_callbackList[];
void *beDataObjStringList_Register(void);
}

void *beDataObjStringList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjStringList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjStringList_GetMetaObject,
        beDataObjStringList_className,
        0x10, /* instance size */
        beDataObjStringList_GetVTable,
        beDataObjStringList_InitFields,
        0, /* extra callback item */
        g_beDataObjStringList_callbackList /* callback list */
    );
}
