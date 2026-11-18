# CRI ADX before ADXB: ADXAMP, the AC-3/AHX glue, the AIFF and AU readers, and SKG

Six CRI files between the game's `main` and ADXB (`0x25b248` up to `0x25d300`), each compiled as one whole file
with Sony EE GCC 2.96 at `-O2 -G0 -ffunction-sections` (their rows in `units.tsv` and `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)). The readers share ADXB's handle in
`include/dw4/cri/adxb.h`.

| file | unit | range | what it is | evidence |
| --- | --- | --- | --- | --- |
| `src/cri/adxamp.c` | `cri_adxamp` | `0x25b248` up to `0x25b968` | ADXAMP: per channel, the peak amplitude of each frame of decoded samples, written as records to an output stream joint; sixteen handles | its init count `0x498730` and handle table `0x498738` (16 × 0x30) open the CRI data; the AC-3 hooks follow at `0x498a38` |
| `src/cri/adxac3.c` | `cri_adxac3` | `0x25b968` up to `0x25bb50` | ADXB's AC-3 glue: input joint, decode length, end of supply and the decode step go to hooks the AC-3 decoder registers; the AC-3 header (mono 16-bit 48 kHz, 1536-sample frames) and the `0x0B77` sync check | its four hook words `0x498a38`..`0x498a44` |
| `src/cri/adxahx.c` | `cri_adxahx` | `0x25bb50` up to `0x25bc40` | ADXB's AHX glue: the same four hooks for the AHX decoder (decode length in 96-sample units) | its four hook words `0x498a48`..`0x498a54`, after AC-3's |
| `src/cri/adxaiff.c` | `cri_adxaiff` | `0x25bc40` up to `0x25c5a0` | the AIFF reader: header parse, `FORM`/`AIFF` check, header decode, 16-bit and 8-bit decode steps | its strings `FORM`, `AIFF` at `0x4ecfa8` |
| `src/cri/adxau.c` | `cri_adxau` | `0x25c5a0` up to `0x25d020` | the Sun/NeXT AU reader: header parse, `.snd`/`.sd` check, header decode, 16-bit, 8-bit and u-law decode steps | its strings `.snd`, `.sd` follow AIFF's; its u-law table `0x498a58` follows the AHX hooks |
| `src/cri/skg.c` | `cri_skg` | `0x25d020` up to `0x25d300` | SKG (`SKG/PS2EE Ver.0.64`): the three ADX keys from a key string through a 1024-entry table, the default string `CRI-MW`, and the ADXKEY callback and seed step | its build-string pointer `0x498c58` follows the u-law table, then its init count and the ADXKEY callback words; its build string, table `0x4ecff8` and `CRI-MW` follow `.sd`; ADXB starts at `0x25d300` with its own data |

ADXB's decode step calls `ADXB_ExecOneAc3`, `ADXB_ExecOneAhx`, `ADXB_ExecOneAiff` and `ADXB_ExecOneAu` by the
handle's format; the readers' header decoders store the sample format in `pcmfmt`, which their `ExecOne`
steps switch on. No AC-3 or AHX decoder registers its hooks in this game, so those words stay null; ADXB
passes the AHX handle to the key hook of its own data.

## Open questions

- Names come from behaviour, in the ADXB, ADXAMP and SKG API styles. The AC-3 slot `0x498a44` is never read.
  SKG's names are the Street Fighter III 3rd Strike libadxe's ([3s-decomp](https://github.com/crowded-street/3s-decomp)),
  by order and size (medium): `SKG_NopFunc`, `SKG_EntryErrFunc`, `SKG_CallErrFunc` and `SKG_GetNextKey` replace
  guesses in the ADXKEY style; its words take the RE4 GameCube table's names for the same library
  ([adonis-singh/re4](https://github.com/adonis-singh/re4), `config/G4BE08/sym_map.tsv`): `skg_init_count`,
  `skg_err_func`, `skg_err_obj`. The encoder's static copy keeps the `ADXKEY_` prefix ([ADXENC](cri-adxenc.md)).
- SKG's build string pointer is data no code reads; it links from retail.
