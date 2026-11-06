/* Returns the metaobject slot of igAnimationSystem, not of the binding list. Read through the
 * array extern so the load stays absolute. */
extern int g_igAnimationSystem_metaObject[4];
int FUN_001e35e0(void) {
    return g_igAnimationSystem_metaObject[0];
}
