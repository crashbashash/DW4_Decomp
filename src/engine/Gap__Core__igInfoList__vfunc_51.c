/* 0x00331800
 * Element descriptor of an info list: the default igIntMetaField descriptor
 * (cell at 0x00586100, the igIntMetaField class handle 0x005860f8 plus 8; same
 * cell as igIntMetaField_GetDefaultDescriptor in list-metadata-access.c).  An
 * igInfoList is a count/capacity/data list like igDataList, so its slot hands out
 * the int descriptor. */
extern int g_igIntMetaField_descriptor_00586100[4];
int Gap__Core__igInfoList__vfunc_51(void) {
    return g_igIntMetaField_descriptor_00586100[0];
}
