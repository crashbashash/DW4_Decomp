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
extern igMetaObject *g_beUnicodeObj_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beUnicodeObj_GetMetaObject(void);
extern const char beUnicodeObj_className[];
int beUnicodeObj_GetVTable(void);
void beUnicodeObj_InitFields(void);
void *beUnicodeObj_Register(void);
}

void *beUnicodeObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beUnicodeObj_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beUnicodeObj_GetMetaObject,
        beUnicodeObj_className,
        0x10, /* instance size */
        beUnicodeObj_GetVTable,
        beUnicodeObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
