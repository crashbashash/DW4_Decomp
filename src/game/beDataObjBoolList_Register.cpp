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
extern igMetaObject *g_beDataObjBoolList_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beDataObjBoolList_GetMetaObject(void);
extern const char beDataObjBoolList_className[];
int beDataObjBoolList_GetVTable(void);
void beDataObjBoolList_InitFields(void);
extern char g_beDataObjBoolList_callbackList[];
void *beDataObjBoolList_Register(void);
}

void *beDataObjBoolList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjBoolList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjBoolList_GetMetaObject,
        beDataObjBoolList_className,
        0x10, /* instance size */
        beDataObjBoolList_GetVTable,
        beDataObjBoolList_InitFields,
        0, /* extra callback item */
        g_beDataObjBoolList_callbackList /* callback list */
    );
}
