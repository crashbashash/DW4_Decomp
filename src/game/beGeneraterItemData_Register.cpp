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
extern igMetaObject *g_beGeneraterItemData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beGeneraterItemData_GetMetaObject(void);
extern const char beGeneraterItemData_className[];
int beGeneraterItemData_GetVTable(void);
void beGeneraterItemData_InitFields(void);
extern char g_beGeneraterItemData_callbackList[];
void *beGeneraterItemData_Register(void);
}

void *beGeneraterItemData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterItemData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterItemData_GetMetaObject,
        beGeneraterItemData_className,
        0x10, /* instance size */
        beGeneraterItemData_GetVTable,
        beGeneraterItemData_InitFields,
        0, /* extra callback item */
        g_beGeneraterItemData_callbackList /* callback list */
    );
}
