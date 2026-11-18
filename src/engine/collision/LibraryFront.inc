void CollisionLibrary_RegisterClasses(void) {
    igCreateCollisionDatabase_EnsureRegistered();
    igCollisionInfo_EnsureRegistered();
    igCollisionGroup_EnsureRegistered();
    igCollisionGroupList_EnsureRegistered();
    igCollisionGridHelper_EnsureRegistered();
    igCollisionGrid_EnsureRegistered();
    igCollisionCell_EnsureRegistered();
    igCollisionCellList_EnsureRegistered();
    igBoundingSphereMaker_EnsureRegistered();
}

unsigned char g_CollisionLibrary_registered;

void CollisionLibrary_MarkRegistered(void) {
    if (g_CollisionLibrary_registered == 0) {
        g_CollisionLibrary_registered = 1;
    }
}

