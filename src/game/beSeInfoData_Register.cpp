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
extern igMetaObject *g_beSeInfoData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beSeInfoData_GetMetaObject(void);
extern const char beSeInfoData_className[];
int beSeInfoData_GetVTable(void);
void beSeInfoData_InitFields(void);
extern char g_beSeInfoData_callbackList[];
void *beSeInfoData_Register(void);
}

void *beSeInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSeInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSeInfoData_GetMetaObject,
        beSeInfoData_className,
        0x14, /* instance size */
        beSeInfoData_GetVTable,
        beSeInfoData_InitFields,
        0, /* extra callback item */
        g_beSeInfoData_callbackList /* callback list */
    );
}
