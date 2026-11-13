# Retail combat unwind metadata

The flat retail image retains exception-index data. GAMERAM's external-table
record at `0x553b80` is `(0x3fca10, 0xa388, 0x544fd4)`: callback, complete code
size, table address. The next physical table is independently anchored by
`0x553bd4 = (0x407120, 0x938, 0x545174)`. These anchors bound the combat table
at 416 bytes; a missing ELF section name does not imply missing unwind data.

## Observed destroy-only format

[`combat_unwind_inventory.py`](../../scripts/combat_unwind_inventory.py) decodes
this bounded subset, using eleven controlled compiler functions to distinguish
sequential, nested and conditional ownership, long ranges, large frames, saved
floating-point registers and outgoing stack arguments.

| Leading-byte pattern | Nonnegative compact value |
| --- | --- |
| bit 0 clear | `byte >> 1` |
| low two bits `01` | `(byte >> 2) << 8`, followed by one low byte |
| low three bits `011` | `(byte >> 3) << 16`, followed by two low bytes, big-endian |

The decoder accepts these observed widths without claiming minimal encoding.
Four-byte prefixes remain unsupported. The header's low six bits count saved
GPRs; bit `0x40` adds a compact FPR count. Compact frame size and save-area base
follow the header, then the optional FPR count. Controlled prologues place the
return-address save at `base + align16(4 * FPRs) + 16 * GPRs`; its eight bytes must
fit inside the frame. Impossible save areas fail rather than producing an
apparently valid inventory.

Protected-range records contain compact `(delta, length, action_offset)`.
Add the delta to the **previous range end**, initially function offset zero.
The end is `start + length`, inclusive. Coordinates are return PCs: eight bytes
past the corresponding MIPS call. A zero-length range therefore protects one
return PC. A literal zero byte ends the range array. Action offsets are relative
to the table start.

A destroy action is `0x02` followed by a compact frame offset and a four-byte
little-endian destructor address. `0x82` marks the final action in a chain.
Nested controlled objects demonstrate inner-before-outer cleanup. Shared action
suffixes are permitted, while overlapping, unreferenced or out-of-bounds action
bytes fail. At most three trailing zero bytes are accepted; that is a bounded
padding allowance, not a claim about every object's alignment policy.

## Complete callback inventory

The generated [inventory](../../data/combat-unwind.json) contains 36 ranges,
34 distinct actions and 22 frame-offset/destructor identities. The header and
ranges occupy `0xaf` bytes; actions cover `0xaf..0x19d`, followed by three zeros.
GAMERAM saves nine GPRs, no FPRs, with save base zero, return address at `+0x90`
and frame size 1,200. All 72 range endpoints independently resolve to JAL/JALR
return PCs. The retail CLI additionally checks ELF file backing, executable
cleanup targets and both index anchors.

```sh
python3 scripts/combat_unwind_inventory.py --out data/combat-unwind.json
python3 testing/test_combat_unwind.py
```

Six tests cover the controlled metadata fixtures, save-area geometry, malformed
records and ELF bounds. The optional retail-input test checks the complete
inventory and independently corrupts an anchor, cleanup pointer and endpoint
call. The generic decoder permits zero destructor pointers in unrelocated
compiler fixtures; the retail command requires aligned executable targets.

Five reference homes have short cleanup scopes:

| Frame home | Protected return PCs, inclusive |
| --- | --- |
| `+0x4ac` | `0x3fcd14`, `0x3fcd28`, `0x3fcd30` |
| copied argument `+0x408` | `0x3fcd28`, before `+0x4ac` |
| `+0x4a8` | `0x3fd674..0x3fd680` |
| `+0x4a4` | `0x3fd6d4..0x3fd6e0` |
| `+0x4a0` | `0x3fd730..0x3fd73c` |
| `+0x49c` | `0x3fd78c..0x3fd798` |

These constrain temporary-like source scopes without proving original syntax.
The main FIGHT string wrapper at `+0x498` spans `0x3fde6c..0x406abc`, with
nested string/list references. The `+0x3e8` cleanup targets an owning object
reference destructor, not a plain vector destructor. See the
[matched cleanup bodies](../systems/combat-reference-helpers.md).

This tool does not decode catches, other action kinds, four-byte numbers or the
packed inline exception-index form. It does not establish ownership for newly
emitted compiler sections. The [whole code/table oracle](../systems/combat-draft-recovery.md)
and [emitted-object checks](emitted-functions.md) remain the banking boundary.

## Retail index records as verification inputs

A standalone C++ unit compiled with exceptions on emits a `.exceptix` index
record, and some also an `.exception` table: the oracle audit counted 3,625 such
units, 246 of them with a table. Left uncompared, those sections are orphans the
relink places outside the compared section, so the verifier compares them with
the retail records described here, for standalone units as well as for the
group units with an `exceptions` row in `config/SLUS-20836/unit-objects.json`.

### The records in the image

Every record is 12 bytes: the function address, its code size with **bit 0 set
when the third word is the packed inline form**, and either that packed
summary (`0x2000`, `0x406000`, `0x4001`, ...; no table) or the table address.
`FUN_001005f0`'s record at `0x546fd4` is `(0x1005f0, 0x1d, 0x2000)`: 28 code
bytes, packed. The retail linker concatenated all `.exceptix` input sections
into one array at `0x546fb0..0x554858` (4,622 records in link order; eight
name 36-byte bodies in inter-function gaps that `config/SLUS-20836/symbols.txt` does not
list) and all `.exception` tables into `0x542ae0..0x546fb0` (514 tables,
17,604 bytes). Neither region has a section name in the flat ELF.

`tools/exceptions.py --write` recovers them into `config/SLUS-20836/exceptions.txt`
(`fn_va index_record_va table_va table_size`, `-` for a packed record). It
scans the image for runs of consecutive record triples and accepts a run only
when at least four of its records name a function of the symbol map with
exactly its size; a table's size is the distance to the next table, and the
last table ends at the index region less whole zero words of padding. The
nine declared `unit-objects.json` rows agree with the recovered table
(`tools/test_exceptions.py`), and `--check` fails when the file is stale.

### What verify, check and link do with them

* `verify_one` (standalone path) compares a unit's `.exceptix` record
  (relocated against the function) and its `.exception` table (relocated, the
  retail slot may end in up to three zero padding bytes) with the retail bytes
  the same way the group path does, and reports `exc=ok`. The combinations
  retail contradicts are failures: `exc=extra` (the object emits metadata,
  retail keeps no record: the retail unit was built with `-Cpp_exceptions off`
  or as C), `exc=missing` (retail keeps a record the object does not produce:
  the retail unit was C++ with exceptions on, the source is not), `exc=differ`
  (both exist, the shape or bytes differ, e.g. a 5-byte table where retail has
  a 16-byte destroy action).
* The group path cross-checks a declared `exceptions` row against the
  recovered table, rejects a group whose owner or emitted member has a retail
  record the unit does not reproduce, and reports `exc=ok`.
* `tools/check.py` prints an `excepts:` line: how many functions with a retail
  record are decompiled and how many reproduce it, miss it, differ or emit
  metadata retail lacks.
* `tools/linkgen.py` places a standalone unit's compiled `.exceptix` and
  `.exception` at the retail addresses when their shape fits the record: the
  raw data unit holding the slots is carved into fragments around them and the
  compiled sections are pinned in between, so the relink reproduces them from
  source and `linkcheck`'s byte compare covers them. Group units' copies are
  still discarded after `verify_emitted_unit` compared them (their retail
  bytes stay raw), as are the `extra`/`missing`/`differ` cases, which linkgen
  counts in its `exception metadata` line and `linkcheck` notes as orphans.

### Coverage

The `excepts:` line of `make check` and the `exception metadata` line of
`make link` carry the current numbers. A `.c` unit, or a `.cpp` unit built with
`-Cpp_exceptions off`, does not produce a retail record. A missing or shorter
table means the source lacks a cleanup scope retail had. A `.cpp` unit can emit
metadata for a function retail compiled without it. Group units' records are
verified by `verify_emitted_unit` but linked from retail bytes, and what
`extra`/`differ` units leave unplaced are orphans that `linkcheck` names. Every one of
these failures is a property of the source (language, exception setting or a
missing lifetime), not of the oracle. A probe of 40 code-only units bears this
out: `exc=extra` units match fully with `-Cpp_exceptions off`, and 12 of 40
`exc=missing` units match unchanged when compiled as C++.

### Records of frameless leaves

Seven retail records have a packed summary of `0`: the function has no frame and
no saved registers, yet the record exists. The compiler keeps one for a leaf when
its source had, before optimisation, an int/float conversion, a `double`
operation, an inlined copy constructor or copy assignment of a class, an inlined
`const` member returning a `float` that is used as a value, or a local of a class
with a destructor, even when the final code has no frame and no call. A function
that only stores constants, or copies plain structs, gets none.
`beNDMWItemBase_GetRevisionColor` keeps its record because it returns an `igVec3f`
whose copy constructor runs on `return`; the same body returning a plain struct
compiles to the same instructions without the record.

## Open questions

- `FUN_00383ed0` keeps a retail record with a packed summary of `0`, but the compiler
  emits none for its current C or C++ spellings. None of the constructs above has
  been tried on it.
