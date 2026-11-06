# Central disk-collector Prmame (`n_prmame`) and the folder engine services

Central's `n_prmame[0]` (stagML12) is a gift NPC, **not** the Save Keeper that earlier notes called it: its
original script calls the engine services `SYSctlDiskFolder` and `SYSctlDeviceFolder`, which were missing
and stopped the conversation (`engine service unavailable: SYSctlDiskFolder`). Both services are now native.
The real Save Keeper is the Digi-Elf whose choice queues `saveshop.lua` and a `stagIS12` stage request
(see [save-keeper edge](../../docs/systems/hub-recovery.md#save-keeper-named-script-edge)); that stage and its
save controllers are still open.

## Script behaviour (original bytecode, `lua/01-lobby-hub/06-lobby-quest-board_e824`)

- `n_prmame_00` (`chunk_0100`) asks `SYSctlDiskFolder("ISMAX", 0, 11, 0)` and sets flag 921 from the answer,
  then speaks according to flags 935 (single player), 405, 3 and 392..401.
- With a full disk-11 stack it chains to the prize script (`chunk_0035`). For the first unset flag in 392..401 it
  asks `SYSctlDeviceFolder("ISMAX")`: a full device folder (36 entries) gives no prize and keeps the disks.
  Otherwise it sets the flag, clears nine disks (`SYSctlDiskFolder("CLR", 0, 11, 9)`), adds one equipment record with
  `SYSctlDeviceFolder("SET", 0, kind, record, revision, pocket)` and plays the item-get jingle. The chain is weapon 200
  (rev 10, pocket 1), armor1 10 (rev 20, pocket 1), weapon 8 (30, 2), weapon 62 (40, 2), armor1 20 (50, 2), weapon 91 (60, 2),
  weapon 115 (75, 2), armor1 4 (90, 3), armor2 32 (110, 0), weapon 49 (150, 3).

## The services

| Engine call | Retail | Native |
| --- | --- | --- |
| `SYSctlDiskFolder(op, player, id, amount)` (`3722c0`) | GAMERAM `CTRLITEM` group `DISK` (`3fca10`, case 17 → `3fd970`) | `dw4_playertransactions_disk_folder`, `dw4_playertransactions_folder_call` (`src/inventorydetail.c`) |
| `SYSctlDeviceFolder(op, player, kind, record, revision, pocket)` (`3721b0`) | `CTRLITEM` group `DEVICE` | existing `dw4_playertransactions_device` through the same call |

Both messengers answer a bool, returned to Lua as the number 0 or 1. Operation names are `SET, CLR, IS, ISMAX,
ISEQUIP, GET, ADD`. The binding chains `dw4_playertransactions_folder_call` after `dw4_playerrecords_call` in the hub,
engine and test bindings (it returns 1 for any other method).

- **DISK**: the DISKFOLDER entry whose record equals `id` holds its count in `revision` (retail `+0x14`; lookup `448050`).
  `SET` adds `amount`, saturating at 9, and answers false when already 9. `CLR` subtracts `amount`, clamped at 0, and answers
  false when already 0. `IS` answers count ≠ 0, `ISMAX` answers count = 9. `ISEQUIP`, `GET` and `ADD` push no answer and change
  nothing (native: false).
- **DEVICE**: the kind name (`weapon`, `armor1`, `armor2`, `abChip`) selects kind 0..3; `ISMAX` ignores it and an
  unknown name or an operation beyond `ISEQUIP` answers false without changing the folder. Capacity is 36.
- Atomic: the folder is changed on a staged copy and committed whole.
- Refused natively where retail is undefined: a missing disk id (retail indexes the list with −1), a negative amount, an
  unknown operation name, the wrong argument count, or a player outside 0..3 are errors, not guesses.

The item-get jingle `ITEM_GET` was added to the lobby clip set (`src/frontaudio.c`); it resolves from the stagml11 sound data
and plays through the existing cue path.

## Verification (all headless)

- `make -C port check-hubprmame` drives the real NPC through the Cross probe and the original scripts: the first
  meeting (sets 405, changes nothing), a stack of eight (refused), a full stack (disks cleared, weapon 200 rev 10 pocket 1
  added, flag 392 set), the second prize (armor1 10 rev 20 pocket 1) and a full device folder (no prize, disks kept), each
  ending with control restored. Fixtures: the disk-11 count, the inventory size and the progress flags the script sets itself.
- `make -C port check-playerinit` covers the engine calls: saturation, clamping, every operation, refusals and the 36-entry
  capacity.
- `make -C port check-playertransactions-retail` executes retail `3fca10` from the ELF for 400 randomized `DISK` states and the
  three operations that push no answer, comparing the answer and every revision with the native transaction.
- `make -C port check-hubnpcs` counts this NPC as an implemented service (its effects are asserted by `check-hubprmame`).

## Boundaries

- The later prizes (flags 394..401) follow the same script lines but only the first two are driven in tests; the
  multiplayer branches (flag 935 = 0) are not exercised.
- The jingle's voice and timing are not compared with retail.
- SUBWND mode 10 (CARD) is requested by no hub pack, so no hub NPC reaches it.
- Only player 0 is wired; co-op is out of scope.
