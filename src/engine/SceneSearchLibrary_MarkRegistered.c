extern unsigned char g_SceneSearchLibrary_registered[4];
void SceneSearchLibrary_MarkRegistered(void) {
    if (g_SceneSearchLibrary_registered[0] == 0) {
        g_SceneSearchLibrary_registered[0] = 1;
    }
}
