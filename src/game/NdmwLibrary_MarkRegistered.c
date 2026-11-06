extern unsigned char g_NdmwLibrary_registered[4];
void NdmwLibrary_MarkRegistered(void) {
    if (g_NdmwLibrary_registered[0] == 0) {
        g_NdmwLibrary_registered[0] = 1;
    }
}
