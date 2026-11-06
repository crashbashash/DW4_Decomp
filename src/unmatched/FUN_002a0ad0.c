/* Clears the two-word record at +508 of the object. */
typedef struct Pair { int a; int b; } Pair;
void FUN_002a0ad0(char *arg0)
{
    Pair *p = (Pair *)(arg0 + 508);
    p->a = 0;
    p->b = 0;
}
