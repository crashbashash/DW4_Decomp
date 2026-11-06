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
extern igMetaObject *g_beAction2InfoList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beAction2InfoList_GetMetaObject(void);
extern const char beAction2InfoList_className[];
int beAction2InfoList_GetVTable(void);
extern char g_beAction2InfoList_callbackList[];
void *beAction2InfoList_Register(void);
}

void *beAction2InfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2InfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beAction2InfoList_GetMetaObject,
        beAction2InfoList_className,
        0x14, /* instance size */
        beAction2InfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beAction2InfoList_callbackList /* callback list */
    );
}
