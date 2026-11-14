# The engine boot chain: from the CRT entry to the frame loop

`main`, the SDK init and both frame functions are C in `src/unmatched/`.  Everything here is in the EE runtime / Alchemy-core region.

## The CRT entry (`_start`, `0x00100008`)

```
0x100008  _start: clear the GPR file, $f0..$f31, mthi/mtlo/mtsah
          clear .bss  0x554b00 .. 0x58d280
0x100198  gp = 0x55c870 ; syscall 60 -> sp
0x1001c0  syscall 61  = SetupHeap(0x0058d280, -1)
0x1001e8  jal 0x1141c8                                      the EE runtime init sequence
0x1001f0  jal 0x10b160(0)                                   FlushCache
0x1001f8  ei
0x1001fc  jal 0x2d1640  = __do_global_ctors               __init_user / C++ static ctors
0x100210  lw a0,[0x554f00] ; a1 = 0x554f04 ; jal 0x2595e0   <-- main
0x100218  jal 0x2d1650  = __do_global_dtors               exit / atexit runner
0x100220  j 0x124d60                                        C++ static destructor runner
```

`0x1141c8` calls the runtime init sub-sequence `0x113f90`, `0x1140b8`, `0x1146a8`, `0x114820(2)`,
`0x114a60`, `0x10bcb8`, `0x1142f0`, `0x1137c8` and tail-jumps `0x115ed8`.  `__init_cpp` sets up
four table pointers (`0x522440`, `0x522480`, `0x546fb0`, `0x554858`) and jumps into `0x100c50`
(the static-initialiser driver).  `__destroy_global_chain` is the atexit list walker
(`while (e) { next = e->next; e->fn(e->arg, -1); }`).  `exit` walks the C++ static
destructor list at `0x004854a0` and then re-enters `0x100228`.

## The game's `main` (`0x002595e0`, 976 bytes)

Read as a sequence of phases:

| phase | calls |
| --- | --- |
| process/argv setup | `0x259a20`, `0x259cd0(argv[0])` |
| globals | `0x587338 = 2`, `0x587340 = 0x4ec870`, gp flags |
| SDK/library init | `0x2d16a0`, `0x259d10`, `0x2590c0` (1308 B) |
| the **app object** at `sp+112` | `0x234900(&obj)`, `0x234d70(&obj, argc, argv)` |
| allocator / root | `0x2f8a20`, `0x165d20` |
| **managers** | `0x1a1ae0`, `0x1a7cc0`, `0x1a67c0` (each 52 B, reached through `0x2f8a20`/`0x2ff820`) |
| scene/parameter setup | `0x25a070`, `0x259f90` |
| the **frame object** `*(0x56dc50)` | `0x1007e0` / `0x238110`, then `+0xe8` (its reference count) is incremented |
| **the loop** | `0x25a8c0` **or** `0x25a580` (chosen by byte `+0xd8` of the frame object) |
| shutdown | `0x30c940`, `0x100610`, `0x25a330`, `0x234b90`, `0x2d1770` |

The `0x1a1ae0`/`0x1a7cc0`/`0x1a67c0` trio is the manager construction (Insight core); the
temporary is released with `0x2ff820` after each, which is the object-model destructor
(`igObject`'s refcount release). `0x25a070` constructs the game's viewer object on the stack: the
viewer setup (`0x463560`) built around a new window, reference holders, an `igFolder` named `cdrom0:`
and a loading-file message; `0x259f90` then stores two of the app's references into it, and `0x25a330`
is its destructor.

### The engine core init (`igObjectSystem_Acquire`)

`igObjectSystem_Acquire` (`0x2d16a0`, called with `0xc80`) is the engine core init/acquire, refcounted on the
64-bit global `0x586dd8`.  On the first call it sets `0x4fb410 = 0` and `0x4fb418 = 1`, calls
`0x32d1f0`, allocates a 928-byte object, runs `0x2d1930` on it, stores it at `0x586dc8`, passes it to
`0x2d1a00`, then runs the init chain `0x2b9620`/`0x2b9470`/`0x2c4d80`/`0x2bb200`/`0x2bad40` and
`0x2d1690`/`0x2d1e40`.  Every call ends in `0x2d18d0(*(0x586dc8), arg0)`.  The test matches only as a
post-increment, `if (counter++ == 0)`; m2c's `counter += 1; if (counter == 0)` leaves register and
delay-slot differences.

### The managers are named

Each of the three is `<Class>_Create`: it runs the class's static init
(`igMetaObject_RunStaticInit(<Class>_Register)`, through the 12-byte `_RunStaticInit` thunks
`0x1a1ca0`/`0x1a7d90`/`0x1a6890`) and then `igMetaObject_CreateInstance(<Class> MetaObject, owner)`.
The class is recovered from both ends and they agree: the `_Register` function the thunk tail-calls,
and the MetaObject global the class's own `_GetMetaObject` accessor lazily fills:

| `main` call | class (`_Create`) | `_RunStaticInit` | MetaObject global | stored at |
| --- | --- | --- | --- | --- |
| `0x1a1ae0` | `igEnbayaContextPool_Create` | `0x1a1ca0` | `0x561b60` | `0x562718` (`g_igEnbayaContextPool_instance`) |
| `0x1a7cc0` | `igAnimationCombinerBoneInfoPool_Create` | `0x1a7d90` | `0x562250` | `0x562528` (`g_igAnimationCombinerBoneInfoPool_instance`) |
| `0x1a67c0` | `igAnimationStatePool_Create` | `0x1a6890` | `0x5620d8` | `0x562540` (`g_igAnimationStatePool_instance`) |

All six are C (`config/SLUS-20836/names/Managers.tsv`, `src/engine/`).  At the semantic level each is
`igMetaObject_CreateInstance`: allocate the class's reflected size (0x20),
run `igObject_InitHeader`, stamp the vtable.

## The frame functions (`FUN_0025a580` / `FUN_0025a8c0`)

Both take the parameter block `main` builds as `arg0`, branch on its `+0x18` and set per-frame
state on the frame object.  The frame object global is `*(0x56dc50)` and the app pointer
`*(0x56df80)` (`lui at,0x57` with a negative offset).

The frame object is 0xF0 bytes, created on demand.  `+0xe8` is its context reference count, not a
frame counter.  `main` holds one count across the call to the frame function, and `FUN_0025a580`
takes another around the per-frame fields.  Each holder decrements it and at <= 0 releases the `+0xec`
and `+0` references (refcount at -4, handle at -8), frees the object through `__dl__FPv` and clears
the global.

**Both contain lifecycle setup, update/render repetition and teardown.**
The [clock scheduling recovery](system-clock.md#executable-lifecycle-and-scheduling-contracts)
shows that `0x25a8c0` can repeat render passes without sampling the world clock
again; these bodies are not single-frame callbacks.
The disassembly of `FUN_0025a580` carries the whole sequence (the same subsystem calls the text
below used to attribute to `0x25a8c0`), so they are two variants `main` chooses between, and the
README's earlier split into a "non-windowed" and a "windowed/drawing" path read the flag as a
pipeline split rather than as a variant selector.

* `FUN_0025a580` (`0x25a580`, 832 B) requires `arg0+24 != 0`, writes the app pointer to
  `*(0x56df80)`, lazily creates `*(0x56dc50)` (`0x1007e0`/`0x238110`), increments `+0xe8`, then
  runs the per-frame field setup: byte `+0xb4 = 0`,
  byte `+0xd5 = 0`, byte `+5 = 0`, float `+0x94`/`+0x98`/`+0x9c = 0.1f`, float `+0xa0 = 1.0f`,
  byte `+0x5c = 0`, byte `+0x5e = 1`, byte `+0xa8 = 1`, then decrements `+0xe8` in the release block
  (`ViewerOptions_ReleaseShared` is that release extracted).  It then runs the per-frame work:
  `0x239390`, `0x238d40`, `0x3343a0`, `0x33bf50`, `0x3719c0`, `0x3b04e0`, `0x463b30(app)`,
  `0x259f80(app)`, `0x463c70(app)`; builds a list from `0x236f80(app->+0, *(0x587d08))` and, when
  `*(0x586f20)` is NULL, creates it via `0x2eb010(0x10)`/`0x2eadf0`, then releases the old list at
  `s0+60` and stores `0x2eaf60(*(0x586f20), &0x4ecf60)`; calls the app's vtable `+152` and then the
  returned object's `+708` with a stack vector; and polls `app+44` / `s0+16` / `s0+64` / `s0+60`
  around `0x259d40`, `0x463bc0`, `0x463bb0`, `0x25afe0` and `0x463b70`.
* `FUN_0025a8c0` (`0x25a8c0`, 928 B) repeats that opening sequence (`0x239390`, `0x238d40`,
  `0x463b30(app)`, `0x259f80(app)`, `0x463c70(app)`) and adds a set of `0x4578c0` state setups,
  its own lazy frame-object create/release, and further present-side calls
  (`0x463bc0`/`0x463bb0`/`0x22fd70`/`0x230298`/`0x3082b0`/`0x463b70`/`0x2ff820`).

`main` calls one of them around `0x2598c0`/`0x2598d0`, chosen by byte `+0xd8` of the frame
object; the update loop itself is inside the body.

`FUN_0025a580` is in `src/game/GameMain.cpp`.  Retail saves `s0`–`s2` in an 80-byte frame, keeps `arg0` in
`s1` and reloads `24(s1)` for the later virtual call.  This allocation is source-driven, not a compiler
flag effect: in a minimal MWCC test a two-parameter function with a `short` second parameter gets
`s1` = arg0, `s0` = arg1 only when the first call in the body takes no argument, and passing a pointer
to that call flips them.
