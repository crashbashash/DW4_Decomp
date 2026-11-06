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
extern igMetaObject *g_beSeData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beSeData_GetMetaObject(void);
extern const char beSeData_className[];
int beSeData_GetVTable(void);
void beSeData_InitFields(void);
void *beSeData_Register(void);
}

void *beSeData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSeData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beSeData_GetMetaObject,
        beSeData_className,
        0x14, /* instance size */
        beSeData_GetVTable,
        beSeData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
