# Contributing

Thanks for helping recover *Digimon World 4*. This page is the method every change follows; the
[README](README.md#installation) covers setup and the [documentation index](docs/README.md) the
engine, formats and recovery notes.

## Finding work

- `PROGRESS.md` and `data/check-categories.tsv` (written by `make check`) show what is matched and
  what is still debt: `code-only` (code matches, exception metadata does not), `foreign-profile`
  (matches only under a per-function compiler override), `name-defect`.
- A symbol with no definition in `src/` has no C yet: that list is the work queue, and
  `tools/m2c_batch.py` drafts from it ([m2c bulk](docs/engine/m2c-bulk.md)). Read such a function
  in `asm/`, which `make` generates from your executable; it is never committed.
- The [findings register](docs/findings/README.md) holds the evidence, the
  open hypotheses and what has been ruled out. Read the relevant entries before repeating an approach.
- Open an issue or comment on one before starting a large module, so two people do not take the
  same one.

## The gate: when a function is done

Byte identity and readability are one gate. A function counts as done when all of these hold:

1. It verifies byte-identical under its **translation unit's profile** in `config/SLUS-20836/units.tsv`
   (compiler, flags, exception mode; [build profiles](docs/engine/build-profiles.md)), including the
   C++ exception metadata. A function that matches only under a per-function override in
   `config/SLUS-20836/unit-flags.tsv` / `unit-compilers.tsv` is `foreign-profile` debt, not a match.
2. It sits in its module translation unit (`src/<module>/<Class or topic>.c|.cpp`), in retail address order.
3. Every identifier is a recovered name, from evidence (RTTI, strings, callers), never a guess. What
   it does should make the name obvious, so source never justifies a name: a hypothesis and its
   evidence go in the findings register. A name
   holding an address is not recovered: it says where a thing is, not what it is. That goes for
   functions, variables, structs and classes alike; a type also needs a real name, not a placeholder
   such as `S`, `Obj` or `Info176`.
4. No m2c idioms (`temp_*`, `var_*`, `argN`, stack-offset locals such as `sp5C`) and no raw offset casts where
   `include/dw4/reflected.h` names the field; real structs, enums and control flow; a comment
   appears only when it is necessary, for what the code cannot say, and it stands alone: no pointer
   to another document, finding or tool, and no account of how the code was recovered.
5. A shape found by a permuter, flag sweep or random walk carries
   `/* matching construct: <tool> — <what moved> */` at the affected line.

When two spellings match the same bytes, keep the more readable one. A function that cannot be
written as C yet stays without a file: its retail instructions wrapped in an `asm` function recover
nothing and are not committed ([asm-body matches](docs/engine/asm-body-matches.md)).

C++ cleanup scopes are written as RAII holder classes whose destructor copies
`config/SLUS-20836/unit-objects.json` names ([emitted functions](docs/engine/emitted-functions.md)).
Strings are named by their text, with no prefix; offset members are decimal `fNN` and temporary; one shared definition
per class lives under `include/dw4/`.

## Checking your work

```sh
python3 tools/check.py --function 0xVA --cand src/unmatched/FUN_XXXXXXXX.c   # one function, every diagnostic line
python3 configure.py && ninja objdiff                                            # then open the folder in objdiff
```

Read every line `tools/check.py` prints; the first one is not always the blocker. objdiff is a diff
aid; `tools/check.py` and `tools/linkcheck.py` are the oracle.

Before opening a pull request, run on your final tree and paste these four lines into the description:

1. `make check` — the `cover :` summary with `0 mismatch` in any `(N not matched: M mismatch, D debt)`
   line, and no fewer `match` functions than before.
2. `make link` — `linkcheck: BYTE-IDENTICAL — the relinked section matches retail exactly`.
3. `make typed-check` — `typed coverage: N recovered accesses, baseline matches`.
4. `make hygiene` — `check_host_details: clean`.

Run `make check-fresh` and `make link-fresh` instead when the change touches `config/<GAMEID>/units.tsv`,
`unit-*`, `extent-overrides.tsv`, `jumptables.txt`, `compiler-runtime-symbols.tsv` or `tools/`. A drop in
the matched count is a regression to find, never to explain away.

The pre-push hook does not run these gates a second time: it checks the pushed lines and commit
messages for host details, and the oracle-change rule when the oracle's own files change. The
[oracle runner](docs/engine/oracle-runner.md) runs all four on every pushed commit.

## Rules for every change

- **No game data.** Never commit disc images, executables, BIOS, saves, savestates, extracted assets,
  screenshots of the game, or the retail code as assembly (the generated `asm/`, or a function's
  instructions in an `asm` wrapper). Recovered metadata is fine. Never force-add.
- **No host details.** Nothing that identifies your machine or account (home paths, user or host
  names, hardware, e-mail addresses, credentials) goes into files, findings or commit messages
  ([host details policy](docs/host-details-policy.md)). Install the hooks once with
  `scripts/install_git_hooks.sh`; they run `make hygiene`. Never use `--no-verify`.
- **Regenerate, never hand-edit** generated files: `config/<GAMEID>/{symbols,layout,jumptables,syscalls}.txt`,
  `data/`, `PROGRESS.md` and the progress blocks (`make progress`).
- **Record what you learn.** A name hypothesis, a compiler constraint or a dead end goes into the
  findings register with repository-relative evidence in the same change (`python3 scripts/findings.py next`).
- Changes to extents or symbol splits state the before/after function and byte
  counts in the commit message.

## Licence

By contributing you agree that your own work (tools, scripts, build files, documentation) is dedicated
to the public domain under CC0 1.0, as described in [LICENSE](LICENSE); the game-derived material
stays as described there.
