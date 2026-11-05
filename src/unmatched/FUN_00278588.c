/* 0x00278588 — FUN_00278588 (132 bytes). Opens an entry: rejects a non-positive entry number or a non-zero rw mode, takes a free handle (FUN_00277fc0) and initialises it (FUN_00278038); failures are reported through FUN_00277de8 and return 0. Its error strings name it mfCiOpenEntry (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern char s_E1041001_invalid_entry_number_mfCiOpenEntry_004f0e78[];          /* 'E1041001:invalid entry number.(mfCiOpenEntry)' */
extern char s_E1041002_rw_is_illigal_mfCiOpenEntry_004f0ea8[];                 /* 'E1041002:rw is illigal.(mfCiOpenEntry)' */
extern char s_E1041002_not_enough_handle_resource_mfCiOpenEntry_004f0ed0[];    /* 'E1041002:not enough handle resource.(mfCiOpenEntry)' */
void FUN_00277de8(void *handle, const char *message);
void *FUN_00277fc0(void);
void FUN_00278038(void *handle);

void *FUN_00278588(int entry, int reserved, int rw) {
    void *handle;

    if (entry <= 0) {
        FUN_00277de8(0, s_E1041001_invalid_entry_number_mfCiOpenEntry_004f0e78);
        return 0;
    }
    if (rw != 0) {
        FUN_00277de8(0, s_E1041002_rw_is_illigal_mfCiOpenEntry_004f0ea8);
        return 0;
    }
    handle = FUN_00277fc0();
    if (handle == 0) {
        FUN_00277de8(0, s_E1041002_not_enough_handle_resource_mfCiOpenEntry_004f0ed0);
        return 0;
    }
    FUN_00278038(handle);
    return handle;
}

