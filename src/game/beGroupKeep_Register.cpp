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
extern igMetaObject *g_beGroupKeep_metaObject[];
void *igGroup_Register(void);
igMetaObject *igGroup_GetPublishedMetaObject(void);
igMetaObject *beGroupKeep_GetMetaObject(void);
extern const char beGroupKeep_className[];
int beGroupKeep_GetVTable(void);
void *beGroupKeep_Register(void);
}

void *beGroupKeep_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGroupKeep_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beGroupKeep_GetMetaObject,
        beGroupKeep_className,
        0x20, /* instance size */
        beGroupKeep_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
