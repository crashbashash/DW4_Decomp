void FUN_00239390(void) {
    FUN_002395b0();
    FUN_00239910();
    FUN_00239c80();
    FUN_00239b20();
    FUN_00239ee0();
    FUN_0023a340();
    FUN_0023a850();
    FUN_0023a650();
    FUN_0023aaf0();
}

void CollisionLibrary_MarkRegistered(void) {
    if (g_CollisionLibrary_registered == 0) {
        g_CollisionLibrary_registered = 1;
    }
}

