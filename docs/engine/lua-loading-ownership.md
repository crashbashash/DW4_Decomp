# Lua loading and ownership

This document records the retail startup, lookup and cleanup contracts.

## Boot, shared definitions and scene startup

The application loop `0x0025a580` initializes its managers and requests
`ndmw.igb` through `beSystem`. Between scene loops it calls `0x0025afe0`, whose
first operation is the manager-wide cleanup thunk `0x00463c80` → `0x002370c0`.
The system/file-list managers then collect the requested scene's native objects
and Lua-info data. Loading objects and executing Lua are separate operations.
`beLua::vfunc_25` (`0x0038a420`) accepts `beLuaInfo` objects and appends them to
`_infoList` at `+0x14`; the archive collector `0x003810c0` routes these objects
through `0x00237030`. This preserves collection order rather than sorting by
logical script name.

`beFileListInfoManager::vfunc_27` (`0x0037fa30`) drives startup. Its `_proc` is
at `+0x3c`. It does nothing while `beSystem+0x58` is positive. Relevant phases:

| Phase | Retail action | Next phase |
| --- | --- | --- |
| 0/1 | Load scene directory; route its native objects. On first use only, prepend `BecText.igb` and `_common/sbiallse.igb` to the supporting-file work. `_isReadOnetime` and `_onetimeCount` retain that native resource distinction. | Supporting-file phases |
| 2 | Finish the queued supporting-file collector. | 3 |
| 3 | Find the Lua manager; replace its Lua state; execute `func.lua`, then `boot.lua`, using `<current-stage>/lua` as file fallback directory. | 4 |
| 4 | Finish the stage asset work and move important objects into the read list. | 20 → 21 → 5 |
| 5 | Route retained read objects to the managers and release the read list. | 6 |
| 6 | Set layer order and loading-layer visibility; resolve authored layer nodes. | 7 |
| 7 | Send `TEXTCTL INITIALIZE`, then execute `start.lua`. | 8 |
| 8 | Set `beSystem+0x2c = 1`. | 9 |
| 9 | Execute `first.lua`, finish the loader and set the ordinary-stage ready flag (except the listed intro scenes). | -1 |

The four scripts are **executed by name**, not executed in their serialized pack
order. Stage `func.lua` supplies the shared helper definitions in a fresh scene
VM. The loader does not inspect the script return status before advancing these
phases.
The phase 0/1 resource list describes native supporting assets, not an additional
permanent shared Lua global environment.

State replacement `0x0038a2d0` releases the old `beLua._luaState` reference
(`+0x18`) before creating a `beLuaState` through `0x0035aa20`. State shutdown
`0x0038a660` frees its file-read scratch buffer (`+0x14`), then base shutdown
`0x002465f0` closes the Lua VM (`state+0x0c`, `0x00253170`) and removes the glue
mapping. This is whole-VM global cleanup: it removes functions, tables and
arbitrary globals as well as named code. It is not selective deletion of globals
written by a chunk. Actual destruction depends on the recovered reference count;
this release does not prove immediate destruction if another native owner holds
an extra reference.

VM recreation is separate from session state. It does not reset the shared RNG,
save fields or progression; the engine's own systems own those.

## Duplicate names and fallback

`0x00389ff0` traverses `beLua._infoList` forward. For each info object it scans
`beLuaInfo._dataList` (`+0x1c`) forward. On its **first** matching `beLuaData.name`
it runs the referenced data buffer and breaks only the inner loop. It continues
through every later info object. Consequently:

- Two equal names within one info execute only the first row.
- Equal names in two infos execute once from each info, in collection order.
  Later assignments may override earlier globals, but earlier native side effects
  have already occurred. There is no single winning closure selected in advance.
- The last executed match determines the return status. An info with no match
  leaves that status alone. Later matches still run after an earlier error.
- Only final status **-1**, including no matches, triggers named-file fallback.
  Status 1 or 2 does not trigger fallback. A successful earlier match followed by
  a -1 match still triggers fallback; its side effects are not rolled back.

The data chain is `beLuaData+0x0c` → `beLuaDataObject`, whose `+8` is byte size
and `+0x0c` is the byte buffer. The call is the Lua state's RunBuffer slot
`+0x64`, with `(state, buffer, size, logical-name)`. Fallback calls RunFile slot
`+0x60` with `<directory>/<name>`; absent an explicit directory, it uses
`<beSystem.current-stage>/lua`. The explicit directory affects fallback only,
not the search across collected infos.

`beLuaState::RunFile` (`0x0038a6e0`) checks file availability through
`0x0037f1b0`, reads the file into owned scratch, locates `[EOF]`, and passes the
preceding bytes to RunBuffer. Availability failure returns 2; open/allocation or
missing-marker failures return -1. This path is distinct from cached original
binary chunks.

## Coordinated chunk, DM and SD teardown

The system-clock manager-wide RemoveAll body `0x002370c0` traverses registered
managers **forward**, calling each vtable's `+0x70` method. Only after that pass
does it release/zero its own collected-object list (`+0x10`). Its caller
`0x0025afe0` performs further scene/render resets afterward. This is a scene
boundary between simulation loops, not a scope removal embedded in a Lua call.

Retained retail title and lobby manager rosters establish this relative order:

| Slot | Owner | Cleanup |
| --- | --- | --- |
| 3 | `beMessenger` | `0x0038d080` → `0x0038c490`: release current argument context; clear receiver registry, selector cache, timed SD messages and auxiliary list; reset selection fields and enabled byte. |
| 5 | `beFileListInfoManager` | `0x0037f3f0`: clear scene, directory, filename, important/read lists and loaded index. |
| 7 | `beLua` | `0x0038a490`: release and zero **all** Lua-info entries, set count zero, then release and null the Lua-state reference. |
| 8 | `beDemoManager` | `0x0037eb80`: clear published DM groups, release unfinished build data, reset switch/cleanup latches. |
| Later model/controller slots | Scene receivers | Controller RemoveAll occurs after the SD/Lua/DM cleanup entries above. |

DM has a real deferral branch: when `_disableRemoveAll` (`+0x21`) equals 1,
RemoveAll only sets `_calledRemoveAll` (`+0x22`). Active and unfinished groups
remain intact. The ordinary branch clears both, resetting `+0x20` and `+0x22`.
At the end of its tick, `0x0037f138..0x0037f154` clears `_disableRemoveAll`,
checks `_calledRemoveAll` and calls the RemoveAll slot if requested.

Lua-info cleanup alone cannot cancel timed SD work; DM cleanup alone cannot
remove arbitrary Lua globals. The retail boundary coordinates all three managers.

## Evidence

The 85 contract samples execute original MIPS instructions: 48 lookup/fallback
cases, eight startup/gating cases, twenty-two Lua/DM/SD cleanup cases and seven
coordinator/state replacement/shutdown cases. Empty and unrolled-loop boundary
sizes are covered. Allocation, archive IO, Lua execution, virtual receiver
handlers and refcount destruction remain controlled leaves. The oracle checks
ordered calls, statuses and ownership fields, not complete script side effects
or rendered/gameplay equivalence. Ghidra's read-only `--noanalysis` exports were
checked against `mipsel-linux-gnu-objdump`; decompiler output alone is not proof.

Offline RAM observations:

| Savestate | Stage | Managers | Lua-info tables / named chunks | Lua-state address |
| --- | --- | --- | --- | --- |
| `logo-close-start+50ms.p2s` | `stagIS10` | 35 | 1 / 10 | `0x01201e60` |
| `logo-close-start+434ms.p2s` | `stagIS10` | 35 | 1 / 10 | `0x01201e60` |
| `dw4-inworld.p2s` | `stagML11` | 38 | 1 / 64 | `0x011b0d30` |

Each table contains `func.lua`, `boot.lua`, `start.lua` and `first.lua`; SD/Lua/DM
cleanup slots are 3/7/8 in all three states. These are independent loaded-world
captures, not a measured transition history or a new emulator playthrough.
Unseen scenes may collect multiple infos; the duplicate rules are established
by original-instruction fixtures rather than an observed duplicate in these
three captures.
