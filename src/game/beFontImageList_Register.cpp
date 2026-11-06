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
extern igMetaObject *g_beFontImageList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beFontImageList_GetMetaObject(void);
extern const char beFontImageList_className[];
int beFontImageList_GetVTable(void);
extern char g_beFontImageList_callbackList[];
void *beFontImageList_Register(void);
}

void *beFontImageList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontImageList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beFontImageList_GetMetaObject,
        beFontImageList_className,
        0x14, /* instance size */
        beFontImageList_GetVTable,
        0,
        0, /* extra callback item */
        g_beFontImageList_callbackList /* callback list */
    );
}
