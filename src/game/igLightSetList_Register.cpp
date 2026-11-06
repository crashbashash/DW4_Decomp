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
extern igMetaObject *g_igLightSetList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *igLightSetList_GetMetaObject(void);
extern const char igLightSetList_className[];
int igLightSetList_GetVTable(void);
extern char g_igLightSetList_callbackList[];
void *igLightSetList_Register(void);
}

void *igLightSetList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightSetList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igLightSetList_GetMetaObject,
        igLightSetList_className,
        0x14, /* instance size */
        igLightSetList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightSetList_callbackList /* callback list */
    );
}
