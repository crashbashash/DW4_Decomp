void CoreLibrary_MarkRegistered(void) {
    if (DAT_00554bf4 == 0) {
        DAT_00554bf4 = 1;
        igThreadManager_EnsureRegistered();
        igThreadList_EnsureRegistered();
        igThread_EnsureRegistered();
        igErrorHandler_EnsureRegistered();
        igContextExt_EnsureRegistered();
    }
}

