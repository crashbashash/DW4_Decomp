# Reflection metadata — MetaObjects, MetaFields and the `be*` structures

The engine (`Gap::Core`, derived from the Insomniac `ig` object model) has a runtime
**reflection** system: every class registers a `MetaObject`, and every field of that class becomes a
`MetaField` carrying its **name, byte offset and type**. This metadata is what the igBinary
(`.igb`) serializer reads and writes. It is also the only place a stripped binary still spells out
its data structures.

**Status: the records are decoded.** `scripts/dump_reflection.py` extracts all of it to
`data/reflection.json` — 1,075 `MetaObject`s, 659 of them with fields, **3,680 fields with name +
offset + type**.

---

[Registration and descriptor construction](reflection-registration.md) covers the
registrar, the descriptor builders and the original Work schema path.

## 1. The registrar: `igMetaObject_RegisterClass`

Every class registers itself in a static-init function that calls `0x002fe9c0`.
Verified from the decompilation:

```c
long igMetaObject_RegisterClass(
    int   abstract_state, // a0  stored as a byte at metaobj+0x1a; getter called for 0
    int  *handle_slot,    // a1  BSS slot; *handle_slot is the MetaObject* (created if 0)
    code *fn1,            // a2  the BASE class's registrar; returns pending initializer callback state
                           //     (RegisterClass returns that callback state; FUN_002d3480 appends items)
    code *fn2,            // a3  the BASE class's MetaObject accessor; its result is inherited by
                           //     igMetaObject_InheritFromBase (fields, +0x20, +0x48, +0x5c)
    int   v54,            // t0  the class's own get-or-register MetaObject accessor, stored at
                           //     metaobj+0x54  (`if (!*handle || flags&4==0) register(); return *handle;`)
    char *class_name,     // t1  <-- the class-name string
    int   v48,            // t2  stored at metaobj+0x48: declared instance size
    code *root_init,      // t3  the class's vtable getter, called only when abstract_state == 0; its
                           //     result is stored at +0x5c, which the igMetaObject reflection struct
                           //     names `_vTablePointer`, and is then inherited
    code *post_init,      // sp+0  <-- no-argument field adder; Work reads its global handle
    int   arg10,          // sp+8  passed to FUN_002d3480 when non-zero
    int  *list_ptrs);     // sp+16 0-terminated word list, one FUN_002d3480 call per entry
```

The only fields needed for the extraction are `handle_slot` (a1) and `class_name` (t1).

> Every argument is an `igMetaObject` field, and the class's own reflection record names them:
> `a0` → `+0x1a _abstractState`, `t0` → `+0x54 _getMetaObjectFunction`, `t1` → `+0x1c _name`,
> `t2` → `+0x48 _sizeofSize`, `t3` → `+0x5c _vTablePointer`, and `sp+0` is the field adder.
> That is what lets each one's role be read off the binary rather than guessed.

Real example, `0x001301d0` registering `igVisualContextAttrDefaultManager`:

```
130214: addiu a1,a1,-5184     ; a1 = 0x56ebc0   (BSS handle slot)
130228: addiu t1,t1,0x49c0    ; t1 = 0x4d49c0   "igVisualContextAttrDefaultManager"
130230: jal   0x002fe9c0
```

> The same holds in the `0x347d00` example: `a1` is the **BSS handle slot** (`0x588148`), `t1` is
> the **class name** (`0x5026d0` = `"beSvPs2McImage128k"`). There is no `Gap::Bec::`-prefixed
> argument here; the namespaced spelling only appears in the `__RTTI__` string.

The class name is *not* stored in the reflection data — it is an argument at the call site. That
is why the record region has no adjacent class-name pointers.

## 2. The per-class field tables

The `post_init` function adds the class's fields in two steps:

```c
/* a0 = metaobj, a1 = ctor table, a2 = field count */
igMetaObject_CreateFields(metaobj, ctor_table, n);            /* 0x002fdf40: create n MetaFields */
/* a0 = metaobj, a1 = names, a2 = descs, a3 = offsets, t0 = start index */
igMetaObject_NameFields(metaobj, names, descs, offsets, start); /* 0x002fe000: name/offset them */
```

`ctor_table`, `names`, `descs` and `offsets` are **four parallel rodata arrays of `n` words**,
packed back to back and each padded with zeros to an 8-byte boundary:

```
[field-ctor fn ptrs …][names …][descs …][offsets …]
```

| array | contents |
|---|---|
| ctor | one `ig*MetaField` constructor per field; the constructor picks the field's **type** |
| names | `_`-prefixed field-name string pointers (`_visualContext`, `_x`, `_matrixList`, …) |
| descs | BSS slots that hold the runtime `MetaField*` |
| offsets | byte offset of the field inside the object |

Example (`igViewportAttr`: ctors at `0x00485940`, names/descs/offsets from `0x00485960`):

```
0x485940  0x002c2cf0 0x002c2cf0 0x002c2cf0 0x002c2cf0
          0x002bce90 0x002c45f0 0x002c45f0            (7 ctors)
0x485960  _x _y _w _h _scissorExt _nearZ _farZ       (7 names)
0x485980  0x0055ebe0 … 0x0055ec10                     (7 BSS MetaField* slots)
0x4859a0  0x0c 0x10 0x14 0x18 0x1c 0x20 0x24          (7 offsets)
```

Note there is **no per-array zero terminator** — the length is `n` and the zeros are alignment
padding, so an odd `n` leaves exactly one zero word after each array.

### Why the name/offset pairs looked like "records"

Every field's byte offset is exact. `igViewportAttr` gives `_x` at `+0x0c`, `_y` at `+0x10`, …,
`_farZ` at `+0x24`; `igLightAttr` gives 16 fields from `_lightType` at `+0x0c` to `_cacheable` at
`+0x91`. These are directly usable as Ghidra structs.

## 3. Field types

The ctor function is a per-type factory. It loads that MetaField class's `MetaObject` handle from a
`0x58xxxx` global and calls `FUN_002fda40(type, ctx)`; the same handle names the class at its own
registration site, so the type is recoverable exactly. All 32 types observed in `game.elf`:

| ctor | type | fields |
|---|---|---|
| `0x2bce90` | `igObjectRefMetaField` | 1278 |
| `0x2c2cf0` | `igIntMetaField` | 762 |
| `0x2ccab0` | `igBoolMetaField` | 487 |
| `0x2c45f0` | `igFloatMetaField` | 227 |
| `0x2b9750` | `igStringMetaField` | 144 |
| `0x2c5fb0` | `igEnumMetaField` | 129 |
| `0x2c19f0` | `igLongMetaField` | 109 |
| `0x2b6d20` | `igUnsignedIntMetaField` | 105 |
| `0x187890` | `igVec3fMetaField` | 81 |
| `0x2bba00` | `igRawRefMetaField` | 76 |
| `0x2bf2e0` | `igMemoryRefMetaField` | 69 |
| `0x188660` | `igMatrix44fMetaField` | 43 |
| `0x1872a0` | `igVec4fMetaField` | 22 |
| `0x2b9f90` | `igShortMetaField` | 18 |
| `0x2b66a0` | `igUnsignedLongMetaField` | 18 |
| `0x187b50` | `igVec2fMetaField` | 16 |
| `0x2c30d0` | `igIntArrayMetaField` | 15 |
| `0x2b5fe0` | `igUnsignedShortMetaField` | 13 |
| `0x2b8990` | `igStructMetaField` | 12 |
| `0x2c48b0` | `igFloatArrayMetaField` | 10 |
| `0x2cbf70` | `igCharMetaField` | 10 |
| `0x2b73e0` | `igUnsignedCharMetaField` | 6 |
| `0x2b76a0` | `igUnsignedCharArrayMetaField` | 5 |
| `0x2cc300` | `igCharArrayMetaField` | 5 |
| `0x2c63c0` | `igEnumArrayMetaField` | 4 |
| `0x2ba320` | `igShortArrayMetaField` | 4 |
| `0x2cce40` | `igBoolArrayMetaField` | 3 |
| `0x2b70b0` | `igUnsignedIntArrayMetaField` | 3 |
| `0x2bd320` | `igObjectRefArrayMetaField` | 2 |
| `0x2c6ba0` | `igDoubleMetaField` | 2 |
| `0x2b6370` | `igUnsignedShortArrayMetaField` | 1 |
| `0x187560` | `igVec4fArrayMetaField` | 1 |

## 4. The `ig*MetaField` type-name catalogue

From the ELF rodata (also embedded verbatim in every igBinary type directory):

```
igMetaField            igIntMetaField          igUnsignedIntMetaField
igShortMetaField       igUnsignedShortMetaField  igLongMetaField
igUnsignedLongMetaField igCharMetaField        igUnsignedCharMetaField
igBoolMetaField        igFloatMetaField        igDoubleMetaField
igStringMetaField      igRawRefMetaField       igRefMetaField
igEnumMetaField        igStructMetaField       igMemoryRefMetaField
igDependencyMetaField  igCompoundMetaField     igTrackedElementMetaField
igVirtualCFuncMetaField igMemoryDescriptorMetaField  igMetaFieldInfo  igMetaFieldList
igVec2fMetaField       igVec3fMetaField        igVec4fMetaField
igVec3ucMetaField      igVec4ucMetaField       igMatrix44fMetaField
igIntArrayMetaField    igCharArrayMetaField    igFloatArrayMetaField
igShortArrayMetaField  igBoolArrayMetaField    igEnumArrayMetaField
igDoubleArrayMetaField igVec4fArrayMetaField   igRawRefArrayMetaField
igUnsignedIntArrayMetaField  igUnsignedCharArrayMetaField
igUnsignedShortArrayMetaField  igUnsignedLongArrayMetaField
igStringArrayMetaField igObjectRefMetaField    igObjectRefArrayMetaField
igMemoryRefArrayMetaField
```

(Other `ig*MetaField`-looking strings such as `igCharMetricsMetaField` are unrelated classes whose
names merely match.)

### `igMetaEnum` — the named value table

`igEnumMetaField` is the *field type*; the value it points at is an **`igMetaEnum`**, the
engine's generic name ↔ value table. Its three declared fields are `+0x08 _name` (the
enum's own name, an `igStringMetaField`), `+0x0c _names` (an `igStringRefList`) and
`+0x10 _values` (an `igIntList`); the two lists are indexed in lockstep, so a value
maps to its name and back. Every enum is a lazily-built singleton — the per-enum
accessor is `if (!*global) *global = igMetaEnum_Create(name, names[], values[], count);`,
e.g. `ApplyType` = `{NOT_SET=0, CUBE_MAP=1, SPHERE_MAP=2}` at `0x131f80` — and the class
has no virtual overrides. The methods are in `config/SLUS-20836/names/ObjectModel.tsv`.

## 5. Running it

```sh
ghidra-post orig/SLUS-20836/SLUS_208.36 \
    --project-path ghidra-projects/dw4 --project-name dw4 --no-analysis \
    -postScript scripts/dump_reflection.py \
    --out ghidra-projects/dw4/reflection.json

# then refresh the committed snapshot
scripts/sync_data.sh
```

### Applying it to Ghidra

```sh
# dry run (default): report only
ghidra-post orig/SLUS-20836/SLUS_208.36 \
    --project-path ghidra-projects/dw4 --project-name dw4 --no-analysis \
    -postScript scripts/apply_reflection_names.py \
    --reflection ghidra-projects/dw4/reflection.json --report build/reflect.json

# commit: one StructureDataType per class under /DW4/reflection (+ table labels)
ghidra-post ... -postScript apply_reflection_names.py \
    --reflection .../reflection.json --label-tables --apply
```

`apply_reflection_names.py` builds **659 `StructureDataType`s** under `/DW4/reflection`, one per
field-bearing class, with each field at its exact recovered offset and a real Ghidra type
(`int`, `float`, `bool`, `pointer`, `float[3]`/`float[4]`/`float[16]` for the vector and matrix
MetaFields, raw bytes otherwise). The recovered `ig*MetaField` name is kept as the field's comment.
Array widths and any type whose nominal width would overrun the next field are taken from the offset
gap, so the layouts are exact; gaps (inherited base fields, alignment padding) become undefined bytes.
It also labels each class's field-table and ctor-table addresses `reflect_<Class>_{fields,ctors}`.

`--apply` is idempotent (replace-by-name). Back the project up first:
`cp -r ghidra-projects/dw4/dw4 ghidra-projects/dw4/dw4.prebak-<ts>`.

### `reflection.json` shape

```jsonc
{
  "counts": { "metaobjects": 1075, "with_fields": 659, "fields": 3680, "field_types": 32, … },
  "field_types": { "0x2bce90": { "type": "igObjectRefMetaField", "type_global": "0x585b20", "fields": 1278 }, … },
  "classes": {
    "0x56ebc0": {
      "class": "igVisualContextAttrDefaultManager",
      "handle": "0x56ebc0", "name_ptr": "0x4d49c0",
      "register_site": "0x130230", "post_init": "0x130270",
      "field_table": "0x485920", "field_count": 1,
      "fields": [ { "name": "_visualContext", "offset": 8, "type": "igObjectRefMetaField", … } ]
    }, …
  }
}
```

## 6. What this does and does not answer

**Answers.**

- Per-class field **names, offsets and types** — the struct layouts of all 659 field-bearing classes,
  including every `be*` game type (`beBaseInfo`, `beNDMWStatusInfo`, `beModelCtrl*`, …),
  materialised as Ghidra structures under `/DW4/reflection`.
- The class-name association for 1,075 `MetaObject`s, including the `ig*MetaField` classes.
- The igBinary reader's own layout: `igIGBFile` is one of the recovered classes, and its header
  fields (`_majorVersion`, `_metaObjectCount`, `_metaFieldCount`, `_objectCount`, `_indexBuffer`,
  `_chunk`, …) are exactly the header [`igbinary-format.md`](igbinary-format.md) describes.

**Does not answer (yet).**

- Some classes legitimately register **no** fields. `beNDMWStatusInfo` is one: its
  siblings `beNDMWStatusInfoRam` (1 field) and `beNDMWStatusInfoWork` (7) carry only manager data,
  so the stat record is not driven by this class's MetaField table.

- **The 47 shared vfunc bodies.** The ctor tables are per-*field*
  factories, not method tables; they carry no virtual-method names. Names for the ambiguous vfunc
  bodies need a different route.
- **`__ct` / `__dt` / `__as` / `__eq`.** These are *not* per-class method names: they occur exactly
  once each, at `0x004fde68`+, in a MWCC **name-mangling/operator lookup table** (beside
  `operator==`, `operator<<`, `>=`, …). Reading them as class method
  metadata is wrong.
- **`{X,Y}` igBinary field descriptors.** The field metadata above is the
  *source* those descriptors index, so this is testable — decode a pack's type directory and
  correlate `{X,Y}` against a known class's field list. Still open.

## 7. Engine object types (`ig*`) and game data types (`be*`, `Gap::Bec::`)

Class names are enumerable from `data/reflection.json` rather than hand-listed. A partial view
of the game types for orientation:

| Group | Types |
| --- | --- |
| Character stats | `beBaseInfo`, `beBaseInfoData`, `beBaseInfoDataList`, `beBaseInfoRam`, `beBaseInfoRamList` |
| Status | `beNDMWStatusInfo`, `beNDMWStatusInfoRam`, `beNDMWPanelWazaInfo`, `beNDMWPanelWazaInfoRam`, `beNDMWStageCtlInfo` |
| Model control | `beModelCtrlData`, `beModelCtrlInfo`, `beModelCtrlInfoRamData`, `beModelCtrlAIData`, `beModelCtrlAIMap`, `beModelCtrlHITBOX`, `beModelCtrlACTION`, `beModelCtrlCTRL`, `beModelCtrlJUMP`, `beModelCtrlMOVE`, `beModelCtrlLABEL`, `beModelCtrlMUTEKI`, `beModelCtrlWCHECK`, `beModelCtrlLUACALL` |
| Action | `beAction2Data`, `beAction2InfoRam`, `beAction2MOTIONSET`, `beAction2FADESET`, `beAction2FLASHSET`, `beAction2JOINTSET`, `beAction2WAITCHECK`, `beActionStarterData`, `beActionStarterInfo` |
| Combat | `beAsTargetModelData`, `beHitLandModelInfo`, `beHitLandDelivInfo`, `beChangePosTransformInfo`, `beCopyTransform` |
| Camera/light | `beCameraCtrlInfo`, `beCameraBoxData`, `beCameraDemoData`, `beLightCtrlInfo` |
| Groups/layers | `beLayerGroup`, `beLayerInfo`, `beLayerGroupList` |
| Misc info | `beBkColorInfo`, `beMatCtrlData`, `beMeterCtrlInfo`, `beNumberCtrlInfo`, `beParticleCtrl2Info`, `bePoint01Info`, `beSelectCtrlInfo`, `beShadow01Info`, `beSwitchCtrlInfo`, `beTextureCtrlAttr`, `beNumVerData` |
| Lua | `beLuaData`, `beLuaDataList`, `beLuaDataObject`, `beLuaDataObjectist`, `beLuaInfo`, `beLuaState` |
| Save | `beSaveDataDeliver`, `beSaveMemoryObj`, `beSaveApi`, `beSaveUtil`, `beSaveUtilInfo`, `beSaveUtilInfoRam`, `beSvPs2McImage128k`, `beNDMWMcSlotPS2/GC/Xbox`, `beNDMWMcUtilCtrl` |
| Platform | `beUnicode`, `beUnicodeObj`, `beUnicodeObjList` |

## 8. Stat field names (from the `beBaseInfo` / `beNDMWStatusInfo` data)

```
hp  mhp  mp  mmp  level  lv  def  power  hit  waza  no  kazu
stun  sleep  poison  guard  powerdown  attackdown
```

(`waza` = technique/skill, `kazu` = count, `no` = number.)

**These do not have offsets**. Reading the `beNDMWStatusInfo` / `beBaseInfo*` entries
in `data/reflection.json` for the layout does not work: `beNDMWStatusInfo` has `field_count 0`, `beBaseInfoData` has one field
(`_version`, `igIntMetaField` @12) and `beBaseInfo` two (`_dataList` @20, `_ramList` @24). The names
exist as strings (`data/strings.json`) and in the igBinary directories only as near-empty records.
Recovering the hp/mhp/… layout needs the stat-name xrefs or a fit against the object instances — see
[`../systems/enemy-data.md`](../systems/enemy-data.md) §"Next steps".

## 9. Live objects — an object's class is its `+0` vtable pointer

Sections 1–4 say what a class *looks like*. This says how to find an **instance** of one in a running
game, which is the object identity [`typed-coverage.md`](typed-coverage.md) needs.

Every engine object begins with its class's **vtable pointer**, and the 478 vtables are already
decoded in `data/vtables.json` (from the RTTI records). So scanning RAM for words equal to one of them
enumerates live objects and returns each one's class name; `data/reflection.json` then supplies the
fields, so a raw address becomes a named, typed field access with no guessing:

```
0x016875a0  class Gap::Bec::beGeneraterData
   +12   _pos                  f32=-117        (three floats at +12/+16/+20)
   +24   _genePosIsGlobal      u32=1
   +36   _geneEnemyId          u32=36
   +44   _startModeStr         "direct"
   +48   _startData            f32=150
   +52   _fillModeStr          "wipeout"
```

That read is field-perfect against the reflection offsets, which is the check that the pairing is
right. Measured on `pre-leomon` (`stag0102`): **18,810 live instances over 171 classes**,
plus 3,271 records over 463 classes below `0x1000000`.

**Two populations, and the word at `+4` separates them.** Heap instances carry **bit 28**
(`0x10000000 | n`, `n` a small per-instance counter) and follow reflection exactly. The records below
`0x1000000` — one per class, for 463 of the 478 — carry the class's own vtable but **not** the
instance layout (a `beGeneraterData` record at `0x63d5b4` reads a rodata pointer at `+12` where the
instance reads a position float), and several classes share the same word at `+12`, i.e. a common
header. What those records *are* is **not established** (candidates: per-class
constructor/descriptor records, statically allocated pools, a registry); they are reported separately
rather than silently dropped, and only the bit-28 hits are treated as instances.

**This needs the emulator**, so it is a recorded measurement rather than a
regenerable artifact under `data/` — the same rule the other live measurements follow. The scanner
itself is kept with the emulator tooling, outside this repository.

**The vtable test undercounts by 3.2×, and the `+4` marker is the fix.** A search for
words equal to a known vtable cannot see the **vtable-less** classes at all — and those are every
`*List` kind (`igVec3fList`, `igFloatList`, `igDataList`, the `be*List` families). Every instance,
vtable-less ones included, instead carries the `0x10000000 | n` word at `+4`, so scanning for that
shape enumerates the whole population: **60,041 objects** in the same `pre-leomon` state where the
vtable scan saw **18,810**. Treat the 18,810 / 171-class figure as a **floor, not a count**, and note
that any per-class census or address-order argument built on the vtable scan inherits the error.
(The `+4` scan is highly selective — ~8 false positives expected across 8M positions — and
reproduces exactly across reloads of the same savestate.) For the list classes `n` equals the list's
own count, which is a useful check.

**End a RAM scan at about `0x1f00000`.** Live engine objects extend above `0x1800000`: a scan of
`0x1000000..0x1800000` for the `beGeneraterInfoWork` vtable `0x536050` finds 4 objects while 14 generators
are live, their works sitting at `0x1801b78` and up. The active generators can be read without scanning for
that vtable, by resolving each `beGeneraterInfoRam._work` (`+0x2c`).

## 10. The generated families as translation units

The reflection boilerplate — `<Class>_Register`, `<Class>_InitFields` and the guard-family
accessors `<Class>_GetMetaObject` / `<Class>_ResolveMetaObject` — is generated, so the
[build profiles](build-profiles.md) gate, "`cat=match` under the unit's own profile", is met in
the generators, not in the 800 files. Two things decide it.

**The language.** A unit compiled with exceptions on keeps a 12-byte exception index record for
every one of these bodies (they all call), and only the C++ front end emits it. A C file in such
a unit is therefore `code-only` (`exc=missing`). The generators resolve the
unit profile (`tools/unitprofiles.resolve`) and write `.cpp` when it says exceptions on, `.c`
otherwise, renaming the twin with `git mv`. C++ has no unprototyped calls, so the declarations
are typed prototypes, not K&R `int f();`:

* `tools/register_gen.py` regenerates `_Register` from `asm/`, resolving every argument through
  `config/SLUS-20836/symbols.txt` or the naming convention of the slot (`g_<Class>_metaObject_<addr>`), the
  class name (`<Class>_className`) and the callback list, and keeping any identifier the
  existing file already uses for the same address. The one declaration of
  `igMetaObject_RegisterClass` names each parameter after §1 (`abstractState`, `slot`,
  `baseRegister`, `baseMetaObject`, `getMetaObject`, `className`, `instanceSize`, `getVTable`,
  `initFields`, `callbackItem`, `callbackList`), the registrar returns the registrar state
  (`return igMetaObject_RegisterClass(...)`, same bytes as the `void` form, and what
  `igMetaObject_RunStaticInit` consumes), and the slot is declared as an array of unknown bound:
  a scalar `extern igMetaObject *slot;` goes to the gp-relative small-data section and is addressed
  with one `addiu a1,gp,…` where retail has `lui/addiu`. **483 of 483 verify `cat=match`** under
  default, combat and 3.0.3 units alike; the output keeps the one-argument-per-line layout with the
  §1 role comments.
* `tools/initfields_gen.py` retargets the verified `_InitFields` C body: it types every
  argument expression against the locals, the local structs and `include/dw4/reflected.h` to spell
  each callee's prototype (a floating literal keeps the unprototyped promotion through a variadic
  tail, a function passed by address gets a pointer to its own prototype), gives a callee whose
  result is stored into a typed pointer that return type, and rewrites `(void *)` casts on such
  stores to the target's type. The reflected member spellings
  (`((igObjectRefMetaField *)f)->_metaObject = …`) are untouched.
* `tools/guard_b_gen.py` emits the guard accessors through `igMetaObject` (`_validity` at +36), not
  a `struct G { int pad[9]; int f; }` view, for both the 18-word and the 19-word retail bodies.

**The declaration order.** A body shaped for another compiler matches only under a provisional
override. The differences between the compilers are small and
systematic: MWCC 3.0-011126 assigns s0, s1, s2 … to the locals in **declaration order**, the 2003
beta (`combat`) in **reverse declaration order** — the m2c names `temp_sN` carry the retail
register, so `initfields_gen.py --order auto` sorts the declarations for the unit compiler and, when
that first guess fails under `--verify`, tries the other orders (bounded). For the guard family the
default compiler needs the value-tested `bool ready = meta->_validity & 4` (plus `asm { nop }` for the
19-word body, marked as a matching construct), while combat and 3.0.3 keep the `sltu` for an
`unsigned char` flag compared with zero and pad the branch target themselves, so the generator picks
the shape from the unit compiler.

`tools/verify.py` checks each unit, unit profile first. The `_GetVTable` family is in
[getvtable-fold.md](getvtable-fold.md#one-translation-unit-one-profile).
Where a row carries an override its unit profile makes unnecessary the verifier prints
`override=unused`; those rows are stale and are pruned with `tools/gen_unit_profiles.py --from-check`.

Two bodies need more than the unit profile:

* `igTransformSequence_InitFields` (0x195620, unit default `-O3`, exceptions off): the
  `FUN_002d9500(field, -1.0)` call passes the double as a 128-bit value (`dsll32 v0; … pcpyld
  a1,zero,v0`), which the 2003 beta emits and the default build does not (it writes `dsll32 a1,v0,0`
  after the call); the body matches only under its combat override. Either the unit's profile or
  the default compiler's double-passing is the open question — a `tools/unitprofiles` review item,
  not a source shape.
* `igMovieInfo_InitFields` (0x336580, combat `-O3,p`): the code reproduces under the unit profile but
  needs **two symbols at 0x149980** — `FUN_00149980` and the data-named `DAT_00149980` — because
  retail loads the address twice; with one name the compiler keeps it in a saved register and the
  frame grows. With one name in `config/SLUS-20836/symbols.txt` the file verifies `name-defect` and needs its
  override.

Reproducing:

```
python3 tools/register_gen.py <Class>_Register ...                       # from asm/, language from the unit
python3 tools/guard_b_gen.py <Class>_GetMetaObject <Class>_ResolveMetaObject ...
python3 tools/initfields_gen.py --verify src/<module>/<Class>_InitFields.c ...   # retarget in place
python3 tools/verify.py 0x<va> <file>                                   # the gate
```
