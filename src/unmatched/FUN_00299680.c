/* Formats "%08x.%08x" from `first` and the 2048-byte sector count of `size` into a 20-byte name,
 * enters it with FUN_00299068 and clears the buffer. */
int sprintf(char *, const char *, ...);
void *memset(void *, int, unsigned int);
void FUN_00299068(void *player, char *name);

extern char DAT_004f4978[]; /* "%08x.%08x" */

void FUN_00299680(void *player, int first, unsigned int size) {
    char name[20];

    sprintf(name, DAT_004f4978, first, (size + 2047) >> 11);
    FUN_00299068(player, name);
    memset(name, 0, sizeof(name));
}
