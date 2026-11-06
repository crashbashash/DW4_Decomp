/* Reads two words of a 16-entry table pair at +644 and +708 of the object, indexed by the clamped
 * slot number (at most 15). The base is kept in its own local rather than written back into the
 * parameter: the unit compiler (combat build) otherwise emits the add with the operands in the
 * other order. */
void FUN_0017cb40(int arg0, int arg1, int *arg2, int *arg3) {
    int i = arg1 < 15 ? arg1 : 15;
    int off = i * 4;
    int p = off + arg0;
    *arg2 = *(int *)(p + 644);
    *arg3 = *(int *)(p + 708);
}
