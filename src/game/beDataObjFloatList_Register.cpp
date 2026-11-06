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
extern igMetaObject *g_beDataObjFloatList_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beDataObjFloatList_GetMetaObject(void);
extern const char beDataObjFloatList_className[];
int beDataObjFloatList_GetVTable(void);
void beDataObjFloatList_InitFields(void);
extern char g_beDataObjFloatList_callbackList[];
void *beDataObjFloatList_Register(void);
}

void *beDataObjFloatList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjFloatList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjFloatList_GetMetaObject,
        beDataObjFloatList_className,
        0x10, /* instance size */
        beDataObjFloatList_GetVTable,
        beDataObjFloatList_InitFields,
        0, /* extra callback item */
        g_beDataObjFloatList_callbackList /* callback list */
    );
}
