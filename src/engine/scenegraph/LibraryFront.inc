unsigned char g_SceneGraphLibrary_registered;

void SceneGraphLibrary_MarkRegistered(void) {
    if (g_SceneGraphLibrary_registered == 0) {
        g_SceneGraphLibrary_registered = 1;
    }
}

igMetaObject *g_igGroup_metaObject;
igMetaField *g_igGroup_childListMetaField;

igMetaObject *igGroup_GetPublishedMetaObject(void) {
    return g_igGroup_metaObject;
}

