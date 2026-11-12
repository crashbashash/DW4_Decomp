void SceneGraphLibrary_MarkRegistered(void) {
    if (g_SceneGraphLibrary_registered == 0) {
        g_SceneGraphLibrary_registered = 1;
    }
}

igMetaObject *FUN_001943a0(void) {
    return g_igGroup_metaObject[0];
}

