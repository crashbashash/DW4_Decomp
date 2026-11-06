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
extern igMetaObject *g_beNDMWStatusInfoWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWStatusInfoWork_GetMetaObject(void);
extern const char beNDMWStatusInfoWork_className[];
int beNDMWStatusInfoWork_GetVTable(void);
void beNDMWStatusInfoWork_InitFields(void);
extern char g_beNDMWStatusInfoWork_callbackList[];
void *beNDMWStatusInfoWork_Register(void);
}

void *beNDMWStatusInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWStatusInfoWork_GetMetaObject,
        beNDMWStatusInfoWork_className,
        0x24, /* instance size */
        beNDMWStatusInfoWork_GetVTable,
        beNDMWStatusInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusInfoWork_callbackList /* callback list */
    );
}
