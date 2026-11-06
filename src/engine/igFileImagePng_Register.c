extern char igFileImage_Register[];
extern char igFileImagePng_GetVTable[];
extern char thunk_igFileImagePng_GetMetaObject[];
extern char igFileImage_GetPublishedMetaObject[];
extern char g_igFileImagePng_callbackList[];
extern char igFileImagePng_className[];
extern char g_igFileImagePng_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igFileImagePng_InitFields();

void igFileImagePng_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileImagePng_metaObject,
        igFileImage_Register,
        igFileImage_GetPublishedMetaObject,
        thunk_igFileImagePng_GetMetaObject,
        igFileImagePng_className,
        0x60, /* instance size */
        igFileImagePng_GetVTable,
        &igFileImagePng_InitFields,
        0, /* extra callback item */
        g_igFileImagePng_callbackList /* callback list */
    );
}
