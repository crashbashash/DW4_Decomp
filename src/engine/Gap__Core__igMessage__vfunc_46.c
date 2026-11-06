/* Vtable slot 46 of the igMessage vtable (0x0052d000): returns the first word of the igRenderer
 * metaobject handle at 0x0058c208 (class name from data/reflection.json). Why igMessage answers
 * with igRenderer's metaobject is unproven; the vtable is attributed to igMessage by its GetVTable
 * accessor. The receiver is not touched. */
extern int g_igRenderer_metaObject[4];
int Gap__Core__igMessage__vfunc_46(void) {
    return g_igRenderer_metaObject[0];
}
