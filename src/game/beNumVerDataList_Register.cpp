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
extern igMetaObject *g_beNumVerDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNumVerDataList_GetMetaObject(void);
extern const char beNumVerDataList_className[];
int beNumVerDataList_GetVTable(void);
extern char g_beNumVerDataList_callbackList[];
void *beNumVerDataList_Register(void);
}

void *beNumVerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumVerDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumVerDataList_GetMetaObject,
        beNumVerDataList_className,
        0x14, /* instance size */
        beNumVerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumVerDataList_callbackList /* callback list */
    );
}
