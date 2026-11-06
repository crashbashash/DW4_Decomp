extern unsigned char g_SceneGraphLibrary_registered[4];
void SceneGraphLibrary_MarkRegistered(void) {
    if (g_SceneGraphLibrary_registered[0] == 0) {
        g_SceneGraphLibrary_registered[0] = 1;
    }
}
