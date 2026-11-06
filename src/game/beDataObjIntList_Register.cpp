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
extern igMetaObject *g_beDataObjIntList_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beDataObjIntList_GetMetaObject(void);
extern const char beDataObjIntList_className[];
int beDataObjIntList_GetVTable(void);
void beDataObjIntList_InitFields(void);
extern char g_beDataObjIntList_callbackList[];
void *beDataObjIntList_Register(void);
}

void *beDataObjIntList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjIntList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjIntList_GetMetaObject,
        beDataObjIntList_className,
        0x10, /* instance size */
        beDataObjIntList_GetVTable,
        beDataObjIntList_InitFields,
        0, /* extra callback item */
        g_beDataObjIntList_callbackList /* callback list */
    );
}
