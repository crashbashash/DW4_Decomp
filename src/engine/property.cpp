/* src/engine/property.cpp — the property-record accessors
 *
 * Named GAMERAM property records (LEVEL, HP, flags...) are looked up by string key in a
 * container with igProperty_FindByName, which needs the descriptor of the record's name
 * member alongside the key (docs/engine/property-system.md, "Getter/setter wrappers").
 * Each accessor below supplies that descriptor and returns the record found.  The four
 * retail wrappers are identical code at different addresses; their callers differ in how
 * they use the record (whole record, byte value at +12, array copy for the save, folder
 * fields).  The third parameter is not read by any of them.
 *
 * One translation unit: 4 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */

/* The global at 0x00585be0 holds the descriptor of the record's name member: a
 * live savestate read shows an igMetaField-shaped object whose +8 (_offset) is 8, the
 * offset the lookup adds to each record to reach its name string
 * (docs/engine/property-system.md, "Registry object").  Array form keeps the load
 * absolute (lui/lw). */
extern "C" int g_propertyNameField[4];

extern "C" {
int igProperty_FindByName(int container, int nameField, char *key);
int igProperty_GetRecord(int container, char *key, int unused);
int igProperty_GetRecordByte(int container, char *key, int unused);
int igProperty_GetRecordArray(int container, char *key, int unused);
int igProperty_GetRecordFolder(int container, char *key, int unused);
}

/* 0x003a9220 */
int igProperty_GetRecord(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

/* 0x003a9280 */
int igProperty_GetRecordByte(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

/* 0x003a92b0 */
int igProperty_GetRecordArray(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

/* 0x003a9340 */
int igProperty_GetRecordFolder(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}
