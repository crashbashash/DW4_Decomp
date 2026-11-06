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
extern igMetaObject *g_beGeneraterPlayerData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beGeneraterPlayerData_GetMetaObject(void);
extern const char beGeneraterPlayerData_className[];
int beGeneraterPlayerData_GetVTable(void);
void beGeneraterPlayerData_InitFields(void);
extern char g_beGeneraterPlayerData_callbackList[];
void *beGeneraterPlayerData_Register(void);
}

void *beGeneraterPlayerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterPlayerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beGeneraterPlayerData_GetMetaObject,
        beGeneraterPlayerData_className,
        0x18, /* instance size */
        beGeneraterPlayerData_GetVTable,
        beGeneraterPlayerData_InitFields,
        0, /* extra callback item */
        g_beGeneraterPlayerData_callbackList /* callback list */
    );
}
