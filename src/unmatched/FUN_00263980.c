/* CRI thunk: re-enters FUN_002639a0 with the default range (start 0, limit
 * 0xfffff) after the two incoming arguments. */
extern void FUN_002639a0(int a, int b, int start, int limit);

void FUN_00263980(int a, int b)
{
    FUN_002639a0(a, b, 0, 0xfffff);
}
