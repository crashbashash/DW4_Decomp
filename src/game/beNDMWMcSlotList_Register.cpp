struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWMcSlotList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNDMWMcSlotList_GetMetaObject(void);
extern const char beNDMWMcSlotList_className[];
int beNDMWMcSlotList_GetVTable(void);
extern char g_beNDMWMcSlotList_callbackList[];
void *beNDMWMcSlotList_Register(void);
}

void *beNDMWMcSlotList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcSlotList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWMcSlotList_GetMetaObject,
        beNDMWMcSlotList_className,
        0x14, /* instance size */
        beNDMWMcSlotList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWMcSlotList_callbackList /* callback list */
    );
}
