extern unsigned char g_InsightLibrary_registered[4];
void InsightLibrary_MarkRegistered(void) {
    if (g_InsightLibrary_registered[0] == 0) {
        g_InsightLibrary_registered[0] = 1;
    }
}
