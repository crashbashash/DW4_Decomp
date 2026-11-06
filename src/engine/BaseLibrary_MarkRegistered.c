extern unsigned char g_BaseLibrary_registered[4];
void BaseLibrary_MarkRegistered(void) {
    if (g_BaseLibrary_registered[0] == 0) {
        g_BaseLibrary_registered[0] = 1;
    }
}
