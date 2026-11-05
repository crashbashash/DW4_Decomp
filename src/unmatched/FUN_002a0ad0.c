/* 0x002a0ad0 — FUN_002a0ad0. Clears the two-word record at +508 of the object. Written through a
 * record pointer: the unit compiler (Sony EE GCC 2.96 -O2 -G0) then forms the record address once and
 * stores both fields relative to it, as retail does. */
typedef struct Pair { int a; int b; } Pair;
void FUN_002a0ad0(char *arg0)
{
    Pair *p = (Pair *)(arg0 + 508);
    p->a = 0;
    p->b = 0;
}
