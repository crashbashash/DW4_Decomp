# `tools/dispatcher/`: register-allocation and shape tools

Written while matching the GAMERAM combat dispatcher ([result](../../docs/systems/combat-dispatcher.md)); the tools work on any
function. Background: [register allocation](../../docs/engine/register-allocation.md).

## Register allocation tools

    python3 tools/dispatcher/regalloc_trace.py src/unmatched/Gap__Bec__beNDMWGameRam__vfunc_34.cpp [--only-case N] [--tail N] [--adj DIR --ctx FILE] [--ids a,b,c]
    python3 tools/dispatcher/regalloc_sim.py DIR/adj1.json FILE

`regalloc_trace.py` traces the pinned compiler's graph colouring (last big pass) and reports the receiver colour and the last
pushed nodes; with `--adj/--ctx` it also dumps the interference graph, which `regalloc_sim.py` replays exactly for what-if
experiments.  `ALLOCATION.md` explains the rules and how the receiver was brought to `s4`.
## Small functions

    python3 tools/dispatcher/regalloc.py FUNCTION_OR_VA CANDIDATE.c[pp] [--flags "..."] [--compiler EXE] [--max-pool N] [--show-all] [--no-suggest]

Run from the repository root.  `FUNCTION_OR_VA` is a symbol of `config/SLUS-20836/symbols.txt` or a VA (`0x1c5870`).  The tool takes the
compiler and flags the build uses for that function (`config/SLUS-20836/unit-compilers.tsv`, `config/SLUS-20836/unit-flags.tsv`, else the default
`-O3 -Iinclude` with the 3.0 compiler), prints `tools/verify.py`'s verdict and instruction diff (classified: register-only,
same registers with the operands swapped, other), traces the compiler's last general-register colouring of the candidate
and reports, for every node whose register differs from retail, its id, cost, degree, push position, neighbours and what it
is.  It then replays simplify/select on the dumped graph (checked against the compiler's own pushes and colours) and searches the
permutations of the node ids of the involved nodes for an order that gives retail's colours; the order is printed with the
instruction that defines each node.  Exit status 0 = match, 1 = still different, 2 = tool error.

Typical loop: `python3 tools/m2c_batch.py --only NAME --keep-all --max-size 4096` writes the draft to `build/m2c/NAME.c`;
copy it, make the instruction sequence match first (anything marked "not a register difference"), then run the tool and apply
the suggested id order by moving declarations (the id rules are in the tool's docstring and in
`docs/engine/register-allocation.md`); repeat.

The tool is built on the modules above: `regalloc_trace.py` (`trace()`: profiles for the two compilers the tree uses, selected
by the SHA-256 of the executable), `regalloc_sim.py` (replay) and the IR dump added to the trace helper.

What it cannot do:

* It only runs for a compiler build it has a patch profile for (`local/mwcps2/3.0-011126` and the pinned combat build); for any
  other build it stops with "no trace profile".  gdb, GNU `as`/`ld` with 32-bit x86 support, `local/wibo`,
  `mipsel-linux-gnu-objdump` and permission to ptrace the loader are required.
* It explains *register choice only*.  A different instruction sequence (size, order, extra moves, a `t9` virtual call,
  operand order of a commutative operation) is reported but not explained.
* The alignment between the compiler's IR and the emitted instructions is a register-set heuristic; heavy scheduling or large
  address-materialising sequences leave some nodes without an instruction ("IR op ..."), and a node tied to conflicting retail
  registers is excluded from the search.
* The only lever it searches is the id order (declaration position, web joins).  Costs, extra edges (a longer live range) and
  different webs are not searched; "no permutation" means one of those is needed.
* Spills: it follows the last pass, but a function that spills in retail but not in the candidate (or the reverse) is
  structural.
* Pools of more than 8 nodes are searched by random swaps, not exhaustively.
* One translation unit may contain several functions; the pass is chosen by how well it fits the emitted code of the
  requested function, so keep helper functions out of the candidate when possible.
