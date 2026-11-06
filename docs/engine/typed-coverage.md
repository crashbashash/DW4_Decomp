# Typed coverage

**How much of the matched C speaks in recovered structs instead of offset casts** — the inward
metric, next to matched bytes (outward) and identified data. Tool: `tools/typed_coverage.py`.
The gate is `make typed-check` against the baseline `config/typed-coverage.json`.

## What is measured

Every field access in the matched C falls in one bucket:

| Bucket | Spelling | Key in the baseline and in `docs/progress.json` |
| --- | --- | --- |
| on a **recovered** class | `igMetaObject *g; g->_validity` | `recovered` (the gated count) |
| raw offset cast | `*(int *)((char *)p + 36)` | `offset_casts` |
| on a synthetic layout | `struct G { char pad[36]; int f; }` | `synthetic` |
| other member accesses | a member of a type the metadata does not know | `total` minus the three above |

`typeable` is a separate figure: the raw casts that the receiver-class rule (see
[Receiver class from the function name](#receiver-class-from-the-function-name)) could convert
mechanically.

The live numbers are not restated here. Read them from:

- `make typed` (the report, with the per-class breakdown);
- `config/typed-coverage.json` (the recorded baseline: `recovered`, `total`, `offset_casts`,
  `synthetic`, `typeable`, and the `by_class` and `by_folder` breakdowns);
- the `typed` block of the generated [`docs/progress.json`](../progress.json);
- the `raw_casts.reflected` row of the generated [progress report](../../PROGRESS.md), which is
  the `typeable` figure.

What the count means and does not mean:

- **It is an access-count metric**, not a count of instructions or of recovered bytes. The
  denominator moves as expression spellings change, without any change in matched code.
- **Typed coverage is gated by the identity of the object each access points into**, not just by
  reflection's field offsets. An access counted as recovered uses a reflected struct member; the
  metric does not distinguish a confirmed receiver identity from a recorded class hypothesis.
- **The metric needs the class name in the function body.** A `typedef` alias of a reflected
  class, a struct derived from it, or accesses inside a static member are not counted, so use the
  reflected name in the declaration where the compiler allows it (the shop helpers gained 52
  accesses that way).
- **Two readable spellings are under-counted**, so moving a hand-spelled release into a class-body
  holder lowers the metric with the typing unchanged. A reference release in an inline destructor
  or static member inside a class body is invisible, because the function splitter sees only
  top-level definitions. A field read through a typed global array element
  (`g_<Class>_metaObject[0]->_validity`) has no declared local to attribute the class to. Counting
  class-body member functions and typed array elements would remove the gap.
- **`((T *)base)->field` counts as recovered.** The access scanner has a `CAST_MEMBER_RE` for that
  form, which is how the typing passes spell an access whose class came from reflection rather
  than a declaration.
- **Matched source written against the reflected structs adds recovered accesses without a typing
  pass**; the [title menu controller](title-menu-controller.md) is such source.

## Why it matters

m2c's output reproduces retail instruction-for-instruction while writing every field as a cast:

```c
return *(int *)((char *)(*(int *)((char *)(arg0) + 52)) + 8);   /* matches retail exactly */
```

That satisfies the matching oracle and is useless to another compiler: it encodes 4-byte pointers and
hand-computed offsets, which is what a port has to undo by hand (the port plan's `port/docs/project/README.md` §*What a native
build changes about the constraints*). Typing is measured as **neutral for matching** and is
essential for the port — same work, different objective.

## The gate

Two things are recorded and one is gated:

| | |
| --- | --- |
| `config/typed-coverage.json` | the baseline: recovered count, totals, and the **per-class** breakdown, so a drop names the class that lost typing |
| `make typed` / `make typed-check` | report it / fail if this run differs from the baseline |
| CI (`.github/workflows/progress.yml`) | runs `--check` on every push to main |

**The gate is on the count of recovered accesses, never on the percentage** — and that distinction is
the whole design. The m2c loop keeps adding matched C, and every new function arrives with offset
casts, so the *ratio* can fall while the count only grows. A percentage gate would fail on progress,
which trains you to ignore it. The count is monotonic in a way the ratio is not.

A *gain* fails the check too, until the baseline is re-recorded:

```sh
make typed            # report
make typed-baseline   # record the new count, then commit config/typed-coverage.json
make typed-check      # what CI runs
```

That is deliberate: it means every change in coverage — up or down — is a reviewed diff, and a drop
cannot hide behind a stale baseline. When a drop is a *move* (accesses retyped from one class to
another) the output shows both classes, so the intent is visible rather than inferred.

The gate is tested both ways, because a gate that has not been tested is not a gate: reverting one
converted file gives exit 1 with a line of the form
`REGRESSION — 549 recovered accesses, baseline 550 (-1)` and the class delta `igMetaObject -1`;
restoring it gives exit 0.

## How the types are recovered

`data/reflection.json` holds 659 classes and 3,680 fields with a name, a byte offset and a MetaField
type. `scripts/gen_type_headers.py` turns that into `include/dw4/reflected.h` — real C structs, with
these rules that keep them honest:

- **A struct carries its ancestors' fields too** (`data/class-hierarchy.tsv`, recovered from the
  registrar's base MetaObject). Reflection lists only a class's *own* fields, so a subclass whose
  fields are all inherited — `igVec3fList`, whose `_count`/`_capacity`/`_data` come from `igDataList`
  — would otherwise have **no struct at all** and could not be declared, which is what a port needs
  and what typing an object-graph walk needs (`((igVec3fList *)p)->_count`). Because a base sits at
  offset 0 the layout is unchanged. The header defines 1,040 structs; its opening comment states the
  class and field totals.
- **The offsets are the authority for where a field sits.** Gaps become explicit `char _padN[K];`,
  so every field lands where reflection recorded it. `igMetaField` has `_persistent` (a bool) at
  +38 and `_shallowCopyMethod` (a char) at +39, so a bool is one byte, and a type map that guessed
  `int` there would shift every later field.
- **A field's type and size come from its MetaField kind**
  ([next section](#sizing-fields-by-their-metafield-kind-and-the-registered-instance-size)).
- **A disagreement is printed, not hidden.** Where the metadata's size for a field contradicts the
  offsets the generator reports it, because that is a fact about the recovered metadata. The count
  is **0**.

### Sizing fields by their MetaField kind and the registered instance size

The generator takes **type and size from the kind**, through three tables:

- `SCALAR`: a MetaField whose C type is fixed by the metadata (bool/char/short/int/long/float/
  double, plus the 4-byte refs — handles, not inline data) takes that type's size, and the rest of
  the gap becomes explicit padding. So `unsigned char _refCounted; char _pad61[3]; int _poolName;`
  and `unsigned char _construct; unsigned char _destruct;`. Sizing a scalar by the distance to the
  next field does not work: `igObjectRefMetaField._refCounted` (a bool at +60, next field at +64)
  and `igRefMetaField._destruct` (a bool at +53, the last field) would be `int`, the code writes
  them with **1-byte** stores, and no member access could be typed (it also produced 72 spurious
  "offset vs metadata" disagreements). By the same rule `igMetaField._isAlikeShallowMethod` is
  `char` plus 3 bytes of padding, not `char[4]` (its siblings are all single chars and its type is
  `igCharMetaField`, not `igCharArrayMetaField`), and `unsigned short _size` is a scalar, not
  `_size[1]`.
- `VECTOR`: `igVec2f/3f/4fMetaField` → `float[2|3|4]`, `igMatrix44fMetaField` → `float[16]`.
- `ARRAY`: an `ig*ArrayMetaField` → its element type, with the count from the span.

`igStringMetaField` stays `int` by decision — the 4-byte handle of an interned string, like the
object references, because the port keeps four-byte references in an arena and `const char *`
would widen the field on a 64-bit host. `igStructMetaField` (an inline struct reflection does not
describe) keeps the distance-to-next-field rule.

Sizing an aggregate by the distance to the next field is wrong in two ways. The **last** field of
a class has no next field, so a trailing vector or matrix would be a lone `int`:
`igFogAttr._color` (an `igVec4fMetaField` at +28) makes the struct 44 bytes, not 32, and
`igAABox._max`, `igMatrixObject._m`, `igCommonTraversal._jointMvmInverseBase` and 30 more fields
are in the same position. A non-trailing vector or matrix would get the right *size* but the wrong
*type* (`int[16]` for a matrix the code multiplies as floats), which forces units into
`*(float *)&self->_avgPos[0]`, `(&b->_max)[k]` and `0xBF800000` stores of float bit patterns.
Relative to that rule, typing by kind changes the type of **270 fields** (126 Vec3f, 72
Matrix44f, 24 Vec4f, 16 Vec2f, 32 arrays) and the `sizeof` of 57 classes.

What closes the struct is the registered size: **every class registers its `sizeof`** with
`igMetaObject_RegisterClass` (`li t2,N` in `asm/<Class>_Register.s`, `reflection-metadata.md` §1),
and the generator reads it for all 1,039 registered classes (the one exception is the
duplicate-handle `igModelViewMatrixBoneSelectList`). That sizes a trailing array —
`igMersenneTwisterRandomNumber._mt` is `(2508 - 12) / 4 = 624` words, the MT19937 state, and
`igCompressedAnimationSequenceQS._interpolationMethod` at +57 is 7 bytes of a 64-byte object —
and pads the tail, so `sizeof(Class)` on the host is the retail one. Each struct's comment records
`sizeof N (registered instance size)`, and `scripts/check_reflected_layout.py` asserts the 1,040
sizes and every field type next to the offsets (`make reflected-check`). No class's fields overrun
its registered size.

The generator's `WORD_TYPED` table (`typed int: N matched units read it as a word`) is for a field
that must stay a word because matched units read it as one. It is empty: no field needs the
exception. It exists so that an exception is recorded in the header rather than hidden.

### Spellings in units that touch kind-typed fields

The byte rule holds with the kind-derived types. Of the 179 units that touch such a field and the
15 that use a reflected struct by value or through pointer arithmetic, 18 need a particular
spelling to keep their bytes; each is written readably in the unit rather than by keeping a word
type:

- float-literal stores instead of hex patterns (`_offsetPos[0] = -121.0f`, `_directionLimiter[1] =
  7.0f`, `_avgPos[k] = -1.0f`): `Gap__Bec__beNDMWShopCtrl50/DeviceSell/DiskSell/Evolve/XdataChip/
  Sell__vfunc_21`, `beNDMWShopSelect11__vfunc_22`, `beNDMWStatusCtrlD0__vfunc_21`,
  `beNDMWStatusSelect01__vfunc_22`, `beNDMWMdlPlayer__vfunc_36`, `beShadow01__vfunc_32`,
  `FUN_00378ed0` — MWCC stores a float constant through a GPR, so the bytes are the same;
- `x->_max[k]` / `x->_pos[k]` instead of the `(&x->_max)[k]` idiom that assumes a scalar:
  `FUN_003908e0`, `FUN_00396940`, `FUN_003dcc60`; `float *` prototypes and locals where the
  matrix or centre is passed: `Gap__Sg__igLod__vfunc_27`, `FUN_00378ed0`;
- `igMousePosObserver_GetVTable` declares a plain `igMousePosObserver s`: the struct is the real
  100 bytes, so no local wrapper pads it;
- the `beNDMWLoadIntf2NameSel` receiver (`beNDMWLoadIntf2NameSel__Update`, `FUN_003de990`): the
  class registers 288 bytes and reflection lists fields up to +100, so the per-cell save area
  after the listed fields is the unlisted tail of the same object, spelled as a
  `union { beNDMWLoadIntf2NameSel n; NameSelTail t; }`.

These spellings do not change the recovered-access count: the units spell the accesses as members
either way.

## Typing passes

Each pass is a script with rules that stop it from inventing a type. Every pass is verified, not
assumed: `make check` must show 0 mismatching and `make link` must be **BYTE-IDENTICAL** —
typing that changes codegen is a bug, and the build is the test that says so. After a pass that
adds coverage, the baseline is re-recorded with `make typed-baseline`.

Typed files begin with `#include "dw4/reflected.h"`. `tools/units.py`'s `definitions()` resets the
statement start at a top-level preprocessor line, so a leading `#include` is not taken as part of
the next function's signature (which would skip that function in `extract` and in the `cover`
count for any unit whose first function has no forward declaration).

### Synthetic layouts from automatch

`tools/automatch.py` emits a layout with no meaning — 550 files, all identical:

```c
struct G { char pad[36]; int f; };
extern struct G *DAT_0055ebc0[4];
struct G *g = DAT_0055ebc0[0];
if (!g || !(t = g->f & 4)) FUN_001301c0();
return DAT_0055ebc0[0];
```

Every fact needed to say that meaningfully is recovered: the global is a **reflection class
handle**, so what it holds is an **`igMetaObject *`** (the invariant the object-model work
established), reflection names the field at +36 **`_validity`**, and this accessor is the lazy
get-or-register path — `if (!*handle || flags & 4 == 0) register();` — so `_validity & 4`
is read, not guessed.

`scripts/retype_metaobject_idiom.py` rewrites those 550 files (and only files whose shape is exactly
that one, with the field used only through that pointer, with a real class handle, and with a
reflected field of the same width at that offset):

```c
#include "dw4/reflected.h"
extern igMetaObject *DAT_005610e0[4];
igMetaObject *g = DAT_005610e0[0];
if (!g || !(t = g->_validity & 4)) FUN_0018a780();
return DAT_005610e0[0];
```

### Receiver class from the function name

`scripts/retype_receiver_class.py` is the general form of the pass above: a matched function named
`<Class>_<Method>` (or a sanitised `Gap__Bec__<Class>__vfunc_N` / `thunk_...`) has the class in its
name, so its first argument *is* that class and its offset casts can become member accesses:

```c
/* before */  int igMetaField_Write(void *arg0) {
                  return -(*(unsigned char *)((char *)(arg0) + 38) == 0);
              }
/* after  */  #include "dw4/reflected.h"
              int igMetaField_Write(igMetaField *arg0) {
                  return -(arg0->_persistent == 0);
              }
```

Three rules keep it from inventing anything, and everything skipped is counted and reported:

* the receiver class is taken from the **function's name**, never inferred from the body;
* the field comes from the reflection metadata and its **width must equal the cast's width** — a
  `char` field written through a 4-byte cast is left raw, because rewriting it changes codegen and
  `make check` would (correctly) fail. This is why the converter reads the *generated* header rather
  than the MetaField→C map: `igMemoryRefMetaField._releaseOnCopy` is a `bool` (1 byte) and the code
  does a byte store, which the map alone would have called `int`;
* only the receiver (`arg0`/`this`) is usable as a base — **a temporary generally holds a different
  object.** An `_InitFields` body's `temp_s2` is the *field* object returned by
  `igMetaObject_GetFieldAt`, not the class the function is named for; using the function-name class
  there would produce wrong member names that happen to compile.

`--class-regex` scopes a pass to matching class names. The port plan scopes typed coverage
to game code because the engine middleware is replaced wholesale on a port, so `--class-regex be`
restricts a pass to the **game** classes. The names it produces are real, not placeholders:
`Gap__Bec__beNDMWItemWeapon__vfunc_24` unpacks to `arg0->_recNo` / `_isEquip` / `_kindNo` /
`_pocket` / `_revision`, and `Gap__Bec__beCameraMode__vfunc_08` reads `arg0->_model`.

Measured yield of the rule: 46 accesses across 31 files for the `<Class>_<Method>` names, and 119
accesses in 27 files (+41 in the metric) for `--class-regex be` with the RTTI-less vtable names
below in place. What the rule can still convert is the `typeable` figure.

### The signature table and the `_InitFields` family

The receiver rule only sees the *caller's* name. The larger multiplier is the **callee's return
type** — so `config/SLUS-20836/signatures.tsv` carries recovered signatures (`name`, return,
parameters, and the evidence that settles each), seeded from the object model:

```
igMetaObject_GetFieldAt<TAB>igMetaField *<TAB>igMetaObject *, int<TAB>...
```

`scripts/retype_initfields.py` uses it on the `<Class>_InitFields` family (416 functions), whose
shape is fixed:

```c
temp_s0 = igMetaObject_GetFieldCount(temp_s1);
igMetaObject_CreateFields(temp_s1, &DAT_004c8060[0], 4);
temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));   /* field k = 1 */
*(int *)((char *)(temp_s2) + 56) = FUN_001a5fe0();
```

`temp_s0` is the class's own field count, so `GetFieldAt(_, count + k)` returns the MetaField object
for **`reflection[Class].fields[k]`**, and *its class* is that field's declared type. That fixes what
+52/+56 mean per field: `beAction2InfoRam`'s four object-ref fields get `_metaObject` at +56, and
`igGeometryAttr`'s five object-ref fields get +56 while its one enum field gets
`_getMetaEnumAttribute`/`_getMetaEnumFunction` at +52 — exactly the accesses those files contain. The
rewrite adds an explicit cast around the temporary rather than retyping its declaration, so it is one
expression:

```c
((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001a5fe0();
```

The rules of this pass:

- **The index mapping is validated.** The `CreateFields` count equals the number of reflected
  fields in **416 of 416** files (0 mismatches). That is what makes the mapping safe, since a wrong
  `k` would pick a different field's MetaField class and put a wrong struct name in the C without
  breaking the build.
- **`k` is read in registration order.** The field index in `GetFieldAt(metaObject, count + k)` is
  written in registration order, and reflection's field list is registration order, not offset
  order; the two disagree for **55 of 470 classes** (`igCollisionGrid` lists `_cells`,
  `_activeCells`, `_processedCells`, … and only then `_sizeX`/`_sizeY`/`_sizeZ`). The pass takes
  the given order. Sorting by offset indexes the wrong field: it produces no *wrong* member names
  (a wrong `k` picks a field type with no field at the accessed offset, so the access is skipped),
  but it silently misses the fields that moved (28 accesses, 10 of them `igCollisionGrid`'s
  object-ref fields).
- **`k` can be hex** (`temp_s0 + 0xA`, `+ 0xB`, …). The 41 object-ref fields of
  `libBecRuntimePlugin` are written that way; accepting `0x…` covers 113 accesses across 16 files.
- **Inherited fields resolve through the ancestors.** The family also sets fields it *inherits*:
  an `igObjectRefMetaField` object's `+52` char store is `igRefMetaField._construct` and its `+38`
  store is `igMetaField._persistent`. The pass merges each class's ancestors' fields (from the
  generated `data/class-hierarchy.tsv`) into one offset map, which covers 359 accesses across 167
  files.
- **A field is reached through the struct that declares it.** The merged map carries each field's
  declaring class and the rewrite casts to that — `((igRefMetaField *)p)->_construct = 1;`,
  `((igMetaField *)p)->_persistent = 0;`. The field really is the base's.
- **Byte-wide fields depend on the `SCALAR` size rule.** With scalars sized by the metadata, the
  1-byte stores type as members (93 accesses across 63 files that an `int`-sized bool blocks).

The direct `+52`/`+56` rewrites alone are 717 accesses across 310 files.

`python3 scripts/retype_initfields.py --check` is the source initializer audit: it re-derives every
emitted member from the mapping and fails if one disagrees, which matters because a wrong `k` would
put a wrong struct name in the C and still compile. A descriptor's uses are bounded by reassignment
of the temporary: a reused local is checked only against the descriptor currently assigned to it
(checking it against every descriptor ever assigned produces 46 false mismatches across
`igPsx2Media_InitFields` and `igPsx2VertexArray1_1_InitFields`). The audit checks 2,039 accesses
consistently with registration order. `python3 testing/test_retype_initfields.py` covers valid
reuse, unrelated reassignment, and real type errors both before and after reuse.

### RTTI-less vtables

`scripts/seed_names_getvtable_slots.py` resolves the class of every vtable from the class's own
`<Class>_GetVTable` function, taking the map from the 478 RTTI vtables to
**958 / 980 classes**, and names the **1,177** unmatched unique slots of the 499 non-RTTI vtables
(`config/SLUS-20836/names/GetVTableSlots.tsv`). All of them are `ig*` engine classes — the game's `be*`
classes all carry RTTI — so this is T6 naming, not game typing. For the port's method dispatch the
same generator emits `data/vtables-getvtable.json` (vtable → class + slots, P2.6). The names feed
the receiver rule above.

### The 316-file typing pass

The pass replaces raw offsets and private layouts in 316 existing source files with fields
from `include/dw4/reflected.h`. It claims no new function and no matched code byte.

The edits cover engine receiver fields, object headers, retained list storage, matrix translation
arrays and field-descriptor initialization. References in the authoritative structs remain four-byte
integers. Typed views retain the original access widths, signed extensions, volatile reads and
compiler-specific virtual-call scaffolding where byte matching requires them.

Class identity remains separate evidence: a byte match verifies code generation, so receiver
interpretations that rest on layout alone are not confirmed class identities. In particular, the
unchanged symbols
`Gap__Core__igObject__vfunc_26` and `FUN_0015e2b0` are viewed through
`beBaseInfoManager` and `igVertexArray1_1` layouts respectively; their symbol/receiver ownership
discrepancies remain unresolved. Followed-reference target classes likewise need separate class,
reflection or ownership evidence. Matching alone proves none of these identities.

Most of the pass's gain is outside the narrower [game-layer scope](typed-game-layer.md), which is
measured separately (`make typed-scope`) and is above its 80 % stop condition. The pass is closed;
it is not the start of another blanket typing sweep.

Validation of a pass of this size: uncached verification of all edited source files (for these 316
files, 323 functions match, including owned emitted bodies), then complete `make check` and
`make link`; also `make typed-check`, `make reflected-check`, `make hygiene` and
`python3 tools/progress.py --check`. The fresh source check uses an isolated tree of the edited
files with
`python3 tools/check.py --no-cache --src <edited-source-tree> --flags="-O3 -Iinclude" --jobs 8`;
compiler profiles and emitted-function ownership still come from the committed configuration. The
source initializer audit is `python3 scripts/retype_initfields.py --check` (above).

### Port-critical closure helpers

Thirty-odd `FUN_` helpers of the port-critical closure are typed by taking
each receiver from evidence rather than from the offsets alone: a typed matched caller
(`dw4/reflected.h` casts or prototypes), the matched dispatcher that passes the object, or an exact
multi-field offset match against a reflected class. Practical findings, all verified with
`tools/verify.py`:

* **Spelling changes codegen.** Replacing a matched private list view (volatile `count`, pointer `data`) with the reflected `igObjectList` changes register
  allocation in one sort (`FUN_00422c00`); the matched list view stays and the items are typed. Removing a `me = (Class *)owner` copy changes another.
* **Unreflected neighbours stay local.** The `igProperty` records, the property block of `beNDMWDegiData__LoadFromProperties` (`0x003ee6d0`), the sort key of the item subclasses and the
  Lua stack of `LuaAPI_Dispatch` have no reflected class and keep small private views; they are recorded as unconfirmed, not invented.

An exact offset-and-width scan of every private struct view in `src/unmatched` against
`include/dw4/reflected.h` returns no further game-region match except one that agrees on widths
only (`FUN_00464540`, outside the closure). The live list of untyped closure functions is the
generated
[closure's untyped list](../../port/docs/project/critical-dependency-map.md#what-is-left-to-type-biggest-first);
these entries stay untyped for a recorded reason:

| Function | Why it stays |
|---|---|
| `LuaAPI_Dispatch` | its views are the Lua 4.0 argument stack (24-byte value slots); no reflected class describes it |
| `MemoryContext_*`, `igMemoryRefMetaField_DeepCopy` | Alchemy memory and meta-field middleware, which the port replaces |
| `beNDMWDegiData__LoadFromProperties` (`0x003ee6d0`), `beNDMWDegiData__UpdateFieldsFromData` (`0x003ee4d0`) | typed up to the 2.6 KB property block of a `beNDMWDegiData`, which has no reflected class |
| `beNDMWLoadIntf2ComMdlCtrl__StartAt` (`0x003e3e00`), `FUN_003a8140`, `FUN_00394400` | typed except for `igProperty` records and string-chunk headers, which are not reflected classes |
| `beNDMWLoadIntf2NameSel__Update` (`0x003def80`) | typed through `beNDMWLoadIntf2NameSel`; the per-cell save area after it is unreflected |
| `FUN_00423000`, `FUN_0043a450`, `FUN_00422c00` | typed except the item subclass fields (sort key at +20, a field at +16) whose class is not established |
| `FUN_0039a500`, `FUN_004535d0`, `FUN_0037a690`, `FUN_003a7d80`, `FUN_003a5d70` | the receiver class is not reflected or no typed caller names it; a one-field match is not evidence |
| `FUN_00393b20`, `FUN_00391a10`, `FUN_003f6620` | callers are unnamed or untyped, so the receiver would be a guess |

## Shared headers and the struct report

- `include/dw4/pool_slot.hpp` names its slot view `igObjectSlotView`, with `_refCount` like the
  reflected layout. A `class igObject` there would be incompatible with the reflected
  `struct igObject`.
- The reference release has one spelling. `include/dw4/igobject_release.h` holds
  `IG_OBJECT_RELEASE(obj)`, whose expansion is the retail sequence, and all five users
  (`FUN_004614b0`, `FUN_00235370`, `FUN_00164f50`,
  `Gap__Bec__beNDMWShopCtrlSell__vfunc_21`, `beAction2FADESET_Start`) match through it. The
  argument is evaluated more than once on purpose (a stack slot whose address escaped must be
  re-read, as retail does); a unit whose source holds the pointer in a smart-pointer temporary
  releases through a local copy (`igObject *held = p; IG_OBJECT_RELEASE(held);`). The `Ref`
  destructor in `beAction2FADESET_Start` keeps its own `& 0x7fffff` spelling: it is a matching
  construct of the retail `__dt__3RefFv`, not a use site.
- `scripts/check_struct_conflicts.py` (`make struct-report`, a report, not a gate) parses every
  local struct/class view in `src/` and `include/dw4/` and prints (a) same non-generic names with
  clashing layouts across units, (b) receiver views that disagree with the reflected class their
  unit is named for, and (c) `fNN` members whose NN is not the member's decimal offset, grouped by
  name with file:line pairs. Tests: `testing/test_check_struct_conflicts.py` and
  `testing/test_check_vtable_slots.py` (run by `make struct-report` / `make vtable-slots-check`).
- The `IntList` views in `FUN_00383bf0`, `Gap__Bec__beNDMWMdlPlayer__vfunc_38` and `FUN_00235370`
  agree and are not a conflict: all put `count` at +8 and `capacity` at +12 — the order
  `asm/FUN_00383bf0.s` shows (`lw s5,8(s4); lw v1,12(s4)`, the in-capacity test, then
  `sw v1,8(s4)` for the increment and `lw a1,16(s4)` for the data) and the reflected `igIntList`.

## Limits on recovering a receiver's class

Two routes for the game-side receiver queue are measured and are dry:

- Attributing a receiver class from the offsets it accesses against `reflection.json` is too weak —
  **0** of 78 unmatched game functions with `argN` casts has a unique matching class (thousands of
  classes share a field at +8/+16/+20).
- Adjacency to the same class's RTTI `vfunc_*` on both sides **does** recover the class, because
  MWCC emits a translation unit's functions contiguously. `scripts/retype_block_receiver.py` types
  an unnamed `FUN_*` that sits between two `<Class>__vfunc_N` symbols, and leaves it alone unless
  every `arg0`/`this` offset cast lands on a reflected field of that class with matching width;
  `--game-only` limits it to the module map's `0x334000..0x460000`. For example, `FUN_004482c0` sits
  between `Gap__Bec__beNDMWItemWeapon__vfunc_21` and `vfunc_23` and resolves to
  `beNDMWItemWeapon._kindNo/_recNo/_isEquip/_pocket/_revision`. Field names beginning `_pad` are not
  all padding: `_padManager` and `_padList` are real object references. Adjacency does not give the
  **role**, and a name whose only justification is an inferred role is a hypothesis, not
  an overlay line. So the item cluster's per-class record setters (`FUN_004482c0` and five
  siblings, each writing a distinct `_kindNo` 0..5) are typeable but stay unnamed until a role
  source appears.

## Scheduling

Typing is sequenced **byte-first**: standalone passes whose only result is a higher typed coverage
number are deferred behind matching work, with a reassessment point at **20–25 %** verified matched
code bytes (`code_bytes` in `docs/progress.json`). This is a sequencing decision, not permission to
accumulate known wrong types or to discard the recovered model:

- apply a type when it unlocks exact code generation, establishes an ABI or signature, identifies a
  receiver or module, completes the module currently being recovered, or directly serves current
  mod/port work;
- keep the recovered-access count monotonic with `make typed-check`; the percentage may fall as the
  matching loop adds raw C;
- type a completed module while its evidence and calling relationships are still fresh, rather than
  postponing the entire typing backlog until the executable is nearly matched;
- use **code bytes**, not function count, to decide when the phase has reached its reassessment
  point.

## Raising it further

The order that pays:

1. **The remaining mass is object *identity*, not signatures.** In the measurement that set this
   order, of 2,826 raw casts **2,621 are in unnamed `FUN_*` units**, and of the 1,830 that apply
   the offset to `arg0`, **1,777 are in functions whose name-implied class is not a reflected class
   at all**. Only ~40 are call results any signature could type. So the levers are **naming** (each
   name whose class is recovered converts that function's accesses at once) and the **live
   identity** route below — `config/SLUS-20836/signatures.tsv` should still grow (it is seeded with
   the object model only, and passes read it), but it is not the biggest lever.
2. **Name receivers** (the naming loop) — each name converts that function's accesses from *not
   typeable* to typeable.
3. **Object identity from a live instance** — the one route that supplies *identity*
   without naming the receiver first. Every engine object's `+0` word is its class's vtable, and the
   478 vtables are decoded, so scanning RAM for vtable words enumerates live objects by class
   and reading them at their reflection offsets gives named, typed fields (verified field-perfect on
   `beGeneraterData`, and cross-validated against the stat table). That is a source of types
   that does not depend on the naming loop, though it needs the emulator and so cannot run in CI: it
   is evidence for a name or a cast, like any other live measurement.
   It also bounds the work — only **171 of 478** classes are instantiated in a loaded stage, so a
   batch can be scoped to what the game actually builds.

## Open items

- The closure functions in the table under
  [Port-critical closure helpers](#port-critical-closure-helpers) stay partly or wholly untyped
  until their receiver or neighbouring record has a reflected class or a typed caller.
- The symbol/receiver ownership discrepancies of `Gap__Core__igObject__vfunc_26` and
  `FUN_0015e2b0`, and the receiver interpretations resting on layout alone, are
  unresolved.
- The item cluster's per-class record setters (`FUN_004482c0` and five siblings) have a class but
  no role source, so they are unnamed.
- `config/SLUS-20836/signatures.tsv` is seeded with the object model only.

## What didn't work

These mechanical routes to more typed accesses are measured and dry, so do not retry them. What
remains is naming `FUN_*` bodies by hand, after which the receiver rule types them.

- **Vtable membership.** Only 28 distinct `FUN_*` symbols appear in the 478 vtables, their owners are
  ambiguous shared defaults, and no decompiled `FUN_*` unit is a vtable slot.
- **Call-site propagation.** Looking for an argument of known class at each `FUN_*` call gives 0
  votes, because callers' locals are untyped m2c temporaries.
- **Object-ref chains.** A (class, field) -> referenced-class map built from the `_InitFields`
  `_metaObject` assignments has 485 pairs but types only 2 accesses, because the functions that walk
  object graphs are the unnamed `FUN_*` units.
- **Assert and log strings.** The `Class::method` strings are used up, leaving only 2 unnamed
  functions, one a deliberately declined twin of `igIGBFile_ReadFile`.
- **Other data.** The unapplied `register_site`/`post_init` sites in `data/reflection.json` (the 52
  non-function-start `post_init` addresses are leaf fragments in unclaimed gaps), the signature field
  of `data/functions.json` (1 of 15,974 functions) and `ctor_table` are all empty of new types.
- **Live vtable scan.** It gives runtime objects' classes, not a static function's `arg0`; that needs
  a trace.
