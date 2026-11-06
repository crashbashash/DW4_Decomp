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
extern igMetaObject *g_beFontGeomAttrPairList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beFontGeomAttrPairList_GetMetaObject(void);
extern const char beFontGeomAttrPairList_className[];
int beFontGeomAttrPairList_GetVTable(void);
extern char g_beFontGeomAttrPairList_callbackList[];
void *beFontGeomAttrPairList_Register(void);
}

void *beFontGeomAttrPairList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontGeomAttrPairList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beFontGeomAttrPairList_GetMetaObject,
        beFontGeomAttrPairList_className,
        0x14, /* instance size */
        beFontGeomAttrPairList_GetVTable,
        0,
        0, /* extra callback item */
        g_beFontGeomAttrPairList_callbackList /* callback list */
    );
}
