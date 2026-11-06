/* Element descriptor of an info list: the default igIntMetaField descriptor (the igIntMetaField
 * class handle plus 8; same cell as igIntMetaField_GetDefaultDescriptor). An igInfoList is a
 * count/capacity/data list like igDataList, so its slot hands out the int descriptor. */
extern int g_igIntMetaField_descriptor[4];
int Gap__Core__igInfoList__vfunc_51(void) {
    return g_igIntMetaField_descriptor[0];
}
