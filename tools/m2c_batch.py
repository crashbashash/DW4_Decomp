#!/usr/bin/env python3
"""m2c_batch.py — bulk m2c → verify → bank, over the not-yet-matched functions.

The pipeline is deliberately *fail-closed* in the same way `automatch.py` is: a
candidate is written to `src/` only when `tools/verify.py` proves the compiled
bytes identical to retail. m2c's draft is a starting point, never an authority.

Per function:

  1. generate the spimdisasm assembly from the retail bytes (`m2c_one.asm_for`);
  2. run m2c **in-process** (importing `m2c.main` once is ~0.08 s; invoking
     `m2c.py` per function costs ~2.1 s of interpreter startup, so this is the
     difference between 0.5 and ~300 functions/s);
  3. mechanically clean the C: m2c's `s32`/`?` types, `func_XXXX`/`D_XXXX`
     names, `void *arg->unkN` member syntax, and numeric global addresses;
  4. compile with MWCC and diff every instruction word (`verify.verify_one`).

The **address form has to match retail**, and that cannot be decided from the
source: MWCC materialises a *literal* address through a scratch register with
`ori`, and a *symbol* address straight into the destination with `addiu`
. m2c emits literals, so both spellings are generated and verified —
whichever matches is kept. That is why this pass can bank a function whose
"correct" source nobody wrote by hand.

Usage:
  m2c_batch.py --report 200                 # sample 200 functions, print the yield
  m2c_batch.py --max-size 64                # every unmatched function <= 64 bytes
  m2c_batch.py --max-size 64 --write        # bank the matches into src/
  m2c_batch.py --only FUN_00100c20 --show   # one function, print the C and the diff
"""
import argparse
import contextlib
import io
import collections
import itertools
import os
import re
import struct
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import cc
sys.path.insert(0, os.environ.get("DW4_M2C_DIR",
                                  os.path.join(os.path.dirname(HERE), "local", "m2c")))

import automatch as am          # noqa: E402
import m2c_one                  # noqa: E402
import syscalls                 # noqa: E402
import units                    # noqa: E402
import verify as vfy            # noqa: E402
import m2c_compat               # noqa: E402,F401  (guards a vendored-m2c crash)
import m2c.main as m2c_main     # noqa: E402

TYPES = {"s8": "char", "s16": "short", "s32": "int", "s64": "long long",
         "u8": "unsigned char", "u16": "unsigned short", "u32": "unsigned int",
         "u64": "unsigned long long", "f32": "float", "f64": "double"}
TYPE_RE = re.compile(r"\b(%s)\b" % "|".join(TYPES))
ADDR_RE = re.compile(r"0x([0-9A-Fa-f]{5,8})\b")
NAME_RE = re.compile(r"\b(func_([0-9A-Fa-f]+)|D_([0-9A-Fa-f]+))\b")
# m2c spells an unknown member access `EXPR->unkN` (pointer) or `EXPR.unkN`
# (value): the base can be an identifier, an array element, a call result, a
# parenthesised expression or a deref-cast, and accesses **chain**
# (`a->unk4->unk8`). One scan finds each and `_primary_start` finds the base.
# `unk-8` is a **negative** offset (m2c's spelling for a field before the base, e.g. a
# container-of); the digit lookahead has to admit the sign or 634 unmatched functions
# keep an uncompilable `->unk-8`.
MEMBER_SCAN = re.compile(r"->unk-?(?=[0-9A-Fa-f])|\.unk-?(?=[0-9A-Fa-f])")
# m2c spells a store into an unknown member with a width cast: `arg0->unk68 =
# (u8) X;`, `arg1->unk60 = (s64) X;`, `x->unkC = (f32) v;`. The cast carries the
# access width; the member is not really 4 bytes wide. Rewriting it to an int
# store turns retail's `sb`/`sd`/`swc1` into a `sw`, so the width cast has to
# survive on the deref. `char`/`short` only covered the narrow half, which left
# every 64-bit and float access as a word (the residual of the ≤3-diff tier).
NARROW = (r"unsigned char|char|unsigned short|short|long long|unsigned long long"
          r"|float|double|s8|s16|s32|s64|u8|u16|u32|u64|f32|f64")
# m2c's width spellings -> the C type the deref must carry.
WIDTH_TYPE = {"s8": "char", "s16": "short", "s32": "int", "s64": "long long",
              "u8": "unsigned char", "u16": "unsigned short", "u32": "unsigned int",
              "u64": "unsigned long long", "f32": "float", "f64": "double"}
# a `void *` declaration whose arithmetic has to be cast: `(p + N)` is not C.
VOID_PTR_DECL_RE = re.compile(r"\bvoid\s*\*\s*([A-Za-z_]\w*)\s*(?=[,;=)])")
# m2c writes an unknown-width load as a bare `*(expr)`; default it to a word load.
UNK_DEREF_RE = re.compile(
    r"\*\((?!\s*(?:int|char|short|long|void|float|double|unsigned|signed|struct|s8|s16|s32|s64|u8|u16|u32|u64)\b)")
# `*(int (**)())EXPR()` — m2c's spelling of a call through a global fn pointer.
FNPTR_CALL_RE = re.compile(r"\*\(\s*(\w[\w ]*)\s*\(\*\*\)\s*\(\s*\)\s*\)\s*([^()]*?)\s*\(\)")


def _diffcount(report):
    """Differing words in a verify.py report (works with and without --verbose)."""
    n = 0
    for l in report.splitlines():
        if l.strip().startswith("!!") or re.match(r"^\s*\[\s*\d+\]", l):
            n += 1
    return n


load_bounds = m2c_one.load_bounds        # re-export for callers of this module


def _match_back(c, i, close, open_):
    """Index of the `open_` matching the `close` at `i`, scanning backwards."""
    depth = 0
    while i >= 0:
        if c[i] == close:
            depth += 1
        elif c[i] == open_:
            depth -= 1
            if depth == 0:
                return i
        i -= 1
    return i + 1


def _primary_start(c, end):
    """Start of the primary expression that ends just before `end`.

    Handles what m2c puts on the left of a member access: an identifier, an array
    element (`DAT_x[0]`), a call result (`f()`), a parenthesised expression
    (`(a + 8)`) and a deref-cast (`*(int *)(...)` — which is also what this pass
    itself emits, so folding a chain one member at a time works).
    """
    b = end
    while b > 0:
        ch = c[b - 1]
        if ch.isalnum() or ch == "_":
            while b > 0 and (c[b - 1].isalnum() or c[b - 1] == "_"):
                b -= 1
            continue
        if ch == "]":
            b = _match_back(c, b - 1, "]", "[")
            continue
        if ch == ")":
            lb = _match_back(c, b - 1, ")", "(")
            # `*(TYPE *)(EXPR)`: the deref and its cast belong to the base.
            if lb > 0 and c[lb - 1] == ")":
                lt = _match_back(c, lb - 1, ")", "(")
                if lt > 0 and c[lt - 1] == "*":
                    b = lt - 1
                    continue
            b = lb
            continue
        break
    return b


def rewrite_members(c):
    """`EXPR->unkN` / `EXPR.unkN` -> an explicit word load or store.

    m2c uses `->unkN` when it does not know the pointee type, and `.unkN` when the
    base is a *value* (a global of unknown type, a local). The rewrite folds the
    base correctly, which the earlier left-to-right scan did not: `a->unk4->unk8`
    came out as a load from `a + 12` (the inner deref was dropped) and
    `slot->unk28(...)` lost its `((int (*)())…)` wrapper, so the candidate could
    not compile. The access is 4 bytes wide unless m2c marked a narrow one with a
    cast (`= (u8) …` on a store, `(u8) …` on a load); that cast is the width, so
    the deref carries it or a `sb` becomes a `sw`. The width belongs to the
    **outermost** access of a chain, so it is read after the member is isolated.
    """
    while True:
        m = MEMBER_SCAN.search(c)
        if m is None:
            return c
        j = m.start()
        arrow = m.group(0).startswith("->")
        b = _primary_start(c, j)
        d0 = j + (5 if arrow else 4)              # first char after `unk`
        neg = d0 < len(c) and c[d0] == "-"
        k = d0 + 1 if neg else d0
        while k < len(c) and c[k] in "0123456789abcdefABCDEF":
            k += 1
        off = int(c[d0 + 1 if neg else d0:k], 16)
        if neg:
            off = -off
        base = c[b:j]
        wtype = "int"
        if not MEMBER_SCAN.match(c, k):           # not the innermost of a chain
            wm = re.match(r"\s*=\s*\((%s)\)" % NARROW, c[k:])
            if wm is None:
                wm = re.search(r"\((%s)\)\s*$" % NARROW, c[:b])
            if wm is not None:
                wtype = WIDTH_TYPE.get(wm.group(1), wm.group(1))
        addr = "(char *)(%s) %s %d" % (base, "+" if off >= 0 else "-", abs(off))
        if arrow:
            deref = "*(%s *)(%s)" % (wtype, addr)
        else:
            # a *value* member: the field lives at the base's own address
            deref = "*(%s *)((char *)&(%s) %s %d)" % (wtype, base,
                                                       "+" if off >= 0 else "-", abs(off))
        if k < len(c) and c[k] == "(":            # a call through that slot
            deref = "((int (*)())%s)" % deref
        c = c[:b] + deref + c[k:]


def fix_void_arith(c):
    """`(p + N)` is not C when `p` is a `void *`, and MWCC rejects it.

    m2c emits `(arg0 + 0x1FC)->unk4` for a pointer parameter it could not type;
    the machine does an `addiu`, so the base wants a `char *`. Only declared
    `void *` names are touched, so a real `char *`/`int *` base is left alone.

    The binary `name + N` form was the first rule; the same machine arithmetic
    appears three more ways, each of which MWCC rejects with a different message
    (`illegal type` / `illegal operand` / `pointer/array required`) so the tier
    taxonomy never grouped them: the **compound assignment** `p += N` (m2c's
    loop-pointer advance), `N + p` and a `(void *)` **cast** used as an
    arithmetic base.
    """
    for n in set(VOID_PTR_DECL_RE.findall(c)):
        # `(arg0 + 0x1FC)` and a bare `arg0 + 0x1FC` are both pointer arithmetic;
        # the lookbehind keeps a name that is already inside a cast
        # (`(char *)arg0 + …`) from being cast twice.
        c = re.sub(r"(?<![A-Za-z0-9_*])%s\s*([-+])\s+" % re.escape(n),
                   lambda m: "(char *)%s %s " % (n, m.group(1)), c)
        # `p += N;` / `p -= N;` — byte arithmetic on a void*.
        c = re.sub(r"(?<![A-Za-z0-9_*])%s\s*([-+])=\s*([^;\n]+);" % re.escape(n),
                   lambda m: "%s = (void *)((char *)%s %s (%s));"
                             % (n, n, m.group(1), m.group(2).strip()), c)
        # `N + p` — the index on the left.
        c = re.sub(r"\+\s*%s\b" % re.escape(n),
                   lambda m: "+ (char *)%s" % n, c)
        # `p - q` and `N - p` on the right-hand side of a subtraction.
        c = re.sub(r"-\s*%s\b" % re.escape(n),
                   lambda m: "- (char *)%s" % n, c)
    # A `(void *)` cast whose result is an arithmetic base: the base wants a char*.
    c = re.sub(r"\(void \*\)(\([^()]*\)|[A-Za-z_]\w*(?:\[[^\]]*\])?)\s*([-+])",
               lambda m: "(char *)%s %s" % (m.group(1), m.group(2)), c)
    return c


def clean(c, addr_mode="symbol", bounds=None):
    """m2c C -> compilable C, with all global addresses in one chosen form."""
    SECTION_LO, SECTION_HI = bounds or (0x100000, 0x58D280)
    decls = []
    c = TYPE_RE.sub(lambda m: TYPES[m.group(1)], c)
    c = fix_unknown_type(c)                       # m2c's unknown return/param type
    c = NAME_RE.sub(lambda m: ("FUN_%08x" if m.group(2) else "DAT_%08x")
                    % int(m.group(2) or m.group(3), 16), c)
    # `EXPR->unkN` / `EXPR.unkN` are rewritten at the end by `rewrite_members`, once
    # the base addresses are in their final form — doing it here with an
    # identifier-only regex is what broke chained accesses and dropped the
    # call-through-slot wrapper.
    c = FNPTR_CALL_RE.sub(lambda m: "((%s (*)())%s)()" % (m.group(1).strip(), m.group(2).strip()), c)
    c = UNK_DEREF_RE.sub("*(int *)(", c)
    # `*(int *)p = (void *)q;` — a pointer stored through a word store; MWCC rejects
    # the implicit pointer->int conversion, and the width is the same either way.
    c = re.sub(r"=\s*\(void \*\)", "= (int)", c)
    c = re.sub(r"\*\(void \*\)", "*(int *)", c)
    if addr_mode in ("symbol", "hybrid"):
        def sub(m):
            v = int(m.group(1), 16)
            if not (SECTION_LO <= v < SECTION_HI):
                return m.group(0)
            # In hybrid mode only an address used as a *base* of a cast (`*(T *)ADDR`,
            # `(T *)ADDR`) becomes a symbol; a bare `= 0xADDR` is a stored constant,
            # which retail materialises with `ori`.
            if addr_mode == "hybrid":
                before = c[max(0, m.start() - 16):m.start()]
                if "*)" not in before:
                    return m.group(0)
            decls.append("extern char DAT_%08x[];" % v)
            # An address that is an *operand of a bitwise operator* is an int value, not
            # a pointer base: m2c writes the PS2 uncached alias as `0x5586C0 | 0x20000000`,
            # and naming the constant makes that `char[] | int`, which MWCC rejects
            # (FUN_001109f0's `illegal operand`). Keep it an int.
            aft = c[m.end():m.end() + 12].lstrip()
            if aft[:1] in ("|", "&", "^") or aft[:2] in ("<<", ">>"):
                return "(int)DAT_%08x" % v
            if c[max(0, m.start() - 16):m.start()].rstrip()[-1:] in ("|", "&", "^"):
                return "(int)DAT_%08x" % v
            return "DAT_%08x" % v
        c = ADDR_RE.sub(sub, c)
        c = arrayize_globals(c)
    elif addr_mode == "literal":
        c = desymbolize_globals(c)
    # a `void *` parameter that is only ever used through the arithmetic above is fine;
    # so is `int`, so nothing else needs rewriting.
    #
    # A name can be declared twice: `ADDR_RE.sub` adds `extern char DAT_x[];` for a
    # numeric address, while m2c's own `extern void *DAT_x;` (for the same address,
    # seen through `%hi/%lo`) is arrayized to `extern void *DAT_x[4];` above. MWCC
    # rejects the redeclaration (`identifier 'DAT_x' redeclared ... was declared as:
    # 'char[]' now declared as: 'void *[4]'`), which was the top compile failure in
    # the large-function tier. The arrayized m2c declaration is the one whose uses
    # were rewritten to `DAT_x[0]`, so keep it and drop the duplicate.
    pre = []
    for d in sorted(set(decls)):
        nm = re.search(r"(DAT_[0-9a-f]{8})", d).group(1)
        # Skip it only if the body already *declares* it. Testing for a mere mention
        # dropped the declaration of every symbol this pass just named: the *use*
        # (`*(int *)DAT_004be890 = 1;`) contains the name, so `extern char DAT_004be890[]`
        # was never emitted and the candidate failed with "undefined identifier".
        # That was 710 of the 5,076 compile failures (14 %), the second-largest bucket.
        if re.search(r"(?m)^\s*(?:extern|static)\b[^;\n]*\b%s\b" % nm, c):
            continue
        pre.append(d)
    c = "".join(d + "\n" for d in pre) + c
    # Member accesses can only be rewritten once the bases are final symbols, and
    # m2c writes an unknown-type store as a cast on an lvalue, which C rejects.
    # m2c infers an unknown 64-bit parameter from an `sd` store and casts the 32-bit
    # address to `long long`; MWCC then zero-extends it with `dsll32`/`dsrl32` before
    # the store, where retail stores the sign-extended 32-bit pointer directly (for an
    # address the two extensions are the same value, so the pair is pure overhead).
    c = re.sub(r"\(long long\)\s*(&)", r"\1", c)
    # A function address stored into a *word* slot (a vtable/thunk entry) is an int: now
    # that `FUN_x` is declared a function, the store needs the cast back or MWCC rejects
    # `int (*)()` -> `int`.
    c = re.sub(r"(\*\(int \*\)\([^;\n]*\)\s*=\s*)&(FUN_[0-9a-fA-F]{8})\b",
               r"\1(int)&\2", c)
    c = rewrite_members(c)
    c = fix_void_arith(c)
    # A `FUN_<addr>` symbol referenced only as an *address* (never called) is still a
    # function: m2c declares it `extern int FUN_x;`, and MWCC then treats it as small
    # data and reaches it gp-relative (`addiu r,gp,imm`), where retail uses absolute
    # `lui`/`addiu`. Declaring it a function makes `&FUN_x` an ordinary function pointer.
    c = re.sub(r"(?m)^extern\s+(.+?)\s+FUN_([0-9a-fA-F]{8})\s*;$",
               lambda m: "%s FUN_%s();" % (m.group(1).strip(), m.group(2)), c)
    c = loosen_prototypes(c)
    c = declare_stack_placeholders(c)
    c = fix_pointer_types(c)
    c = re.sub(r"\((?:void|int|char|short|long|float|double)\s*\*+\)\s*(?=\*\s*\(\s*int\s*\*\s*\)\s*\()", "", c)
    c = re.sub(r"\bNULL\b", "0", c)
    return c


TYPE_KEYWORDS = {"extern", "static", "const", "volatile", "register", "unsigned",
                 "signed", "struct", "union", "enum", "typedef", "inline"}
# m2c writes an unknown type with a *known width* as `?32` (see types.py: an any-reg
# type with `size_bits` set). The `?`-prefix rule below turns the `?` into `int` and
# leaves the digits behind, so the draft used to carry an undeclared `int32`.
UNK_WIDTH = {8: "char", 16: "short", 32: "int", 64: "long long"}


def fix_unknown_type(c):
    """m2c's `?` means "unknown type" — but `?` is also the ternary operator.

    A blanket substitution corrupts ternaries (`(a == 0) ? 4 : 2` ->
    `(a == 0) int 4 : 2`), which was the single largest compile-failure cause.
    The two are cleanly separable: a **ternary** `?` is always preceded by a token
    that can end an expression (identifier, `)`, `]`, digit, string/char literal);
    a **type** `?` never is — it follows `(`, `,`, `;`, `{`, `=`, a type keyword, or
    the start of a line.
    """
    out, last = [], 0
    for m in re.finditer(r"\?", c):
        j = m.start()
        k = j - 1
        while k >= 0 and c[k] in " \t":
            k -= 1
        prev = c[k] if k >= 0 else "\n"
        if prev.isalnum() or prev == "_":
            w = re.search(r"[A-Za-z_]\w*$", c[:k + 1])
            is_type = bool(w) and w.group(0) in TYPE_KEYWORDS
        else:
            is_type = prev not in ")]" and not prev.isdigit() and prev not in "'\""
        out.append(c[last:j])
        if is_type:
            wm = re.match(r"\d+", c[j + 1:])
            if wm is not None:
                # `?32` -> the width's C type, consuming the digits so they do not
                # survive as an `int32` identifier; an unmapped width degrades to int.
                out.append(UNK_WIDTH.get(int(wm.group(0)), "int"))
                last = j + 1 + len(wm.group(0))
                continue
            out.append("int")
        else:
            out.append("?")
        last = j + 1
    out.append(c[last:])
    return "".join(out)


def loosen_prototypes(c):
    r"""Make m2c's callee declarations arity-agnostic (`T f(args);` -> `T f();`).

    m2c infers a prototype from one call site and then emits calls with a different
    number of arguments ('function call FUN_x(int) does not match FUN_x(int,int)'),
    which is the largest compile failure in the *large* function tier — the tier that
    holds ~71% of the remaining code bytes. In C an empty parameter list means
    "unspecified", so every call site is accepted. Only declarations are touched:
    lines that end in `;`, have no `=`, `{` or `(*`, and are not the function being
    decompiled (which has a body).

    The name must be separated from the type tokens by whitespace or `*`
    (`[\s*]+`), or the pattern also matches a bare *call statement*: with
    `[A-Za-z_]\w*\s*` an identifier as long as `FUN_00102d08` backtracks into
    `FUN_00102` + `d08`, `FUN_00102d08(arg3);` matches, and the rewrite then replaces
    it with `FUN_00102d08();` — silently **dropping the argument** from every bare
    call statement. That is exactly the shape of the near-miss tier's diff
    (`FUN_001033f8`: one instruction, retail's `move a2,a3` against our `nop`), so it
    was corrupting candidates rather than failing loudly. A call statement has no
    type token, so it cannot satisfy the separator requirement.
    """
    out = []
    for line in c.split("\n"):
        s = line.strip()
        if (s.endswith(";") and "(" in s and ")" in s and "=" not in s
                and "{" not in s and "(*" not in s and "}" not in s
                and not s.startswith(("if", "while", "for", "switch", "return", "do"))):
            m = re.match(r"^(\s*(?:[A-Za-z_]\w*\s+)*[A-Za-z_]\w*[\s*]+)"
                         r"([A-Za-z_]\w*)\s*\([^;]*\)\s*;\s*$", line)
            if m and "(" not in m.group(2):
                line = "%s%s();" % (m.group(1), m.group(2))
        out.append(line)
    return "\n".join(out)


def declare_stack_placeholders(c):
    """m2c names an unknown stack slot `sp`/`sp<hex>` and never declares it.

    In C an undeclared identifier is an implicit int, so this only ever mattered for the
    *declaration* m2c expects to be there; in C++ it is a hard error, which is how the
    C++ virtual-call path found it: `spD0` reaches MWCC as
    `undefined identifier`. Declaring them is also the right *shape*, not just a spelling
    fix -- a declared local lives in the frame, which is where retail's slot is.
    """
    first = c.find("{")
    if first < 0:
        return c
    body = c[first:]
    decls = []
    for nm in sorted(set(re.findall(r"(?<![\w.$])(sp[A-F0-9]*)\b", body))):
        if re.search(r"(?m)^\s*[\w][\w \t]*\*?\s*%s\s*(?:;|\[)" % re.escape(nm), c):
            continue
        decls.append(nm)
    if not decls:
        return c
    return c[:first + 1] + "\n" + "".join("    int %s;\n" % d for d in decls) + c[first + 1:]


PTR_DECL_RE = re.compile(
    r"(?m)^\s*(?:extern\s+|static\s+)?((?:unsigned\s+|signed\s+)?[A-Za-z_]\w*)\s*"
    r"(\*+)\s*([A-Za-z_]\w*)\s*(\[\s*\d+\s*\])?\s*;")
SCALAR_DECL_RE = re.compile(
    r"(?m)^\s*(?:extern\s+|static\s+)?((?:unsigned\s+|signed\s+)?"
    r"(?:int|long))\s+([A-Za-z_]\w*)\s*;")
ASSIGN_RE = re.compile(r"^(?P<lhs>.+?)\s=\s(?P<rhs>.+?)\s*;$")
PTR_CAST_RE = re.compile(r"^\(\s*([A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\**)\s*\)")


def fix_pointer_types(c):
    """Make the cleaner's own casts agree with the types m2c already recovered.

    m2c declares every pointer it recovered correctly -- `void *temp_a0;`,
    `int *temp_a1;`, a `void *arg0` parameter -- but writes an access whose type it
    does not know as a bare `int`, and this cleaner used to strip `void *` from both
    directions with two blanket rules (`= (void *)` -> `= (int)`, `*(void *)` ->
    `*(int *)`).  Neither looks at the lvalue, so the draft stopped compiling wherever
    the two disagreed, and those disagreements *are* MWCC's int/pointer buckets: the
    first error over the compile tier was `'int' to 'void *'` 1,826 times over 292
    functions, with the mirror image right behind it.

    Every rewrite is a cast between a 32-bit pointer and a 32-bit integer, so the
    emitted instructions cannot change (`lw`/`sw` either way) -- only the types have
    to agree for MWCC to accept the statement.  A 64-bit value is left alone: casting
    one to a pointer would truncate it, which is a real code change.
    """
    ptr, scalar, returns, arrays = {}, {}, {}, set()
    for m in PTR_DECL_RE.finditer(c):
        typ, stars, name, arr = m.group(1), m.group(2), m.group(3), m.group(4)
        ptr[name] = "%s %s" % (typ, stars)
        if arr:
            arrays.add(name)
    for m in SCALAR_DECL_RE.finditer(c):
        scalar[m.group(2)] = m.group(1)
    # A function pointer is a pointer too: `int (*temp_v1)(int, int, int);` is a
    # declaration m2c emits for a slot call it recovered (`lw t9, slot; jalr t9`),
    # and the word loaded into it is what `*(int *)` turned into an `int` -- 68
    # functions' first error was `'int' to 'int (*)(int)'` and its siblings.
    FNPTR_DECL_RE = (r"([A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*)\s*\(\s*(\*+)\s*"
                     r"([A-Za-z_]\w*)\s*\)\s*\(([^()]*)\)")
    for m in re.finditer(FNPTR_DECL_RE, c):
        ptr[m.group(3)] = "%s (*)(%s)" % (m.group(1), m.group(4))
    head = c[:c.find("{")] if "{" in c else c
    for m in re.finditer(r"\(([^()]*)\)", head):          # the parameter list
        for p in m.group(1).split(","):
            d = re.match(r"\s*((?:unsigned\s+|signed\s+)?[A-Za-z_]\w*)\s*(\*+)\s*"
                         r"([A-Za-z_]\w*)\s*$", p)
            if d:
                ptr[d.group(3)] = "%s %s" % (d.group(1), d.group(2))
                continue
            d = re.match(r"\s*((?:unsigned\s+|signed\s+)?(?:int|long))\s+([A-Za-z_]\w*)\s*$", p)
            if d:
                scalar[d.group(2)] = d.group(1)
    for m in re.finditer(r"(?m)^\s*([A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\**)\s*"
                         r"([A-Za-z_]\w*)\s*\(\s*\)\s*;", c):
        returns[m.group(2)] = m.group(1).strip()

    def ptr_valued(e):
        e = e.strip()
        if not e:
            return False
        if e.startswith("&"):
            return True
        if PTR_CAST_RE.match(e):
            return True
        n = re.match(r"([A-Za-z_]\w*)", e)
        if not n:
            return False
        if n.group(1) in ptr or n.group(1) in arrays:
            return True
        return "*" in returns.get(n.group(1), "")

    def is_64bit(e):
        if re.search(r"long\s+long", e):
            return True
        for n in set(re.findall(r"\b([A-Za-z_]\w*)\b", e)):
            if "long long" in scalar.get(n, "") or "long long" in returns.get(n, ""):
                return True
        return False

    def lvalue_type(lhs):
        """('ptr', type) / ('int', type) / None for an assignment target."""
        m = re.match(r"^([A-Za-z_]\w*)\s*\[\s*0\s*\]$", lhs)
        if m and m.group(1) in arrays:
            return ("ptr", ptr[m.group(1)])
        if lhs in ptr:
            return ("ptr", ptr[lhs])
        m = re.match(r"^\*\(\s*int\s*\*\)", lhs)
        if m:
            return ("int", "int")
        if lhs in scalar:
            return ("int", scalar[lhs])
        return None

    out = []
    for line in c.split("\n"):
        m = ASSIGN_RE.match(line.strip())
        if m:
            lhs, rhs = m.group("lhs").strip(), m.group("rhs").strip()
            kind = lvalue_type(lhs)
            indent = line[:len(line) - len(line.lstrip())]
            if kind == ("ptr", "int"):
                pass
            elif kind and kind[0] == "ptr":
                if ptr_valued(rhs):
                    mm = PTR_CAST_RE.match(rhs)
                    if not (mm and mm.group(1).replace(" ", "") == kind[1].replace(" ", "")):
                        line = "%s%s = (%s)(%s);" % (indent, lhs, kind[1], rhs)
                elif not is_64bit(rhs):
                    line = "%s%s = (%s)(%s);" % (indent, lhs, kind[1], rhs)
            elif kind and kind[0] == "int" and ptr_valued(rhs):
                line = "%s%s = (int)(%s);" % (indent, lhs, rhs)
        out.append(line)
    return "\n".join(out)


def arrayize_globals(c):
    """Force absolute addressing for the globals m2c named.

    m2c emits its own `extern void *DAT_00555048;`. That is a 4-byte object, which
    MWCC places in small data and addresses gp-relative — but retail uses absolute
    `lui at` / `lw`. Declaring the symbol as a 4-element array makes
    it non-small-data, and `DAT_x[0]` then compiles to exactly retail's sequence.
    """
    names = re.findall(r"^extern\s+[^;\n]*?\b(DAT_[0-9a-f]{8})\s*;\s*$", c, re.M)
    for n in names:
        c = re.sub(r"^(extern\s+[^;\n]*?)\b%s\b\s*;\s*$" % n,
                   lambda m: "%s %s[4];" % (m.group(1).rstrip(), n), c, count=1, flags=re.M)
        c = re.sub(r"\b%s\b(?!\s*\[)" % n, "%s[0]" % n, c)
    return c


def desymbolize_globals(c):
    """The other spelling: turn the named globals back into plain addresses.

    Retail sometimes materialises a stored pointer constant with `ori` from a
    scratch register rather than `addiu` into the destination, so the
    literal form has to stay available as a candidate.
    """
    # A store needs an lvalue: `0x555048 = x` is not valid C, and retail would use a
    # symbol there anyway (a stored pointer constant is `ori`, not a store to a
    # literal). Keep assignment targets as symbols; desymbolize only reads.
    keep = set(re.findall(r"(?<![=!<>])\b(DAT_[0-9a-f]{8})\b\s*=(?!=)", c))
    c = re.sub(r"^extern\s+[^;\n]*?\bDAT_[0-9a-f]{8}\s*;\s*$", "", c, flags=re.M)
    return re.sub(r"\bDAT_([0-9a-f]{8})\b(?!\s*\[)",
                  lambda m: m.group(0) if m.group(0) in keep else "0x%s" % m.group(1).upper(), c)


# `m2c.main` is not thread-safe (it mutates `sys.argv` and prints to `sys.stdout`), so
# only one thread may call it at a time. The compile/verify half is a `wibo`+`mwccps2`
# subprocess that releases the GIL, which is what `--jobs` exploits; the lock is held
# for ~3 ms per candidate, so many threads still scale.
_M2C_LOCK = threading.Lock()


class _ThreadStdout:
    """A `sys.stdout` shim that captures **per thread**.

    `contextlib.redirect_stdout` rebinds the *global* `sys.stdout`, so under `--jobs`
    a progress `print` from the aggregating thread lands inside a worker's capture
    buffer and is spliced into the m2c draft — the candidate then fails to compile,
    or compiles to something else, non-deterministically. Routing writes through a
    thread-local buffer keeps each worker's capture private and leaves every other
    thread on the real stream.
    """
    def __init__(self, real):
        self._real = real
        self.local = threading.local()

    def _stream(self):
        return getattr(self.local, "buf", None) or self._real

    def write(self, s):
        return self._stream().write(s)

    def flush(self):
        st = self._stream()
        if hasattr(st, "flush"):
            st.flush()

    def __getattr__(self, name):
        return getattr(self._real, name)


if not isinstance(sys.stdout, _ThreadStdout):
    sys.stdout = _ThreadStdout(sys.stdout)


@contextlib.contextmanager
def _capture_stdout():
    """Capture this thread's stdout writes (see `_ThreadStdout`)."""
    out = sys.stdout
    buf = io.StringIO()
    if isinstance(out, _ThreadStdout):
        prev = getattr(out.local, "buf", None)
        out.local.buf = buf
        try:
            yield buf
        finally:
            out.local.buf = prev
    else:                                   # sys.stdout was replaced since import
        with contextlib.redirect_stdout(buf):
            yield buf

# per-pool context, filled in main() before the threads start (read-only afterwards)
_CTX = {}


def _tag():
    """Scratch tag unique to this process *and* thread (see verify.TMP_TAG)."""
    return "%d_%d" % (os.getpid(), threading.get_ident())


# ---------------------------------------------------------------------------
# Width fitting.  The cleaner defaults an untyped member access to 4 bytes, but
# m2c only carries the real width when it had a cast to put on the value: a zero
# store (`arg0->unk20 = 0`) and a 64-bit value whose cast was dropped both leave
# `int`, so the store becomes a `sw`/`lw` where retail has `sb`/`sd`/`ld` (81 of
# the ≤3-diff near-misses).  The retail instruction is the authority, so read it.
WIDTH_OP = {"sb": "char", "sh": "short", "sw": "int", "sd": "long long",
            "lb": "char", "lbu": "unsigned char", "lh": "short",
            "lhu": "unsigned short", "lw": "int", "ld": "long long",
            "lwc1": "float", "swc1": "float"}
ACCESS_RE = re.compile(r"\*\(int \*\)\(\(char \*\)\((\w+)\) ([+-]) (\d+)\)")


def _base_reg(base):
    """m2c's name for a value -> the register it lives in, or None.

    m2c names a held value after its register (`temp_s1` is s1) and a parameter after
    its argument register (`arg0` is a0), so both forms are decodable.  Anything else
    (a struct member, a `var_sN` stack slot) is left alone: a wrong guess only fails to
    match, it never banks, but a needless one costs a variant per candidate.
    """
    if base.startswith("arg") and base[3:].isdigit():
        return "a" + base[3:]
    m = re.match(r"temp_([a-z]+\d*)(?:_\d+)?$", base)
    return m.group(1) if m else None


def retail_accesses(table, va, size):
    """{(base register, offset): C type} for a function's memory instructions."""
    out = {}
    for i in range(max(size, 0) // 4):
        e = table.get(va + 4 * i)
        if not e:
            continue
        mn, ops = e[0], e[1]
        if mn not in WIDTH_OP:
            continue
        m = re.search(r"(-?[0-9A-Fa-fx]+)\((\w+)\)\s*$", ops)
        if not m:
            continue
        off = am.imm(m.group(1))
        if off is not None:
            out[(m.group(2), off)] = WIDTH_OP[mn]
    return out


def fit_widths(c, va, size, table):
    """Rewrite a defaulted `int` access to the width retail uses at that (base, offset).

    Only the simple `*(int *)((char *)(argN) +/- OFF)` form is touched: the base is
    an m2c argument name, so `argN` maps to register `aN`, and a load or store in
    the function at the same (aN, OFF) supplies the real width.
    """
    acc = retail_accesses(table, va, size)
    if not acc:
        return c

    def repl(m):
        base, sign, off = m.group(1), m.group(2), int(m.group(3))
        reg = _base_reg(base)
        t = acc.get((reg, off if sign == "+" else -off)) if reg else None
        if t and t != "int":
            return "*(%s *)((char *)(%s) %s %d)" % (t, base, sign, off)
        return m.group(0)
    return ACCESS_RE.sub(repl, c)


LOADED_RE = re.compile(r"\b(\w+)\s*=\s*(DAT_\w+\[0\])\s*;")


def retype_global_loads(c):
    """Retype a local loaded from a global word as `void *`.

    m2c types the loaded handle `int`, so MWCC loads it straight into the first
    argument register and saves it afterwards (`lw a0,...; move s0,a0`); retail
    loads it into the saved register and moves to the argument (`lw s0,...;
    move a0,s0`).  Typing the local `void *` and casting the load reproduces retail
    -- 141 of the 142 <=3-diff `<Class>_InitFields` reflection field initialisers.
    """
    for name, load in LOADED_RE.findall(c):
        if re.search(r"\bint\s+%s\s*;" % re.escape(name), c):
            c = re.sub(r"\bint\s+%s\s*;" % re.escape(name), "void *%s;" % name, c)
            c = re.sub(r"\b%s\s*=\s*%s\s*;" % (re.escape(name), re.escape(load)),
                       "%s = (void *)%s;" % (name, load), c)
    return c


DECL_RE = re.compile(
    r"^\s*((?:void|char|int|unsigned char|unsigned int|short|long long"
    r"|unsigned long long)\s*\*?)\s*(\w+)\s*;$")


def order_pointer_decls(c):
    """Move pointer-typed locals before integer locals.

    MWCC assigns saved registers by declaration order, and the larger reflection
    initialisers want the field pointer in `s1` and the count in `s2`; m2c declares
    the count (`int temp_s2;`) before the pointer (`void *temp_v0;`), so the two saved
    registers come out swapped (a 6-instruction diff).  Pointers first reproduces
    retail -- 96 of the 237 remaining InitFields.  Verification decides.
    """
    lines = c.split("\n")
    i = 0
    while i < len(lines):
        if DECL_RE.match(lines[i]):
            j = i
            while j < len(lines) and DECL_RE.match(lines[j]):
                j += 1
            block = lines[i:j]
            if len(block) > 1:
                ptr = [l for l in block if "*" in DECL_RE.match(l).group(1)]
                other = [l for l in block if "*" not in DECL_RE.match(l).group(1)]
                if ptr + other != block:
                    lines[i:j] = ptr + other
                    return "\n".join(lines)
            i = j
        else:
            i += 1
    return c


def _match_paren(s, i):
    """Index just past the `)` matching the `(` at `s[i]`, or -1."""
    depth = 0
    while i < len(s):
        if s[i] == "(":
            depth += 1
        elif s[i] == ")":
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return -1


def _vcall_obj(base):
    r"""The address a vtable-call base loads its function pointer from.

    m2c's vtable call starts as `X->unkK()`: "load a word from an address A, then read the
    word at +K from it".  MWCC's C++ virtual call emits that same pair for an object at A
    (`lw t9,0(A); lw t9,K(t9); jalr t9`), so the rewrite needs **A** -- the *address of the
    load*, not the loaded value.  m2c spells it as `*(T *)(A)` (a typed load) or `(*E)`, the
    shorthand for `*(E)`; a naive `^\*(.+)$` grabs the typed form first and returns the cast
    instead of the address, which is why the member-load shape silently never fired.
    """
    b = base.strip()
    while b.startswith("(") and _match_paren(b, 0) == len(b):
        b = b[1:-1].strip()
    if not b.startswith("*"):
        return None
    b = b[1:].strip()
    if not b.startswith("("):
        return b or None                       # `*E` -- the shorthand
    e = _match_paren(b, 0)
    inner = b[1:e - 1].strip()
    if re.match(r"^\w+(?:\s+\w+)?\s*\*+$", inner):
        return b[e:].strip() or None           # `(T *)A` -> A
    return inner or None                       # `(E)` -> E


_VCALL_OPEN = "((int (*)())*("


def _vc_obj_key(e):
    """Normalise an object/argument expression for the `this`-strip comparison.

    m2c spells the same object differently on each side of the call: the vtable base
    becomes `((char *)(arg1) + 0)` (its cast+sized load) while the explicit first
    argument is the bare `arg1`.  A textual equality then misses the strip and the
    object is passed twice (retail has no second `move a1,a0`).  Reduce both to the
    underlying expression: peel balanced parentheses, a trailing `+ 0`, and a leading
    `(char *)` cast.
    """
    e = e.strip()
    while e.startswith("(") and _match_paren(e, 0) == len(e):
        e = e[1:-1].strip()
    e = re.sub(r"\+\s*0$", "", e).strip()
    e = re.sub(r"^\(\s*char\s*\*+\s*\)", "", e).strip()
    while e.startswith("(") and _match_paren(e, 0) == len(e):
        e = e[1:-1].strip()
    return e


def _vc_split_args(s):
    """Top-level comma split: a nested call's own commas are not separators."""
    out, depth, cur = [], 0, []
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    out.append("".join(cur))
    return out


def _vc_rewrite(c, defs):
    """`c` with every rewriteable vtable call re-spelled as a C++ virtual call.

    **Recurses into argument lists.**  A vtable call nested inside another call's
    arguments used to be left as a plain indirect call -- the loop replaced the
    outermost call and then skipped past its args -- and MWCC compiles a plain indirect
    call `jalr v0` where retail has the C++ ABI's `jalr t9`, so those functions could
    never match however many other calls in the body were rewritten.
    `defs` is the shared `(slot, nargs) -> class name` map for the whole function.
    """
    res, i = [], 0
    while True:
        j = c.find(_VCALL_OPEN, i)
        if j < 0:
            res.append(c[i:])
            break
        res.append(c[i:j])
        p = c.find(" *)", j + len(_VCALL_OPEN))
        if p < 0:
            res.append(c[i:])
            break
        p += len(" *)")
        if c[p:p + 10] != "((char *)(":
            res.append(c[i:j + 1])
            i = j + 1
            continue
        bstart = p + 9
        bend = _match_paren(c, bstart)
        if bend < 0:
            res.append(c[i:j + 1])
            i = j + 1
            continue
        m = re.match(r" \+ (\d+)\)\)\(", c[bend:])
        if not m:
            res.append(c[i:j + 1])
            i = j + 1
            continue
        astart = bend + m.end() - 1
        aend = _match_paren(c, astart)
        if aend < 0:
            res.append(c[i:j + 1])
            i = j + 1
            continue
        K = int(m.group(1))
        base = c[bstart + 1:bend - 1]
        args = _vc_rewrite(c[astart + 1:aend - 1], defs)
        obj = _vcall_obj(base)
        if obj is None or not obj or K < 8 or K % 4:
            # Not rewriteable, but a nested call inside its arguments still is.
            res.append(c[i:astart + 1] + args + c[aend - 1:aend])
            i = aend
            continue
        cargs = [a.strip() for a in _vc_split_args(args)] if args.strip() else []
        # A C++ virtual call passes the object as `this`, so an explicit first argument
        # that *is* the object would be passed twice (retail has no second `move a1,a0`).
        if cargs and _vc_obj_key(cargs[0]) == _vc_obj_key(obj):
            cargs = cargs[1:]
        nargs = len(cargs)
        cname = "DW4VC_%d_%d" % (K, nargs)
        defs[(K, nargs)] = cname
        sargs = ", ".join("(int)(%s)" % a for a in cargs)
        res.append("((%s *)(%s))->vX(%s)" % (cname, obj, sargs))
        i = aend
    return "".join(res)


_SRET_CALL_RE = re.compile(
    r"^(\s*)\(\((DW4VC_(\d+)_(\d+)) \*\)\((.*)\)\)->vX\((.*)\);\s*$")


def _virtualize_sret_statements(body):
    """Turn a standalone virtual out-call into MWCC's hidden struct return.

    m2c sees a C++ method returning a class by value as a C-style call whose first
    argument is the address of a stack local.  The cleaned source therefore looks
    like this::

        int sp2C;
        ((DW4VC_280_1 *)(arg1))->vX((int)(&sp2C));
        use(sp2C);

    MWCC's MIPS C++ ABI passes the hidden return buffer in ``a0`` and shifts
    ``this`` to ``a1``.  Re-spelling the statement as a four-byte class return is
    what produces retail's ``lw t9,0(a1)`` call shape.  Keep the
    transform deliberately narrow: a discarded-result statement, an ``int`` local,
    and a first argument that is exactly that local's address.  Verification is
    still the oracle, but the narrow shape avoids multiplying variants for ordinary
    output-parameter calls.

    Returns ``(rewritten_body, defs)`` where each definition is
    ``(slot_offset, explicit_arg_count, return_struct, class_name)``.
    """
    lines = body.splitlines()
    decls = {}
    for i, line in enumerate(lines):
        m = re.match(r"^(\s*)int\s+([A-Za-z_]\w*)\s*;\s*$", line)
        if m:
            decls[m.group(2)] = (i, m.group(1))

    candidates = []
    for i, line in enumerate(lines):
        m = _SRET_CALL_RE.match(line)
        if not m:
            continue
        indent, _, k_s, _, obj, arg_text = m.groups()
        args = [a.strip() for a in _vc_split_args(arg_text)] if arg_text.strip() else []
        if not args:
            continue
        out = re.match(r"^\(int\)\s*\(&([A-Za-z_]\w*)\)$", args[0])
        if not out or out.group(1) not in decls:
            continue
        local = out.group(1)
        explicit = args[1:]
        # m2c sometimes leaves the C ABI's explicit `this` immediately after the
        # hidden return buffer: `vX(&out, object, arg)`.  `_vc_rewrite` cannot drop
        # it as an ordinary first argument because the buffer precedes it.  In the
        # C++ spelling the object is already `this`, so retain only the arguments
        # after an exact `(int)(object)` match.  This is the repeated shape in the
        # 0x002d0a10/0x0031d3f0/0x00322820 families; do not infer it from type or
        # position alone.
        if explicit and explicit[0] == "(int)(%s)" % obj.strip():
            explicit = explicit[1:]
        # One hidden-return call owns one local.  Sharing it between two calls needs
        # control-flow reasoning and is outside this mechanical source shape.
        if any(c[1] == local for c in candidates):
            continue
        candidates.append((i, local, int(k_s), obj, explicit, indent))

    if not candidates:
        return body, []

    defs = []
    transformed = set()
    for call_i, local, K, obj, args, indent in candidates:
        decl_i, decl_indent = decls[local]
        ret = "DW4SR4"
        cname = "DW4VCSR_%d_%d" % (K, len(args))
        lines[decl_i] = "%s%s %s;" % (decl_indent, ret, local)
        # `_vc_rewrite` has already cast every explicit argument to `int`.
        sargs = ", ".join(args)
        lines[call_i] = "%s%s = ((%s *)(%s))->vX(%s);" % (
            indent, local, cname, obj, sargs)
        transformed.add(local)
        defs.append((K, len(args), ret, cname))

    # All other word uses refer to the sole word in the returned class.  Skip the
    # declaration and assignment produced above; address-taking elsewhere becomes
    # ``&local.w0``, which preserves the address while keeping the C++ type honest.
    for local in transformed:
        decl_i, _ = decls[local]
        call_i = next(c[0] for c in candidates if c[1] == local)
        for i, line in enumerate(lines):
            if i in (decl_i, call_i):
                continue
            lines[i] = re.sub(r"\b%s\b" % re.escape(local), local + ".w0", line)
    return "\n".join(lines) + ("\n" if body.endswith("\n") else ""), defs


def virtualize_calls(c, name, sret=False):
    """Re-spell m2c's vtable calls as C++ virtual calls, as a `.cpp` source.

    MWCC's **C** front end emits `jalr v0` for an indirect call; its **C++** front end emits
    the MIPS C++ ABI sequence `lw t9,0(A); lw t9,K(t9); jalr t9`.  So every function whose
    retail body contains a vtable call is unreachable from C, however good the cleaner gets
    -- 1,449 unmatched functions (13.5 %) contain a `jalr t9`, and **no** matched function
    does.  The rewrite is the only thing that was missing: the cleaned C is regular
    (`((int (*)())*(T *)((char *)(BASE) + K))(ARGS)`), the object base is recoverable, and
    `tools/units.py`/`tools/verify.py` already dispatch on the file extension.

    Two traps, both paid for: MWCC reserves **two** vtable slots, so a target at byte K needs
    `K/4 - 2` preceding virtuals; and every declaration has to sit in `extern "C"`, or the
    definition is mangled and `verify.py` cannot find the symbol.

    With ``sret=True``, also try the statement-level hidden-return spelling.  It is a separate variant because an address-first virtual call
    may be an ordinary output parameter rather than a class return.

    Returns the `.cpp` source, or None when the requested shape is absent.
    """
    defs = {}
    body = _vc_rewrite(c, defs)
    # C++ reads `T (*)()` as a pointer to a function taking *no* arguments, so a call
    # through one of the cleaner's casts stops compiling as soon as it has arguments.
    # The remaining casts are the ones the rewrite did not claim (m2c's nested calls).
    body = re.sub(r"\(\s*(\w+(?:\s+\w+)?)\s*\(\*\)\(\)\s*\)", r"(\1 (*)(...))", body)
    if not defs:
        return None
    sret_defs = []
    if sret:
        body, sret_defs = _virtualize_sret_statements(body)
        if not sret_defs:
            return None
    # C++ reads `T (*)()` as a pointer to a function taking *no* arguments, so a call
    # through one of the cleaner's casts stops compiling as soon as it has arguments.
    # The remaining casts are the ones the rewrite did not claim (m2c's nested calls).
    body = re.sub(r"\(\s*(\w+(?:\s+\w+)?)\s*\(\*\)\(\)\s*\)", r"(\1 (*)(...))", body)
    if not defs:
        return None
    m = re.search(r"(?m)^[^\n]*\b%s\s*\(" % re.escape(name), body)
    if not m:
        return None
    head, rest = body[:m.start()], body[m.start():]
    brace = rest.find("{")
    if brace < 0:
        return None
    sig = rest[:brace].strip() + ";"
    # C++ is strict where C is not: `int f();` is a function taking *no* arguments, so every
    # callee the cleaner wrote as `f()` has to be declared variadic (`f(...)`) or the calls
    # below it stop compiling. The function's own declaration is dropped here and re-added
    # with its real signature, so the definition keeps C linkage.
    keep = []
    for ln in head.strip().split("\n"):
        if ln.strip() and re.search(r"\b%s\s*\(" % re.escape(name), ln):
            continue
        keep.append(re.sub(r"\(\s*\);\s*$", "(...);", ln))
    head = "\n".join(keep)
    cls = []
    for (K, nargs), cname in sorted(defs.items()):
        # The sret pass replaces the int-returning call with a sibling class.  Do
        # not leave the now-unused baseline class in the banked source.
        if not re.search(r"\b%s\b" % re.escape(cname), body):
            continue
        dummy = "".join(" virtual void d%d();" % t for t in range(K // 4 - 2))
        cls.append("class %s { public:%s virtual int vX(%s); };"
                   % (cname, dummy, ", ".join(["int"] * nargs)))
    if sret_defs:
        cls.insert(0, "struct DW4SR4 { int w0; };")
        for K, nargs, ret, cname in sorted(set(sret_defs)):
            dummy = "".join(" virtual void d%d();" % t for t in range(K // 4 - 2))
            cls.append("class %s { public:%s virtual %s vX(%s); };"
                       % (cname, dummy, ret, ", ".join(["int"] * nargs)))
    return ("extern \"C\" {\n" + head.strip() + "\n" + sig + "\n}\n"
            + "\n".join(cls) + "\n" + rest)


REPAIR_ROUNDS = 12
_BUILTIN_ARGS = {"memcpy": 3, "memmove": 3, "memset": 3, "memcmp": 3, "strcmp": 2, "strcpy": 2,
                 "strncmp": 3, "strncpy": 3, "strcat": 2, "strlen": 1, "strchr": 2}
_BITWISE_FROM = {"float": "int", "double": "long long", "int": "float", "unsigned int": "float",
                 "long long": "double", "unsigned long long": "double"}


def _operand_end(c, i):
    """The end of the unary operand starting at c[i]: a parenthesis, or a word and its indexing."""
    while c[i] in "*&":
        i += 1
    if c[i] == "(":
        i = _match_paren(c, i)
    else:
        m = re.compile(r"[\w.]+").match(c, i)
        i = m.end() if m else i
    while i < len(c) and c[i] == "[":
        i = c.index("]", i) + 1
    return i


def _repair_bitwise(c):
    used = {}
    pat = re.compile(r"\(bitwise ([\w ]+?)\) ?")
    while True:
        m = pat.search(c)
        if not m:
            break
        kind = m.group(1)
        if kind not in _BITWISE_FROM:
            return c
        end = _operand_end(c, m.end())
        helper = "bitwise_" + kind.replace(" ", "_")
        used[helper] = kind
        c = c[:m.start()] + helper + "(" + c[m.end():end] + ")" + c[end:]
    head = "".join("static inline %s %s(%s x) { union { %s a; %s b; } u; u.a = x; return u.b; }\n"
                   % (k, h, _BITWISE_FROM[k], _BITWISE_FROM[k], k) for h, k in sorted(used.items()))
    return head + c


def _repair_calls(c):
    """`*(int *)(x)(args)` calls the loaded word, so the cast belongs around the load."""
    key = "*(int *)("
    i = c.find(key)
    while i >= 0:
        close = _match_paren(c, i + len(key) - 1)
        nxt = i + len(key)
        if c[close:close + 1] == "(" and c[i - 1:i] != ")":
            call = "((int (*)())" + c[i:close] + ")"
            c = c[:i] + call + c[close:]
            nxt = i + len(call)
        i = c.find(key, nxt)
    return c


def _repair_types(c):
    """Cast where m2c mixes a pointer with an integer, which C++-strict MWCC refuses."""
    kinds = {}
    for m in re.finditer(r"^\s*(?:unsigned )?(int|char|short|void|long long|float|s128)\s*(\*+)?\s*(\w+);$", c, re.M):
        kinds[m.group(3)] = "ptr" if m.group(2) else "int" if m.group(1) != "float" else "float"
    for m in re.finditer(r"[(,]\s*(?:unsigned )?(?:int|char|short|void)\s*(\*+)?\s*(arg\d+)", c):
        kinds[m.group(2)] = "ptr" if m.group(1) else "int"

    def operands(m):
        a, op, b = m.group(1), m.group(2), m.group(3)
        if kinds.get(a) == "ptr" and kinds.get(b) == "int":
            return "(int)%s %s %s" % (a, op, b)
        if kinds.get(a) == "int" and kinds.get(b) == "ptr":
            return "%s %s (int)%s" % (a, op, b)
        return m.group(0)
    c = re.sub(r"\b(\w+) (==|!=|<=|>=|<|>|-) (\w+)\b", operands, c)
    c = re.sub(r" - &(\w+\[0\])", r" - (int)&\1", c)
    head = re.search(r"^(\w[\w ]*\*+)\s*\w+\(", c, re.M)
    if head:
        kind = head.group(1).strip()
        c = re.sub(r"^(\s*)return (?!\(%s\))(?!0;)(.+);$" % re.escape(kind),
                   lambda m: "%sreturn (%s)(%s);" % (m.group(1), kind, m.group(2)), c, flags=re.M)
    return c


def _repair_duplicates(c):
    """m2c gives one stack slot an `int` placeholder and a typed local: keep the typed one."""
    typed = set(re.findall(r"^\s*[\w ]+\*+\s*(sp\w*);$", c, re.M))
    return re.sub(r"^\s*int (sp\w*);\n", lambda m: "" if m.group(1) in typed else m.group(0), c, flags=re.M)


def _repair_wrapper(c):
    """A wrapper leaves leading arguments in registers, so m2c drops them from a builtin's call."""
    m = re.search(r"^(\w+ \*?)(\w+)\(void\) \{", c, re.M)
    if not m:
        return c
    for name, want in _BUILTIN_ARGS.items():
        call = re.search(r"\b%s\(([^;()]*)\)" % name, c[m.end():])
        if not call:
            continue
        have = [x for x in call.group(1).split(",") if x.strip()]
        missing = ["a", "b", "c"][:want - len(have)]
        if not missing:
            continue
        at = m.end() + call.start(1)
        c = c[:at] + ", ".join(missing + [x.strip() for x in have]) + c[m.end() + call.end(1):]
        return c[:m.start(2) + len(m.group(2))] + "(" + ", ".join("int " + x for x in missing) + ")" \
            + c[m.end() - 2:]
    return c


def repair(c):
    """The spellings MWCC or gcc refuse in a draft. A variant only: verify still decides."""
    c = re.sub(r"\(unaligned ([\w ]+?\*?)\)", r"(\1)", c)
    c = c.replace("**(int *)(", "**(int **)(").replace("*(*(int *)(", "*(*(int **)(")
    if "s128" in c:
        c = "typedef struct { int word[4]; } s128;\n" + c
    for step in (_repair_bitwise, _repair_calls, _repair_duplicates, _repair_types, _repair_wrapper):
        c = step(c)
    return c


_BRANCH_LINE = re.compile(r"\b(?:b\w*|j|jr|jal|jalr)\s")


def expand_asm(asm):
    """Rewrite instructions m2c does not know as ones it does, for the draft only.

    `adda.s` and `madd.s` keep a sum in the accumulator, which C writes as `a + b + c * d`.
    `c1` is an undecoded `sqrt.s`. An `ldl`/`ldr` or `sdl`/`sdr` pair is one unaligned word, and
    `pcpyld rd,zero,rt` only widens a 64-bit value. verify compares the result with retail.
    """
    if "adda.s" in asm and ("$f30" in asm or "$f31" in asm):
        return asm
    out = []
    for line in asm.split("\n"):
        body = line.split("#")[0]
        m = re.search(r"\badda\.s\s+(\$f\d+),\s*(\$f\d+)", body)
        if m:
            out.append(line[:m.start()] + "add.s $f31, %s, %s" % m.groups())
            continue
        m = re.search(r"\bmadd\.s\s+(\$f\d+),\s*(\$f\d+),\s*(\$f\d+)", body)
        if m and not (out and _BRANCH_LINE.search(out[-1].split("#")[0])):
            pre = line[:m.start()]
            out.append(pre + "mul.s $f30, %s, %s" % (m.group(2), m.group(3)))
            out.append(pre + "add.s %s, $f31, $f30" % m.group(1))
            continue
        m = re.search(r"\bc1\s+0x([0-9a-fA-F]+)", body)
        if m and int(m.group(1), 16) & 63 == 4:
            word = int(m.group(1), 16)
            out.append(line[:m.start()] + "sqrt.s $f%d, $f%d" % ((word >> 6) & 31, (word >> 16) & 31))
            continue
        m = re.search(r"\b(ldl|sdl)\s", body)
        if m:
            out.append(line[:m.start()] + "nop")
            continue
        m = re.search(r"\b(ldr|sdr)\s", body)
        if m:
            out.append(line[:m.start()] + ("ld " if m.group(1) == "ldr" else "sd ") + line[m.end():])
            continue
        m = re.search(r"\bpcpyld\s+(\$\w+),\s*\$zero,\s*(\$\w+)", body)
        if m:
            out.append(line[:m.start()] + "move %s, %s" % m.groups())
            continue
        out.append(line)
    return "\n".join(out)


def _last_definition(c):
    return list(re.finditer(r"^([\w ]*?[\w*] ?\*?)(\w+)\(([^()\n]*)\) \{", c, re.M))[-1:]


def _with_params(c, m, params):
    head = re.sub(r"^(\w[^\n(]*\b%s\()[^()\n]*(\);)$" % re.escape(m.group(2)),
                  lambda p: p.group(1) + params + p.group(2), c[:m.start(3)], flags=re.M)
    return head + params + c[m.end(3):]


def _tail_argument(asm):
    """The C for an argument a tail call computes in its delay slot, or None."""
    lines = [l.split("*/")[-1].strip() for l in asm.split("\n") if "*/" in l]
    if len(lines) < 2 or not re.match(r"j\s", lines[-2]):
        return None
    m = re.match(r"lw\s+\$a(\d),\s*(-?(?:0x)?[0-9a-fA-F]+)\(\$a(\d)\)", lines[-1])
    if m:
        return int(m.group(1)), int(m.group(3)), "*(int *)((char *)arg%s + %d)" % (m.group(3), int(m.group(2), 0))
    m = re.match(r"addiu\s+\$a(\d),\s*\$a(\d),\s*(-?(?:0x)?[0-9a-fA-F]+)", lines[-1])
    if m:
        return int(m.group(1)), int(m.group(2)), "(int)((char *)arg%s + %d)" % (m.group(2), int(m.group(3), 0))
    m = re.match(r"move\s+\$a(\d),\s*\$zero", lines[-1])
    if m:
        return int(m.group(1)), None, "0"
    return None


def argument_variants(c, asm):
    """Drafts restoring what m2c loses when an argument only passes through registers.

    Retail states these outright: an unused parameter, a value left in `a0` for the callee, a tail
    call's delay-slot argument, a word loaded but stored narrower, and a byte offset that m2c left
    on an `int *`, which C would scale a second time.
    """
    found = _last_definition(c)
    if not found:
        return []
    m = found[0]
    params = m.group(3).strip()
    out = []
    named = [int(x) for x in re.findall(r"\barg(\d)\b", params)]
    if named and len(named) <= max(named):
        have = {int(x.group(1)): x.group(0) for x in re.finditer(r"[^,]*\barg(\d)\b", params)}
        out.append(_with_params(c, m, ", ".join(have.get(i, "int arg%d" % i).strip()
                                                for i in range(max(named) + 1))))
    body = c[m.end():]
    calls = [x for x in re.finditer(r"\b(\w+)\(([^;{}]*)\);", body)
             if x.group(1) not in ("if", "while", "switch", "return", "sizeof")]
    if params in ("", "void") and len(calls) == 1:
        call = calls[0]
        for k in (1, 2, 3):
            names = ["p%d" % i for i in range(k)]
            args = ", ".join(names + ([call.group(2)] if call.group(2).strip() else []))
            text = c[:m.end()] + body[:call.start(2)] + args + body[call.end(2):]
            out.append(_with_params(text, m, ", ".join("int " + n for n in names)))
    tail = _tail_argument(asm)
    if tail and len(calls) >= 1:
        reg, base, expr = tail
        call = calls[-1]
        have = [x.strip() for x in call.group(2).split(",") if x.strip()]
        if len(have) <= reg:
            have += ["0"] * (reg - len(have)) + [expr]
            text = c[:m.end()] + body[:call.start(2)] + ", ".join(have) + body[call.end(2):]
            if base is not None and "arg%d" % base not in params:
                need = ", ".join("void *arg%d" % i for i in range(base + 1))
                text = _with_params(text, m, need)
            out.append(text)
    scaled = re.sub(r"\(&(\w+)\[0\] \+ \((\w+) \* 4\)\)", r"((char *)&\1[0] + (\2 * 4))", c)
    for walker in re.findall(r"\b(\w+) = \(int \*\)\(", c):
        scaled = re.sub(r"\b%s \+= 4;" % walker, "%s += 1;" % walker, scaled)
    if scaled != c:
        out.append(scaled)
    for narrow in ("short", "unsigned short", "char", "unsigned char"):
        widened = c.replace("(%s) *(%s *)" % (narrow, narrow), "(%s) *(int *)" % narrow)
        if widened != c:
            out.append(widened)
    return out


_ARG_REGS = ["$a%d" % i for i in range(8)]
_FLOAT_REGS = ["$f%d" % i for i in range(12, 20)]
_MEM_TYPES = {"lw": "int", "lh": "short", "lhu": "unsigned short", "lb": "char", "lbu": "unsigned char",
              "ld": "long long", "lwc1": "float", "sw": "int", "sh": "short", "sb": "unsigned char",
              "sd": "long long", "swc1": "float"}
_BINARY = {"addu": "+", "daddu": "+", "subu": "-", "and": "&", "or": "|", "xor": "^", "mult": "*",
           "mult1": "*", "add.s": "+", "sub.s": "-", "mul.s": "*", "div.s": "/"}
_SHIFTS = {"sll": "<<", "sra": ">>", "dsll": "<<", "dsra": ">>"}
_FRAME = re.compile(r"(addiu\s+\$sp,\s*\$sp|[ls]d\s+\$ra,)")


class _NotStraightLine(Exception):
    pass


class _TailCall:
    """What straight-line code holds in each argument register when it reaches a tail call."""

    def __init__(self):
        self.regs = {"$zero": "0"}
        self.regs.update({r: "arg%d" % i for i, r in enumerate(_ARG_REGS)})
        self.regs.update({r: "farg%d" % i for i, r in enumerate(_FLOAT_REGS)})
        self.high = {}
        self.consts = {}
        self.globals = {}
        self.stmts = []

    def read(self, reg):
        if reg not in self.regs:
            raise _NotStraightLine(reg)
        return self.regs[reg]

    def write(self, reg, value, const=None):
        self.regs[reg] = value
        self.high.pop(reg, None)
        self.consts.pop(reg, None)
        if const is not None:
            self.consts[reg] = const

    def place(self, operand, kind):
        """The C lvalue for a memory operand."""
        m = re.match(r"%(?:lo|gp_rel)\((\w+)\)\((\$\w+)\)$", operand)
        if m:
            self.globals[m.group(1)] = kind
            return m.group(1)
        m = re.match(r"(-?(?:0x)?[0-9a-fA-F]+)\((\$\w+)\)$", operand)
        if not m:
            raise _NotStraightLine(operand)
        return "*(%s *)((char *)(%s) + %d)" % (kind, self.read(m.group(2)), int(m.group(1), 0))

    def step(self, line):
        op, _, rest = line.partition(" ")
        args = [x.strip() for x in rest.split(",")]
        if op == "nop" or _FRAME.match(line):
            return
        if op == "move":
            self.write(args[0], self.read(args[1]), self.consts.get(args[1]))
        elif op == "li":
            value = int(args[1], 0)
            self.write(args[0], str(value), value)
        elif op == "lui":
            m = re.match(r"%hi\((\w+)\)$", args[1])
            if m:
                self.write(args[0], "0")
                self.high[args[0]] = m.group(1)
            else:
                value = int(args[1], 0) << 16
                self.write(args[0], str(value), value)
        elif op == "ori" and args[0] == args[1] and args[1] in self.consts:
            value = self.consts[args[1]] | int(args[2], 0)
            self.write(args[0], "0x%X" % value, value)
        elif op == "addiu":
            m = re.match(r"%lo\((\w+)\)$", args[2])
            if m:
                self.globals.setdefault(m.group(1), "int")
                self.write(args[0], "(int)&%s" % m.group(1))
            else:
                self.write(args[0], "(%s + %d)" % (self.read(args[1]), int(args[2], 0)))
        elif op in ("dsll32", "dsra32") and args[2] == "0x10":
            if op == "dsll32":
                self.write(args[0], "(short)%s" % self.read(args[1]))
            else:
                self.write(args[0], self.read(args[1]))
        elif op in _SHIFTS:
            self.write(args[0], "(%s %s %d)" % (self.read(args[1]), _SHIFTS[op], int(args[2], 0)))
        elif op in _BINARY and len(args) == 3:
            self.write(args[0], "(%s %s %s)" % (self.read(args[1]), _BINARY[op], self.read(args[2])))
        elif op == "mtc1":
            if args[0] not in self.consts:
                raise _NotStraightLine(line)
            value = struct.unpack("<f", struct.pack("<I", self.consts[args[0]] & 0xFFFFFFFF))[0]
            self.write(args[1], "%sf" % repr(value))
        elif op in _MEM_TYPES and op[0] == "l":
            self.write(args[0], self.place(args[1], _MEM_TYPES[op]))
        elif op in _MEM_TYPES:
            self.stmts.append("%s = %s;" % (self.place(args[1], _MEM_TYPES[op]), self.read(args[0])))
        else:
            raise _NotStraightLine(line)


def _tail_arguments(regs, initial):
    changed = [i for i, r in enumerate(regs) if regs[r] != initial[r]]
    return max(changed) + 1 if changed else 0


def _argument_kind(value, style):
    """The parameter type a callee declares for `value`.

    MWCC schedules a load into the delay slot only when no conversion stands between it and the
    argument, so a field's type shows in the code: `loaded` needs none, `converted` needs one.
    """
    if style == "loaded" and re.match(r"\(arg\d [+-] \d+\)$", value):
        return "char *"
    m = re.match(r"\*\(([\w ]+) \*\)", value)
    if not m:
        return "int"
    if m.group(1) == "long long" or style == "loaded":
        return m.group(1)
    return "unsigned int" if style == "converted" and m.group(1) == "int" else "int"


def tail_call_drafts(name, asm):
    """C for a function that is straight-line code ending in a tail call.

    m2c reports a callee's arguments only where it can see them used, so one set in a delay slot,
    swapped through `v0`, or held in `a4`-`a7` goes missing. This reads the argument registers at
    the jump instead. verify compares every draft with retail, so a wrong guess costs nothing.
    """
    lines = [re.sub(r"\s+", " ", l.split("*/")[-1].strip()) for l in asm.split("\n") if "*/" in l]
    if len(lines) < 2 or not lines[-2].startswith("j ") or any(_BRANCH_LINE.match(l) for l in lines[:-2]):
        return []
    state = _TailCall()
    initial = dict(state.regs)
    try:
        for line in lines[:-2] + lines[-1:]:
            state.step(line)
    except (_NotStraightLine, ValueError, IndexError):
        return []
    callee = lines[-2].split()[1]
    ints = {r: state.regs[r] for r in _ARG_REGS}
    floats = {r: state.regs[r] for r in _FLOAT_REGS}
    need, need_f = _tail_arguments(ints, initial), _tail_arguments(floats, initial)
    decls = "".join("extern %s %s;\n" % (k, g) for g, k in state.globals.items() if g != callee)
    out = []
    for extra, style, kind in itertools.product((0, 1, 2), ("loaded", "plain", "converted"), ("void", "int")):
        count = min(8, need + extra)
        values = [ints[r] for r in _ARG_REGS[:count]] + [floats[r] for r in _FLOAT_REGS[:need_f]]
        kinds = [_argument_kind(v, style) for v in values[:count]] + ["float"] * need_f
        if style == "converted":
            values = ["(unsigned int)" + v if k == "unsigned int" else v for v, k in zip(values, kinds)]
        seen = " ".join(state.stmts + values)
        used = [int(x) for x in re.findall(r"\barg(\d)\b", seen)]
        used_f = [int(x) for x in re.findall(r"\bfarg(\d)\b", seen)]
        bases = re.findall(r"\(arg(\d) [+-] \d+\)", seen) if "char *" in kinds else []
        params = ["%s arg%d" % ("char *" if str(i) in bases else "int", i)
                  for i in range(max(used) + 1 if used else 0)]
        params += ["float farg%d" % i for i in range(max(used_f) + 1 if used_f else 0)]
        call = "%s%s(%s);" % ("return " if kind == "int" else "", callee, ", ".join(values))
        body = "".join("    %s\n" % x for x in state.stmts + [call])
        text = "%s%s %s(%s);\n%s %s(%s) {\n%s}\n" % (
            decls, kind, callee, ", ".join(kinds) or "void", kind, name, ", ".join(params) or "void", body)
        out.append(text)
        if "(short)arg" in text:
            narrow = re.sub(r"\(short\)(arg\d)", r"\1", text)
            for i in set(re.findall(r"\(short\)arg(\d)", text)):
                narrow = narrow.replace("int arg%s" % i, "short arg%s" % i)
            out.append(narrow)
    return list(dict.fromkeys(out))


def _error_line(src, rep):
    """The line a compile report blames, as an index into `src`, which the report numbers from 2."""
    head = rep.splitlines()[0]
    m = re.search(r"compile failed: (\d+): (.*?) \| ", head) or re.search(r"\.c:(\d+): ()", head.split(" | ")[1] if " | " in head else "")
    if not m:
        return None
    lines = src.splitlines()
    n = int(m.group(1)) - 2
    frag = m.group(2).strip()
    for k in (n, n - 1, n + 1, n - 2, n + 2):
        if 0 <= k < len(lines) and frag in lines[k]:
            return k
    return None


def _cast_sides(line):
    m = re.match(r"^(\s*(?:\} else )?if \()(.+?) (==|!=|<=|>=|<|>) (.+)(\) \{)$", line)
    if m:
        return "%s(int)(%s) %s (int)(%s)%s" % m.groups()
    m = re.match(r"^(\s*[^=]+ = )(.+) (-|\+) (.+);$", line)
    if m:
        return "%s(int)(%s) %s (int)(%s);" % m.groups()
    return None


def repair_error(src, rep):
    """Mend the one line a compile report blames; None when the report offers no safe change."""
    head = rep.splitlines()[0]
    undefined = re.search(r"undefined identifier '(sp\w*)'|`(sp\w*)' undeclared", head)
    if undefined:
        name = undefined.group(1) or undefined.group(2)
        return re.sub(r"^(\w[^\n]*\) \{\n)", lambda m: m.group(1) + "    int %s;\n" % name, src, count=1, flags=re.M)
    k = _error_line(src, rep)
    if k is None:
        return None
    lines = src.splitlines()
    line = lines[k]
    conv = re.search(r"illegal implicit conversion from '[^']*' to \| ?'([^']*)'|illegal implicit conversion from '[^']*' to '([^']*)'", head)
    new = None
    if conv:
        kind = conv.group(1) or conv.group(2)
        if "struct" in kind:
            return None
        m = re.match(r"^(\s*(?:return|[^=(]+ =) )(.+);$", line)
        if m:
            new = "%s(%s)(%s);" % (m.group(1), kind, m.group(2))
    elif "illegal operand" in head or "invalid operands" in head:
        new = _cast_sides(line)
    elif "pointer/array required" in head or "invalid type argument" in head:
        new = re.sub(r"(?<![\w)*])\*(\w+)\b", r"*(int *)\1", line, count=1)
        if new == line:
            new = re.sub(r"\b(\w+)\[", r"((int *)\1)[", line, count=1)
    if new is None or new == line:
        return None
    lines[k] = new
    return "\n".join(lines) + "\n"


def score_candidate(cand):
    """Run one candidate end to end; returns (row, ok, src, report, kind).

    `kind` is "ok", "sdk" or "m2cfail". Pure w.r.t. shared state — the only global
    touched is `_CTX` (read-only) — so it can run in a thread pool.
    """
    va, sz, name = cand
    ctx = _CTX
    if va in ctx["sdk"]:
        return (name, "0x%08x" % va, sz, "sdk", -1, ""), False, None, "", "sdk"
    asm = m2c_one.asm_for(va, name, sz, ctx["table"], ctx["names"], bounds=ctx["bounds"],
                          jtables=ctx["jtabs"].get(va, {}), gp=ctx["gp"])
    asm = expand_asm(asm)
    # a Sony EE GCC unit (config/SLUS-20836/units.tsv) is decompiled for gcc, everything else for MWCC
    target = "mipsee-gcc-c" if va in ctx.get("eegcc", ()) else "mipsee-mwcc-c"
    try:
        with _M2C_LOCK:
            c_src = run_m2c(asm, name, os.path.join(cc.scratch_dir(), "m2c_batch_%s.s" % _tag()),
                            target=target, context=ctx["context"])
    except Exception:                             # noqa: BLE001
        return None, False, None, "", "m2cfail"
    if not c_src.strip() or "Decompilation failure" in c_src or "Decompilation error" in c_src:
        return None, False, None, "", "m2cfail"
    # Keep the *best* mode's report, not the last one's. `rep` used to be left over
    # from `literal`, so a candidate whose hybrid form compiled but whose literal
    # form did not was recorded as `compile` — 2,467 rows of the queue were hidden
    # that way (52 of them ≤3 instruction diffs). status/diffs/mode must all describe
    # the same spelling.
    best = None                  # (nb, mode, src, ok, rep)
    for mode in ("hybrid", "symbol", "literal"):
        src = clean(c_src, addr_mode=mode, bounds=ctx["bounds"])
        # The cleaner defaults an untyped access to 4 bytes; `fit_widths` re-reads
        # the width from the retail instruction (see its comment), so verify both.
        variants = [(src, mode)]
        fit = fit_widths(src, va, sz, ctx["table"])
        if fit != src:
            variants.append((fit, mode + "+w"))
        for base, tag in list(variants):
            ptr = retype_global_loads(base)
            if ptr != base:
                variants.append((ptr, tag + "+p"))
                od = order_pointer_decls(ptr)
                if od != ptr:
                    variants.append((od, tag + "+po"))
            od = order_pointer_decls(base)
            if od != base and all(od != v for v, _ in variants):
                variants.append((od, tag + "+o"))
        # C++ virtual calls: MWCC's C front end cannot emit `jalr t9`, so a function whose
        # retail body contains one is unreachable from C.
        for base, tag in list(variants):
            vc = virtualize_calls(base, name)
            if vc and all(vc != v for v, _ in variants):
                variants.append((vc, tag + "+vcpp"))
            sret = virtualize_calls(base, name, sret=True)
            if sret and all(sret != v for v, _ in variants):
                variants.append((sret, tag + "+sretvcpp"))
        for base, tag in list(variants):
            for i, extra in enumerate(argument_variants(base, asm)):
                if all(extra != v for v, _ in variants):
                    variants.append((extra, "%s+a%d" % (tag, i)))
        for base, tag in list(variants):
            fixed = repair(base)
            if fixed != base:
                variants.append((fixed, tag + "+r"))
        if mode == "hybrid":
            variants = [(x, "tail%d" % i) for i, x in enumerate(tail_call_drafts(name, asm))] + variants
        for vsrc, vmode in variants:
            tmp = os.path.join(cc.scratch_dir(), "m2c_batch_%s%s" % (_tag(), ".cpp" if "vcpp" in vmode else ".c"))
            open(tmp, "w").write("/* %s */\n" % name + vsrc)
            good, rep = vfy.verify_one(va, tmp, symbols=ctx["symbols"], elf=ctx["elf"])
            for _ in range(REPAIR_ROUNDS if "+r" in vmode else 0):
                if "compile failed" not in rep.splitlines()[0]:
                    break
                mended = repair_error(vsrc, rep)
                if mended is None:
                    break
                vsrc = mended
                open(tmp, "w").write("/* %s */\n" % name + vsrc)
                good, rep = vfy.verify_one(va, tmp, symbols=ctx["symbols"], elf=ctx["elf"])
            if "compile failed" in rep.splitlines()[0] or rep.startswith("object defines no symbol"):
                nb = 10 ** 9        # neither is a 0-diff candidate
            else:
                nb = _diffcount(rep)
                if "size:" in rep:  # a size difference is at least one instruction
                    nb += 1
            if best is None or nb < best[0]:
                best = (nb, vmode, vsrc, good, rep)
            if good:
                break
        if best is not None and best[3]:
            break
    nbad, mode_used, src, ok, rep = best
    row = (name, "0x%08x" % va, sz, "match" if ok else
           ("compile" if nbad >= 10 ** 9 else "mismatch"),
           -1 if nbad >= 10 ** 9 else nbad, mode_used or "")
    return row, ok, src, rep, "ok"


def run_m2c(asm_text, name, asm_path, target="mipsee-mwcc-c", context=None):
    open(asm_path, "w").write(asm_text)
    old = sys.argv
    # With a context, keep m2c's parse cache (foo.c.m2c): re-parsing 659 structs for
    # every one of ten thousand candidates would dominate the run.
    sys.argv = (["m2c.py", "-t", target, "-f", name, "--comment-style", "none"]
                + (["--context", context] if context else ["--no-cache"]) + [asm_path])
    try:
        with _capture_stdout() as buf:
            m2c_main.main()
    except SystemExit:
        pass
    finally:
        sys.argv = old
    return buf.getvalue()


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", default=os.environ.get(
        "DW4_ELF", os.path.join(os.path.dirname(HERE), "orig", "SLUS-20836", "SLUS_208.36")))
    ap.add_argument("--symbols", default=os.path.join(os.path.dirname(HERE),
                                                      "config", "SLUS-20836", "symbols.txt"))
    ap.add_argument("--src", default=os.path.join(os.path.dirname(HERE), "src", "unmatched"),
                    help="where a match is banked (unnamed units live in src/unmatched/)")
    ap.add_argument("--src-root", default=os.path.join(os.path.dirname(HERE), "src"),
                    help="the whole src/ tree, for the 'already has C' set — a unit is "
                         "resolved by symbol at any depth (tools/srctree.py), so listing "
                         "one directory re-sweeps every named function")
    ap.add_argument("--min-size", type=int, default=0)
    ap.add_argument("--max-size", type=int, default=64)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--report", type=int, default=0, help="sample N functions only")
    ap.add_argument("--context", default=None,
                    help="m2c --context file (see tools/m2c_context.py)")
    ap.add_argument("--only", action="append", default=[])
    ap.add_argument("--jtbl-only", action="store_true",
                    help="restrict to the functions with a jump table (config/SLUS-20836/jumptables.txt)")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--worklist", default=None,
                    help="TSV of every candidate: name, va, size, status, diffs, mode")
    ap.add_argument("--jobs", type=int, default=1,
                    help="score this many candidates concurrently (the MWCC subprocess "
                         "releases the GIL; m2c itself is serialised by a lock)")
    ap.add_argument("--show", action="store_true")
    ap.add_argument("--keep-all", action="store_true", help="keep candidates in build/m2c/")
    a = ap.parse_args(argv)

    img = open(a.elf, "rb").read()
    syms = am.load_symbols(a.symbols)
    have = set(units.scan(a.src_root))
    lo = min(v for v, _, _ in syms)
    hi = max(v + s for v, s, _ in syms)
    table = am.disassemble(img, lo, hi)
    bounds = load_bounds(a.elf)
    gp = m2c_one.load_gp(a.elf)
    names = {v: n for v, s, n in syms}
    bysym = {v: (s, n) for v, s, n in syms}
    jtabs = m2c_one.load_jtables(a.elf, a.symbols)
    # The EE kernel syscall stubs (tools/syscalls.py) are Sony SDK assembly, not game
    # C — there is no source to recover and MWCC cannot spell `syscall`. Report them
    # as `sdk` instead of scoring them as compile failures the pipeline keeps retrying.
    sdk = syscalls.load()

    cands = [(v, s, n) for v, s, n in syms if n not in have
             and a.min_size <= s <= a.max_size]
    import unitprofiles
    eegcc = set()
    for v, _s, _n in cands:
        try:
            res = unitprofiles.resolve(v, vfy.FLAGS_DEFAULT, vfy.MWCC_DEFAULT, symbols=a.symbols)
        except ValueError:
            continue
        if cc.is_eegcc((res.override or res.profile).compiler):
            eegcc.add(v)
    if a.jtbl_only:
        cands = [c for c in cands if c[0] in jtabs]
    if a.only:
        want = set(a.only)
        cands = [c for c in cands if c[2] in want]
    if a.report:
        cands = cands[:a.report]
    if a.limit:
        cands = cands[:a.limit]

    jobs = max(1, a.jobs)
    print("m2c: %d candidates (%d..%d bytes), jobs=%d"
          % (len(cands), a.min_size, a.max_size, jobs))
    matched, written, failed, m2cfail = [], 0, collections.Counter(), 0
    skipped = 0
    rows = []
    _CTX.update(table=table, names=names, bounds=bounds, gp=gp, jtabs=jtabs, sdk=sdk, eegcc=eegcc,
                symbols=a.symbols, elf=a.elf, context=a.context)
    t0 = time.time()
    pool = ThreadPoolExecutor(max_workers=jobs) if jobs > 1 else None
    # `map` preserves candidate order, so the worklist is deterministic regardless of
    # how many threads scored it; a worker only returns, it never appends to `rows`.
    results = (pool.map(score_candidate, cands) if pool else map(score_candidate, cands))
    try:
        for i, (row, ok, src, rep, kind) in enumerate(results, 1):
            if kind == "sdk":
                rows.append(row)
                skipped += 1
            elif kind == "m2cfail":
                m2cfail += 1
            else:
                rows.append(row)
                if a.keep_all:
                    keep = os.path.join("build", "m2c", row[0] + (".cpp" if "vcpp" in (row[5] or "") else ".c"))
                    os.makedirs(os.path.dirname(keep), exist_ok=True)
                    open(keep, "w").write(src)
                if ok:
                    matched.append(row[0])
                    if a.write:
                        dest = os.path.join(a.src, row[0] + (
                            ".cpp" if "vcpp" in (row[5] or "") else ".c"))
                        os.makedirs(os.path.dirname(dest) or ".", exist_ok=True)
                        if not os.path.exists(dest):
                            open(dest, "w").write(src)
                            written += 1
                else:
                    first = rep.splitlines()[0] if rep else "(no report)"
                    if "compile failed" in first:
                        failed["compile"] += 1
                    else:
                        failed["mismatch"] += 1
                    if a.show:
                        print("---- %s %s (%d B)" % (row[0], row[1], row[2]))
                        print(src)
                        print(rep[:900])
            if i % 250 == 0:
                print("  %d/%d  matched=%d  (%.0f funcs/s)"
                      % (i, len(cands), len(matched), i / (time.time() - t0)), flush=True)
    finally:
        if pool is not None:
            pool.shutdown()
    dt = time.time() - t0
    print("m2c_batch: %d/%d matched (%.1f%%), %d written, %d sdk-skipped, %d m2c failures, %d compile, %d mismatch  [%.0fs, %.0f f/s]"
          % (len(matched), len(cands), 100.0 * len(matched) / max(1, len(cands)),
             written, skipped, m2cfail, failed["compile"], failed["mismatch"], dt,
             len(cands) / max(dt, 1e-9)))
    if a.worklist:
        with open(a.worklist, "w") as fh:
            fh.write("name\tva\tsize\tstatus\tdiffs\tmode\n")
            for r in rows:
                fh.write("\t".join(str(x) for x in r) + "\n")
        near = sum(1 for r in rows if r[3] == "mismatch" and 0 < r[4] <= 3)
        print("   worklist -> %s (%d rows; %d mismatches within 3 instructions)"
              % (a.worklist, len(rows), near))
    if matched:
        print("   matched: %s%s" % (", ".join(matched[:12]),
                                    " ..." if len(matched) > 12 else ""))
    return 0


if __name__ == "__main__":
    sys.exit(main())
