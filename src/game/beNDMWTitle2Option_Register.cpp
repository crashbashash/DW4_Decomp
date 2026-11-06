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
extern igMetaObject *g_beNDMWTitle2Option_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWTitle2Option_GetMetaObject(void);
extern const char beNDMWTitle2Option_className[];
int beNDMWTitle2Option_GetVTable(void);
void beNDMWTitle2Option_InitFields(void);
extern char g_beNDMWTitle2Option_callbackList[];
void *beNDMWTitle2Option_Register(void);
}

void *beNDMWTitle2Option_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWTitle2Option_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWTitle2Option_GetMetaObject,
        beNDMWTitle2Option_className,
        0x38, /* instance size */
        beNDMWTitle2Option_GetVTable,
        beNDMWTitle2Option_InitFields,
        0, /* extra callback item */
        g_beNDMWTitle2Option_callbackList /* callback list */
    );
}
