# `flags/` — flag & progression data

The authoritative mapping of every flag operation in the game's Lua. The big per-flag xref is
kept as **TSV**, not markdown, so it stays machine-readable and greppable.

| File | What | Kind |
|---|---|---|
| [`flag-map.md`](flag-map.md) | Save-flag encoding + story-state map, derived from real save diffs. **Overrides the heuristic labels** below where they disagree. | hand-written |
| [`flag-meanings.md`](flag-meanings.md) | Curated story flags + heuristic labels, grouped by category (human-readable). | hand-written / curated |
| [`flag-meanings.tsv`](flag-meanings.tsv) | The same per-flag meaning + confidence + evidence, machine-readable. | generated |
| [`flag-xref.tsv`](flag-xref.tsv) | **Every flag operation** in the decompiled Lua — one row per operation. The canonical cross-reference. | generated |

Generators (in `scripts/`):

```sh
python3 flag_xref.py      lua docs/systems/flags  # -> flag-xref.tsv
python3 flag_meanings.py  lua docs/systems/flags  # -> flag-meanings.{md,tsv}
```

## `flag-xref.tsv` schema

Tab-separated, one row per operation, with a header row:

| column | meaning |
|---|---|
| `op` | `set` / `chk` (runtime `FLGset` / `FLGisOn`), `folder:IS/SET/CLR` (persistent folders), `ctr:set` / `ctr:get` (counters) |
| `flag` | the flag id (integer), or `COUNTER <n>` for counters |
| `kind` | `runtime` / `folder` / `counter` |
| `value` | the value written (writes) or empty (reads) |
| `entry` | AFS entry (Lua pack) |
| `stage` | stage name for that entry |
| `chunk` | the Lua file within the entry |
| `line` | line number |
| `text` | the source line (truncated) |

Query it with anything — e.g. all writes to flag 375:

```sh
awk -F'\t' '$2==375 && $1=="set"' docs/systems/flags/flag-xref.tsv
```

## Reading the flags

The corpus and tables now use stock Lua signed decoding. Ordinary script flag
writes/checks use **0/1**; `FLGisOn` returns the retail unsigned byte, so a
stored -1 would be 255, not false. Do not infer an inverse save encoding from
the old -1/0 decompilation. The [historical save map](flag-map.md) retains raw
observations with a correction notice.

- Stage-entry scratch loops include **100..319**, cleared to **0**.
- Shop level predicates use flags **908/909/910** and levels **16/46/76**.
- Persistent folders occupy **0..11**, independently of runtime flag IDs.
  The quest-board completion script writes **folder 11**.
- Counter and difficulty literals also changed with the signed correction.

Curated runtime IDs and thresholds were corrected in the generators. See the [numeric audit](../../engine/lua-numeric-audit.md)
before using older prose as an implementation contract.
