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
extern igMetaObject *g_beGeneraterItemDataOneList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beGeneraterItemDataOneList_GetMetaObject(void);
extern const char beGeneraterItemDataOneList_className[];
int beGeneraterItemDataOneList_GetVTable(void);
extern char g_beGeneraterItemDataOneList_callbackList[];
void *beGeneraterItemDataOneList_Register(void);
}

void *beGeneraterItemDataOneList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterItemDataOneList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterItemDataOneList_GetMetaObject,
        beGeneraterItemDataOneList_className,
        0x14, /* instance size */
        beGeneraterItemDataOneList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterItemDataOneList_callbackList /* callback list */
    );
}
