/* 0x002b40b0 — FUN_002b40b0. Stores the two words at +96/+100 of the object. Written through a
 * record pointer: the unit compiler (Sony EE GCC 2.96 -O2 -G0) then forms the record address once and
 * stores both fields relative to it, as retail does. */
typedef struct Pair { int a; int b; } Pair;
void FUN_002b40b0(char *arg0, int arg1, int arg2)
{
    Pair *p = (Pair *)(arg0 + 96);
    p->a = arg1;
    p->b = arg2;
}
