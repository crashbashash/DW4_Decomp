/* igObjectList metaobject accessor: returns the first word of the class's metaobject handle at
 * 0x00585b60 (same accessor shape as ParticleInfo). */
extern int g_igObjectList_metaObject[4];
int igObjectList_GetMetaObject_Virtual(void) {
    return g_igObjectList_metaObject[0];
}
