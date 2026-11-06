struct igMetaObject;
extern "C" {
void AdxMovieLibrary_MarkRegistered(void);
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
extern igMetaObject *g_igAdxAudio_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *igAdxAudio_GetMetaObject(void);
extern const char igAdxAudio_className[];
int igAdxAudio_GetVTable(void);
void igAdxAudio_InitFields(void);
void *igAdxAudio_Register(void);
}

void *igAdxAudio_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAdxAudio_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igAdxAudio_GetMetaObject,
        igAdxAudio_className,
        0x30, /* instance size */
        igAdxAudio_GetVTable,
        igAdxAudio_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
