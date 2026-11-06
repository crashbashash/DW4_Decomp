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
extern igMetaObject *g_beNodeAnim_metaObject[];
void *igGroup_Register(void);
igMetaObject *igGroup_GetPublishedMetaObject(void);
igMetaObject *beNodeAnim_GetMetaObject(void);
extern const char beNodeAnim_className[];
int beNodeAnim_GetVTable(void);
void beNodeAnim_InitFields(void);
void FUN_0034eaf0(void);
void *beNodeAnim_Register(void);
}

void *beNodeAnim_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNodeAnim_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beNodeAnim_GetMetaObject,
        beNodeAnim_className,
        0x70, /* instance size */
        beNodeAnim_GetVTable,
        beNodeAnim_InitFields,
        FUN_0034eaf0, /* extra callback item */
        0 /* callback list */
    );
}
