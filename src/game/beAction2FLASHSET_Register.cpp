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
extern igMetaObject *g_beAction2FLASHSET_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beAction2FLASHSET_GetMetaObject(void);
extern const char beAction2FLASHSET_className[];
int beAction2FLASHSET_GetVTable(void);
void *beAction2FLASHSET_Register(void);
}

void *beAction2FLASHSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2FLASHSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2FLASHSET_GetMetaObject,
        beAction2FLASHSET_className,
        0xc, /* instance size */
        beAction2FLASHSET_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
