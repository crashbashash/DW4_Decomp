extern char igContextExt_GetPublishedMetaObject[];
extern char thunk_igMultiTextureExt_GetMetaObject[];
extern char igContextExt_Register[];
extern char igMultiTextureExt_className[];
extern char g_igMultiTextureExt_metaObject[];
/* Run-once guard shared by the registrars: sets a gp-relative flag byte. */
int FUN_00149bc0();
int igMetaObject_RegisterClass();
/* Code in the gap after this function: the class's no-argument field adder (10th registration argument). */
extern int igMultiTextureExt_InitFields_0014d650[4];
void igMultiTextureExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMultiTextureExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igMultiTextureExt_GetMetaObject,
        igMultiTextureExt_className,
        0x14, /* instance size */
        0,
        &igMultiTextureExt_InitFields_0014d650[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
