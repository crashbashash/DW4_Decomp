# `ps2_` sound banks — the game's SE/BGM container

A stage's resident effects live inside CRI `ps2_` banks in its own sound pack
(finding [#450](../findings/findings-0251-0500.md#f450)). Music and ambience can instead be standalone ADX streams in
`NDMW.AFS`: the title metadata resolves `ST_CHARA`, `AM_TITLE` and `AM_START` to
entries 53, 19 and 18 (finding [#777](../findings/findings-0751-1000.md#f777)). The no-ADX-in-AFS
conclusion attached to [#447](../findings/findings-0251-0500.md#f447) does not hold; its Sofdec MPEG-1/ADX identification is valid.

This page is the format; the port's reader is the executable spec (the `DW4_Port` repository's
`src/sfp.c`, CLI `dw4asset sfp`), and its `tools/verify_sound.py` proves the decoder against
ffmpeg sample-for-sample.

## Where a pack's sound lives

A stage is delivered as a **pair of `NDMW.AFS` entries** listed by its manifest (finding [#431](../findings/findings-0251-0500.md#f431)). The
smaller entry is its sound + SE pack, the bigger its model/setup pack:

| stage | sound pack | size | model pack | size |
| --- | --- | --- | --- | --- |
| `stag0102` | `NDMW.AFS` 620 | 494,084 B | 621 | 5,060,706 B |
| `stag0201` | 641 | 346,670 B | 642 | 5,173,220 B |

The sound pack is an ordinary **igBinary container** (magic `0x40c`, version 38 for entry 620). Its
record chain is small — 29 classes, 617 records over 24,232 bytes at `+0x18a0 .. +0x7748` — and the
**content pool** that follows (`hdr[6]` = 463,548 bytes, `+0x7748 .. end`) is almost entirely the sound
data. That pool is:

```
+0x7748  580 bytes: a 145-entry u32 list (sound IDs the stage uses)
+0x798c  bank 0
+0x139a4 bank 1
+0x201a4 bank 2
+0x2a3f0 bank 3
+0x2fc90 bank 4
+0x45a04 bank 5
```

Each bank is one `.sfp` file. The pack's `beCriSfpData` records name them and carry their sizes, and
`_pcmSize` matches the bank's `DTPK` size field exactly — so the name set is recovered, not guessed:

| bank | record name | `_pcmSize` | `DTPK` at | VAG bytes | rate | sounds |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | `e_goburi.sfp` | 49,152 | `0x798c` | 46,336 | 24000 | 5 |
| 1 | `e_ogre.sfp` | 51,200 | `0x139a4` | 48,832 | 24000 | 7 |
| 2 | `common_blst.sfp` | 40,960 | `0x201a4` | 37,504 | 24000 | 4 |
| 3 | `scannon.sfp` | 20,480 | `0x2a3f0` | 16,960 | 24000 | 2 |
| 4 | `stag0102.sfp` | 88,064 | `0x2fc90` | 85,952 | 24000 | 6 |
| 5 | `e_blosso.sfp` | 208,896 | `0x45a04` | 206,400 | 24000 | 9 |

## A bank's three chunks

Everything is little-endian; the sample rate is a u16 (24000 = `c0 5d` on disk).

```
+0x000  ps2_DTPK
         +0x00  "ps2_DTPK"
         +0x08  0x00004102
         +0x0c  pcm_size    the bank's total size (matches beCriSfpData `_pcmSize`)
         +0x10  field       equals beCriSfpData slot 7 (800..1216); role unproven
         +0x18  vag_size    ADPCM bytes in the VAGD chunk (= beCriSfpData slot 8)
         +0x1c  header_size the VAGD chunk's offset — 0x800 in every bank seen
         +0x20  three 0x4000 words (0x20..0x2b), then zero

+0x060  ps2_TBLD
         +0x08  0x00004102
         +0x0c  length      the table's own extent (it does NOT include the record table below)
         +0x20… decode tables: a volume curve (a byte ramp 0…255), a nibble table, and
                per-voice filter records
         then, somewhere in the chunk and 16-byte aligned but not aligned to the chunk,
         one record per sound:
           { u16 x,  u16 rate,  u32 a,  u32 end,  u32 0 }
           `x` varies per record; `rate` is the constant sample rate; `end` is the
           entry's end offset within the VAGD chunk (0 on the last record = chunk end)

+0x800  ps2_VAGD
         +0x08  0x00004102
         +0x0c  vag_size    must equal the DTPK's (the reader self-checks this)
         +0x20  the ADPCM
```

The record table's `end` fields **tile the VAGD chunk exactly** — entry *i* is `[end_{i-1}, end_i)`,
starting at `0x20` — so a bank's sounds are delimited with no counting and no guesswork.

## The ADPCM is Sony VAG, with a control byte

Frames are 16 bytes, but three details distinguish this from a stock VAG stream, and each one was
pinned by matching ffmpeg's `adpcm_psx` output:

1. **byte 0** is the usual `shift` (low nibble) / `filter` (high nibble);
2. **byte 1 is a control byte**, so the 28 four-bit samples are the nibbles of **bytes 2..15**, low
   nibble first. `0x00` is normal, `0x01` appears on the last audio frame of an entry, and **`0x07`
   silences the frame and resets the predictor** — it is the padding between sounds;
3. the predictor feeds back the **unclamped** sample (only the output is clamped to int16), and the
   two-tap prediction is a **truncating** `/ 64`.

The predictor coefficients are the standard VAG pairs:

```
filter 0: (0, 0)   filter 1: (60, 0)   filter 2: (115, -52)
filter 3: (98, -55)   filter 4: (122, -60)
```

The sample rate is 24,000 Hz for every bank seen.

## Named sounds: the entry → name map

The bank container carries sizes but no names, and the pack's banks hold no name strings
at all. The names live in the pack's **records** (finding [#452](../findings/findings-0251-0500.md#f452)):

```
beCriSfpData._name     the bank's name (e_goburi.sfp, …)
beCriSfpData._pcmSize  equals the bank's DTPK size — so the bank ↔ name match is exact
beSoundData._name      the sound's name (goDEAD01, …)
beSoundData._fnameIdx  which bank, through beSoundInfo._fnameList
beSoundData._memoryIdx high 16 bits = sequence index; low 16 bits = sequence-group tag
sequence note -> tone table -> waveform index (see #783 below)
```

The list `_fnameIdx` indexes is the stage's `beSoundInfo._fnameList`, read live from a loaded
`stag0102`:

```
[0]  sound/sfp/PS/allse.sfp        [6]  sound/sfp/PS/STAG0102.sfp
[1]  sound/sfp/PS/COMMON_BLST.sfp  [7]  sound/sfp/PS/scannon.sfp
[2]  [0.55]                        [8]  sound/sfp/PS/e_ogre.sfp
[3]  [0.30]                        [9]  sound/sfp/PS/e_goburi.sfp
[4]  [0.33]                        [10] sound/sfp/PS/e_blosso.sfp
[5]  [0.23]
```

(`allse.sfp` is a 64-sound **global** bank in `sbiallse.igb`, NDMW entry 897;
the four `[pt.entry]` slots are the notation of finding [#445](../findings/findings-0251-0500.md#f445).) The original CLI
reader does not decode the filename list, so it matches each
`_fnameIdx` group to the one bank whose entry count equals the group's size — which is unique on every
shipped pack — and leaves a group that matches no bank external. The result names the 33 stage
sequence selectors (`goDEAD01`/`goNATK01`… for `e_goburi`, `og*` for `e_ogre`, `bl*` for
`e_blosso`, the four blasts in `common_blst`, the stage objects `TARU_BLST01`/`OBJ_TORCH_CRASH`/… in
`stag0102.sfp`). The CLI diagnostic still labels sequence numbers as entries;
that label does not establish waveform identity. Native front-end playback uses
the full selector resolution described in [#783](../findings/findings-0751-1000.md#f783).

## What this does and does not settle

**Settled:** every bank decodes to PCM offline, so the port can play SE/BGM with no emulator and no
load-time-ordinal replay (unlike textures and models), and every stage sound is **named**. All six
banks of entry 620 decode sample-for-sample identical to ffmpeg — **773,472 samples, 0 differences** —
and `tools/verify_sound.py` also asserts the bank names and that no entry is left unnamed.

**Global bank recovered ([#777](../findings/findings-0751-1000.md#f777)):** `sbiallse.igb` contains `allse.sfp` at an unaligned
DTPK offset, `0xecc7`, with 64 entry records. Four-byte-aligned scans miss it.
The native front-end audio adapter also decodes `beSoundInfo._fnameList`: its
slot 7 references an `igNamedObjectList`, whose slot 4 points to a pool block of
little-endian named-object IDs. `_fnameIdx` indexes this list, removing the need
for group-size matching in the adapter. It resolves global cursor/window effects
and the embedded `STAGIS10.sfp` start cue. See the port's
[native playback record](../../port/docs/audio-playback.md).

**Open:** the meaning of the `TBLD` record table's `x`/`a` fields and of `DTPK`
`field_10`. The resident sequence selector is described under [#783](../findings/findings-0751-1000.md#f783) below.

## Pre-lobby selection mapping ([#780](../findings/findings-0751-1000.md#f780))

The complete `beSeCtl` runtime group (`0x0039c900..0x0039cb6c`) is represented in
[`sectl.c`](../../recovered/frontend/sectl.c). Its action dispatcher at
`0x0039c990` selects the **last** matching `beSeInfoData` model name, walks every
matching `beSeData` action, then sends `MODELCTRL(model, slot)` / `SETSOUND` with
sound-name and signed-16 delay converted to float. This binds sound to model
actions; a button press alone does not select a cue.

NDMW **805**, referenced by `stagis10.igb`, gives these selection mappings:

| Model / action | Sound | Bank entry |
| --- | --- | --- |
| `j_startmenu01 LINEON00`; `j_startmenu02 LINEON00/01` | `CURSOR_START` | `STAGIS10.sfp` sequence 1 → waveform 2 |
| `j_startmenu02 LINEUP00/LINEDW01` | `CURSOR_MOVE2` | `STAGIS10.sfp` sequence 3 → waveform 0 |
| `j_optioncursor11 MOVE` | `CURSOR_MOVE2` | `STAGIS10.sfp` sequence 3 → waveform 0 |
| `j_optioncursor12 MOVE` | `CURSOR_MOVE` | `allse.sfp` sequence 2 → waveform 28 |
| `j_optioncursor11 LINEON00..03` | `CURSOR_START` | `STAGIS10.sfp` sequence 1 → waveform 2 |
| `j_chrselmesswin LINEON00/01`; name `NAMEON00..07` | `CURSOR_DECIDE` | `allse.sfp` sequence 1 → waveform 29 |
| `j_chrselmesswin LINEUP00/LINEDW01`; name `NAMECG00..07` / `LINECG00` | `CURSOR_MOVE` | `allse.sfp` sequence 2 → waveform 28 |
| `j_digifacewin CHANGE` | `WINDOW_CLOSE2` | `allse.sfp` sequence 8 → waveform 47 |
| `j_mainstatuswin LINEON00` | `CURSOR_START` | `STAGIS10.sfp` sequence 1 → waveform 2 |

These delays are zero. AREA620 / NDMW806 option value sequences `SQ_LINERTxx` /
`SQ_LINELFxx` first issue `ACTION MOVE`; their direction-specific joint actions
are separate. Available `CURSOR_CHANGE` and `CURSOR_DECIDE3` clips have no
`beSeData` selection mapping in this pack and are not substitutes.

Run `python3 scripts/verify_sectl.py --elf orig/SLUS-20836/SLUS_208.36` from the
decomp repository: **392 retail/C comparisons**, 150 instruction addresses,
ordered stores/calls, duplicate model/action rows, absent/null names, initialization,
and signed delay extremes. The oracle stubs messaging and integer-to-float leaves;
it verifies dispatch, not downstream audible timing or mixing. This is behavioral
recovery for immediate port work and adds no byte-matched `src/` coverage.

## Resident sequence-to-waveform resolution ([#783](../findings/findings-0751-1000.md#f783))

Finding [#452](../findings/findings-0251-0500.md#f452)'s filename/bank recovery is valid, but its direct
`_memoryIdx >> 16` → waveform inference is wrong. The packed low 16 bits
select a sequence group: `0x49a9` for STAGIS10 and `0x02a9` for the menu
sounds in allse. The high half selects a sequence within that group.

DTPK-relative `+0xa4` points to a sequence directory: a last-index word,
then packed group rows `{u16 offset, u8 group, u8 0xa9}`. Offsets are relative
to the directory. Each group holds another last-index word and relative
sequence offsets. The supported menu sequences are six-byte events
`c0 df NOTE 7f 80 ff`; allse group 2 sequence 7 contains two events and must
not be collapsed to a single waveform. DTPK `+0xa8` points to the tone
directory. Its `+8` offset selects a 32-byte header followed by 32-byte
note records; note byte 2 is the waveform index. This describes the shipped
front-end single-note subset, not a general CRI sequencer implementation.

The PCSX2 recording `../local/evidence/videos/2026-10-10 06-35-25.mp4`
(20.466667 seconds, 48 kHz AAC stereo) independently confirms the resolved
waveforms at their authored 24 kHz rate. High-pass 100-ms templates find
START at 2.0524/4.1075/16.1024 seconds (minimum correlation 0.985), six
DECIDE cues (minimum 0.895), four OPEN cues (minimum 0.886), and two CLOSE
cues (minimum 0.879). DECIDE is allse waveform 29; OPEN/CLOSE are 24/25.
These comparisons tolerate the captured music/AAC mix and do not establish
absolute gain, envelope or native action-to-audio timing.

The native reader resolves bank data instead of a hardcoded menu map.
`port/tools/verify_menu_capture.py` reproduces all 15 comparisons; the audio
harness verifies each resolved cue and rejects unsupported/malformed inputs.
The lobby terminal sequence 7 resolves to waveform 7.

## Repeat admission and stream levels ([#781](../findings/findings-0751-1000.md#f781)/#782)

Static inspection covers the complete eight-body `beSound` runtime group
`0x0039e540..0x0039fc2c`. The selection playback arm of its message dispatcher
at `0x0039ec10` samples the signed world clock at `context+0x50`. It suppresses
an SE when its resolved sound index matches a `_playSEs` row and `now < deadline`.
A positive playback handle adds a row with `deadline = now + 0x02faf07e`
(**49,999,998 ns**). Equal time permits playback; unrelated sounds do not block
one another. Expired row cleanup is separate from admission.

Stream types 1/2 follow the `beCriAudio` stream path at `0x0037c2c0`, adding
`beSoundInfo._baseVolume` to signed `beSoundData._volume`. Volume routes through
`0x003a6f70`, `0x00332430` and `0x0026c660`; the latter also adds an optional
CRI channel adjustment. `0x0027ae18` clamps enabled-driver levels to `[-999,0]`.
The command packet builder at `0x00279790` loads the table word from
`0x004b0e20 - level*4` and writes it as the volume command's Q8 amplitude.
Every one of its 1,000 words equals `floor(256 * 10^(level / 200))`.

NDMW805 and NDMW819 both store base volume **-30**. For the currently used
tracks, the combined levels are `ST_CHARA=-40`, `AM_TITLE/AM_START=-30`,
`ST_LOBBY=-50` and `AM_LOBBY=-160`. The port applies the corresponding normalized
Q8 ratios **161/256**, **181/256**, **143/256**, **40/256**. Resident SFP playback
is a separate SFX master/per-voice path, including `_sndfVolume=75`; applying
this stream attenuation to resident cues would be unjustified.

From the workspace root, run
`python3 port/tools/verify_frontaudio_rules.py --elf orig/SLUS-20836/SLUS_208.36`.
It executes original admission and deadline-store regions for **473 cases**,
all **1,000** original table packet writes, and the original level clamp at
boundary values. It compares the actual native helper code. It does not recover
the complete dispatcher as executable C, nor validate downstream IOP output,
extra channel offsets, fades, positional mixing, or audible scheduling.
The asset-backed `test_audio` checks adapter admission and `verify_audio.py`
checks loaded gains. No additional byte-matched source is claimed.

## Recovering it

The container is decoded by `dw4asset sfp` and checked by `make check` in the port tree:

```sh
build/dw4asset sfp --afs NDMW.AFS --entry 620
build/dw4asset sfp --afs NDMW.AFS --entry 620 --bank 0 --wav e_goburi.wav
```

`tools/verify_sound.py` re-derives the banks from the pack, wraps each VAGD stream in a `VAGp` header
for ffmpeg, and compares the two decodes sample-for-sample. A new pack is decoded with no changes: the
scan finds the `ps2_DTPK` magics, and every offset is self-checked against the VAGD size field.

Findings: **[#450](../findings/findings-0251-0500.md#f450)** (this format), **[#447](../findings/findings-0251-0500.md#f447)** (the movies are MPEG-1 + ADX) and **[#777](../findings/findings-0751-1000.md#f777)** (standalone
ADX streams in `NDMW.AFS`). See also [`afs-archives.md`](afs-archives.md) for the archive/container level and
[`igbinary-format.md`](igbinary-format.md) for the pack that holds the banks.

## Stage cue catalogue and event bytes ([#2757](../findings/findings-2751-3000.md#f2757)–[#2760](../findings/findings-2751-3000.md#f2760))

Every stage or dungeon file with a sound pack (96 of the 2,076 igb files: 39 `stag*` and 57 `dng*`) lists its whole cue
set as `beSoundData` records (8,855 cues, 68 to 134 per pack; 326 streamed tracks and 8,529 resident effects), each resolving through
`beSoundInfo._fnameList`. The single-note event `c0 df NOTE BYTE 80 ff` carries `0x7f` in the menu cues and
`0x5a`–`0x78` in 168 gameplay cues; all resolve through the tone table. Not resolved: the two-event allse
sequence 7 of group 2 (`WINDOW_OPEN2`, with a `00 82 02` wait between its notes; one per pack, the only resident cue silent in all 96). Two cases a reader has to handle: a pack's
bank names assigned by size swap for the equal-size `mcannon`/`scannon` pair (the cue's group tag, unique per bank,
selects the right one), and a bank's entry-record table can hold 48000 Hz records among 24000 Hz ones (`stag0403.sfp`, nine
entries, the fifth at 48 kHz). The port's reader and its
measurements are in [audio playback](../../port/docs/audio-playback.md#stage-sound-catalogue-and-the-gameplay-set).

## beSound runtime: PLAY, stop commands and the voice pool ([#2762](../findings/findings-2751-3000.md#f2762)–[#2765](../findings/findings-2751-3000.md#f2765))

Read from the byte-matched `beSound::vfunc_34` (`0x0039ec10`) and the matched `beCri` players it calls. The message enum
(from the class's enum strings) is `1 STOP, 2 PLAY, 3 PLAYatPAUSE, 4 PAUSEOFF, 5 VOLUMECTL, 6 BGMSTOP, 7 ENVSTOP, 8 SESTOP,
9 GETWORDLIST, 10 VOLUMECTL2, 11 FXCTL, 12 ISREADY, 13 ISBGMREADY, 14 ISENVREADY, 15 ISALLREADY, 16 GETCURRENTBGM,
17 SNDFVOLUME, 18 OFFREEZE, 19 ONFREEZE, 20 MAKEBINLIST, 21 ISDONETRANS, 22 FREESFPDATA`, which is the handler's case order.

**PLAY (2) and PLAYatPAUSE (3, which first sets `_pauseOnetime`).** The cue is found by name in the info's data list, then by
`_type`: type 1 (music) returns without restarting when the name equals `_currentBGM`, otherwise starts in the stream player
(`0x0037c2c0`) and stores the name as the current BGM; when the player returns 0 a delayed PLAY retry is enqueued (also for type 2,
ambience, which never records a current name). Every other type is searched in the playing-SE list for a row with the same
*record index* and a deadline still ahead, which suppresses the play (replying handle 0); otherwise the resident-effect
player (`0x0037c4c0`) plays it and, for a positive handle, a row with deadline now + 49,999,998 ns is stored.

**Stop and fade.** `BGMSTOP`, `ENVSTOP` and `SESTOP` read no name: they stop the BGM handle, the ambience handle or the
resident-effect handles (`0x0037cc50`, kinds 1, 2, 4), and only `BGMSTOP` clears the current-BGM name. `VOLUMECTL` UP/DOWN fades
by handle number or by name over 10.0 (the ten-frame fade); a DOWN of the current BGM clears the name. `VOLUMECTL2 name a b c`
ramps the carrier of that name from `a` to `b` over `c`.

**Fades ([#2767](../findings/findings-2751-3000.md#f2767)).** `VOLUMECTL2 name a b frames`, `VOLUMECTL` UP/DOWN and the 10-frame fade-out of a busy music slot arm a ramp
(`FUN_003a7590`) over two adjacent 60-entry ease tables (`0x004c8fc0` rising from 0.04, `0x004c90b0` falling from 0.96; both end at
index 53). Each frame (`FUN_003a7890`/`FUN_003a7810`) advances the position by `(last - first) / frames` entries and yields the level
`base + volume + (int)(210 * factor) - 210` in 0.1 dB, finishing as soon as the target level is reached and returning -999 (silence) for a
target of 0: a 10-frame fade to 0 is silent on frame 9.

**Music change ([#2768](../findings/findings-2751-3000.md#f2768)).** `FUN_0037c2c0` takes the BGM slot for type 1 and the ambience slot for type 2 (memory index -1 only). If the slot's
voice is still playing it arms the 1.0 -> 0.0 over 10.0 ramp (only when none runs) and returns 0; `beSound::vfunc_34` then enqueues the PLAY
again with delay 0xB. The per-frame update (`beCri::vfunc_27`) steps the ramp and stops the voice when a fade to 0 passes -209 (ADX) or
127 * factor < 13 (sound bank), after which the retry starts the new track at `_volume + _baseVolume`. A music PLAY of the current BGM is
ignored before any of this.

**Voice pool.** `FUN_0037d310` appends 4 ADX handles (24 kHz) and 48 sound-bank handles to the effect list; the BGM and
ambience streams are separate 48 kHz ADX handles. `FUN_0037c130(kind, priority)` returns the first idle capable handle
(kind 1 needs an ADX object, kind 0 a sound-bank object), else stops and reuses the lowest-priority handle whose priority is
not above the request's, oldest first; a play stores the cue's type, priority and an increasing request id in the handle. Only
30 of the 8,855 cue records have a priority other than 0 (all 1).

**Level.** The ADX route (memory index -1) sets the voice level to `_volume + _baseVolume`, like the streams; the sound-bank
route sets level 127 and stores `_volume` as the handle maximum. The sound-bank backend is an RPC into the sound IOP module (`0x00281bb8`: play = command 1 with the id and the packed
sequence number, volume = command 4), so the event byte, the `00 82 02` wait of `WINDOW_OPEN2` and the handle maximum are
interpreted on the IOP side and are not recoverable from the EE program ([#2766](../findings/findings-2751-3000.md#f2766)). No code in the EE program reads `_channel` ([#2772](../findings/findings-2751-3000.md#f2772)). See the port's
[audio notes](../../port/docs/audio-playback.md#stage-sound-catalogue-and-the-gameplay-set).
