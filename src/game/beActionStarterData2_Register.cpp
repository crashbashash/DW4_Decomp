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
extern igMetaObject *g_beActionStarterData2_metaObject[];
void *beActionStarterData_Register(void);
igMetaObject *beActionStarterData_GetPublishedMetaObject(void);
igMetaObject *beActionStarterData2_GetMetaObject(void);
extern const char beActionStarterData2_className[];
int beActionStarterData2_GetVTable(void);
void beActionStarterData2_InitFields(void);
void *beActionStarterData2_Register(void);
}

void *beActionStarterData2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarterData2_metaObject,
        beActionStarterData_Register,
        beActionStarterData_GetPublishedMetaObject,
        beActionStarterData2_GetMetaObject,
        beActionStarterData2_className,
        0x30, /* instance size */
        beActionStarterData2_GetVTable,
        beActionStarterData2_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
