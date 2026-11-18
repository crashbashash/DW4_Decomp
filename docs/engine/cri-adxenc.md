# CRI ADXENC: the ADX encoder

ADXENC (`ADXENC/PS2EE Ver.1.09` at `0x4ee3f0`, and the DLL name `ADXENC.DLL Ver.1.09` its version query
returns) encodes 16-bit PCM read from input streams into ADX blocks written to an output stream. It keeps 8
encoders of 0x2f8 bytes, 16 predictors and 16 filters, derives the encryption key from a key string
(`CRI-MW` is the default), and runs every active encoder from a server step. The source is
`src/cri/adxenc.c`. It builds with Sony EE GCC 2.96 at `-O2 -G0` as one whole file (`cri_adxenc` in
`units.tsv`, its rows in `unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x2674e8` up to `0x269c30` | one call cluster: the API near the end calls the init and key functions at the start; the functions from `0x269c30` use the next module's data |
| read-only data | `0x4ee3e8` up to `0x4ee460` | `CRI-MW`, the version string, the DLL name, two `32767.0` constants and `(c)CRI`; the next module's `ADXSTMF_ExecHndl` message follows |
| data | `0x4a5d58` up to `0x4a7ef0` | the init count, the error callback and its object, the build-string pointer, the maximum scale, the `(c)CRI` pointer, then the encoder, predictor and filter tables, which end where the next module's data begins |

Compiling the file whole matters: the block encoder at `0x268960` matches only with the two functions it calls
compiled earlier in the same file, because the calls are then known not to throw.

## Layout

An encoder (`AdxEnc`, 0x2f8 bytes) starts with four status bytes (in use, state, channel count, ended), then
its input streams, its output stream, the counts and positions of the encode, two filter pointers at +0x80,
the previous samples of each channel and the key. A predictor (`IirFilt`, CRI's `_iir_filt`) is 12 bytes, a filter
(`PredictFilt`, CRI's `predict_filt`) 0x90 bytes; the handle `AdxEnc` is `ADX_SJENC`, all three named from the 2002 SDK STABS ([CRI ADXB](cri-adxb.md#layout)).

Destroying an encoder clears the four status bytes with one word store, which the source writes as a 4-byte
`memset` (inline under GCC). Creating one sets the in-use byte alone, and the server tests it alone.

`ADXSJE_Create` computes the samples per block as `(f80 - 2) * 8 / f84` from the two fields it has just
stored, and the end position as that count rounded up from `0x7fff0000`. GCC keeps the divide (with its
divide-by-zero check) for the stored count but folds the other uses to 32, which leaves the dead `li t3,32`
retail has. Both functions follow `adx_sje.c` of the Resident Evil 4 decompilation's CRI library (ADXT/GC 9.31,
carried as `src/cri/re4` in [Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation)).
`adxsje_output_header` writes each header item through a macro that checks the write, jumps to one
`err:` label (the shared `move v0,zero` before the epilogue) and adds the item's size to the length; the
length starts after the signature and the header size, which are written apart, and the result adds their
four bytes back.

## Open questions

- The functions have no names from strings beyond the module's; the fields are named from use. CRI's names
  come from the 2002 SDK's `adx_sje.o` ([recvx-decomp-cri](https://github.com/SkeletonPicture/recvx-decomp-cri))
  and the CRI names the Persona 4 decompilation matched in unstripped PS2 builds
  ([Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation), `docs/cri/proven_names.json`).
  Medium: `adxsje_output_sdata`, `ADXSJE_SetExtString` (SDK order), and the AINF setters
  `ADXSJE_SetAinfOutputVol`, `ADXSJE_SetAinfOutputPan`, `ADXSJE_SetAinfDataId`, `ADXSJE_ClearAinf` and
  `ADXSJE_SetCommonInf` (that list, same order; it also has an `ADXSJE_SetAinfDataIdMem` this build lacks).
  The data take the SDK's names: `adxkey_init_cnt`, `AdxGainDataMax`, `cri_str`, `adxsje_obj`; the two error
  callback words are named like them from use (`adxkey_err_func`, `adxkey_err_obj`). The two strings around the
  build string are extern names of their text (`CRI_MW`, `text_ADXENC_DLL_Ver_1_09_Oct_6_2004`): written as
  literals they would precede the build string, which no function of the file reads, and the file defines none
  of its data, so the build string has no place in its source yet.
- The file opens with a static copy of the SKG key functions under the SDK's `ADXKEY_` prefix: `ADXKEY_NopFunc`,
  `ADXKEY_EntryErrFunc`, `ADXKEY_CallErrFunc`, `ADXKEY_Init`, `ADXKEY_Finish`, `ADXKEY_GenerateKey`,
  `ADXKEY_GetDefKey`, `ADXKEY_GetNextKey`. `ADXKEY_Init`, `ADXKEY_Finish`, `ADXKEY_GenerateKey` and
  `ADXKEY_GetDefKey` are the SDK's own static names in this file; the other four are the SKG library's names in
  that prefix (medium; alternative: the SKG names with a file prefix, as the RE4 GameCube table spells this
  file's copy of the SKG data `skg_*`).
- The block encoder at `0x268188` matches only with the sample filter at `0x267e50` defined above it in the
  file: with the filter only declared, one branch becomes `blezl`.
