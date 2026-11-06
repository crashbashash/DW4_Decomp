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
extern igMetaObject *g_beSvFormatApi_metaObject[];
void *beSaveApi_Register(void);
igMetaObject *beSaveApi_GetPublishedMetaObject(void);
igMetaObject *beSvFormatApi_GetMetaObject(void);
extern const char beSvFormatApi_className[];
int beSvFormatApi_GetVTable(void);
void *beSvFormatApi_Register(void);
}

void *beSvFormatApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvFormatApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFormatApi_GetMetaObject,
        beSvFormatApi_className,
        0x40, /* instance size */
        beSvFormatApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
