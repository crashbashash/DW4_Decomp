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
extern igMetaObject *g_beBaseInfoRamList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beBaseInfoRamList_GetMetaObject(void);
extern const char beBaseInfoRamList_className[];
int beBaseInfoRamList_GetVTable(void);
extern char g_beBaseInfoRamList_callbackList[];
void *beBaseInfoRamList_Register(void);
}

void *beBaseInfoRamList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoRamList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoRamList_GetMetaObject,
        beBaseInfoRamList_className,
        0x14, /* instance size */
        beBaseInfoRamList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoRamList_callbackList /* callback list */
    );
}
