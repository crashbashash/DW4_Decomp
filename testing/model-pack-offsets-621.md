# Where a live vertex buffer sits inside `NDMW.AFS` entry 621's pool

`extract_live_models.py --from <ee-dump>.bin --pack NDMW.AFS:621` located **446**
of the 669 live meshes' vertex buffers in the pack, byte-identically.  Comparing each found
offset with the block boundaries the `_memSize` prefix-sum rule predicts (`igb_pool.py`):

| bytes past the nearest block start | n | block sizes seen | verts seen |
| --- | --- | --- | --- |
| +45 | 213 | 48, 360, 288 | 4, 30, 24 |
| +59 | 171 | 216, 288, 336 | 18, 28, 24 |
| +16 | 36 | 48, 300, 156 | 4, 25, 13 |
| +141 | 12 | 1512, 504, 360 | 126, 42, 30 |
| +20 | 4 | 1008, 972, 648 | 84, 81, 54 |
| +15 | 3 | 1008, 576, 468 | 84, 48, 39 |
| +9 | 2 | 36, 84 | 3 |
| +11 | 1 | 48 | 4 |
| +1557 | 1 | 2256 | 8 |
| +65 | 1 | 276 | 6 |
| +333 | 1 | 1032 | 62 |
| +1 | 1 | 8 | 4 |

**Zero** of the 446 are at a block start, the offset does not correlate with the block's size
or vertex count, and it does not accumulate across the pack (it stays <=141 for all 446 even
though the pack has 12,362 blocks).  So the `_memSize` prefix sum places each block's *region*
correctly, and the stream inside a block begins at a small per-block offset.

The instance to work from (finding [#477](../docs/findings/findings-0251-0500.md#f477)): live mesh `0x0111ca30` -- 55 verts, `_primType` 4,
14 prims -- has its positions in memory block id **38756** (660 B = 55x12 = `_memSize`) at
**block+59**, byte-identical to the live heap; the 59 bytes before it are small dyadic values.
The 446 located offsets are in `model-pack-offsets-621.tsv`.

