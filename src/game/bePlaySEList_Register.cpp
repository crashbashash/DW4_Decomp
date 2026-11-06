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
extern igMetaObject *g_bePlaySEList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *bePlaySEList_GetMetaObject(void);
extern const char bePlaySEList_className[];
int bePlaySEList_GetVTable(void);
extern char g_bePlaySEList_callbackList[];
void *bePlaySEList_Register(void);
}

void *bePlaySEList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePlaySEList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        bePlaySEList_GetMetaObject,
        bePlaySEList_className,
        0x14, /* instance size */
        bePlaySEList_GetVTable,
        0,
        0, /* extra callback item */
        g_bePlaySEList_callbackList /* callback list */
    );
}
