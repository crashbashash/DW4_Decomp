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
extern igMetaObject *g_beNDMWLoadSavePlWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWLoadSavePlWork_GetMetaObject(void);
extern const char beNDMWLoadSavePlWork_className[];
int beNDMWLoadSavePlWork_GetVTable(void);
void beNDMWLoadSavePlWork_InitFields(void);
extern char g_beNDMWLoadSavePlWork_callbackList[];
void *beNDMWLoadSavePlWork_Register(void);
}

void *beNDMWLoadSavePlWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadSavePlWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadSavePlWork_GetMetaObject,
        beNDMWLoadSavePlWork_className,
        0x34, /* instance size */
        beNDMWLoadSavePlWork_GetVTable,
        beNDMWLoadSavePlWork_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadSavePlWork_callbackList /* callback list */
    );
}
