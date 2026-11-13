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
readers) holds its in-use word, the ADXPD handle at +8, a 44-byte buffer block (`AdxbBuf`) at +72, a
callback at +120, and the three decryption key values at +160, +162 and +164 as 16-bit words.

## Open questions

- Function and field names beyond `ADXB_DecodeHeaderAdx`.
- The 32-byte helper at `0x25d2e0`, between the SKG and ADXB pools, is unreferenced; it most likely ends SKG.
- The buffer-position function at `0x25e018` has no source and links from the retail image (24 words off:
  register choice and where an offset is added).
- `adxb_get_wr` matches only with the handle's PCM buffer typed `short *` and the callback at +120 returning
  `short *`; an `int` buffer address adds the casts that move its loads.
