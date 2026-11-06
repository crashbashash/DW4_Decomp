struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWStatusInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusInfoRam_GetMetaObject(void);
extern const char beNDMWStatusInfoRam_className[];
int beNDMWStatusInfoRam_GetVTable(void);
void beNDMWStatusInfoRam_InitFields(void);
extern char g_beNDMWStatusInfoRam_callbackList[];
void *beNDMWStatusInfoRam_Register(void);
}

void *beNDMWStatusInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWStatusInfoRam_GetMetaObject,
        beNDMWStatusInfoRam_className,
        0x30, /* instance size */
        beNDMWStatusInfoRam_GetVTable,
        beNDMWStatusInfoRam_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusInfoRam_callbackList /* callback list */
    );
}
