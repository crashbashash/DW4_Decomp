extern unsigned char g_CollisionLibrary_registered;
void CollisionLibrary_MarkRegistered(void) {
    if (g_CollisionLibrary_registered == 0) {
        g_CollisionLibrary_registered = 1;
    }
}
