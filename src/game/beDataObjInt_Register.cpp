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
extern igMetaObject *g_beDataObjInt_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beDataObjInt_GetMetaObject(void);
extern const char beDataObjInt_className[];
int beDataObjInt_GetVTable(void);
void beDataObjInt_InitFields(void);
void *beDataObjInt_Register(void);
}

void *beDataObjInt_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjInt_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjInt_GetMetaObject,
        beDataObjInt_className,
        0x10, /* instance size */
        beDataObjInt_GetVTable,
        beDataObjInt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
