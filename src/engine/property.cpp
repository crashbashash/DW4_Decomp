/* Named GAMERAM property records (LEVEL, HP, flags...) are looked up by string key in a container
 * with igProperty_FindByName, which needs the descriptor of the record's name member alongside the
 * key. Each accessor below supplies that descriptor and returns the record found. The four retail
 * wrappers are identical code; their callers differ in how they use the record (whole record, byte
 * value at +12, array copy for the save, folder fields). The third parameter is not read by any of
 * them. */

/* The global holds the descriptor of the record's name member: an igMetaField-shaped object whose
 * +8 (_offset) is 8, the offset the lookup adds to each record to reach its name string. Array
 * form keeps the load absolute (lui/lw). */
extern "C" int g_propertyNameField[4];

extern "C" {
int igProperty_FindByName(int container, int nameField, char *key);
int igProperty_GetRecord(int container, char *key, int unused);
int igProperty_GetRecordByte(int container, char *key, int unused);
int igProperty_GetRecordArray(int container, char *key, int unused);
int igProperty_GetRecordFolder(int container, char *key, int unused);
}

int igProperty_GetRecord(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

int igProperty_GetRecordByte(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

int igProperty_GetRecordArray(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

int igProperty_GetRecordFolder(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}
