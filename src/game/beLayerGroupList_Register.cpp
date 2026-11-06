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
extern igMetaObject *g_beLayerGroupList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beLayerGroupList_GetMetaObject(void);
extern const char beLayerGroupList_className[];
int beLayerGroupList_GetVTable(void);
extern char g_beLayerGroupList_callbackList[];
void *beLayerGroupList_Register(void);
}

void *beLayerGroupList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLayerGroupList_GetMetaObject,
        beLayerGroupList_className,
        0x14, /* instance size */
        beLayerGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLayerGroupList_callbackList /* callback list */
    );
}
