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
extern igMetaObject *g_beNDMWStatusPowerSocket_metaObject[];
void *beNDMWStatusCtrlBaseEquip_Register(void);
igMetaObject *beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusPowerSocket_GetMetaObject(void);
extern const char beNDMWStatusPowerSocket_className[];
int beNDMWStatusPowerSocket_GetVTable(void);
void *beNDMWStatusPowerSocket_Register(void);
}

void *beNDMWStatusPowerSocket_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusPowerSocket_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusPowerSocket_GetMetaObject,
        beNDMWStatusPowerSocket_className,
        0x7c, /* instance size */
        beNDMWStatusPowerSocket_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
