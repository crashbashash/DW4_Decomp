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
extern igMetaObject *g_beDataObjString_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beDataObjString_GetMetaObject(void);
extern const char beDataObjString_className[];
int beDataObjString_GetVTable(void);
void beDataObjString_InitFields(void);
void *beDataObjString_Register(void);
}

void *beDataObjString_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjString_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjString_GetMetaObject,
        beDataObjString_className,
        0x10, /* instance size */
        beDataObjString_GetVTable,
        beDataObjString_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
