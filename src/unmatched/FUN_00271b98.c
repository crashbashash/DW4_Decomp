/* Between FUN_0027e1f0 and FUN_0027e268, sets the word at offset 4 of an object to 1, printing
 * DAT_004efc40 (null object) or DAT_004efc60 (already 1) through FUN_0010d108 instead. */
typedef struct Object_271b98 {
    int f0;
    int f4;             /* 0x04 */
} Object_271b98;

extern char DAT_004efc40[];
extern char DAT_004efc60[];
void FUN_0027e1f0(void);
void FUN_0027e268(void);
void FUN_0010d108(const char *text);

void FUN_00271b98(Object_271b98 *object) {
    FUN_0027e1f0();
    if (object == 0) {
        FUN_0010d108(DAT_004efc40);
    } else if (object->f4 == 1) {
        FUN_0010d108(DAT_004efc60);
    } else {
        object->f4 = 1;
    }
    FUN_0027e268();
}
