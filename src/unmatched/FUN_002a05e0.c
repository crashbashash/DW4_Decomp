/* Returns the first id in [first, last] for which sfd_HdrHasStm succeeds with a non-zero result, or
 * 0. */
int sfd_HdrHasStm();

int FUN_002a05e0(void *table, int first, int last) {
    int found;
    int id;

    for (id = first; id <= last; id++) {
        if (sfd_HdrHasStm(table, (unsigned char)id, &found) != 0 && found != 0) {
            return id;
        }
    }
    return 0;
}
