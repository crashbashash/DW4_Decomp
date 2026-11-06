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
extern igMetaObject *g_beFileListInfo_metaObject[];
void *igInfo_Register(void);
igMetaObject *igInfo_GetPublishedMetaObject(void);
igMetaObject *beFileListInfo_GetMetaObject(void);
extern const char beFileListInfo_className[];
int beFileListInfo_GetVTable(void);
void beFileListInfo_InitFields(void);
extern char g_beFileListInfo_callbackList[];
void *beFileListInfo_Register(void);
}

void *beFileListInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFileListInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beFileListInfo_GetMetaObject,
        beFileListInfo_className,
        0x1c, /* instance size */
        beFileListInfo_GetVTable,
        beFileListInfo_InitFields,
        0, /* extra callback item */
        g_beFileListInfo_callbackList /* callback list */
    );
}
