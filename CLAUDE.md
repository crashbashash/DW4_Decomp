# Digimon World 4 decompilation

Rules for AI coding agents in this repository: the strict form of [CONTRIBUTING.md](CONTRIBUTING.md), which
you read first. The goal is to recover the PS2 release of **Digimon World 4** (USA, `SLUS-20836`) as
readable, evidence-named source that rebuilds to a byte-identical retail ELF.

## Hard rules

- **Privacy.** Nothing that identifies a developer's machine or account goes into the repository,
  generated files or commit messages: no absolute home/container paths, hardware models, driver/kernel
  versions, device nodes, user/host names, e-mail addresses, credentials, or emulator-driving facts (socket
  paths, display numbers). State requirements, not "this host" facts
  ([host details policy](docs/host-details-policy.md)). Install the hooks once per clone
  (`scripts/install_git_hooks.sh`), run `make hygiene` before every commit or push, never `--no-verify`, and
  fix a reported line rather than allow-list it unless it is a deliberate fixture.
- **Assets.** No game binaries or extracted assets in the repository (disc images, executables, IRX,
  BIOS, memory cards, savestates, screenshots, small extracts), and no retail code as assembly in any
  wrapper (see [No asm bodies](#decompilation)); the generated `asm/` tree is gitignored. Recovered
  metadata is fine. The retail executable is reached through the gitignored `orig/<GAMEID>/`. Never
  force-add, and never modify a disc image: work on a copy.
- **Only the owner approves assembly, inline `asm` and `volatile`.** A hand-written `.S` source needs a row in
  `config/assembly-sources.tsv` ([assembly sources](docs/engine/assembly-sources.md)); inline `asm`, `volatile`
  or an MWCC `asm` function in C and C++ needs a row in `config/source-approvals.tsv`
  ([source approvals](docs/engine/source-approvals.md)). The owner adds a row after reviewing the evidence
  that the original source used it. An agent writes one only when the owner has explicitly told it to add
  that specific routine or function, never on its own initiative or as part of a broader request ("match
  everything", "clear the queue"). The one standing instruction: the integrator writes the row the owner's
  way when a Fable 5.2 check recommends approving with high confidence; the report lists each such row, and
  the owner can revoke it.
- **Scope.** The repository holds the decompilation and what it needs: source, build tables, tools,
  evidence and reference documentation. Agent handoffs, session logs, per-wave work reports, changelogs and
  accounts of how the repository was reorganised, player-facing guides and catalogues, and tools that
  drive or read a running emulator (with their captures) go to the workspace's archive outside Git. Write
  what a wave learned into the topic's document, not a dated log.
- **One build at a time.** At most one full build (`make check`, `make link`, `make objdiff`) runs on a
  host, from the integrating session, never from a sub-agent. Where several sessions share a host, take a
  lock: `flock <shared lock file> make check`.
- **Sub-agents write only to a scratch directory outside the repository**, never `src/`, `config/`, `asm/`,
  `docs/` or the repository root. The integrator promotes work ([Delegated work](#delegated-work)).
- **Commits.** Sync with `git fetch && git merge origin/main` (never rebase shared history).

## Every task

- **Done means the four completion lines** ([Completion and regression](#completion-and-regression)),
  quoted from runs on the final tree.
- **Every landing includes the readability pass** on what it touches ([Readable](#matched-and-readable)).
- **Sub-agent models are set by the kind of work** ([Delegated work](#delegated-work)): byte matching and
  mechanical work start on Sonnet 5.5, the integrator (which runs on Opus 5.5) reviews every Sonnet result and
  fixes what it could not match or explain (and does the readability pass), and Fable 5.2 is the last resort for
  what Opus 5.5 cannot land. The integrator does no bulk mechanical work itself, and names each sub-agent's model
  to the owner.
- **Owner decisions are presented one at a time, as a question** the owner answers (the options with a
  recommendation, and the evidence), and an approval row is written only on the owner's instruction for it.
  An `asm` or `volatile` goes to the owner only after a Fable 5.2 sub-agent has checked whether it is needed:
  it looks for plain C first, strips each keyword to show which change the bytes, and judges what remains
  against the approval standard. A high-confidence Fable 5.2 approval is written without asking and listed in
  the report; medium or low confidence, and anything Fable leaves open, goes to the owner as a question.
- **Names.** A proposed name with high or medium confidence that says what the thing is or does, and reads
  like a name a person on the original team would have written, is applied without asking and listed in the
  report, with its evidence (medium ones with the alternative considered). Low-confidence guesses stay out
  until there is more evidence.

## Layout

Paths are repository-relative, and commands run from the repository root.

- `src/` recovered source (`src/third_party/` is stock zlib, libpng and Lua, never edited;
  [README](src/third_party/README.md)); `asm/` the retail split, generated from your executable and never
  committed (`make asm`; `make check` writes it when it is missing or stale); `include/dw4/` shared headers
  (`reflected.h` is generated); `tools/` build and matching tools ([README](tools/README.md)); `scripts/`
  analysis; `data/` recovered data; `lua/` the game's Lua scripts decompiled and filed by stage
  (`scripts/lua_tree.py` resolves a pack entry and chunk to its file); `docs/` the documentation
  ([index](docs/README.md), whose Conventions cover how documents are written).
- The build follows the [dtk-template](https://github.com/encounter/dtk-template) layout
  ([build system](docs/build-system.md)): each version's address-bearing tables live in `config/<GAMEID>/`
  (`config.yml`, `symbols.txt`, `units.tsv` as the splits, `regions.tsv`, `data-owners.tsv`, `unit-*`,
  `exceptions.txt`, `names/`, `build.sha1`); project-wide policy files stay in `config/`
  (`debt-baseline.json`, `typed-*`). `make` extracts the executable from a disc image in `orig/<GAMEID>/`,
  and `python3 tools/download_tools.py` fetches the pinned compilers into `local/`.
- Documentation states the current state, never tallies of matched functions, and a method document names
  no function ([conventions](docs/README.md#conventions); `make hygiene` enforces the function names).
  Preserve unrelated changes.

## Decompilation

Read [naming](docs/engine/naming.md), [asm-body matches](docs/engine/asm-body-matches.md) and
[matched and readable](#matched-and-readable) before module work. A draft may be rough while it is in
scratch; what lands is both matched and readable.

- **Source compiles as whole files, never as functions.** The original build compiled each source file
  whole, and so does this one: a function lands inside its whole-file unit (`src/<module>/<file>.c|.cpp`,
  one `config/<GAMEID>/units.tsv` row and one `unit-objects.json` row with `whole_file`, measured by
  `tools/whole_file_rows.py`, never typed), in retail address order, and the whole unit must verify. A
  function in a range not yet folded is never banked as a new one-function file: fold the range into its
  file first (the file's extent from its strings, data and same-file calls, `scripts/same_file_calls.py`;
  `tools/merge_units.py` for the one-function files already there), then join the function. Compiling
  whole decides code under both compilers, so a candidate that matches alone can differ inside its file and
  one that misses alone can match there ([whole-file units](docs/engine/emitted-functions.md#whole-file-units)):
  `tools/check.py --function` on a one-function candidate is a drafting aid, and the verdict is the
  file's. The one-function files left in `src/unmatched/` and the per-function rows of `units.tsv` are
  legacy, each removed when its range is folded.
- **Every landing includes the readability pass on what it touches.** Folding functions into a whole-file
  unit, or joining held-out functions to one, makes the touched code readable in the same change: the unit
  is the scope, with one header and one set of types.
- **A function that resists matching is understood before it is searched.** When the obvious spellings
  fail, read the function and its unit first: real types from `include/dw4/reflected.h`, what each value
  is for, names from evidence, the same virtual slot in sibling classes, and the GameCube and Xbox builds.
  Only then run a permuter or a variant search. A spelling whose only reason is the bytes (a temporary
  that holds a stack slot, a one-element array that holds a register, a directive that ends a scheduling
  block, a class shaped to dodge the inliner) needs a reason in the code's own terms before it is proposed.
  [Understanding a resisting shape](docs/engine/understanding-shapes.md) gives the procedure, the instruments
  (the compiler's IR dump, gdb tracing, the register-allocator tracer, other builds, SDK archives) and the
  causes found so far.
- **One translation unit, one profile.** Every method of a class, and every function of a folded unit,
  verifies under the same compiler and flags. A per-function row that disagrees with its siblings is
  provisional: note it in the topic's open questions, re-attempt under the sibling profile, and count it
  separately until resolved. Never pin a profile to make one function pass while its unit says otherwise.
- **Exception metadata is part of the match.** C++ cleanup scopes are RAII holder classes whose destructor
  copies `config/<GAMEID>/unit-objects.json` names (`emitted`, `duplicates`, `externals`, `exceptions`, and
  `stripped` for an out-of-line destructor copy the retail linker dead-stripped);
  [emitted functions](docs/engine/emitted-functions.md).
- **Progress is fully matched source** (`functions.fully_matched` in `docs/progress.json`; what counts is
  in the [conventions](docs/README.md#conventions)). No partial score for a near miss, and no figure summed
  with asm bodies.
- **No asm bodies.** A function without C has no file in `src/`: it links from the retail image and reads
  from the generated `asm/`. Its retail instructions wrapped in an `asm` function recover nothing and are
  not committed; `make check` files any that appear as `asm-body`, counted in no figure. The exception is a
  function the original source wrote as an MWCC `asm` function, with an owner's `asm-function` row
  ([asm-body matches](docs/engine/asm-body-matches.md)). The work queue is every symbol without a
  definition in `src/`: `python3 tools/m2c_batch.py` drafts them (gcc target for Sony EE GCC units), and a
  draft lands only by joining its whole file. When a compiler is added, re-attempt the functions in its
  blocks first. Blocks built by a compiler build the project does not have stay without source.
- **No unapproved inline `asm` or `volatile`.** Either passes the byte check whether or not C could produce
  the same bytes, so it can hide a spelling nobody found: find the C. A function using one without its row
  is `unapproved`: it links, but it is not matched. Only `sync` and `ei` need no row, as C cannot spell
  them. A `volatile` that only pins when a load is scheduled, where retail reads once, is never approved.
  `python3 tools/sourceapprovals.py --list` is the queue, `tools/inline_asm.py --test <source>` shows which
  `asm` statements can go, and `tools/progress.py --debt-check` fails on any rise in `inline_asm.other`.
- **Names** follow [Readable](#matched-and-readable) item 2. Apply overlays with `tools/apply_names.py`
  (dry run, then `--apply --check`).

### Matched and readable

**Matched** is one condition: the function verifies byte-identical as a member of its whole-file unit,
compiled under that **translation unit's profile** in `config/SLUS-20836/units.tsv` (compiler, flags,
exception mode; [build profiles](docs/engine/build-profiles.md)), including the C++ exception metadata. A
function that matches only under a per-function override in `config/SLUS-20836/unit-flags.tsv` /
`unit-compilers.tsv` is `foreign-profile` debt, not a match, and one using inline `asm` or `volatile` without
an owner approval is `unapproved` debt.

**Readable** is the second condition, measured by the README's Readable column, and every landing meets it.
A function is readable when all of these hold:

1. It sits in its module translation unit (`src/<module>/<Class or topic>.c|.cpp`), in retail address order.
2. Every identifier is a recovered name: from RTTI, strings or callers where they exist, otherwise a best
   guess from what the thing does. What it does should make the name obvious, so source never justifies a
   name: doubt about one goes in the topic document's open questions. A name holding an address is not
   recovered: it says where a thing is, not what it is. That goes for functions, variables, structs and
   classes alike; a type also needs a real name, not a placeholder such as `S`, `Obj` or `Info176`.
   Strings are named by their text, with no prefix.
3. No m2c idioms (`temp_*`, `var_*`, `argN`, stack-offset locals such as `sp5C`) and no raw offset casts where
   `include/dw4/reflected.h` names the field; real structs, enums and control flow; offset members are
   decimal `fNN` and temporary, with one shared definition per class under `include/dw4/`. A comment appears
   only when it is necessary, for what the code cannot say, and it stands alone: no pointer to another
   document or tool, and no account of how the code was recovered.
4. A shape found by a permuter, flag sweep or random walk carries
   `/* matching construct: <tool> — <what moved> */` at the affected line.

An owner-approved assembly source counts as readable once it has a recovered name. When two spellings match
the same bytes, keep the more readable one.

### Completion and regression

A task is complete only when the report quotes these four lines verbatim from runs on the final tree
([oracle runner](docs/engine/oracle-runner.md) re-runs them on every pushed commit):

1. `make check`: the `cover :` summary, `0 mismatch` in its `(N not matched: M mismatch, D debt)` line when
   that line appears, and the `match` count at or above `functions.fully_verified` in the parent commit's
   `docs/progress.json`.
2. `make link`: `linkcheck: BYTE-IDENTICAL — the relinked section matches retail exactly`.
3. `make typed-check`: `typed coverage: N recovered accesses, baseline matches` (or the re-recorded baseline
   with the reason).
4. `make hygiene`: `check_host_details: clean`.

Run `make check-fresh` and `make link-fresh` (cache ignored) before any commit that changes
`config/<GAMEID>/units.tsv`, `unit-*`, `extent-overrides.tsv`, `jumptables.txt`, `compiler-runtime-symbols.tsv`
or `tools/`, and before a milestone. A drop in the `match` count is a regression, including a function
moving to `unapproved` (such as through a new `volatile`): find the cause, never explain it away. A debt
counter that rises (`tools/progress.py --debt-check`) is re-recorded only with a reason
(`--debt-baseline --allow-increase "<reason>"`; [debt ratchet](docs/engine/debt-ratchet.md)).

### Extents, splits and regenerated artifacts

Changes to `config/<GAMEID>/extent-overrides.tsv` or `data/function-extents.json`, symbol splits/merges and
a regenerated `config/<GAMEID>/symbols.txt` are reviewed in the commit message with before/after counts
(functions, laid-out bytes, truncated units) and how the denominator changed. Regenerate, never hand-edit:
`config/<GAMEID>/{symbols,layout,jumptables,syscalls}.txt`, `data/`, `lua/`, flag tables and progress blocks
(`scripts/sync_data.sh`, `make progress`). Update topic documents, generated views and prose in the same
commit.

### Tools and limits

- One Ghidra process at a time; reuse an analysed project with `--no-analysis`. Check function shape with
  `mipsel-linux-gnu-objdump`; decompiler output alone is not proof.
- `python3 tools/m2c_batch.py --jobs 8 …`; never invoke imported `m2c.main` concurrently. `make check`/`make link`
  already run in parallel.
- `make objdiff` is a diff aid ([build system](docs/build-system.md)); `tools/check.py` and
  `tools/linkcheck.py` are the oracle.
- Callers and callees of retail functions: grep `asm/` and `src/` for the symbol, or the Ghidra xref scripts
  (`scripts/dump_xrefs.py`, `scripts/xrefs_multi.py`).

## Delegated work

Sub-agents draft; the integrator verifies and promotes. A sub-agent report lists, per function: address,
symbol, candidate path (in its scratch directory), the exact `tools/check.py --function` (or `tools/verify.py`)
command with flags, compiler path and SHA-256, the verifier's last line, and any `config/<GAMEID>/unit-*` rows
the match needs. The integrator re-runs that command before promoting anything and treats an unreproduced
claim as unmatched. Brief sub-agents with what matched and readable mean; they never run full builds and
never write into the repository. An agent briefed on a resisting shape is pointed at
[understanding a resisting shape](docs/engine/understanding-shapes.md), with the earlier agent's report.

The sub-agent's model is set by the kind of work. This is a requirement, not a preference:

- **Mechanical work** (renames, applying names or data names, regenerating or rewriting tables and config
  rows, landing agents' files, collecting data): Sonnet 5.5.
- **Byte matching, first pass** (drafting functions, folding a range into whole files, matching them under the
  unit profile): Sonnet 5.5. Its report lists what matched and, separately, what it could not match or explain.
- **Review and fix:** the integrator, which runs on Opus 5.5, reviews every Sonnet 5.5 matching result before it
  lands: real types and names, no byte-only spellings or stray `asm`/`volatile`, extents and rows right, the
  readability pass done. It fixes what Sonnet left unmatched or unexplained. Opus 5.5 sub-agents take the review,
  one per slice, when it is too large for the integrator alone or when several Sonnet results are waiting at once,
  so the reviews run in parallel. Understanding work with no Sonnet pass (a resisting shape, a tool change) starts
  at Opus 5.5.
- **Last resort:** Fable 5.2, handed the Opus 5.5 report, for a function or shape Opus 5.5 still cannot land.

How it is enforced:

- **Every start names its model.** No sub-agent runs on a default model by omission. Before starting
  sub-agents, the integrator gives the owner the list of sub-agent and model. A slice that mixes kinds is
  split, or runs on the model of its hardest part.
- **The integrator does no bulk mechanical work itself.** It plans, briefs, re-verifies, promotes and fixes
  what verification finds. A mechanical pass over many files or rows goes to a Sonnet 5.5 sub-agent, with the
  exact mapping or table to apply and the check that proves it was applied.
- **Every leftover is handed on, in order.** A leftover is a function that still differs, a shape whose
  mechanism is unexplained, an extent or boundary nothing proves, or an approval item. Sonnet 5.5's go to the
  integrator's Opus 5.5 review; what Opus 5.5 still cannot land goes to a Fable 5.2 sub-agent with the Opus
  report, and every approval item goes through Fable 5.2 before it reaches the owner. Work does not count as done
  before that, and listing a leftover under open questions without the handoffs is not done. If Fable 5.2 cannot
  explain it either, the open question records the reports.
- **Reports carry the model.** A sub-agent's report states its model in its first line. A progress or
  final report that credits a sub-agent's result names the model that produced it. The final report lists
  every Fable 5.2 handoff with its outcome.

## Retail-game work

Read [testing tools](testing/tools.md), the [game reference](docs/reference/game-reference.md),
[stage selection](docs/systems/dev-stage-debug-menu.md) and the documentation for the build under test.
Live-memory claims need a running-game or offline savestate read; a savestate carries the loaded world, so
test a disc change by booting the disc and loading the stage afterwards. Menus accept stick and D-pad; in the
world only the stick moves the player. Emulator-driving tools and their notes stay outside the repository.
