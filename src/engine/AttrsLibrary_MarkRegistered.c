extern unsigned char g_AttrsLibrary_registered;
void AttrsLibrary_MarkRegistered(void) { if (!g_AttrsLibrary_registered) g_AttrsLibrary_registered = 1; }
