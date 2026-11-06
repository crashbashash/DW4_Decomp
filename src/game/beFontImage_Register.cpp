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
extern igMetaObject *g_beFontImage_metaObject[];
void *igBitmapFont_Register(void);
igMetaObject *igBitmapFont_GetPublishedMetaObject(void);
igMetaObject *beFontImage_GetMetaObject(void);
extern const char beFontImage_className[];
int beFontImage_GetVTable(void);
void *beFontImage_Register(void);
}

void *beFontImage_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontImage_metaObject,
        igBitmapFont_Register,
        igBitmapFont_GetPublishedMetaObject,
        beFontImage_GetMetaObject,
        beFontImage_className,
        0x24, /* instance size */
        beFontImage_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
