/* The receiver is the address of an object-reference slot (the caller passes
 * &((beDataObjBoolList *)o)->_data), so the body is a plain load of the 4-byte
 * handle stored in that slot, not a member of a struct. */
int FUN_00406f10(int *p)
{
    return *p;
}
