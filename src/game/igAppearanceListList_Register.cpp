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
extern igMetaObject *g_igAppearanceListList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *igAppearanceListList_GetMetaObject(void);
extern const char igAppearanceListList_className[];
int igAppearanceListList_GetVTable(void);
extern char g_igAppearanceListList_callbackList[];
void *igAppearanceListList_Register(void);
}

void *igAppearanceListList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAppearanceListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAppearanceListList_GetMetaObject,
        igAppearanceListList_className,
        0x14, /* instance size */
        igAppearanceListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAppearanceListList_callbackList /* callback list */
    );
}
