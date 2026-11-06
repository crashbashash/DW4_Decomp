/* Scans `length` bytes of `text` for a header that starts with DAT_004f5a68 and carries the
 * 8-character tag DAT_004f59f8 (FUN_00127004 compares); records the last such position in *found
 * and its parsed value (FUN_002b5838) in *value, both 0 when absent. */
extern char DAT_004f5a68[];
extern char DAT_004f59f8[];

int FUN_00127004(char *a, char *b, int count);
int FUN_002b5838(char *header);

void FUN_002b5770(char *text, int length, char **found, int *value) {
    int i;

    *value = 0;
    *found = 0;
    if (text == 0 || length <= 0) {
        return;
    }
    for (i = 0; i < length; i++, text++) {
        if (FUN_00127004(text, DAT_004f5a68, 1) == 0 && FUN_00127004(text, DAT_004f59f8, 8) == 0) {
            *found = text;
            *value = FUN_002b5838(text);
        }
    }
}
