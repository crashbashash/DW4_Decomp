# CRI DTR and DTX: data transfer between EE and IOP

DTR (`DTR Ver.1.06`) moves stream data between CRI stream joints (SJ) in 64-byte transfer objects, 32 of them
at `0x4a9310`. DTX (`DTX Ver.1.08`) is its RPC side: 16 objects of 68 bytes at `0x4a9b30`, a SIF RPC server
bound on the EE (`Hello from EE`) and the queues and buffers it uses. Both build with Sony EE GCC 2.96 at
`-O2 -G0` as one whole file each (`cri_dtr`, `cri_dtx` in `units.tsv`, their rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)).

| file | range | strings | data |
| --- | --- | --- | --- |
| `src/cri/dtr.c` | `0x2729e8` up to `0x273078` | `0x4eff20` (build string) up to `0x4f0080` | the init count at `0x4a930c`, the objects at `0x4a9310` |
| `src/cri/dtx.c` | `0x273078` up to `0x273988` | `0x4f0080` (build string) up to `0x4f0180` | `0x4a9b10` (build-string pointer) up to the RPC structures ending at `0x4aa640` |

Each pool starts with its build string, and the next module's build string follows it directly; the first
function after DTR's code is the first to use DTX's data.

## Open questions

- The RPC server's thread function at `0x273128` matches only with its ready flag (`0x4a9b18`) `volatile`;
  it has no approval and stays `unapproved`.
