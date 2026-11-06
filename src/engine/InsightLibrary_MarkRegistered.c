extern unsigned char g_InsightLibrary_registered;
void InsightLibrary_MarkRegistered(void) {
    if (g_InsightLibrary_registered == 0) {
        g_InsightLibrary_registered = 1;
    }
}
