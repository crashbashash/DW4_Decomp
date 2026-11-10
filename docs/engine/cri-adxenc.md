# CRI ADXENC — the ADX encoder

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
| read-only data | `0x4ee3e8` up to `0x4ee460` | `CRI-MW`, the version string, the DLL name, two `32767.0` constants and `(c)CRI`; the next module's `adxstmf_stat_exec` message follows |
| data | `0x4a5d58` up to `0x4a7ef0` | the init count, the error callback and its object, the build-string pointer, the maximum scale, the `(c)CRI` pointer, then the encoder, predictor and filter tables, which end where the next module's data begins |

Compiling the file whole matters: the block encoder at `0x268960` matches only with the two functions it calls
compiled earlier in the same file, because the calls are then known not to throw.

## Layout

An encoder (`AdxEnc`, 0x2f8 bytes) starts with four status bytes (in use, state, channel count, ended), then
its input streams, its output stream, the counts and positions of the encode, two filter pointers at +0x80,
the previous samples of each channel and the key. A predictor (`AdxEncPredictor`) is 12 bytes, a filter
(`AdxEncFilter`) 0x90 bytes.

Destroying an encoder clears the four status bytes with one word store, which the source writes as a 4-byte
`memset` (inline under GCC). Creating one sets the in-use byte alone, and the server tests it alone.

## Open questions

- The functions have no names from strings beyond the module's; the fields are named from use.
- The first function, at `0x2674e8`, is an unreferenced `return 0` that could instead end the ADXB wrappers
  before it.
- Seven functions have no source and link from the retail image, among them the create function at
  `0x2692c8` (retail has three padding `nop`s in its free-slot search loop that this compiler does not emit
  for the drafted loop) and the end-flag setter at `0x269630`, where retail loads the constant 1 once for both
  the store and the return value.
