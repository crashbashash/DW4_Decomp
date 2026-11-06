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
extern igMetaObject *g_beNDMWStatusMainSlot_metaObject[];
void *beNDMWStatusCtrlBaseEquip_Register(void);
igMetaObject *beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusMainSlot_GetMetaObject(void);
extern const char beNDMWStatusMainSlot_className[];
int beNDMWStatusMainSlot_GetVTable(void);
void *beNDMWStatusMainSlot_Register(void);
}

void *beNDMWStatusMainSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusMainSlot_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusMainSlot_GetMetaObject,
        beNDMWStatusMainSlot_className,
        0x7c, /* instance size */
        beNDMWStatusMainSlot_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
