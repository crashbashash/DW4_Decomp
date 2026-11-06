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
extern igMetaObject *g_beShadow01InfoList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beShadow01InfoList_GetMetaObject(void);
extern const char beShadow01InfoList_className[];
int beShadow01InfoList_GetVTable(void);
extern char g_beShadow01InfoList_callbackList[];
void *beShadow01InfoList_Register(void);
}

void *beShadow01InfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beShadow01InfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beShadow01InfoList_GetMetaObject,
        beShadow01InfoList_className,
        0x14, /* instance size */
        beShadow01InfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beShadow01InfoList_callbackList /* callback list */
    );
}
