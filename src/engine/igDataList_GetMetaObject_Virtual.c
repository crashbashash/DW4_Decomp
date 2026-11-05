/* 0x00142b40 - igDataList metaobject accessor: returns the first word of the class's
 * metaobject handle at 0x00586788 (same accessor shape as ParticleInfo,
 * src/game/ParticleInfo.c). */
extern int g_igDataList_metaObject_00586788[4];
int igDataList_GetMetaObject_Virtual(void) {
    return g_igDataList_metaObject_00586788[0];
}
