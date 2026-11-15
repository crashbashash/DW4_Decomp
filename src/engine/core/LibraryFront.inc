unsigned char g_CoreLibrary_registered;

void CoreLibrary_MarkRegistered(void) {
    if (g_CoreLibrary_registered == 0) {
        g_CoreLibrary_registered = 1;
        igThreadManager_EnsureRegistered();
        igThreadList_EnsureRegistered();
        igThread_EnsureRegistered();
        igErrorHandler_EnsureRegistered();
        igContextExt_EnsureRegistered();
    }
}

