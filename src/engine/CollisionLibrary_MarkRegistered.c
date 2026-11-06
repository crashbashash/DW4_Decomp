extern unsigned char g_CollisionLibrary_registered[4];
void CollisionLibrary_MarkRegistered(void) {
    if (g_CollisionLibrary_registered[0] == 0) {
        g_CollisionLibrary_registered[0] = 1;
    }
}
