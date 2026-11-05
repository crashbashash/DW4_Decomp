/* 0x00331660 - igIntList metaobject accessor: returns the first word of the class's
 * metaobject handle at 0x00586880 (same accessor shape as ParticleInfo,
 * src/game/ParticleInfo.c). */
extern int g_igIntList_metaObject_00586880[4];
int igIntList_GetMetaObject_Virtual(void) {
    return g_igIntList_metaObject_00586880[0];
}
