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
extern igMetaObject *g_beAction2Info_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beAction2Info_GetMetaObject(void);
extern const char beAction2Info_className[];
int beAction2Info_GetVTable(void);
void beAction2Info_InitFields(void);
extern char g_beAction2Info_callbackList[];
void *beAction2Info_Register(void);
}

void *beAction2Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beAction2Info_GetMetaObject,
        beAction2Info_className,
        0x28, /* instance size */
        beAction2Info_GetVTable,
        beAction2Info_InitFields,
        0, /* extra callback item */
        g_beAction2Info_callbackList /* callback list */
    );
}
