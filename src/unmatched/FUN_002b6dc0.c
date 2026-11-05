/* 0x002b6dc0 — FUN_002b6dc0. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int igUnsignedIntMetaField_EnsureRegistered();
int FUN_0030e960();
int igObject_AllocateRawStorageDefault();
int igObject_CloneViaMetadata();
extern unsigned char * DAT_00586dc8[4];
int FUN_002b6dc0(int arg0, int arg1) {
    int temp_v0;

    if (*DAT_00586dc8[0] != 0) {
        igUnsignedIntMetaField_EnsureRegistered();
        return igObject_CloneViaMetadata(arg0, arg1);
    }
    temp_v0 = igObject_AllocateRawStorageDefault(0x34, 0);
    if (temp_v0 != 0) {
        temp_v0 = FUN_0030e960(temp_v0, arg0);
    }
    return temp_v0;
}
