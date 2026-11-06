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
extern igMetaObject *g_beMemory_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *beMemory_GetMetaObject(void);
extern const char beMemory_className[];
int beMemory_GetVTable(void);
void beMemory_InitFields(void);
extern char g_beMemory_callbackList[];
void *beMemory_Register(void);
}

void *beMemory_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMemory_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beMemory_GetMetaObject,
        beMemory_className,
        0x24, /* instance size */
        beMemory_GetVTable,
        beMemory_InitFields,
        0, /* extra callback item */
        g_beMemory_callbackList /* callback list */
    );
}
