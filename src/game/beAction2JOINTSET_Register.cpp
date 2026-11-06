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
extern igMetaObject *g_beAction2JOINTSET_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beAction2JOINTSET_GetMetaObject(void);
extern const char beAction2JOINTSET_className[];
int beAction2JOINTSET_GetVTable(void);
void beAction2JOINTSET_InitFields(void);
void *beAction2JOINTSET_Register(void);
}

void *beAction2JOINTSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2JOINTSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2JOINTSET_GetMetaObject,
        beAction2JOINTSET_className,
        0x18, /* instance size */
        beAction2JOINTSET_GetVTable,
        beAction2JOINTSET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
