# Native FMV, front-end and arrival audio

Windowed launches play audio automatically through SDL2's default output
device. No launch flag is required. ffmpeg decodes Sofdec soundtracks and
standalone ADX; resident sound effects use the native VAG decoder. Builds
without SDL2 and unavailable audio devices keep video playback and report the
missing audio backend. Headless boot checks stay silent.

Losing window focus keeps gameplay, rendering and audio running in the
background. Focus return requires no resume key. Title, character creation and
lobby focus-event checks verify continued audio sample-clock advancement
alongside world-clock advancement and presentation; see the
[background-focus regression](lua-integration.md#live-simulation-pump). FMVs
keep their continuous playback.

Pass `--mute` to `dw4` to silence FMVs, title/lobby ambience and music, menu
cues and the terminal beep. For example,
`./build/dw4 --roms ../../local/extracted --mute`. Muting clears the mixed
output while voices and the sample clock continue advancing, preserving FMV
synchronization. It applies to devices opened later, including attract replay
and the lobby device.

## Mixer

`src/audio.c` mixes immutable clips in an SDL callback, requesting a 512-sample
device buffer. The mixer has 64 voices and the final mix saturates to int16. The title, lobby and Commander Room sets use the music
voice, the ambience voice and five rotating cue voices; the gameplay set adds a
pool of 4 ADX handles (voices 8–11) and 48 sound-bank handles (voices 12–59),
described under
[the gameplay rules](#retail-effect-pool-music-and-stop-rules-in-the-gameplay-set).
SDL resamples resident mono effects from 24 kHz to stereo 48 kHz.

Builds without SDL still prepare resident menu clips: decoded mono samples are
duplicated without gain adjustment into a private stereo PCM WAV and passed
through the ffmpeg 48 kHz stereo decoder. The output device remains
unavailable. This keeps headless scene/audio metadata preparation independent
of device compilation; SDL builds use the SDL converter.

## FMV playback

`src/movie.c` prerolls the soundtrack to 48 kHz signed-16 stereo PCM before
starting the first video frame. Video follows the audio sample clock,
interpolated within the current buffer. Stale presentations are omitted after
decode/render stalls; every compressed frame is still decoded. The sample clock
continues through silence after the soundtrack ends.

Skip, window close and EOF close the device before releasing PCM. Attract
replay uses a new device and clock. SDL buffers and downstream hardware latency
limit the estimated audible position; no speaker-level calibration is claimed.
PCM preroll is bounded to 128 MiB per clip and adds a decode delay before
presentation.

Normal windowed movies use hardware presentation and GPU FPS bitmap/plate work;
standalone playback honours an explicitly selected software reference mode.
There is no forced SDL software selection. Normal Vulkan resizing uses GPU
nearest-source-index conversion while raw RGB/RGBA/channel packing remains
transport work. Audio preroll/sample clocks, 29.97 video cadence, stale-frame
omission and skip semantics are independent of the presentation path. GPU
failures are reported separately from a clean window close. Hardware SDL/Vulkan
startup and standalone acceptance are recorded in
[GPU rendering](gpu-rendering.md#normal-path-audit).

## Title and character creation

`src/frontaudio.c` resolves `beSoundInfo._fnameList` through its named-object
list and pool IDs, then follows each `beSoundData._fnameIdx`. The title sound
pack is loaded through `stagis10.igb`'s references. Asset evidence is recorded
as finding [#777](../../docs/findings/findings-0751-1000.md#f777) in this repository's recovery findings.

| Sound | Retail source | Playback |
| --- | --- | --- |
| `ST_CHARA` | NDMW ADX entry 53 | Resume at title tick 239; repeat the authored loop, samples 658336–6582824 at 48 kHz. |
| `AM_TITLE` | NDMW ADX entry 19 | Title ambience, played once. |
| `AM_START` | NDMW ADX entry 18 | Title entrance sound, played once. |
| `CURSOR_START` | Embedded `STAGIS10.sfp`, sequence 1 → waveform 2 | START and main-menu confirmation; option-row confirmation and login. |
| `CURSOR_MOVE2` | Embedded `STAGIS10.sfp`, sequence 3 → waveform 0 | Main-menu movement and option-row movement. |
| `WINDOW_CLOSE2` | `allse.sfp`, sequence 8 → waveform 47 | Character face `CHANGE`. |
| `CURSOR_CANCEL`, `CURSOR_DECIDE`, `CURSOR_MOVE` | `allse.sfp`, sequences 0, 1, 2 → waveforms 30, 29, 28 | Menu and character/name input cues. |
| `WINDOW_CLOSE`, `WINDOW_OPEN` | `allse.sfp`, sequences 5, 6 → waveforms 25, 24 | Loaded and available to the cue adapter. |

The global bank is the manifest's `sbiallse.igb` (NDMW entry 897). Its DTPK
starts at unaligned pool offset `0xecc7`; the sound scanner visits byte offsets
to recognize its 64 sounds. Embedded banks are selected by recovered bank
names.

The packed `_memoryIdx` is a sequence selector, not a waveform number. Its low
two bytes select a sequence group; its high half selects a sequence in that
group. The sequence note resolves through the tone table to the VAG waveform.
`dw4_sfp_resolve` accepts the shipped single-note cues and rejects unsupported
multi-event sequences. Reading `_memoryIdx` as a direct waveform index plays
unrelated samples (a 0.22-second sample for the 0.96-second START cue).

The PCSX2 reference capture confirms 15 occurrences: three
START, six DECIDE, four OPEN and two CLOSE. At the authored 24 kHz rate, 100-ms
waveform templates correlate with the captured mix at 0.879–0.993. This
establishes sample identity and rate; captured output gain and native
model-event scheduling are separate verification boundaries.

### Cue selection and repeat admission

Selection cues resolve the original `beSeInfoData._actionList` / `beSeData`
model/action table in NDMW805 ([finding #780](../../docs/engine/sound-format.md#pre-lobby-selection-mapping-780)).
Title model sequence requests emit their first authored ACTION; horizontal
option sequences emit `MOVE`. Character/name actions use the same lookup.
Ignored confirmation during menu movement, empty-name Start and full-name Cross
stay silent. The adapter accepts zero-delay rows; unmatched actions stay
silent.

Successful SE plays suppress repeats of the same cue until simulation time
reaches the stored deadline: **49,999,998 ns** after the play. Equality permits
replay; different cues remain independent. Held simulation time keeps the
deadline held, even while SDL device time advances. The title and lobby pass
their current simulation clocks into the adapter.

Music continues into character selection and name/card creation. The menu
device closes on lobby handoff, exit or attract playback; attract return
restarts it.

### Original title sound event

The title entrance sound executes the original `snd_j_startback.lua` from NDMW
806 through Lua 4.0.1. Its `be:sd("SOUND", nil, -1, "PLAY", "AM_START")`
selects the native stream. Invocation uses the title adapter's entrance point;
general model-event timing is not restored. The original startup script's
PAUSEOFF literal is 240, while the native `ST_CHARA` resume uses zero-based
audio tick 239; that tick is not claimed to match the retail timed-message
deadline. See [Lua integration](lua-integration.md).

### Title pacing

Title pacing begins after audio preroll. A pacing timer started before decoding
creates a frame backlog that rushes the opening blue traces: with presentation
waits disabled, the first 60 title frames then run in 0.084 seconds after
loading, against 1.000 seconds with the pacing origin after preroll. The
pacing check delays each ADX decode by two seconds and checks that the first 60
title frames still take at least one second after loading. The opening's asset
time range is 209 frames at 60 Hz; a synchronized PS2 comparison is needed to
establish exact visual timing parity.

## Stream levels

Streamed tracks apply the recovered pack base volume plus sound volume through
the CRI Q8 attenuation table. Positive levels clamp to zero and levels below
-999 clamp to -999. Each word is `floor(256 * 10^(level / 200))`; the native
gain is that word divided by 256. The two level fields are signed shorts.

| Track | Combined retail level | Native gain |
| --- | --- | --- |
| `ST_CHARA` | -40 | 161/256 |
| `AM_TITLE`, `AM_START` | -30 | 181/256 |
| `ST_LOBBY` | -50 | 143/256 |
| `AM_LOBBY` | -160 | 40/256 |

Resident SFP effects use a separate SFX master/per-voice path; the stream
attenuation formula is not applied to them. This establishes admission and
stream-level behaviour without claiming full audible retail mixing or cue-frame
equivalence.

## Main Lobby first arrival

The arrival adapter resolves three clips through `stagml11.igb`'s sound
reference, NDMW **819**, using the same metadata/bank reader as the title:

| Sound | Retail source | Playback |
| --- | --- | --- |
| `ST_LOBBY` | NDMW ADX 58 | Start at lobby publication; preserve loop samples 1620576–6661052 at 48 kHz. |
| `AM_LOBBY` | NDMW ADX 13 | Start alongside music; preserve loop samples 22976–1879961 at 48 kHz. |
| `mlBEEP01` | Embedded `STAGML01.sfp`, sequence 7 → waveform 7 | Play once after page 48's window finishes closing, at the start of the 90-tick wait. |

Original NDMW 820 layer-setup Lua starts `AM_LOBBY` and `ST_LOBBY` for the
normal hub. The flag-500 introduction calls `PLAY mlBEEP01` between
`funcCloseMessage` for page 48 and `SQ_DELAY01`. `tools/gen_lobby_arrival.py`
checks that ordering against original Lua bytecode and generates the cue name.
The scoped sound pack supplies the ADX references and resident bank index; no
synthesized beep or external replacement asset is used.

The loading worker decodes immutable clips without opening an output device.
Missing/undecodable arrival clips fail destination preparation into Retry/Back.
Publication opens the device on the presentation thread and starts both tracks;
no arrival audio runs during the loading hold. Device failure reports the SDL
error and permits silent arrival. Cancellation frees prepared clips; lobby exit
closes the device before freeing them. Headless arrivals skip audio
preparation.

## STATUS menu cues and sound ducking

Lobby audio includes the original menu cues and CURSOR_NG. Missing lobby menu
records resolve from the title sound metadata using the same named tags and
bank decoder; that preparation decodes only SE clips, not title music, and
opens no extra device. The original CURSOR_NG maps to allse sequence three,
waveform 27 (14,840 frames). Both payload PLAY and named-selector PLAY route
through the owned cue path; unsupported/missing tags fail.

Original SOUND ONFREEZE/OFFREEZE (`39ec10` -> `37d570`) is a gain operation: it
selects records with a live handle, type four and a playing source. Backend
kind three uses attenuation 127/0, while the other path uses zero/default
level. Streams and ordinary type-three effects are unaffected. Native PCM
therefore ducks only existing type-four voices to zero gain and restores their
owned gain; sample positions continue. Newly played menu voices have their own
gain. This is not an audio-device pause or a global music mute.

120 original eligibility/level cases verify that selection with the playback
query and level setter controlled. Native mixer checks keep cursors advancing
during zero gain, and prepared lobby service checks accept freeze/cue/restore
without a device.

The generic controller owner emits a borrowed model/action event without
ticking or mutating the model from its sink. The session forwards it to the
lobby's original zero-delay beSeData lookup; lobby preparation collects its
action mappings as the title does. Focused prepared-controller checks verify
event delivery and detach; dummy-device checks verify `i_stcursor01` LINEUP00 →
CURSOR_MOVE, `i_stfolder` AWINON → WINDOW_OPEN and `i_stmenu01` CLOSE →
WINDOW_CLOSE from NDMW 819.

The five specialized lobby window controllers forward their own ACTION events
through a borrowed sink installed during lobby audio preparation and detached
before audio teardown. This covers STATUS's borrowed message-window peer as
well as original script-owned greeting windows. The callback does not advance
the controller. `test_lobbyui` checks that the authored `SQ_OPEN`/`SQ_CLOSE`
programs emit exactly OPEN/CLOSE and that detaching stops delivery;
`test_audio` resolves those actions to WINDOW_OPEN/WINDOW_CLOSE in NDMW 819.
These checks establish event routing and asset selection; audible output and
retail cue timing are separate validation, and delayed sound scheduling is not
implemented.

## Hub device ownership at publication

Private destination preparation records original PLAY requests without opening
a device. Application commit transfers the source mixer's device to the
destination, stops all source PCM references before old clips can be freed,
then publishes the destination's prepared voice/gain state. The source owns no
device after success. Preparation failure keeps the source clips/device for
Retry/Back. This avoids opening a second lobby device and losing music commands
executed before activation.

Headless SDL dummy application transfers operate through Terminal/Central/Shop;
all six routes, initial-source failure recovery, in-flight shutdown, a headless
GPU two-transfer run and later-source sanitizer recovery pass. This is
ownership and script-state validation, not speaker-level mixing parity.

## Commander Room music

The Commander Room (`stagML02`) prepares its own sound bank (NDMW 815), not the
Terminal's: `ST_COMMA` and `AM_LOBBY` on the music and ambience voices, the
shared lobby cues, the event tracks `AM_OFNI1`, `AM_OFNI2`, `DM_LEOMN`,
`DM_SERAF`, `DM_OFNI`, `QS_HURRY`, `QS_DOIT` and the room's model sounds. A
streamed track past the first two replaces the music voice (or the ambience
voice for `AM_*`). The room's scripts also use `PLAYatPAUSE`/
`querySD ISALLREADY`/`PAUSEOFF` (held start), `BGMSTOP <name>` and
`VOLUMECTL2 "<name>/F<from>/F<to>/F<ticks>"`. `BGMSTOP` stops the music voice
whatever name it carries and `VOLUMECTL2` follows the retail stream ramp, as
described under
[the gameplay rules](#retail-effect-pool-music-and-stop-rules-in-the-gameplay-set).
See [Commander Room](commander-room.md). This is script-state validation, not
mixing parity.

## Model subcommand sound ownership

Prepared generic MODELCTRL owners schedule SETSOUND through typed SCSound
records at the shared subcommand phase. PLAY returns an exact 64-bit native
voice-generation token and the original sound type; only valid type-four
handles stay in the source list. Sequence cleanup requests VOLUMECTL DOWN,
matching `399d10` and the sound receiver's ten-frame fade request; it does not
stop the device or voice. Replaced tokens cannot fade a newer voice. Missing or
unprepared clips fail explicitly; prepared clips with no output device produce
no retained handle. Hub and normal-lobby prepared controllers borrow their
scene's audio owner, which outlives their cleanup.

The linear native fade helper runs from set_clock. Dummy-device tests cover a
half/completed ten-frame fade, held simulation time and voice reuse. This
establishes routing and native ownership, not audible retail fade shape,
positional mixing or cue-frame parity. The published player borrows the same
services with explicit detach/close ordering; see
[player dependencies](controller-services.md#published-player-dependencies)
and [the complete service contract](controller-services.md#effect-sound-and-attachment-services).

## Stage sound catalogue and the gameplay set

A stage's sound set is the record collection in its sound pack, not a per-scene
name list. `src/stagesound.c` (`dw4/stagesound.h`) reads every `beSoundData`
the stage's `[pt.entry]` packs hold: name, `_type`, `_fnameIdx`, `_memoryIdx`,
`_channel`, `_volume`, `_priority`, plus the pack's `beSoundInfo._baseVolume`,
and resolves each `_fnameIdx` through `_fnameList` to a file. A file is a
resident `.sfp` bank (`allse.sfp` is the shared bank in `sbiallse.igb`, others
are embedded in the pack) or an ADX `[pt.entry]` stream. Opening reads records
only; decoding one cue is explicit (`dw4_stagesound_decode`) and can run on a
worker. Findings [#2757](../../docs/findings/findings-2751-3000.md#f2757) to [#2760](../../docs/findings/findings-2751-3000.md#f2760).

| Measured over the shipped stages | |
|---|---|
| igb files / with a sound pack | 2,076 / 96 (39 `stag*` stages and 57 `dng*` dungeons) |
| cues in total | 8,855 (68 to 134 per pack) |
| streamed tracks (types 1, 2) / resident effects (types 3, 4) | 326 / 8,529 |
| records with an unresolved file name | 0 |
| resident effects that decode | 8,433 of 8,529 |

Every streamed track has a valid ADX entry. All 75 distinct sound names that
the decompiled game scripts `PLAY` or `PLAYatPAUSE` exist in some pack
(`tools/verify_stagesound_lua.py`; the dungeon music such as `AM_DUNGE` and
`DG_CAVE1` is in the `dng*` packs). That check does not say which stage runs
which script. `stag0102` (the first mission stage) holds 101 cues: 2 type 1,
1 type 2, 83 type 3, 15 type 4, over `allse.sfp`, `COMMON_BLST`, `scannon`,
`e_ogre`, `e_goburi`, `e_blosso` and `STAG0102.sfp` and four ADX tracks. Each
gameplay stage repeats the shared `allse` cue records (cursor, window, `PC_*`
player, `plWARP01`, impact) beside its own enemy and stage-object banks.

### Sequence events

The resident resolver follows the single-note event `c0 df NOTE BYTE 80 ff`.
The byte after the note is `0x7f` in the menu cues but `0x64` (84 cues), `0x69`
(39), `0x6e` (36), `0x73`, `0x5a` and `0x78` (3 each) in 168 gameplay cues.
`dw4_sfp_resolve_note` accepts 1 to `0x7f` and reports the byte; a resolver
that accepts only `0x7f` leaves those 168 cues silent. The byte is not applied
as a gain: no retail path was traced for it (unconfirmed, [#2759](../../docs/findings/findings-2751-3000.md#f2759)).

96 of the 8,855 cues stay silent, with an explicit `DW4_STAGESOUND_*` code and
never a guess: the two-event `WINDOW_OPEN2`
(`c0 df 2e 7f 00 82 02 df 2f 7f 80 ff`, one per pack; the `00 82 02` wait is
not decoded).

### Bank resolution ([#2760](../../docs/findings/findings-2751-3000.md#f2760))

A pack's banks are named by matching the `beCriSfpData` size, which two banks
of equal size can swap: the `mcannon` and `scannon` banks of `stag0204`,
`stag0304` and `stag0401` (12 cues). A bank's directory row carries its group
tag, unique within a pack, so a cue whose named bank lacks its group resolves
to the bank that holds it.

`stag0403.sfp`'s entry table has a 48 kHz record (fifth entry) among its 24 kHz
ones. Entries carry their own rate; a walk that assumes one rate stops there
and lists four of nine entries (5 cues). Across all 138 banks of the 39 `stag*`
packs, `stag0403.sfp` is the only bank whose listing depends on this (9 entries
against 4). Audible correctness of the cannon pair and the 48 kHz entry is not
compared with retail output.

### Adapter

`dw4_frontaudio_prepare_gameplay(mount, "stag0102.igb")` prepares every effect
and track of a stage by its record name: effects take the cue voices with the
49,999,998 ns repeat window, streams take the music voice (the ambience voice
for an `AM_` name) with the recovered pack-base-plus-sound stream level, and
the stage's `beSeInfoData` model/action table is collected for
`dw4_frontaudio_action`. The typed SCSound leaf
(`dw4_frontaudio_model_play`/`_down`) then resolves any name the stage's
records define. A cue that cannot decode stays silent (stderr trace) and the
stage still prepares. Field stages opened through the lobby loader (`stag0*`,
`stagGF*`) prepare this set instead of the Terminal's lobby list, falling back
to it when a stage has no sound pack. `tools/survey_stagesound` lists a stage's
cues with their type, volume, file and decode result.

`check-fieldstage` asserts that every sound request a field-stage flow makes
(typed SCSound, script `SOUND PLAY` and the cues that model `ACTION` events
look up in the stage's sound table, counted by `dw4_frontaudio_model_stats`)
names a prepared clip: the `stag0101` `hurt` flow makes 14 requests (the music
`ST_DEATH` and ambience `AM_VALLE`, nine `goNATK01` goblin-attack cues and the
three game-over window cues) and the `stagGF03` Leomon room flow 48
(`ST_GOBLI`, `AM_GOBLI`, the boss's `m4SDMG01`/`m4LDMG04`/`m4ACTN03` and
others), none unresolved ([#2778](../../docs/findings/findings-2751-3000.md#f2778)). The flows are headless, so no device plays
them: this proves the routing from enemy and player actions to the stage
catalogue and the name resolution, not audible playback, mixing or timing.

### Dungeon stages ([#2761](../../docs/findings/findings-2751-3000.md#f2761))

The 57 `dng*` packs are catalogued and decode like the field stages, and
`dw4_lobby_prepare_audio` picks the gameplay set for every non-hub world, so a
dungeon needs no audio change. A floor opens only when
`dw4_field_stage_ready` accepts it; the first dungeon (Humid Cave, `dng101b1`
and `dng101b2`) opens from `stag0101` through its own exit regions, and the
floors that are playable are listed in [dungeon floors](dungeon-floors.md).
Opening a floor proves the sound requests of its scripts resolve to prepared
clips, not that they are audible or timed like retail. The Blossomon intro
waits on `querySD ISREADY <name>` (beSound case 12, `FUN_0037dd10`); the
gameplay set answers 1 for a decoded clip ([#2788](../../docs/findings/findings-2751-3000.md#f2788), unconfirmed timing).
`check-dungeonroute` plays the Humid Cave floors for one player and every one
of the second floor's 1,220 sound requests resolves to a prepared clip.

## Retail effect pool, music and stop rules in the gameplay set

The retail rules traced in [sound format](../../docs/engine/sound-format.md#besound-runtime-play-stop-commands-and-the-voice-pool-27622765)
(findings [#2762](../../docs/findings/findings-2751-3000.md#f2762)–[#2765](../../docs/findings/findings-2751-3000.md#f2765)) are followed by `dw4_frontaudio_prepare_gameplay` sets:

| Rule | Native behaviour | How it is checked |
|---|---|---|
| Effect pool | 4 ADX handles (mixer voices 8–11) and 48 sound-bank handles (12–59); a cue whose file is an ADX entry takes an ADX handle, every other effect a bank handle. The first idle handle is used, else the lowest-priority handle not above the cue's priority is stopped and reused, oldest first; no qualifying handle fails the play. | `dw4_voicepool_pick` against the original `FUN_0037c130` instructions (`tools/verify_voicepool.py`, 4,830 randomized pools: index and stop call agree wherever retail is defined; where no handle qualifies the retail result is caller register state, so native fails the play); `test_stagesound` fills all 48 bank handles and checks the 49th reuses the oldest. |
| Repeat window | Every effect type (not streams) is held for 49,999,998 ns after a successful play, per cue. | The admission oracle (473 cases) and `test_stagesound`. |
| Music | A music (type 1) `PLAY` of the current BGM does not restart it; the name is recorded on start and cleared by `BGMSTOP`; ambience (type 2) has no current name. A request for a slot whose track is still playing starts a 10-frame fade-down of that track (unless a ramp already runs), returns, and is retried 11 frames later; the track is stopped by the update once the fade-down passes -209 (0.1 dB), and the retry then starts the new track at `_volume + _baseVolume`. | `tools/verify_streamplayer.py` (the request decision against the original `FUN_0037c2c0`, 10,368 combinations) and `test_stagesound` (BT_SBOSS fades and stops, ST_DEATH starts at the retry). |
| Stop commands | `BGMSTOP`, `ENVSTOP` and `SESTOP` read no cue name and stop the music voice, the ambience voice and the effect handles. Scripts use them with and without a name (216, 7 and 3 requests); both forms are supported. | `test_stagesound`. |
| Stream fades | `VOLUMECTL2` on a music or ambience voice follows the retail ramp: an ease table walked at `(last - first) / frames` entries per 60 Hz frame, level `base + volume + (int)(210 * factor) - 210`, silence once a fade to 0 reaches its target (frame 9 of a 10-frame fade), through the stream level table; a stream whose fade to 0 passes -209 is stopped by the update, as in retail (`beCri::vfunc_27`). Effect fades (`SOUND DOWN` of a handle) stay linear: their level goes through the sound IOP module. | `tools/verify_ramp.py` (original `FUN_003a7590`/`FUN_003a7890`/`FUN_003a7810`, 1,500 armed states, 39,952 frames; assumed EE rounding) and the fade levels in `test_stagesound`. |
| Level | Streams and effects whose file is an ADX entry use `_volume + _baseVolume` through the stream level table (BT_WIN03 plays at 181/256); sound-bank effects stay at full level. | Gain by name in `test_stagesound`; the downstream level setter is the same one the stream oracle covers. |

The title, lobby and Commander Room sets keep their five rotating cue voices;
of these rules they follow only the name-independent
`BGMSTOP`/`ENVSTOP`/`SESTOP` and the stream fade curve.

## Verification

From the port root:

```sh
make check-audio DW4_ROMS=../../local/extracted
python3 tools/verify_title_pacing.py --roms ../../local/extracted
```

- `tools/verify_frontaudio_rules.py --elf ../../local/extracted/SLUS_208.36`
  executes retail instruction regions for repeat admission/deadline creation
  (473 cases), all 1,000 stream-level table packet writes and the level clamp.
  This is a focused oracle; playback/allocation/messenger leaves and the rest
  of `beSound` are boundaries. Findings
  [#781 and #782](../../docs/engine/sound-format.md#repeat-admission-and-stream-levels-781782)
  record the traced paths.
- The callback test checks a loop with an intro, overlapping voices, saturation
  and silence after EOF. The device harness checks mono conversion, sample
  clock advancement/reset and repeated cleanup.
- `tools/verify_audio.py` requires all eleven front-end clips and all three
  arrival clips to resolve, checks the authored music/ambience loops and
  start/cancellation cleanup, and captures each of the three opening movies
  with SDL's disk driver. Every emitted PCM sample after preroll matches an
  independent ffmpeg export. It also checks skip, unavailable-device fallback
  and silent decode-only playback. Tests use dummy/file drivers and do not
  output to speakers.
- The integrated arrival audio harness advances all greeting pages with input
  during transitions, checks the 16-close/90-wait/16-open gap, requires exactly
  one beep before message 49, and checks muted lobby PCM output. It also checks
  distinct cues, exact SE expiry, held simulation time while device time
  advances, and loaded track gains. CPU-only preparation also succeeds with an
  invalid SDL audio driver selected, confirming it does not open a device.
- The audio harness rejects unknown sequence tags, out-of-range selectors,
  truncated banks and the global bank's multi-event sequence 7. It checks every
  loaded front-end waveform and decoded length, including the terminal beep
  mapping.
- `make check-audio` also runs `build/test_stagesound` and
  `tools/verify_stagesound_lua.py`: the whole-game numbers above, `stag0102`'s
  record counts and named cues, the cannon and 48 kHz bank cases, the
  velocity-byte resolution (`plWARP01` = `0x69`, a menu cue = `0x7f`, the
  two-event sequence rejected), and the adapter with a dummy device (effect
  handles, the repeat window, `SOUND PLAY` of a stream on the music voice,
  unknown and undecodable names failing explicitly). ASan/UBSan pass over the
  same test. The `[pt.entry]` reference scanner (`dw4_mount_scan_refs`) bounds
  a digit run to six digits (real references are small; a longer run overflowed
  a signed integer), covered by the same test.
- The 64-voice mixer and the stop/fade rules are also covered by
  `check-fieldstage`, `check-background-focus`, `check-titlecall`,
  `check-lobbyrows`, `check-lobbywalk`, `check-lobbycollision`,
  `check-hubload`, `check-hubsave`, `check-hubstages`, `check-hubnpcs`,
  `check-hubtalk`, `check-hubbank`, `check-hublabo`, `check-hubdisk`,
  `check-hubshops`, `check-hubcnos`, `check-hubprmame`, `check-hubcard`, the
  three `check-hub-boot*` recipes, `check-bootcards`, `check-status-boot` and
  `check-fronttext`.

Full opening playback completes with 1,921 video frames over a 64.098-second
audio clock. A normal windowed launch using dummy video/audio drivers reaches
the main menu, Create Digimon, species selection and name entry with audio
loaded.

To reproduce the reference-capture comparison (requires numpy/scipy):

```sh
python3 tools/verify_menu_capture.py <capture>.mp4 --roms ../../local/extracted
```

## Open items

These checks establish the collection, its file mapping, admission, stream
levels and playback routing from retail records. They do not establish retail
mixing, so general player and enemy sound coverage is **not** claimed.

- This is a bounded adapter, not a general `igAudioContext` replacement. Cues
  follow accepted host menu/character actions, state transitions and model
  ACTION events. Exact retail Action2 sound-event scheduling, delayed sound
  rows and general model-event timing are not implemented.
- Resident effect mixing: the SFX master level, authored bank parameters,
  fades, extra CRI channel adjustments, effect volume/pan and positional
  behaviour are not recovered. The sound-bank backend's use of the event
  (velocity) byte and the handle maximum are open ([#2765](../../docs/findings/findings-2751-3000.md#f2765); the byte is
  unconfirmed, [#2759](../../docs/findings/findings-2751-3000.md#f2759)), and no EE code reads `_channel` ([#2772](../../docs/findings/findings-2751-3000.md#f2772)).
- The sound-bank backend is an RPC into the sound IOP module ([#2766](../../docs/findings/findings-2751-3000.md#f2766)), so the
  two-event `WINDOW_OPEN2` sequence stays silent; its timing is not decoded.
- The retail stream player's music cross-fade and delayed retry
  (`0x0037c2c0`/`0x0037cf30`) are not claimed.
- Pause routing and user volume controls are not implemented.
- Streaming and audio device hotplug/recovery are not implemented.
- A complete live STATUS sound receiver/trace hand-off is missing.
- Audible device output and a synchronized retail/native audio comparison are
  manual validation that has not been done: cue-frame equivalence, audible
  timing, fade shape and mixing are unverified.
