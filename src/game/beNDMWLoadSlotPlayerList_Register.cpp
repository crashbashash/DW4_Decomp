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
extern igMetaObject *g_beNDMWLoadSlotPlayerList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadSlotPlayerList_GetMetaObject(void);
extern const char beNDMWLoadSlotPlayerList_className[];
int beNDMWLoadSlotPlayerList_GetVTable(void);
extern char g_beNDMWLoadSlotPlayerList_callbackList[];
void *beNDMWLoadSlotPlayerList_Register(void);
}

void *beNDMWLoadSlotPlayerList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadSlotPlayerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadSlotPlayerList_GetMetaObject,
        beNDMWLoadSlotPlayerList_className,
        0x14, /* instance size */
        beNDMWLoadSlotPlayerList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadSlotPlayerList_callbackList /* callback list */
    );
}
