/* Calls FUN_00269650 with all four arguments, then FUN_00269640(object, a2), FUN_002696d0(object,
 * a3) and FUN_00269648(object, 284). */
void FUN_00269650(void *object, void *a1, char *a2, void *a3);
void FUN_00269640(void *object, char *value);
void FUN_002696d0(void *object, void *value);
void FUN_00269648(void *object, int value);

void FUN_00269878(void *object, void *a1, char *a2, void *a3) {
    /* matching construct: permuter — the no-op a2++/a2-- raises a2's use count so ee-gcc gives it s0 (retail order s0=a2, s1=object, s2=a3) */
    a2++;
    a2--;
    FUN_00269650(object, a1, a2, a3);
    FUN_00269640(object, a2);
    FUN_002696d0(object, a3);
    FUN_00269648(object, 284);
}
