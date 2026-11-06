/* Formats "%08x.%08x" from `first` and the 2048-byte sector count of `size` into a 20-byte name
 * and passes it to the object's method at vtable +24, then clears the buffer. */
int sprintf(char *, const char *, ...);
void *memset(void *, int, unsigned int);

extern char DAT_004f3940[]; /* "%08x.%08x" */

struct Object00295cc8;
struct ObjectVtbl00295cc8 {
    char pad0[24];
    void (*method24)(struct Object00295cc8 *self, char *name); /* +24 */
};
struct Object00295cc8 {
    struct ObjectVtbl00295cc8 *vtbl;
};

void FUN_00295cc8(struct Object00295cc8 *object, int first, unsigned int size) {
    char name[20];

    sprintf(name, DAT_004f3940, first, (size + 2047) >> 11);
    object->vtbl->method24(object, name);
    memset(name, 0, sizeof(name));
}
