# `*_GetVTable` — the plain-family stack-offset fold (a measured MWCC wall)

The 983 `*_GetVTable` functions split into ~345 **plain** (48–68 B) bodies and ~638
larger variants (68–964 B). Every one of them ends in the same
**stack-offset fold**:

```
lw   v0,916(v0)        ; slot = *(*(0x586dc8) + 916)   (a byte offset, usually 0)
addu v0,v0,sp          ; v0 = slot + frame pointer
lw   v0,16(v0)         ; return *(void **)(&tmp + slot)      tmp at fp+16
```

Retail folds the frame temporary's own offset (`D` = the temporary's frame slot:
16 for a `-32` frame, 24 for the 8-byte `igObject` variant, 32/48/… for the larger
ones) into the final load's displacement. It is **one instruction / one stack-offset
fold away**: the closest source form compiles to

```
addu v0,v0,sp
addiu v0,v0,16         ; <- not folded
lw   v0,0(v0)
```

— 11 of 15 instructions identical, 60 vs 64 bytes, the 5 relocations identical
(`tools/verify.py 0x1307f0 …`). Status: **fail-closed**, a compiler wall; the drafts stay in `build/m2c/` and nothing guessed is committed.

## The measured addressing rule

Reproduce on this toolchain with `python3 scripts/mwcc_addr_probe.py` (and `--sweep`).
MWCC 3.0-011126, 2.4 and 2.3.3 give identical results:

| source | emitted tail |
|---|---|
| `char u[16]; … u[i]` (value) | `addu v0,i,sp ; lb v0,16(v0)` — **folded** |
| `int u[4]; … u[i]` (value) | `sll v0,i,2 ; addu v0,v0,sp ; lw v0,16(v0)` — **folded** |
| `char u[16]; … &u[i]` / `u + i` / `*(T*)((char*)u + i)` | `addu v0,i,sp ; addiu v0,v0,16 ; lw v0,0(v0)` — **not** folded |
| `int *p; … *(T*)((char*)p + i + 16)` (register base) | `addu v0,p,i ; lw v0,16(v0)` — folded |

So the frame symbol's offset folds into the load displacement **only on the scalar
*value-subscript* path** (`arr[i]`), never on the address path (`&arr[i]`,
`arr + i`). On that path the load width *and* the index scale both follow
`sizeof(element)`, so a **4-byte (word) load is inseparable from a scale-4 `sll`**.
There is no C type with `sizeof == 1` that loads 4 bytes (a packed union, a
`-enum min` enum array and a size-1 struct all still emit `lb`/`lbu`), so a
**scale-1 word fold is unrepresentable in C** on this compiler.

A trailing constant folds into the load only when the addend base is a *register*
(a parameter, a loaded pointer, `__builtin_frame_address`, an `alloca`/VLA base) —
never when it is the frame pointer `sp` itself. The only register equal to `sp` is
a parameter, and `*_GetVTable` takes none (its `a0` is the temporary's address).

Flags are not the discriminator: `-O1`…`-O4`, `,p`/`,s`, `-enum min`, C and C++
front ends all emit the `addiu` form (`-O1`/`-O2` additionally change the epilogue,
ruling them out).

## The generator space and its result

`scripts/mwcc_addr_probe.py --sweep` is the committed, reduced form of the search
(168 forms, 0 fold-hits). The full scratch generator
(`getvtable_gen{,2}.py`, `getvtable_wide.py`, `typed_member_sweep.py`) tested
**~9,000 form-settings** — a single full run of the `gen2` space was **7,200
forms across 6 flag sets, 0 fold-hits**, plus focused sweeps over the
required axes:

- **aggregate / type layout** — `char`/`short`/`int`/`void *`/`long long`/`float`/
  `double`/struct/union/packed/`-enum min` arrays, lengths 1–16; 4/8/16-byte
  `igObject`-shaped structs; union overlays;
- **stack-header construction** — the `igObject_InitHeader(&tmp)` call plus the
  vtable store, before/after, per-member stores, zeroed second word;
- **index / address expressions** — pointer arithmetic, subscript, address-of,
  `(int)/(char)/(unsigned)/(short)` casts, `*1`/`+0`/`<<0`/`>>2`/`/4`, reversed
  addend order, parenthesisation/reassociation, `+K − K` cancellation;
- **declaration / temporary ordering** — junk locals, typed intermediates, pointer
  locals, nested blocks;
- **aliasing / qualification** — `volatile`/`const`/`register`, inlined helpers and
  macros, `__builtin_frame_address`, `alloca`/VLA;
- **compiler modes** — `-O1`…`-O4`, `,p`, `,s`, `-enum min`, C vs C++ (extensions),
  plus MWCC 2.4 / 2.3.3.

**Zero fold-hits.** The project's decomp-permuter searched ~1,800 candidates from
the closest hand-typed seed and floored at score 100 (never 0). There is **no
matched oracle**: all four non-`GetVTable` sites carrying the fold
(`FUN_0024bda0` v0/16, `FUN_00447ed0` v1/80 and v1/48,
`Gap__Bec__beNDMWShopCtrl10__vfunc_21` a1/112) are themselves unmatched.

## Hypotheses eliminated

Folded-tail shape from a stack temporary; `char*`/pointer-variable base; typed
struct-member access; union/overlaid aggregate layout; per-class temporary size;
`sw`/`lw` width; signedness or width of the index; index scaling (`>>2`, `/4`);
addend order and parenthesisation; declaration order / extra temporaries;
`volatile`/`const`/`register`; inlined helper or macro; compiler flags and compiler
version; C vs C++ front end. All produce the `addiu` form (or an `sll`-carrying
subscript), never the fold.

## Decision: link-verbatim where no source matches

A `*_GetVTable` that no C or C++ source reproduces stays as retail bytes reassembled from `asm/`. These are per-class type-metadata accessors; no matched or
native code depends on them being C, the port reimplements behaviour from recovered contracts, and the only other way to match one is
whole-function inline assembly, which recovers no source and would only inflate the percentage. If a C or C++ spelling of the fold under
the default compiler is ever found (the stack-offset fold is the open question) they can be matched mechanically; until then do not spend matching time on that spelling.

The decision does not cover the accessors the pinned alternate compiler reproduces: the stack-object `*_GetVTable` accessors with a 48-byte frame (171 functions of the 60-byte family) match as C at `-O3,p` with a `struct Obj { int *vt; char pad[28]; }` template. Other `_GetVTable` sizes are worth re-testing with the same template.

## One translation unit, one profile

Build settings resolve per translation unit ([build profiles](build-profiles.md)), and a
`*_GetVTable` is done only when it prints `cat=match` under its **unit's** profile. Reproducing the
code bytes is not enough for two kinds of accessor, 590 in all, and they have different causes.

### `exc=missing` (317 units): the right bytes in the wrong language

MWCC keeps a 12-byte exception index record for every function with a frame or a call when
exceptions are on, and only the C++ front end emits one. A matched C body therefore verifies
`code-only` in an exceptions-on unit. The fix is mechanical and does not touch the body:
`tools/initfields_gen.py` (the retargeting engine the InitFields family shares; reachable as
`tools/getvtable_stack_gen.py --retarget FILE...`) rewrites the unit as `.cpp` — typed `extern "C"`
prototypes inferred from the call sites because C++ has no unprototyped calls, `(void *)` casts on
stores into typed pointers replaced by the target's own type, the body unchanged — and verifies it
under the unit profile. **307 of the 317 verify `cat=match`** as `.cpp`. `getvtable_stack_gen.py` runs the same step on every draft it writes, so a newly generated
accessor lands in the language its unit needs.

The ten that stay `code-only` (`libBecRuntimePlugin`, `libNdmwRuntimePlugin`, `beTransformSync`,
`beModelCtrlNode2`, `beModelCtrlInfoWork`, `beCopyTransform`, `beCopyModelCtrl2`, `beCameraCtrl`,
`beNDMWMdlPlayerInfoWork`, `beNDMWMdlItemInfoWork` `_GetVTable`) reproduce the code and the index
record, but retail also keeps a **16–20-byte exception table** for them (`config/SLUS-20836/exceptions.txt`,
`exc=differ orphan=20`): the stack object had a destructor the unwinder must run, i.e. the original
was a real C++ class temporary (`Class tmp; return tmp.vtable slot`) whose destructor is the
`(&o, 0)` call the C shape spells by hand. A C-shaped body cannot emit that table; reproducing it
needs the class with its destructor declared, which is model recovery, not retargeting. They are
left as they are.

### `foreign-profile` (273 units): the stack-offset fold is the profile question

272 of the 273 sit in units whose profile is the default compiler (3.0-011126), and the code bytes
are reproduced only under their provisional `combat` override. This is exactly the measured wall
above: the default compiler never folds the frame temporary's offset into the final load, so no
spelling can make these functions match under the unit profile. The question is therefore the
profile, not the source ([build profiles, reviewing a provisional unit, case 3](build-profiles.md#reviewing-a-provisional-unit)).
Probing every one of the 272 files as written, with the unit tables disabled
(`tools/verify.py --units /dev/null --unit-flags /dev/null --unit-compilers /dev/null --mwcc … --flags …`):

| compiler, flags (unit's exception mode) | reproduces the code bytes |
| --- | --- |
| combat `-O3` | 173 (147 `match`, 26 `code-only`: `.c` in an exceptions-on unit) |
| combat `-O3,p` (the 99 the row above misses) | 99 (24 `match`, 75 `code-only`) |
| 3.0.3 `-O3` | 0 |

Every one of the 272 is reproduced by the 2003 beta and none by the default build; the
3.0.3-020716 build mismatches all 272. The units' other members (the
`_Register`/`_InitFields`/`_GetMetaObject` siblings) verify under the unit profile, and none of them
reproduces under combat: that holds for all 8,677 undecided (function, candidate) pairs over the pins
of every provisional unit. So the unit profiles stand, and the 272 stay `foreign-profile` overrides,
reported as such and never counted. A unit that did move to the combat profile would have its
`_GetVTable` a `tools/getvtable_stack_gen.py --retarget` away from `match` (the 26 + 75 `code-only`
rows need the `.cpp` form).

The 273rd, `igOptInterface_GetVTable` (0x225ae0), lies inside the `alchemy-base_225770` unit (3.0.3,
exceptions off), a run of the Base library whose profile it does not share: case 1 of the review
list.

### Reproducing

```
python3 tools/getvtable_stack_gen.py --retarget src/<module>/<Class>_GetVTable.c   # existing drafts
python3 tools/getvtable_stack_gen.py <Class>_GetVTable                               # new drafts, retargeted on write
python3 tools/verify.py 0x<va> src/<module>/<Class>_GetVTable.cpp                    # the gate: cat=match, no foreign override
```

## Open questions

- **The larger variants.** Unproven beyond one instance: the larger `*_GetVTable` variants are the plain
  core plus a tail. `igVisualContextAttrDefaultManager_GetVTable` (`0x1300b0`, 140 B) has the same
  60-byte core, then a null-checked refcount decrement and a call to `igObject_Destroy` (`0x2ff820`),
  which is dead there because the tested pointer was just zeroed. Size histogram of the 983 functions:
  plain form 60 B x334, 68 B x7, 48 B x3; then 140 B x101, 132 B x45, 216 B x41, 116 B x36, 224 B x32,
  100 B x22, up to 964 B.
- **Where the 272 accessors were compiled.** Unproven: they were not compiled in the class unit at all,
  and come from a generated accessor object or a later build of the same unit.
