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
extern igMetaObject *g_beNDMWLoadIntf2DegiStateList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2DegiStateList_GetMetaObject(void);
extern const char beNDMWLoadIntf2DegiStateList_className[];
int beNDMWLoadIntf2DegiStateList_GetVTable(void);
extern char g_beNDMWLoadIntf2DegiStateList_callbackList[];
void *beNDMWLoadIntf2DegiStateList_Register(void);
}

void *beNDMWLoadIntf2DegiStateList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2DegiStateList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadIntf2DegiStateList_GetMetaObject,
        beNDMWLoadIntf2DegiStateList_className,
        0x14, /* instance size */
        beNDMWLoadIntf2DegiStateList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiStateList_callbackList /* callback list */
    );
}
