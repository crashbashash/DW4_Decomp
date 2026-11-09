# Digimon World 4 — decompilation

Guidance for AI coding agents (and a summary for people) working in this repository. The method
contributors follow is in [CONTRIBUTING.md](CONTRIBUTING.md); read it first. This file holds the
strict form of it: what makes a function matched and readable, and the rules for driving the build,
delegating work and reporting a result.

The goal: recover the PS2 release of **Digimon World 4** — USA `SLUS-20836` — as readable,
evidence-named source that rebuilds to a byte-identical retail ELF. Run every command from the repository root; paths here are repository-relative.

## Hard rules

- **Privacy.** Nothing that identifies a developer's machine or account goes into the repository,
  generated files or commit messages: no absolute home/container paths, hardware
  models, driver/kernel versions, device nodes, user/host names, e-mail addresses, credentials, or
  emulator-driving facts (socket paths, display numbers). State requirements, not "this host" facts
  ([host details policy](docs/host-details-policy.md)).
  Install the hooks once per clone (`scripts/install_git_hooks.sh`), run `make hygiene` before every
  commit or push, never `--no-verify`, and fix a reported line rather than allow-list it unless it is a
  deliberate fixture.
- **Assets.** No game binaries or extracted assets in the repository (disc images, executables, IRX,
  BIOS, memory cards, savestates, screenshots, small extracts), and no retail code as assembly: the
  generated `asm/` tree is gitignored and a function's retail instructions are never committed in any
  wrapper. The one exception is a routine the owner has approved as hand-written assembly: its `.S`
  source is in `src/` with a row in `config/assembly-sources.tsv`, approved after the owner reviewed
  the evidence that its original source was assembly
  ([assembly sources](docs/engine/assembly-sources.md)). Only the owner approves a row. An agent may
  write one only when the owner has explicitly told it to add that specific routine, after reviewing
  its evidence; it never adds one on its own initiative or as part of a broader request ("match
  everything", "clear the queue").
- **Approved `asm` and `volatile`.** Inline `asm` and `volatile` in C and C++ take the same approval as a
  `.S` file: a row in `config/source-approvals.tsv`, added after the owner reviewed the evidence that the
  original source used it ([source approvals](docs/engine/source-approvals.md)). Only the owner approves a
  row. An agent may write one only when the owner has explicitly told it to add that specific function; it
  never adds one on its own initiative or as part of a broader request.
  Recovered metadata is fine. The retail executable is reached through the gitignored
  `orig/<GAMEID>/`. Never force-add, and never modify a disc image: work on a copy.
- **Scope.** The repository holds the decompilation and what it needs: source,
  build tables, tools, evidence and reference documentation. These do not belong in it and go to the
  workspace's archive outside Git: agent handoffs, session logs and per-wave or per-shard work
  reports; changelogs and accounts of how the repository was reorganised; player-facing guides and
  catalogues; tools that drive or read a running emulator, and
  their captures. Write what a wave learned into the topic's document, not a dated log.
- **One build at a time.** At most one full build (`make check`, `make link`, `make objdiff`) runs on a host, from the integrating session, never from a sub-agent.
  Where several sessions share a host, take a lock: `flock <shared lock file> make check`.
- **Sub-agents write only to a scratch directory outside the repository**, never `src/`, `config/`, `asm/`,
  `docs/` or the repository root. The integrator promotes work (see Delegated work).
- **Commits.** Sync with `git fetch && git merge origin/main` (never rebase shared history).

## Layout

- `src/` recovered source (`src/third_party/` is stock zlib, libpng and Lua, never edited;
  [README](src/third_party/README.md)), `asm/` the retail split, one unit per function, generated from
  your executable and never committed (`make asm`; `make check` writes it when it is
  missing or stale), `include/dw4/` shared headers
  (`reflected.h` is generated), `tools/` build and matching tools ([README](tools/README.md)),
  `scripts/` analysis, `data/` recovered data, `lua/` the game's Lua scripts decompiled and filed by
  stage (`scripts/lua_tree.py` resolves a pack entry and chunk to its file), `docs/` the
  documentation ([index](docs/README.md)).
- The build follows the [dtk-template](https://github.com/encounter/dtk-template) layout
  ([build system](docs/build-system.md)): each version's address-bearing tables live in
  `config/<GAMEID>/` (`config.yml`, `symbols.txt`, `units.tsv` as the splits, `regions.tsv`, `data-owners.tsv`, `unit-*`, `exceptions.txt`,
  `names/`, `build.sha1`); project-wide policy files stay in `config/` (`debt-baseline.json`, `typed-*`); `make` extracts the
  executable from a disc image in `orig/<GAMEID>/`, and `python3 tools/download_tools.py` fetches the
  pinned compilers into `local/`.
- Keep documentation with its topic and index it from the owning folder's README. A document states the
  current state: no dated sections, update notes or accounts of how a result was reached (Git keeps the
  history); when something changes, rewrite the passage that describes it. Preserve unrelated changes.
- A document never records which functions match or lack source, nor tallies of matched functions or
  bytes: `data/check-categories.tsv` and `PROGRESS.md` own that, and a copy in prose goes stale. Describe
  behaviour, layout and why a shape compiles as it does. Output generated from those tables is fine.
- A method document, one on how to match or check code rather than what a part of the game does, names no
  function: it gives the source shape and its instructions, since an example goes stale when the function is
  renamed or respelled and nothing updates it. Placeholders are `FUN_XXXXXXXX` and `0xVA`. A document naming
  functions must be a subject document listed in `config/doc-subjects.txt`, and every name it uses must exist in
  the symbol table, so a rename updates the documents with it. `scripts/check_doc_function_names.py` enforces both
  in `make hygiene` and the pre-commit hook.

## Decompilation

Read [naming](docs/engine/naming.md), [asm-body matches](docs/engine/asm-body-matches.md) and
[matched and readable](#matched-and-readable) before module work. Byte matching and readability are
**separate jobs**: a function lands once it matches, in whatever form it matched, and a later pass can
make it read well. Either can be done alone.

- **One translation unit, one profile.** Every method of a class, and every function of a folded unit,
  verifies under the same compiler and flags. A per-function row that disagrees with its siblings is
  provisional: note it in the topic's open questions, re-attempt under the sibling profile, and count it
  separately until resolved. Never pin a profile to make one function pass while its unit says otherwise.
- **Exception metadata is part of the match.** Cleanup scopes are RAII holder classes whose destructor copies
  `config/<GAMEID>/unit-objects.json` names (`emitted`, `duplicates`, `externals`, `exceptions`, and
  `stripped` for an out-of-line destructor copy the retail linker dead-stripped);
  [emitted functions](docs/engine/emitted-functions.md). A stock library's rows
  (`whole_file`, `data`, `symbol`) are measured by `tools/whole_file_rows.py`, never typed.
- **Progress is fully matched source.** The headline is `functions.fully_matched` and
  `code_bytes.fully_matched` in `docs/progress.json`: units `make check` classifies as `match`, plus
  owner-approved assembly sources, whose original was written in assembly. `fully_verified` is the
  `match` count alone, which the regression rule compares. The code-bytes-identical figure adds the
  verification debt, and is reported second, never as the headline. Nothing else earns credit: no
  partial score for a near miss (objdiff's fuzzy percentage included), and no figure summed with asm
  bodies.
- **No asm bodies.** A function without C has no file in `src/`: it links from the retail image and reads
  from the generated `asm/`. Its retail instructions wrapped in an `asm` function recover nothing and are
  not committed; `make check` files any that appear as `asm-body`, counted in no figure
  ([asm-body matches](docs/engine/asm-body-matches.md)). The work queue is every symbol without a
  definition in `src/`: `python3 tools/m2c_batch.py` drafts them (gcc target for Sony EE GCC units;
  `--write` adds a draft only when the C verifies). When a compiler is added, re-attempt the functions in
  its blocks first. Blocks built by a compiler build the project does not have stay without source.
- **No unapproved inline `asm` or `volatile`.** Either passes the byte check whether or not C could produce
  the same bytes, so it can hide a spelling nobody found. Find the C. A function using one without a row in
  `config/source-approvals.tsv` is filed as `unapproved`: it links, but it is not matched
  ([source approvals](docs/engine/source-approvals.md)). Only `sync` and `ei` need no row, as C cannot spell
  them. A `volatile` that only pins when a load is scheduled, where retail reads once, is never approved.
  `python3 tools/sourceapprovals.py --list` is the queue, and `tools/inline_asm.py --test <source>` shows
  which `asm` statements can go. `tools/progress.py --debt-check` also fails on any rise in `inline_asm.other`,
  which counts every statement without a row for each function it reaches; `sync`, `ei` and an approved
  statement are not debt.
- **Names** come from the strongest evidence there is. Where no source survives, a best guess from what the function,
  variable or struct does is a valid name; doubt about it goes in the topic document's open questions. Apply overlays with
  `tools/apply_names.py` (dry run, then `--apply --check`).

### Matched and readable

**Matched** is one condition: the function verifies byte-identical under its **translation unit's
profile** in `config/SLUS-20836/units.tsv` (compiler, flags, exception mode;
[build profiles](docs/engine/build-profiles.md)), including the C++ exception metadata. A function that
matches only under a per-function override in `config/SLUS-20836/unit-flags.tsv` / `unit-compilers.tsv`
is `foreign-profile` debt, not a match, and one using inline `asm` or `volatile` without an owner approval
is `unapproved` debt. That is all a match needs: decompiler output, `FUN_` names and
raw casts can land as they are.

**Readable** is a separate pass over matched code, measured by the README's Readable column. A function
is readable when all of these hold:

1. It sits in its module translation unit (`src/<module>/<Class or topic>.c|.cpp`), in retail address order.
2. Every identifier is a recovered name: from RTTI, strings or callers where they exist, otherwise a best
   guess from what the thing does. What it does should make the name obvious, so source never justifies a
   name: doubt about one goes in the topic document's open questions. A name
   holding an address is not recovered: it says where a thing is, not what it is. That goes for
   functions, variables, structs and classes alike; a type also needs a real name, not a placeholder
   such as `S`, `Obj` or `Info176`.
3. No m2c idioms (`temp_*`, `var_*`, `argN`, stack-offset locals such as `sp5C`) and no raw offset casts where
   `include/dw4/reflected.h` names the field; real structs, enums and control flow; a comment
   appears only when it is necessary, for what the code cannot say, and it stands alone: no pointer
   to another document or tool, and no account of how the code was recovered.
4. A shape found by a permuter, flag sweep or random walk carries
   `/* matching construct: <tool> — <what moved> */` at the affected line.

An owner-approved assembly source counts as readable once it has a recovered name: its row in
`config/assembly-sources.tsv` records the evidence that no C reproduces it.

When two spellings match the same bytes, keep the more readable one. A function that cannot be
written as C yet stays without a file: its retail instructions wrapped in an `asm` function recover
nothing and are not committed ([asm-body matches](docs/engine/asm-body-matches.md)).

C++ cleanup scopes are written as RAII holder classes whose destructor copies
`config/SLUS-20836/unit-objects.json` names ([emitted functions](docs/engine/emitted-functions.md)).
Strings are named by their text, with no prefix; offset members are decimal `fNN` and temporary; one shared definition
per class lives under `include/dw4/`.

### Completion and regression

A task is complete only when the report quotes these four lines verbatim from runs on the final tree.
The pre-push hook does not repeat them (it checks host details and the oracle-change rule); the oracle
runner runs them again on every pushed commit ([oracle runner](docs/engine/oracle-runner.md)).

1. `make check` — the `cover :` summary, `0 mismatch` in its `(N not matched: M mismatch, D debt)` line when
   that line appears, and the `match` count at or above `functions.fully_verified` in the parent commit's
   `docs/progress.json`.
2. `make link` — `linkcheck: BYTE-IDENTICAL — the relinked section matches retail exactly`.
3. `make typed-check` — `typed coverage: N recovered accesses, baseline matches` (or the re-recorded baseline
   with the reason).
4. `make hygiene` — `check_host_details: clean`.

Run `make check-fresh` and `make link-fresh` (cache ignored) before any commit that changes
`config/<GAMEID>/units.tsv`, `unit-*`, `extent-overrides.tsv`, `jumptables.txt`, `compiler-runtime-symbols.tsv`
or `tools/`, and before a milestone. A drop in the `match` count is a regression, and that includes a function moving to `unapproved`, such as
through a new `volatile`: find the cause, never
explain it away. A debt counter that rises (`tools/progress.py --debt-check`) is re-recorded only with a
reason (`--debt-baseline --allow-increase "<reason>"`; [debt ratchet](docs/engine/debt-ratchet.md)).

### Extents, splits and regenerated artifacts

Changes to `config/<GAMEID>/extent-overrides.tsv` or `data/function-extents.json`, symbol splits/merges and
a regenerated `config/<GAMEID>/symbols.txt` are reviewed in the commit message with before/after counts
(functions, laid-out bytes, truncated units) and how the denominator changed. Regenerate, never hand-edit:
`config/<GAMEID>/{symbols,layout,jumptables,syscalls}.txt`, `data/`, `lua/`,
flag tables and progress blocks
(`scripts/sync_data.sh`, `make progress`).
Update topic documents, generated views and prose in the same commit.

### Tools and limits

- One Ghidra process at a time; reuse an analysed project with `--no-analysis`. Check function shape with
  `mipsel-linux-gnu-objdump`; decompiler output alone is not proof.
- `python3 tools/m2c_batch.py --jobs 8 …`; never invoke imported `m2c.main` concurrently. `make check`/`make link`
  already run in parallel.
- objdiff: `make objdiff` (one unit per function; base = the function compiled as
  `tools/check.py` extracts it, target = its retail words with relocations from `tools/target_asm.py`).
  Functions without source are target-only units there, so they read as unmatched. objdiff's percentage is a diff aid; `tools/check.py` and `tools/linkcheck.py`
  are the oracle.
- Callers and callees of retail functions: grep `asm/` and `src/` for the symbol, or the Ghidra xref scripts
  (`scripts/dump_xrefs.py`, `scripts/xrefs_multi.py`).

## Delegated work

Sub-agents draft; the integrator verifies and promotes. A sub-agent report lists, per function: address,
symbol, candidate path (in its scratch directory), the exact `tools/check.py --function` (or `tools/verify.py`)
command with flags, compiler path and SHA-256, the verifier's last line, and any `config/<GAMEID>/unit-*` rows
the match needs. The integrator re-runs that command before promoting anything and treats an unreproduced
claim as unmatched. Brief sub-agents with what matched and readable mean; they never run full builds and never write into the
repository.

## Retail-game work

Read [testing tools](testing/tools.md), the [game reference](docs/reference/game-reference.md),
[stage selection](docs/systems/dev-stage-debug-menu.md) and the documentation for the build under test.
Live-memory claims need a running-game or offline savestate read; a savestate carries the loaded world, so
test a disc change by booting the disc and loading the stage afterwards. Menus accept stick and D-pad; in the
world only the stick moves the player. Emulator-driving tools and their notes stay outside the repository.
