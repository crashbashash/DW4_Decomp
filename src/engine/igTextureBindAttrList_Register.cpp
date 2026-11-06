struct igMetaObject;
extern "C" {
void AdxMovieLibrary_MarkRegistered(void);
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
extern igMetaObject *g_igTextureBindAttrList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *igTextureBindAttrList_GetMetaObject(void);
extern const char igTextureBindAttrList_className[];
int igTextureBindAttrList_GetVTable(void);
extern char g_igTextureBindAttrList_callbackList[];
void *igTextureBindAttrList_Register(void);
}

void *igTextureBindAttrList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureBindAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igTextureBindAttrList_GetMetaObject,
        igTextureBindAttrList_className,
        0x14, /* instance size */
        igTextureBindAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureBindAttrList_callbackList /* callback list */
    );
}
