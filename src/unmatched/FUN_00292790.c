/* Predicate over a 0..5 code: codes 2 and 3 give 0, everything else (including out of range) gives 1. Compiled to a jump table. */
int FUN_00292790(unsigned int k)
{
    switch (k) {
    case 2:
    case 3:
        return 0;
    case 0:
    case 1:
    case 4:
    case 5:
    default:
        return 1;
    }
}
