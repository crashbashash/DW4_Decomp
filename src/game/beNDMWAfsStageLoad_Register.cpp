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
extern igMetaObject *g_beNDMWAfsStageLoad_metaObject[];
void *igAction_Register(void);
igMetaObject *igAction_GetPublishedMetaObject(void);
igMetaObject *beNDMWAfsStageLoad_GetMetaObject(void);
extern const char beNDMWAfsStageLoad_className[];
int beNDMWAfsStageLoad_GetVTable(void);
void beNDMWAfsStageLoad_InitFields(void);
extern char g_beNDMWAfsStageLoad_callbackList[];
void *beNDMWAfsStageLoad_Register(void);
}

void *beNDMWAfsStageLoad_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsStageLoad_metaObject,
        igAction_Register,
        igAction_GetPublishedMetaObject,
        beNDMWAfsStageLoad_GetMetaObject,
        beNDMWAfsStageLoad_className,
        0x10, /* instance size */
        beNDMWAfsStageLoad_GetVTable,
        beNDMWAfsStageLoad_InitFields,
        0, /* extra callback item */
        g_beNDMWAfsStageLoad_callbackList /* callback list */
    );
}
