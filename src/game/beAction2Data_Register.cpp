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
extern igMetaObject *g_beAction2Data_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beAction2Data_GetMetaObject(void);
extern const char beAction2Data_className[];
int beAction2Data_GetVTable(void);
void beAction2Data_InitFields(void);
extern char g_beAction2Data_callbackList[];
void *beAction2Data_Register(void);
}

void *beAction2Data_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2Data_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2Data_GetMetaObject,
        beAction2Data_className,
        0x10, /* instance size */
        beAction2Data_GetVTable,
        beAction2Data_InitFields,
        0, /* extra callback item */
        g_beAction2Data_callbackList /* callback list */
    );
}
