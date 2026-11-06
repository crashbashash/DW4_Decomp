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
extern igMetaObject *g_beAction2WAITCHECK_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beAction2WAITCHECK_GetMetaObject(void);
extern const char beAction2WAITCHECK_className[];
int beAction2WAITCHECK_GetVTable(void);
void beAction2WAITCHECK_InitFields(void);
void *beAction2WAITCHECK_Register(void);
}

void *beAction2WAITCHECK_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2WAITCHECK_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2WAITCHECK_GetMetaObject,
        beAction2WAITCHECK_className,
        0x10, /* instance size */
        beAction2WAITCHECK_GetVTable,
        beAction2WAITCHECK_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
