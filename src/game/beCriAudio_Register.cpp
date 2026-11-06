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
extern igMetaObject *g_beCriAudio_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beCriAudio_GetMetaObject(void);
extern const char beCriAudio_className[];
int beCriAudio_GetVTable(void);
void beCriAudio_InitFields(void);
extern char g_beCriAudio_callbackList[];
void *beCriAudio_Register(void);
}

void *beCriAudio_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriAudio_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriAudio_GetMetaObject,
        beCriAudio_className,
        0x18, /* instance size */
        beCriAudio_GetVTable,
        beCriAudio_InitFields,
        0, /* extra callback item */
        g_beCriAudio_callbackList /* callback list */
    );
}
