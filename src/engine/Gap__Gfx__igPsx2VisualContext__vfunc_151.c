/* The base is kept in its own local rather than written back into the parameter; otherwise the add
 * is emitted with the operands swapped. */
void Gap__Gfx__igPsx2VisualContext__vfunc_151(int arg0, int arg1, int *arg2, int *arg3) {
    int i = arg1 < 15 ? arg1 : 15;
    int off = i * 4;
    int p = off + arg0;
    *arg2 = *(int *)(p + 644);
    *arg3 = *(int *)(p + 708);
}
