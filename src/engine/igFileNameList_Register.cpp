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
extern igMetaObject *g_igFileNameList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *igFileNameList_GetMetaObject(void);
extern const char igFileNameList_className[];
int igFileNameList_GetVTable(void);
extern char pL3[];
void *igFileNameList_Register(void);
}

void *igFileNameList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileNameList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igFileNameList_GetMetaObject,
        igFileNameList_className,
        0x14, /* instance size */
        igFileNameList_GetVTable,
        0,
        0, /* extra callback item */
        pL3 /* callback list */
    );
}
