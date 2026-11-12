void ViewerLibrary_MarkRegistered(void) {
    if (g_ViewerLibrary_registered == 0) {
        g_ViewerLibrary_registered = 1;
    }
}

int FUN_004586a0(void) {
    if (DAT_0058c680[0] == 0) {
        DAT_0058c680[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c680[0];
}

