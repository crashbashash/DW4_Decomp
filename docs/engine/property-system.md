# GAMERAM Property / Method System

All persistent player/world state (LEVEL, EXP, HP, BIT, items, flags, …) is
stored as **named property records** inside the GAMERAM object graph, accessed
by string key. This is the layer the `SYS*` script functions use.

The complete list/lookup group now has [behavioral source and original-instruction
verification](object-lists.md), including two corrected historical search labels.

## Core lookup — `0x3022c0`
```asm
3022c0: addiu sp,sp,-112
3022d0: move  s5,a0        ; s5 = container
3022d8: move  s4,a1        ; s4 = registry  (*(0x00585be0))
3022e0: move  s3,a2        ; s3 = key string
3022e8: beqz  s4, fail
3022f0: bnez  s3, 0x302300
302300: lw    s1,8(s5)     ; s1 = container->count
302308: move  s2,zero      ; i = 0
30230c: lw    v1,16(s5)    ; v1 = container->entries
302314: lw    v0,8(s4)     ; v0 = registry->name_offset
302318: addu  v1,v1,a0     ; v1 = &entries[i]
30231c: lw    s0,0(v1)     ; s0 = record
302320: addu  v0,s0,v0     ; v0 = record + name_offset
302324: lw    a0,0(v0)     ; a0 = record->name
302330: jal   0x12a4a4      ; strcmp(a0, key)
302338: bnez  v0, next     ; not equal -> continue
302340: move  v0,s0        ; FOUND -> return record
302348: addiu s2,s2,1
30234c: slt   v0,s2,s1
302350: bnez  v0, 0x30230c
302354: move  v0,zero      ; not found
```

### Container layout
| Offset | Field |
| --- | --- |
| `+8` | record **count** |
| `+16` | pointer to array of **record pointers** |

### Property record layout
| Offset | Field |
| --- | --- |
| `+ *(registry+8)` | **name** (char*) |
| `+12` | **value** (u32; u8 for boolean props) |

`registry = *(0x00585be0)`; its `+8` field is the name-member offset — **measured
live as `8`** (see "Registry object" below), so a record's name pointer is at `+8`
and its value at `+12`, exactly as the record layout says.

### `strcmp` — `0x12a4a4`
Word-parallel `strcmp` using the `0x01010101`/`0x80808080` tricks. Returns 0 on
equal.

## Sibling accessors
| Function | Behaviour |
| --- | --- |
| `0x3022c0` | find-by-name (strcmp), returns record |
| `0x302380` | find-by-name-**pointer** (pointer equality) |
| `0x3023f0` | binary-search a sorted unsigned selected key, then verify equality and return its record |
| `0x302480` | return an equal midpoint or unsigned-key insertion position; -1 for null descriptor, 0 for empty list |

## Getter/setter wrappers
| Function | Behaviour |
| --- | --- |
| `0x3a9220(a0, key)` | `igProperty_FindByName(a0, *(0x00585be0), key)` — get record (u32) |
| `0x3a9280` | get record, value read as byte (`lbu ...,12(v0)`) |
| `0x3a92b0` | get record (byte-array copy form, used by save) |
| `0x3a92e0`, `0x3a92a0`, `0x3a9250`, `0x3a92b0` | variants used in save/load |
| `0x3a9340` | get record, used for "folder"/array fields |

### Usage pattern (`SYSgetPlayerLevel` = `0x00372590`)
```asm
372598: jal 0x371c10      ; v0 = player struct (a0 = idx+1)
3725a8: jal 0x3a9220      ; v0 = record for key 0x0050da00 = "LEVEL"
3725b4: lw  v0,12(v0)     ; return record->value
```

### Setting a value (`SYSsetDifficulty` = `0x00371dd0`)
```asm
371de0: jal 0x371c10      ; player struct
371df0: jal 0x3a9220      ; record for "DIFFICULTY"
371df8: sw  s0,12(v0)     ; record->value = new value
```

## Player struct pointer chain
`bePlayer_GetStruct(idx+1)`:
1. Indexes a player-slot table at `0x004c8720` (method names: `GETCOMMON`,
   `GETPLAYER1..4`, `PCWA/PCCA/…`).
2. Calls `0x38e5f0(main_obj, "GAMERAM", 0, 0, method_name)`.
3. Returns `0x38f800(main_obj, 0)` = `*( *( *(main+16) + 40 ) + 16 + 0*4 )`.

Each returned player struct is itself a property container (`+8` count,
`+16` entries).

## Stat getter dispatch — `0x003fd1e0`
A function that `strcmp`s the method key and resolves through `0x3a9220`:
```
"HP"  (0x00518890)   "MHP" (0x00518898)   "MP" (0x005188a0)  "LEVEL" (0x00518858)
```
Method keys → property names:
| Method key | Property | Address |
| --- | --- | --- |
| `GETHP` | `HP` | 0x00519040 / 0x00518890 |
| `GETMHP` | `MHP` | 0x005190f0 / 0x00518898 |
| `GETMP` | `MP` | 0x005190f8 / 0x005188a0 |
| `GETMMP` | `MMP` | 0x00519100 |
| `GETEXP` | `EXP` | 0x0050da50 |
| `GETLEVEL` | `LEVEL` | 0x0050da68 / 0x00518858 |
| `BASE_EXP` | `BASE_EXP` | 0x0050da58 / 0x00517fa0 |
| `BASE_LEVEL` | `BASE_LEVEL` | 0x0050da78 / 0x00517f90 |

## Key vocabulary
### Scalar / progression keys
```
LEVEL  BASE_LEVEL  GETEXP  BASE_EXP  GETLEVEL  GETHP  GETMHP  GETMP  GETMMP
ADDHP  ADDMP  MHPUP  MHPUP2  NINZU  ISUSE  BASE_ISUSE  UNIQUE  BIT
DIGIMONNAME  DIGIMONNO  PLAYERNAME  POWERSOCKETNAME  XDATA
DIFFICULTY  CAMERAMODE  LIGHTMODE  GATESTAGENO  GATESTAGENAME
DEVICE  DEVICEFOLDER  DISKFOLDER  FLAGFOLDER  FLAG  CTRLITEM  DISK
CARDLIST  KAZU  SET  CLR  COUNTER  SUBWND  ISRUN  SETSHINKA  CTRLPLAYER
MAINSLOT  SUBSLOT  MAINPOCKET  POWERPOCKET  POWERSOCKET  SOUBI  SKILL
SKILLPOINT  TSUYOSA  BASE_COUNTER  BASE_FLAG  BASE_SKILL  BASE_UPCNT
BANKBIT  BANKDEVICE  INI_WEAPON1  SaveDataTime  MakeDataTime
```
### Method / controller keys
```
GAMERAM  MODELCTRL  NUMBERCTRL  SETVALUE  ONE  CHECKSTATUS  FIND_SPACE
GENERATE  PLAYERPOINT  GETGENERATEPOS  GETMATRIX  GETMATRIXDIRECT
GETPEBASEWORK  PLAYER  ENEMY  FIGHTCALC  LOADINTF2  SETDIFFICULTMAX
ACTION  FLASH  WAIT  FADE  NDSP  STAGECTL  NEXTSTAGE  GETCOMMON  GETPLAYER*
```
### Status-effect set keys
```
SETSTUN  SETPOISON  SETSLEEP  SETBIND  SETATTACKDOWN  SETPOWERDOWN
SETPERCENT  SETLABEL  SETCOLOR  SETGENERATEPOS  ALLCLEARSTATUS
```
### Fight-calc keys
```
P2E* (player→enemy): P2EISHITCHECK P2EISCRITICAL P2EDAMAGE P2ESTUNTIME
  P2EPOISONTIME P2ESLEEPTIME P2EBINDTIME P2EATKDWNTIME P2EPOWDWNTIME
  P2ESKILLUP P2EEXPUP P2EKOUKAMAGIC
E2P* (enemy→player): E2PISHITCHECK E2PDAMAGE E2PDAMAGERANK E2PSTUNTIME
  E2PPOISONTIME E2PSLEEPTIME E2PBINDTIME E2PATKDWNTIME E2PPOWDWNTIME GETPATKZOKUSEI
```
Element names: `common`, `fire`, `ice`, `thunder`, `dark`.

### Player-slot method names (`0x004c8720`, indexed by player+1)
```
[0] GETCOMMON   [1] GETPLAYER1  [2] GETPLAYER2  [3] GETPLAYER3  [4] GETPLAYER4
[8] PCWA  [9] PCCA  [10] PCSA  [11] PCMA  [12] PCBA  [13] PCTK  [14] ENAT
[15] PCMK  (ENSP nearby)
```

## Key string address ranges
| Range | Region |
| --- | --- |
| `0x0050c700`–`0x0050cfa0` | the 116 API names |
| `0x0050d8f0`–`0x0050df90` | GAMERAM method/property vocabulary |
| `0x00517e50`–`0x00517ee0` | save-record field order (`ISUSE UNIQUE LEVEL HP MHP MP MMP PLAYERNAME ME DIGIMONNAME AME XDATA BIT DEVICEFOLDER DISKFOLDER …`) |
| `0x00518858`–`0x00519120` | stat property/method keys (`LEVEL HP MHP MP … GETHP … ISEQUIP`) |

## Registry object (measured, not inferred)

`*(0x585be0)` is read (never written) by this code path — every one of the ~15
references in the ELF is a `lui at,0x58` + `lw a1,23520(at)` load — so it is a BSS
slot filled by the generic object machinery, and its value can only be read, not
reconstructed statically. Read from off-line EE RAM (`p2s_ram.py` on
`states/SLUS-20836/dw4-inworld.p2s`):

```
*(0x585be0) = 0x005da690
  +0x00  0x00533180   vtable
  +0x04  0x04000104   refcount/flags
  +0x08  8            <-- the name-member offset
  +0x0c  0x0067b15c
  +0x10  0x00020004
  +0x14  4
  +0x18  0x005da5c8
  +0x1c  0x00585be0   pointer back to its own handle slot
```

So `*(registry+8) == 8`: the container lookup's
`record + *(registry+8)` → name pointer is a literal `record + 8`, and the value
sits at `+12`. The `+0x1c` word pointing at its own handle slot is how the class
instance is reachable from the fixed global.

## `sd` — the four internal ids (29–32)

The Lua-facing `sd` is registered **four times**, and they are not four different
operations: they are **two operations, each in a with/without-optional-5th-argument
pair**. Each id is a trampoline (`0x00370c38`, `0x00370c58`, `0x00370c78`,
`0x00370ca0`) that pulls the Lua frame's argument slots — a 24-byte stride at
`+16`, `+40`, `+64`, `+88`, `+112`, `+136` — and forwards them to an impl:

| id | trampoline | impl | forwards to |
| --- | --- | --- | --- |
| 29 | `0x00370c38` | `0x00372ff0` | `0x38d860(root,a,b,c)`; if arg5 ≠ 0 also `0x372cf0(arg5)`; then `0x38e060(root,arg4)` |
| 30 | `0x00370c58` | `0x00373060` | `0x38e5f0(root,a,b,c,d)` = `0x38d860` + `0x38e060` |
| 31 | `0x00370c78` | `0x003730a0` | `0x38e6b0(root,a,b,c)`; if arg5 ≠ 0 also `0x372cf0(arg5)`; then `0x38e8f0(root,arg4,arg6)` |
| 32 | `0x00370ca0` | `0x00373120` | `0x38eca0(root,a,b,c,d,e)` = `0x38e6b0` + `0x38e8f0` (5th read with `ld`, i.e. 64-bit) |

`0x38e5f0` **is** `0x38d860` followed by `0x38e060`, and `0x38eca0` **is** `0x38e6b0`
followed by `0x38e8f0` — verified in the decompiler, which is what collapses the
"four ids" into two operations. So ids 29/30 differ only in whether the optional
5th argument is applied, and 31/32 likewise; `0x372cf0` is the helper that consumes
that optional argument. All six object-system calls take the root object
`*(0x58a1c0)` as their first argument.

## GAMERAM property template (`0x004cedf0`, 64 × 12 bytes)

`0x003f7310` passes `0x004cedf0` to `0x003f6620`; each entry is
`{u32 type, u32 count, char *name}` at offsets +0, +4 and +8. A scan that starts
at the first name pointer (`0x004cedf8`) shifts the other two words into the
following entry, so its apparent nonzero defaults and bitmasks are the next
entry's type and count. A type of -1 terminates the table at
`0x004cf0f0`.

Constructor dispatch `0x00518b90` selects integer scalar (0), integer array (1),
byte scalar (2), byte array (3), string (4), string array (5), object array (6)
and float array (7). Scalar integers/bytes start at zero; array counts come from
the +4 word. LEVEL has type 0/count 0, SKILL type 1/count 9, UPCNT type 1/count 11,
PLAYERNAME type 6/count 0 and POWERSOCKET type 6/count 3. BASE_LEVEL and BASE_SKILL
have 16 and 144 elements, filled separately with ones by `0x003f7310`.
BASE_EXP (16), BASE_UPCNT (176), UPDATA (11) and DOWNDATA (7) start at zero.
BASE_ISUSE is a 16-byte array; selected species membership is set by `0x003f9570`.

`0x003f82a0` selects the current species from base arrays and copies its
MODEL_NAME from shinka. `0x003f8990` constructs three weapons using INI_WEAPON1–3;
`0x003f8c90` selects the three weapon sockets. `0x003fab90` writes current stats,
using only the first socket's weapon contribution. The name path `0x003f96e0`
runs the US converter `0x00382eb0`, copies up to eight resulting codes into a
Unicode object and zero-pads it before replacing PLAYERNAME's object list.

## Not yet resolved
- Which object-system operations `0x38d860`/`0x38e060` and `0x38e6b0`/`0x38e8f0`
  actually perform (create-vs-lookup, and what the second call in each pair does),
  and what optional argument `0x372cf0` consumes.
