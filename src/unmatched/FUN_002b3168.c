/* Stores the fourth and fifth arguments at +68/+72 of the object and tail-calls FUN_002b3f48 with
 * all arguments. */
int FUN_002b3f48();
struct Obj0044 {
    char pad[68];
    int f68;
    int f72;
};

void FUN_002b3168(struct Obj0044 *obj, int a1, int a2, int a3, int a4) {
    obj->f68 = a3;
    obj->f72 = a4;
    FUN_002b3f48(obj, a1, a2, a3, a4);
}
