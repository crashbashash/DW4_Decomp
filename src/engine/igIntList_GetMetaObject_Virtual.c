/* igIntList metaobject accessor: returns the first word of the class's metaobject handle at
 * 0x00586880 (same accessor shape as ParticleInfo). */
extern int g_igIntList_metaObject[4];
int igIntList_GetMetaObject_Virtual(void) {
    return g_igIntList_metaObject[0];
}
