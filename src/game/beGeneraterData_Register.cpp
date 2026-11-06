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
extern igMetaObject *g_beGeneraterData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beGeneraterData_GetMetaObject(void);
extern const char beGeneraterData_className[];
int beGeneraterData_GetVTable(void);
void beGeneraterData_InitFields(void);
extern char g_beGeneraterData_callbackList[];
void *beGeneraterData_Register(void);
}

void *beGeneraterData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterData_GetMetaObject,
        beGeneraterData_className,
        0x44, /* instance size */
        beGeneraterData_GetVTable,
        beGeneraterData_InitFields,
        0, /* extra callback item */
        g_beGeneraterData_callbackList /* callback list */
    );
}
