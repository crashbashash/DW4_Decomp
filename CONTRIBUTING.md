# Contributing

Thanks for wanting to help recover *Digimon World 4*! You don't need to know the whole project to
be useful here. Picking one small function and making it read well is a real contribution.

Start with the [README](README.md#installation) to get a build working. The
[documentation index](docs/README.md) is there when you want to dig into how the engine works.

## Finding something to work on

Functions that have no C yet are the main to-do list. `tools/m2c_batch.py` will draft a starting
point for you ([how that works](docs/engine/m2c-bulk.md)), and you can read the original instructions
in `asm/`, which the build generates from your own copy of the game.

There's plenty to do on code that already matches, too. [PROGRESS.md](PROGRESS.md) shows what's done,
and the Readable section lists the most common things still to tidy up. Renaming a mystery function,
or giving a struct real fields, helps everyone who reads that code afterwards.

Before you try something, have a look through the [findings](docs/findings/README.md). That's where we
keep what we've learned, including what didn't work, so you might save yourself an evening. If you're
planning something big, open an issue first so two people don't end up on the same module.

## What good code looks like here

There are two things we're after, and they count equally: the compiled code has to match the original
byte for byte, and a person has to be able to read it. A match nobody can follow isn't finished.

- **Name things for what they are.** A name should come from something you can point to: a string,
  type information, how it's called. If you're only guessing, leave the name alone and write the
  guess up in the findings instead. Good names don't need explaining, and an address is never a name.
- **Clean up after the decompiler.** Rename things like `temp_s0` and `sp5C` to what they actually
  are, use real structs instead of pointer maths, and write loops and conditions the way a person
  would.
- **Keep comments for what the code can't tell the reader.** If someone would have to open another
  file to understand your comment, it isn't helping.
- **Flag anything odd that's only there to match.** If you had to write something strange to get the
  bytes right, say so with `/* matching construct: <what and why> */`, so nobody tidies it away.
- **When two versions match, keep the nicer one.**

Put code in the file for its class or module, in the same order the functions appear in the game. If
you can't get a function into C yet, that's fine, just leave it out. It keeps building from the
original until someone cracks it, and please don't wrap its instructions in an `asm` block to count it
as done.

Getting a match sometimes depends on the compiler and flags in `config/SLUS-20836/units.tsv`.
Everything in a file should build with the same settings, so if one function only matches with
different ones, it's worth finding out why. [Build profiles](docs/engine/build-profiles.md) explains
more.

## Checking your work

To try one function:

```sh
python3 tools/check.py --function 0xVA --cand src/unmatched/FUN_XXXXXXXX.c
```

Read everything it prints, because the first line isn't always the real problem. For a side-by-side
view, run `python3 configure.py && ninja objdiff` and open the folder in
[objdiff](https://github.com/encounter/objdiff). It's great for chasing a difference, but `tools/check.py`
has the final say.

Before you open a pull request, run these and include the results:

```sh
make check        # every function still matches, and none were lost
make link         # the rebuilt game is byte-identical to the original
make typed-check  # struct field coverage didn't slip
make hygiene      # nothing private is about to be published
```

If you changed `tools/` or the build tables in `config/`, use `make check-fresh` and `make link-fresh`
so nothing stale from the cache hides a problem. If the matched count goes down, something broke, so
please track it down before you open the PR. These checks also run automatically on everything pushed.

## A few things that can't go in the repo

- **Nothing from the game itself.** That means disc images, executables, BIOS files, saves, extracted
  assets, screenshots and the game's code as assembly. Names, offsets and notes we've worked out are
  fine.
- **Nothing about your own machine.** Paths with your username in them, hardware details, email
  addresses and passwords all stay out, including from commit messages. Run
  `scripts/install_git_hooks.sh` once and the hooks will catch these for you. Please don't skip them
  with `--no-verify`; our [host details policy](docs/host-details-policy.md) has the reasoning.
- **Generated files shouldn't be edited by hand.** That covers `PROGRESS.md`, most of `data/` and the
  symbol tables in `config/`. Change what they're generated from, then run `make progress`.

If you learn something useful, like what a value means or why an approach failed, add it to the
findings in the same change. `python3 scripts/findings.py next` gives you the next number. That's what
saves the next person from starting over.

## Licence

Your own work here (tools, scripts, build files, documentation) is dedicated to the public domain under
CC0 1.0, as described in [LICENSE](LICENSE). Game-derived material stays as described there.
