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
extern igMetaObject *g_beNDMWAfsSetupData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beNDMWAfsSetupData_GetMetaObject(void);
extern const char beNDMWAfsSetupData_className[];
int beNDMWAfsSetupData_GetVTable(void);
void beNDMWAfsSetupData_InitFields(void);
void *beNDMWAfsSetupData_Register(void);
}

void *beNDMWAfsSetupData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsSetupData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beNDMWAfsSetupData_GetMetaObject,
        beNDMWAfsSetupData_className,
        0x10, /* instance size */
        beNDMWAfsSetupData_GetVTable,
        beNDMWAfsSetupData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
