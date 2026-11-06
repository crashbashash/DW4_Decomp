/* igDataList metaobject accessor: returns the first word of the class's metaobject handle at
 * 0x00586788 (same accessor shape as ParticleInfo). */
extern int g_igDataList_metaObject[4];
int igDataList_GetMetaObject_Virtual(void) {
    return g_igDataList_metaObject[0];
}
