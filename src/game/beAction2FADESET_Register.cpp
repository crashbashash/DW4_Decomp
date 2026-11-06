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
extern igMetaObject *g_beAction2FADESET_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beAction2FADESET_GetMetaObject(void);
extern const char beAction2FADESET_className[];
int beAction2FADESET_GetVTable(void);
void beAction2FADESET_InitFields(void);
void *beAction2FADESET_Register(void);
}

void *beAction2FADESET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2FADESET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2FADESET_GetMetaObject,
        beAction2FADESET_className,
        0x14, /* instance size */
        beAction2FADESET_GetVTable,
        beAction2FADESET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
