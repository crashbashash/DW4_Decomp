extern unsigned char g_SceneSearchLibrary_registered;
void SceneSearchLibrary_MarkRegistered(void) {
    if (g_SceneSearchLibrary_registered == 0) {
        g_SceneSearchLibrary_registered = 1;
    }
}
