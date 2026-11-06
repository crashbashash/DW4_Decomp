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
extern igMetaObject *g_beDataObjListList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beDataObjListList_GetMetaObject(void);
extern const char beDataObjListList_className[];
int beDataObjListList_GetVTable(void);
extern char pA6[];
void *beDataObjListList_Register(void);
}

void *beDataObjListList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataObjListList_GetMetaObject,
        beDataObjListList_className,
        0x14, /* instance size */
        beDataObjListList_GetVTable,
        0,
        0, /* extra callback item */
        pA6 /* callback list */
    );
}
