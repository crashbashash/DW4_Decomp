# CRI ADXB: the ADX decoder core

ADXB is the decoder-handle layer of CRI ADX: 16 handles of 260 bytes, each owning an ADX predictive
decoder (ADXPD) handle and a buffer block. It decodes the ADX stream header (`ADXB_DecodeHeaderAdx`, with
the AHX check `can't play AHX data by this handle`), keeps each handle's channel, rate and key values, and
runs the per-voice decode step from a server loop over the handle table. The source is `src/cri/adxb.c`. It
builds with Sony EE GCC 2.96 at `-O2 -G0` as one whole file (`cri_adxb` in `units.tsv`, its rows in
`unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x25d300` up to `0x25e668` | the SKG module (`SKG/PS2EE Ver.0.64`, its data `0x498c58` up to `0x498c64`) ends before it; the file opens with the init that starts ADXPD and SKG and clears the handle table; the SPSD reader starts at `0x25e668` with its own strings |
| strings | `0x4ed800` up to `0x4ed850` | the header-decode and AHX messages; `SPSD` follows at `0x4ed850` |
| data | `0x498c68` up to `0x499cc0` | three hook words, the default key values, then the handle table at `0x498c80`; the WAV reader's data starts at `0x499cc0` |

Compiling the file whole matters: the per-voice decode step matches only with the function it calls first
compiled earlier in the same file, because the call is then known not to throw and one branch takes its
likely form.

## Layout

A handle (`AdxbObj`, 260 bytes, declared in `include/dw4/cri/adxb.h` for ADXB and the SPSD and WAV
readers) is CRI's `_adx_intbuf`, grown from the 2002 SDK's 176 bytes. Its members up to +154 and the decode
request `AdxDecPara` (`_adx_dec_para`) at +72 take the member names of the STABS in the 2002 SDK's `libadxe.a`
(members `adx_bsc.o`, `adx_bahx.o`; high): `hdcdflag`, `xpd`, `code`, `bps`, `blknsmpl`, `lp_ins_nsmpl`,
`lp_spos`…`lp_eofst`, `maxnch`, `getwrfunc`/`getwrobj`, `addwrfunc`/`addwrobj`, `total_ndecsmpl`, `curwpos`,
`ndecsmpl`, `ndeclen`, `fmttype`, and the keys `k0`/`km`/`ka`. The 2002 `ADXB_GetOutBps` reads the sample format at
+154, this build at +156: `cdctype` moved by the new `def_fmttype` at +154. The members after the 2002 layout take
their names from the functions that read them (`ADXB_GetAinfLen`, `ADXB_GetDataId`, `ADXB_GetDefOutVol`,
`ADXB_GetDefPan`, `ADXB_EntryDecFunc`; medium, matching the RE4 library's `ainf_len`, `def_outvol`, `def_pan`,
`cb_func`/`cb_obj`): `ainf_len`, `dataid`, `def_outvol`, `def_pan`, `decfunc`/`decobj`, `cb_ndeclen` (the
length at the last `decfunc` call; alternative RE4's `cb_nbyte`), and `xp_key`/`xp_km`/`xp_ka` for the snapshot of
the decoder's keys (alternative RE4's `extprm[3]`).

The same STABS name the other ADX objects: the encoder `AdxEnc` (`ADX_SJENC`, with `predict_filt` as
`PredictFilt` and `_iir_filt` as `IirFilt`, `adx_sje.o`), the header records in `adxhdr.c` (`ADXHDR`,
`ADXLOOPPRM`, `ADXPLYPRM`, and `ADXHINFO` for `AdxtHdrInfo`, `adx_hdr.o`; CRI's own `ADXT_GetHdrInfo` stores the
loop count in `lptype`), `adxwav.c`'s `tWAVEFORMATEX` (`adx_bwav.o`), `AdxSjdObj` (`ADX_SJDEC`), the partition
info's `type`/`rev`, the DTR line counts `srclin`/`dstlin`, LSC's `ck`, `reqsct` and `errcnt`, HTCI's `end_fg`, and
the SJ function table's first three slots (`_sj_vtbl`). The encoder's 2004 members after `ka` are named from
`ADXSJE_SetAinf*` (`ainf_flg`, `dataid`, `outvol`, `outpan`; medium).


## Open questions

- Names come from the Street Fighter III 3rd Strike decompilation's libadxe
  ([3s-decomp](https://github.com/crowded-street/3s-decomp), order and size), the RE4 GameCube symbol table
  ([adonis-singh/re4](https://github.com/adonis-singh/re4), `config/G4BE08/sym_map.tsv`) and the CRI names the
  Persona 4 decompilation matched in unstripped PS2 builds
  ([Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation), `docs/cri/proven_names.json`).
  Medium, by position in those lists: `ADXB_SetDefPrm`, `ADXB_GetLpStartOfst`, `ADXB_GetAinfLen`,
  `ADXB_GetDefOutVol`, `ADXB_GetDataId`, `ADXB_RestoreSnapshot`, `ADXB_SetExtString`, `ADXB_SetDefExtString`,
  `ADXB_ExecHndl`, `adxb_dec_cb_proc`. Medium from behaviour: `ADXB_ResetDefFmt` (alternative `ADXB_ClearDefFmt`)
  and `ADXB_EntryDecFunc`, named like `ADXSJD_EntryDecFunc` above it (alternative `ADXB_SetCbDec`).
- `AdxbObj` +158 and +248 have no reader: +158 is a gap before the keys, +248 is only cleared with
  `ndecsmpl`, `ndeclen` and `cb_ndeclen` in `ADXB_EntryData`. No source names +248 (the 2002 SDK's 176-byte
  `_adx_intbuf` predates the layout), so it carries the neutral reserved name `rsv`, which claims only that.
  `AdxSjdObj` keeps `hdr` for the 64-byte header copy that the 2002 STABS call `spsdinfo`, as this
  build copies every format's header there.
- `SKG_GetNextKey` (`0x25d2e0`), between the SKG and ADXB pools, is unreferenced; 3rd Strike's order puts it
  last in SKG.
- `adxb_DefGetWr` matches only with the handle's PCM buffer typed `short *` and the callback at +120 returning
  `short *`; an `int` buffer address adds the casts that move its loads.
