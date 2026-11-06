extern unsigned char g_NdmwLibrary_registered;
void NdmwLibrary_MarkRegistered(void) {
    if (g_NdmwLibrary_registered == 0) {
        g_NdmwLibrary_registered = 1;
    }
}
