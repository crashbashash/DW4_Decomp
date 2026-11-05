/* The decomp's generated structs are the authoritative layout of the game's objects (include/dw4/reflected.h in the
 * repository root, generated from data/reflection.json). The technical specification retargets recovered code to the
 * host with four-byte references in an arena, so the port must be able to include that header with its own flags and
 * agree with it: this compiles under the port's -std=c99 -Wall -Wextra next to a port header and asserts the layout
 * facts the arena model relies on. A failure is a compile error. */
#include <stddef.h>
#include <stdint.h>
#include "dw4/scene.h"
#include "dw4/reflected.h"

#define DW4_LAYOUT_ASSERT(name, cond) typedef char name[(cond) ? 1 : -1]

/* every engine object starts with a vtable reference and a reference-count word */
DW4_LAYOUT_ASSERT(igobject_two_words, sizeof(igObject) == 8);
DW4_LAYOUT_ASSERT(igobject_refcount_at_4, offsetof(igObject, _refCount) == 4);
/* subclass fields keep their reflected absolute offsets */
DW4_LAYOUT_ASSERT(messenger_argdata_at_16, offsetof(beMessenger, _argData) == 16);
DW4_LAYOUT_ASSERT(gameram_messenger_at_20, offsetof(beNDMWGameRam, _messenger) == 20);
/* a reference field is as wide as the port's arena handle (pointer-model decision, option (a)/(b)) */
DW4_LAYOUT_ASSERT(reference_is_handle_sized, sizeof(((beMessenger *)0)->_argData) == sizeof(dw4_handle));

int main(void) { return 0; }
