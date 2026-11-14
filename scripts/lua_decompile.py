#!/usr/bin/env python3
"""
lua_decompile.py — Lua 4.0.1 bytecode decompiler for Digimon World 4.

Produces readable Lua source from the compiled chunks inside NDMW.AFS.

Instruction layout (verified against reference Lua 4.0.1):
    OP(6) | B(9 bits @6) | A(17 bits @15)
    GETARG_U = ins >> 6          GETARG_S = (ins>>6) - (2^25 - 1)
    GETARG_B = (ins>>6) & 0x1ff  GETARG_A = ins >> 15

Lua 4.0.1 semantics (retail evidence::
  * OP_CALL: A = stack position of function, B = nresults.
  * OP_PUSHSELF: pops receiver, pushes [method, receiver].
  * Jump target = pc + 1 + s, including numeric-for branches.
  * Jump opcodes are the STOCK pop variants (JMPONT/JMPONF are never
    emitted, so there is no `and`/`or` short-circuit in the scripts):
      38 = JMPT = pop, jump if truthy   -> condition `not x`
      39 = JMPF = pop, jump if falsy    -> condition `x`
  * Comparison jumps (32-37) are standard: pop both, jump if comparison is
    TRUE.  As an if/while condition they are the "skip when false" branch,
    so the reconstructed condition is the INVERSE of the opcode.
  * Local variable names are stripped (nlocvars == 0); synthetic names used.

Usage:
  python3 lua_decompile.py NDMW.AFS --out DIR [--entry N]
"""
import struct
import sys
import os
from collections import defaultdict

import lua_names

SIZE_OP = 6
SIZE_B = 9
MAXARG_S = (1 << 25) - 1

OPCODES = [
    "OP_END", "OP_RETURN", "OP_CALL", "OP_TAILCALL", "OP_PUSHNIL", "OP_POP",
    "OP_PUSHINT", "OP_PUSHSTRING", "OP_PUSHNUM", "OP_PUSHNEGNUM",
    "OP_PUSHUPVALUE", "OP_GETLOCAL", "OP_GETGLOBAL", "OP_GETTABLE",
    "OP_GETDOTTED", "OP_GETINDEXED", "OP_PUSHSELF", "OP_CREATETABLE",
    "OP_SETLOCAL", "OP_SETGLOBAL", "OP_SETTABLE", "OP_SETLIST", "OP_SETMAP",
    "OP_ADD", "OP_ADDI", "OP_SUB", "OP_MULT", "OP_DIV", "OP_POW",
    "OP_CONCAT", "OP_MINUS", "OP_NOT", "OP_JMPNE", "OP_JMPEQ", "OP_JMPLT",
    "OP_JMPLE", "OP_JMPGT", "OP_JMPGE", "OP_JMPT", "OP_JMPF", "OP_JMPONT",
    "OP_JMPONF", "OP_JMP", "OP_PUSHNILJMP", "OP_FORPREP", "OP_FORLOOP",
    "OP_LFORPREP", "OP_LFORLOOP", "OP_CLOSURE",
]
OP = {n: i for i, n in enumerate(OPCODES)}

CMP_JUMPS = {OP['OP_JMPNE'], OP['OP_JMPEQ'], OP['OP_JMPLT'],
             OP['OP_JMPLE'], OP['OP_JMPGT'], OP['OP_JMPGE']}
JMP_ALL = CMP_JUMPS | {OP['OP_JMPT'], OP['OP_JMPF'], OP['OP_JMP'],
                       OP['OP_JMPONT'], OP['OP_JMPONF']}

# inverse comparison: a comparison jump skips the then-body when the
# comparison is TRUE, so the reconstructed condition is the inverse.
CMP_INV = {
    OP['OP_JMPNE']: '==', OP['OP_JMPEQ']: '~=', OP['OP_JMPLT']: '>=',
    OP['OP_JMPLE']: '>', OP['OP_JMPGT']: '<=', OP['OP_JMPGE']: '<',
}

BINOPS = {
    OP['OP_ADD']: '+', OP['OP_ADDI']: '+', OP['OP_SUB']: '-',
    OP['OP_MULT']: '*', OP['OP_DIV']: '/', OP['OP_POW']: '^',
}


# ---------------------------------------------------------------- parser

class ChunkReader:
    def __init__(self, data, off):
        self.data = data
        self.pos = off

    def u8(self):
        v = self.data[self.pos]; self.pos += 1; return v

    def u32(self):
        v = struct.unpack_from("<I", self.data, self.pos)[0]; self.pos += 4; return v

    def i32(self):
        v = struct.unpack_from("<i", self.data, self.pos)[0]; self.pos += 4; return v

    def f64(self):
        v = struct.unpack_from("<d", self.data, self.pos)[0]; self.pos += 8; return v

    def read_string(self):
        n = self.u32()
        if n == 0:
            return None
        raw = self.data[self.pos:self.pos + n]
        self.pos += n
        return raw.rstrip(b"\x00").decode("latin1", "replace")


def parse_function(c):
    source = c.read_string()
    line_defined = c.i32()
    numparams = c.i32()
    is_vararg = c.u8()
    maxstack = c.i32()
    nloc = c.i32()
    locals_ = []
    for _ in range(nloc):
        varname = c.read_string()
        startpc = c.i32()
        endpc = c.i32()
        locals_.append((varname, startpc, endpc))
    nlines = c.i32()
    lineinfo = [c.i32() for _ in range(nlines)]
    nkstr = c.i32()
    kstr = [c.read_string() for _ in range(nkstr)]
    nknum = c.i32()
    knum = [c.f64() for _ in range(nknum)]
    nkproto = c.i32()
    kproto = [parse_function(c) for _ in range(nkproto)]
    ncode = c.i32()
    code = [c.u32() for _ in range(ncode)]
    return {
        "source": source, "lineDefined": line_defined, "numparams": numparams,
        "is_vararg": is_vararg, "maxstack": maxstack, "locals": locals_,
        "lineinfo": lineinfo, "kstr": kstr, "knum": knum, "kproto": kproto,
        "code": code,
    }


def parse_chunk(data, off):
    c = ChunkReader(data, off)
    assert c.u8() == 0x1B
    assert bytes([c.u8(), c.u8(), c.u8()]) == b"Lua"
    version = c.u8()
    endian = c.u8()
    for _ in range(7):
        c.u8()
    c.f64()
    main = parse_function(c)
    return main, c.pos - off


# ---------------------------------------------------------------- rendering

PREC = {'or': 1, 'and': 2, 'compare': 3, 'concat': 4, 'add': 5,
        'mul': 6, 'unary': 7, 'pow': 8, 'atom': 100}


def quote(s):
    return '"' + s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n') + '"'


def render(expr):
    kind = expr[0]
    if kind == 'const':
        v = expr[1]
        if v is None:
            return 'nil'
        if isinstance(v, float):
            if v == int(v) and abs(v) < 1e15:
                return str(int(v))
            return repr(v)
        return str(v)
    if kind == 'string':
        return quote(expr[1])
    if kind == 'local':
        return expr[1]
    if kind == 'global':
        return expr[1]
    if kind == 'index':
        return render(expr[1]) + '[' + render(expr[2]) + ']'
    if kind == 'dot':
        return render(expr[1]) + '.' + expr[2]
    if kind == 'binop':
        op, l, r = expr[1], expr[2], expr[3]
        lp = prec_of_op(op)
        rp = lp if op in ('..', '^') else lp + 1
        return f"{render_with(l, lp)} {op} {render_with(r, rp)}"
    if kind == 'unop':
        op, operand = expr[1], expr[2]
        return op + " " + render_with(operand, PREC['unary']) if op == 'not' \
            else op + render_with(operand, PREC['unary'])
    if kind == 'call':
        func, args = expr[1], expr[2]
        return render_with(func, PREC['atom']) + '(' + ', '.join(render(a) for a in args) + ')'
    if kind == 'method':
        recv, name, args = expr[1], expr[2], expr[3]
        return render_with(recv, PREC['atom']) + ':' + name + '(' + ', '.join(render(a) for a in args) + ')'
    if kind == 'table':
        array, hash_ = expr[1], expr[2]
        # Lua 4 separates a constructor's list part from its record part with `;`
        parts = [', '.join(render(a) for a in array),
                 ', '.join(f"[{render(k)}] = {render(v)}" for k, v in hash_)]
        return '{' + '; '.join(p for p in parts if p) + '}'
    if kind == 'func':
        return expr[1]
    if kind == 'vararg':
        return '...'
    return '???'


def render_with(expr, min_prec):
    s = render(expr)
    if prec_of(expr) < min_prec:
        return '(' + s + ')'
    return s


def prec_of(expr):
    kind = expr[0]
    if kind == 'binop':
        return prec_of_op(expr[1])
    if kind == 'unop':
        return PREC['unary']
    if kind == 'func':
        return 0  # always parenthesise anonymous functions in call position
    return PREC['atom']


def prec_of_op(op):
    if op == 'or':
        return PREC['or']
    if op == 'and':
        return PREC['and']
    if op in ('~=', '==', '<', '>', '<=', '>='):
        return PREC['compare']
    if op == '..':
        return PREC['concat']
    if op in ('+', '-'):
        return PREC['add']
    if op in ('*', '/'):
        return PREC['mul']
    if op == '^':
        return PREC['pow']
    return PREC['atom']


# ---------------------------------------------------------------- decompiler

class Decompiler:
    def __init__(self, fn, names=None, analyze=False):
        self.code = fn['code']
        self.kstr = fn['kstr']
        self.knum = fn['knum']
        self.kproto = fn['kproto']
        self.nparams = fn['numparams']
        self.is_vararg = fn['is_vararg']
        self.names = names or {}
        self.analyze = analyze
        self.evidence = defaultdict(set)  # slot -> {usage signature}
        self._for_depth = 0
        self.stack = []
        self.stmts = []
        self._pc = 0
        self._end = len(self.code)
        self._jump_tgt = {}
        self._back_targets = set()
        self._memo = {}
        self._block_end = len(self.code)

    # -- locals --
    # A local is rendered ('local', name, key): `key` identifies the binding
    # the slot holds at that point, so names can follow bindings rather than
    # slots (one slot is reused by unrelated locals in sibling blocks):
    #   ('param', slot)            a parameter
    #   ('vararg', slot)           a vararg function's `arg` table
    #   ('for', slot, depth)       a numeric-for control variable
    #   ('ctl', slot)              a numeric-for limit/step slot
    #   ('init', slot, sig)        a local whose initial value has summary `sig`
    #   ('unbound', slot)          a slot the stack model does not cover
    # Stack placeholders that stand for the binding itself carry a fourth
    # element, so a copied local (`local b = a`) is not mistaken for one.
    def local(self, idx):
        """The slot's synthetic name."""
        if idx < self.nparams:
            return f"arg_{idx}"
        if self.is_vararg and idx == self.nparams:
            return "arg"  # Lua 4 binds a vararg function's extra arguments to `arg`
        return f"local_{idx}"

    def name_of(self, key):
        return self.names.get(key) or self.local(key[1])

    def binding(self, idx):
        if self.is_vararg and idx == self.nparams:
            return ('vararg', idx)
        entry = self.stack[idx] if idx < len(self.stack) else None
        if entry is None:
            return ('unbound', idx)
        if entry[0] == 'local' and len(entry) == 4:
            return entry[2]
        return ('init', idx, self.sig(entry))

    def ref(self, idx):
        """The expression for a read or write of slot idx."""
        key = self.binding(idx)
        if self.analyze:
            self.evidence[key].add(('ref',))
        return ('local', self.name_of(key), key)

    def placeholder(self, key):
        return ('local', self.name_of(key), key, 'binding')

    # -- usage evidence for local naming (first pass only) --
    def _note(self, expr, *usage):
        if self.analyze and expr[0] == 'local':
            self.evidence[expr[2]].add(usage)

    def sig(self, expr):
        """Hashable summary of an expression, for naming evidence."""
        kind = expr[0]
        if kind == 'const':
            return ('num', expr[1])
        if kind == 'string':
            return ('str', expr[1])
        if kind == 'local':
            return ('local',) + expr[2][:2]
        if kind == 'global':
            return ('global', expr[1])
        if kind in ('call', 'method'):
            args = expr[2] if kind == 'call' else expr[3]
            return ('call', self.callee(expr), tuple(self.sig(a) for a in args))
        if kind == 'func':
            return ('func', next((i for i, p in enumerate(self.kproto) if p is expr[2]), None))
        if kind == 'binop':
            return ('binop', expr[1], self.sig(expr[2]), self.sig(expr[3]))
        if kind == 'unop':
            return ('unop', expr[1], self.sig(expr[2]))
        if kind == 'index':
            return ('index', self.sig(expr[1]), self.sig(expr[2]))
        if kind == 'dot':
            return ('dot', self.sig(expr[1]), expr[2])
        return (kind,)

    def callee(self, expr):
        """`be:FLGisOn`, `:method`, a global function's name, or None."""
        if expr[0] == 'method':
            recv = expr[1]
            return ('be:' if recv == ('global', 'be') else ':') + expr[2]
        func = expr[1]
        if func[0] == 'global':
            return func[1]
        return None

    def s(self, k):
        return ('string', self.kstr[k] if k < len(self.kstr) else f"<str[{k}]>")

    def n(self, k):
        return ('const', self.knum[k] if k < len(self.knum) else 0.0)

    def _jt(self, pc):
        _, _, s, _, _ = self.decode(pc)
        return pc + 1 + s

    def decode(self, pc):
        ins = self.code[pc]
        op = ins & 0x3F
        u = ins >> 6
        s = u - MAXARG_S
        b = (ins >> 6) & 0x1ff
        a = ins >> 15
        return op, u, s, b, a

    def push(self, e):
        self.stack.append(e)

    def pop(self):
        return self.stack.pop() if self.stack else ('const', None)

    def emit(self, text, lev=0):
        self.stmts.append((lev, text))

    def indent_block(self, stmts, extra):
        return [(lev + extra, t) for lev, t in stmts]

    # ----------------------------------------------------------------
    def decompile(self):
        self._precompute()
        self._pc = 0
        self._end = len(self.code)
        # the function's parameters occupy the lowest stack slots, then a
        # vararg function's `arg` table
        for i in range(self.nparams):
            self.push(self.placeholder(('param', i)))
        if self.is_vararg:
            self.push(self.placeholder(('vararg', self.nparams)))
        self.collect(self._end)
        self._declare(len(self.stack))
        return self.stmts

    def _declare(self, base):
        """Emit `local` for every value below `base` that no statement has
        consumed: Lua 4 keeps a local in the stack slot its initial value was
        pushed to, and leaves nothing else on the stack across a statement.
        Called before each statement is emitted, so the declaration lands
        between the statements its value was computed between."""
        for p in range(min(base, len(self.stack))):
            entry = self.stack[p]
            if entry[0] == 'local' and len(entry) == 4:
                continue  # already a binding
            key = ('init', p, self.sig(entry))
            name = self.name_of(key)
            if self.analyze:
                self.evidence[key].add(('ref',))
            self.stmts.append((0, f"local {name}" if entry == ('const', None)
                               else f"local {name} = {render(entry)}"))
            self.stack[p] = self.placeholder(key)

    def _precompute(self):
        for pc in range(len(self.code)):
            op = self.code[pc] & 0x3F
            if op in JMP_ALL:
                t = self._jt(pc)
                self._jump_tgt[pc] = t
                if t <= pc:
                    self._back_targets.add(t)

    # ----------------------------------------------------------------
    # collect: decompile statements until `limit` or an unconditional jump.
    def collect(self, limit):
        # The block ends at `limit`, or just before it when its last
        # instruction is the jump over an `else`. Lua threads a jump to the end
        # of a block straight to wherever that block's own exit goes, so a
        # jump past the block's end means "to the end of this block".
        saved = self._block_end
        end = limit
        if self._pc <= limit - 1 < len(self.code) and self.code[limit - 1] & 0x3F == OP['OP_JMP'] \
                and self._jt(limit - 1) >= limit:
            end = limit - 1
        self._block_end = min(end, saved)
        try:
            while self._pc < limit:
                pc = self._pc
                op = self.code[pc] & 0x3F
                if op == OP['OP_JMP']:
                    return pc
                if op in CMP_JUMPS or op in (OP['OP_JMPT'], OP['OP_JMPF']):
                    self._if_or_while()
                    continue
                if op == OP['OP_FORPREP']:
                    self._num_for()
                    continue
                if op == OP['OP_LFORPREP']:
                    self._lfor()
                    continue
                self._pc = self.step(pc)
            return self._pc
        finally:
            self._block_end = saved

    def _clamp(self, target):
        return min(target, self._block_end)

    # -- and/or short-circuit (38=or, 39=and) handled inside step --
    def _find_backjump(self, start, end):
        for pc in range(start, end):
            op = self.code[pc] & 0x3F
            if op == OP['OP_JMP']:
                t = self._jt(pc)
                if t <= pc:
                    return pc
        return None

    def _pop_cond(self, op):
        if op in CMP_JUMPS:
            rhs = self.pop()
            lhs = self.pop()
            self._note(lhs, 'cmp', CMP_INV[op], self.sig(rhs))
            self._note(rhs, 'cmp', CMP_INV[op], self.sig(lhs))
            return ('binop', CMP_INV[op], lhs, rhs)
        if op == OP['OP_JMPT']:
            # jump if truthy -> skip when `x` truthy -> condition is `not x`
            x = self.pop()
            self._note(x, 'test')
            return ('unop', 'not', x)
        if op == OP['OP_JMPF']:
            # jump if falsy -> skip when `x` falsy -> condition is `x`
            x = self.pop()
            self._note(x, 'test')
            return x
        return ('const', None)

    def _if_or_while(self):
        pc = self._pc
        op = self.code[pc] & 0x3F
        raw = self._jt(pc)
        t = self._clamp(raw)
        conds = [self._pop_cond(op)]
        self._declare(len(self.stack))

        # `and`-chain detection: the game compiles `a and b and c` as nested
        # ifs whose conditions ALL jump to the same else target. Collect them
        # into one flat condition (this also prevents exponential re-decoding
        # of the shared else body).
        scan = pc + 1
        while scan < t:
            cj = self._find_cond_jump_to(scan, t, raw)
            if cj is None:
                break
            self._run_expr(scan, cj)
            conds.append(self._pop_cond(self.code[cj] & 0x3F))
            scan = cj + 1

        cond = conds[0]
        for c in conds[1:]:
            cond = ('binop', 'and', cond, c)

        back = self._find_backjump(scan, t)
        if back is not None:
            body, _ = self._collect_sub(scan, back)
            self.emit(f"while {render(cond)} do")
            self.stmts.extend(self.indent_block(body, 1))
            self.emit("end")
            self._pc = t
        else:
            self._emit_if(scan, t, cond)

    def _find_cond_jump_to(self, start, end, target):
        """Return the pc of the first conditional jump (32-39) in [start,end)
        whose target is `target` and whose operands are all [start, pc)
        computes: no statement or local declaration in between, so the two
        conditions can be joined by `and`. None otherwise."""
        depth = len(self.stack)
        pc = start
        while pc < end:
            op = self.code[pc] & 0x3F
            if op in CMP_JUMPS or op in (OP['OP_JMPT'], OP['OP_JMPF']):
                need = 2 if op in CMP_JUMPS else 1
                if self._jt(pc) == target and depth == len(self.stack) + need:
                    return pc
                return None
            depth = self._expr_depth(pc, depth)
            if depth is None:
                return None
            pc += 1
        return None

    def _expr_depth(self, pc, depth):
        """Stack depth after instruction pc when it is part of an expression;
        None for an instruction that ends a statement."""
        op, u, s, b, a = self.decode(pc)
        if op in (OP['OP_PUSHINT'], OP['OP_PUSHSTRING'], OP['OP_PUSHNUM'], OP['OP_PUSHNEGNUM'],
                  OP['OP_PUSHUPVALUE'], OP['OP_GETLOCAL'], OP['OP_GETGLOBAL'],
                  OP['OP_PUSHSELF'], OP['OP_CREATETABLE']):
            return depth + 1
        if op == OP['OP_PUSHNIL']:
            return depth + u
        if op in (OP['OP_GETDOTTED'], OP['OP_GETINDEXED'], OP['OP_ADDI'],
                  OP['OP_MINUS'], OP['OP_NOT']):
            return depth
        if op in (OP['OP_GETTABLE'], OP['OP_ADD'], OP['OP_SUB'], OP['OP_MULT'],
                  OP['OP_DIV'], OP['OP_POW']):
            return depth - 1
        if op == OP['OP_CONCAT']:
            return depth - u + 1
        if op == OP['OP_CALL'] and b:
            return a + (1 if b == 255 else b)
        if op == OP['OP_SETLIST']:
            return depth - b
        if op == OP['OP_SETMAP']:
            return depth - 2 * u
        if op == OP['OP_CLOSURE']:
            return depth + 1 - b
        return None

    def _run_expr(self, start, end):
        """Process [start, end) as a pure expression (pushes values, no
        statements emitted)."""
        saved_stmts = self.stmts
        self.stmts = []
        saved_pc = self._pc
        self._pc = start
        while self._pc < end:
            self._pc = self.step(self._pc)
        self.stmts = saved_stmts
        self._pc = saved_pc

    def _emit_if(self, then_start, else_pc, cond):
        # then body = [then_start, else_pc). May stop early at a forward JMP.
        then_body, stop_pc = self._collect_sub(then_start, else_pc)
        self.emit(f"if {render(cond)} then")
        self.stmts.extend(self.indent_block(then_body, 1))
        if stop_pc < else_pc:
            # stopped at a forward JMP -> there is an else / elseif at else_pc
            skip_target = self._clamp(self._jump_tgt[stop_pc])
            else_body, _ = self._collect_sub(else_pc, skip_target)
            if self._is_single_if(else_body):
                # flatten 'else: if ...' into 'elseif ...' (levels already correct)
                self.stmts.append((0, else_body[0][1].replace('if ', 'elseif ', 1)))
                self.stmts.extend(else_body[1:-1])
                self.stmts.append((0, 'end'))
            else:
                self.emit("else")
                self.stmts.extend(self.indent_block(else_body, 1))
                self.emit("end")
            self._pc = skip_target
        else:
            self.emit("end")
            self._pc = else_pc

    @staticmethod
    def _is_single_if(stmts):
        if len(stmts) < 2:
            return False
        head = stmts[0][1]
        if not (head.startswith('if ') or head.startswith('if not ')):
            return False
        return stmts[-1][1] == 'end' and stmts[-1][0] == stmts[0][0]

    def _collect_sub(self, start, end):
        """Decompile [start, end) into a statement list. The block sees a
        COPY of the current stack (locals/control vars visible for GETLOCAL
        and CALL), but its stack changes are discarded. Returns (stmts,
        stop_pc). stop_pc == end normally, or < end if a forward JMP hit.

        Memoised by (start, end): deeply nested if-chains frequently share
        one else body, and re-decompiling it per nesting level is what caused
        the exponential output blow-up."""
        key = (start, end)
        if key in self._memo:
            result, stop = self._memo[key]
            return list(result), stop
        saved_stack = self.stack
        saved_stmts = self.stmts
        saved_pc = self._pc
        self.stack = list(saved_stack)
        self.stmts = []
        self._pc = start
        stop = self.collect(end)
        self._declare(len(self.stack))
        result = self.stmts
        self.stmts = saved_stmts
        self.stack = saved_stack
        self._pc = saved_pc
        self._memo[key] = (list(result), stop)
        return result, stop

    # ----------------------------------------------------------------
    def _num_for(self):
        pc = self._pc
        step = self.pop()
        limit = self.pop()
        init = self.pop()
        self._declare(len(self.stack))
        var_pos = len(self.stack)  # init slot = loop variable index
        var = ('for', var_pos, self._for_depth)
        varname = self.name_of(var)
        if self.analyze:
            self.evidence[var].add(('loop', self.sig(init), self.sig(limit)))
        # keep the three control slots on the stack while the body runs
        self.push(self.placeholder(var))
        self.push(('local', f"{varname}_limit", ('ctl', var_pos + 1), 'binding'))
        self.push(('local', f"{varname}_step", ('ctl', var_pos + 2), 'binding'))
        body_start = pc + 1
        after = self._jt(pc)
        # Empty-loop branches can be threaded past the loop's immediate end.
        # Pair by the back edge, which also distinguishes nested loops.
        pc2 = next((p for p in range(body_start, len(self.code))
                    if (self.code[p] & 0x3F) == OP['OP_FORLOOP'] and
                    self._jt(p) == body_start), None)
        if pc2 is None:
            raise ValueError(f"FORPREP at {pc} has no matching FORLOOP")
        # decompile the body inline (stack carries the control slots)
        saved_stmts = self.stmts
        self.stmts = []
        saved_pc = self._pc
        self._pc = body_start
        self._for_depth += 1
        self.collect(pc2)
        self._for_depth -= 1
        body = self.stmts
        self.stmts = saved_stmts
        self._pc = saved_pc
        # drop the three control slots
        self.pop(); self.pop(); self.pop()
        sstep = render(step)
        if sstep == '1':
            self.emit(f"for {varname} = {render(init)}, {render(limit)} do")
        else:
            self.emit(f"for {varname} = {render(init)}, {render(limit)}, {sstep} do")
        self.stmts.extend(self.indent_block(body, 1))
        self.emit("end")
        self._pc = after

    def _lfor(self):
        # generic for: absent from the game's scripts; best-effort
        pc = self._pc
        iter_expr = self.pop()
        after = self._jt(pc)
        body_start = pc + 1
        for pc2 in range(body_start, self._end):
            if (self.code[pc2] & 0x3F) == OP['OP_LFORLOOP']:
                break
        else:
            pc2 = self._end - 1
        body, _ = self._collect_sub(body_start, pc2)
        self.emit(f"for k, v in {render(iter_expr)} do")
        self.stmts.extend(self.indent_block(body, 1))
        self.emit("end")
        self._pc = after

    # ----------------------------------------------------------------
    def step(self, pc):
        op, u, s, b, a = self.decode(pc)

        if op == OP['OP_END']:
            return pc + 1
        if op == OP['OP_RETURN']:
            # RETURN U returns the values from stack slot U up; the slots
            # below are the function's active locals
            vals = self.stack[u:]
            del self.stack[u:]
            self._declare(u)
            self.emit("return" + (" " + ', '.join(render(v) for v in vals) if vals else ""))
            return pc + 1

        if op in (OP['OP_CALL'], OP['OP_TAILCALL']):
            func_pos = a
            nres = b
            nargs = len(self.stack) - func_pos - 1
            args = [self.pop() for _ in range(nargs)][::-1]
            func = self.pop()
            del self.stack[func_pos:]
            if func[0] == 'method':
                # args[0] is the receiver (self) pushed by PUSHSELF
                call = ('method', func[1], func[2], args[1:])
            else:
                call = ('call', func, args)
            if self.analyze:
                self._note_call(call)
            if nres == 0:
                self._declare(func_pos)
                self.emit(render(call))
            else:
                self.push(call)
            return pc + 1

        if op == OP['OP_PUSHNIL']:
            for _ in range(u):
                self.push(('const', None))
            return pc + 1
        if op == OP['OP_POP']:
            # a block's end drops its locals: any still undeclared were
            # declared but never read
            self._declare(len(self.stack))
            for _ in range(u):
                self.pop()
            return pc + 1
        if op == OP['OP_PUSHINT']:
            self.push(('const', s))
            return pc + 1
        if op == OP['OP_PUSHSTRING']:
            self.push(self.s(u))
            return pc + 1
        if op == OP['OP_PUSHNUM']:
            self.push(self.n(u))
            return pc + 1
        if op == OP['OP_PUSHNEGNUM']:
            self.push(('unop', '-', self.n(u)))
            return pc + 1
        if op == OP['OP_PUSHUPVALUE']:
            self.push(('global', f"upvalue_{u}"))
            return pc + 1
        if op == OP['OP_GETLOCAL']:
            self.push(self.ref(u))
            return pc + 1
        if op == OP['OP_GETGLOBAL']:
            self.push(('global', self.kstr[u]))
            return pc + 1
        if op == OP['OP_GETTABLE']:
            key = self.pop()
            t = self.pop()
            self._note(t, 'indexed')
            self._note(key, 'key', self.sig(t))
            self.push(('index', t, key))
            return pc + 1
        if op == OP['OP_GETDOTTED']:
            t = self.pop()
            self._note(t, 'field', self.kstr[u])
            self.push(('dot', t, self.kstr[u]))
            return pc + 1
        if op == OP['OP_GETINDEXED']:
            t = self.pop()
            key = self.ref(u)
            self._note(t, 'indexed')
            self._note(key, 'key', self.sig(t))
            self.push(('index', t, key))
            return pc + 1
        if op == OP['OP_PUSHSELF']:
            recv = self.pop()
            # PUSHSELF pushes TWO values: the method (function) and the
            # receiver (self argument). Track both so CALL's absolute stack
            # positions stay correct.
            self.push(('method', recv, self.kstr[u], []))
            self.push(recv)
            return pc + 1
        if op == OP['OP_CREATETABLE']:
            self.push(('table', [], []))
            return pc + 1
        if op == OP['OP_SETLOCAL']:
            v = self.pop()
            self._declare(len(self.stack))
            target = self.ref(u)
            self._note(target, 'set', self.sig(v))
            self.emit(f"{target[1]} = {render(v)}")
            return pc + 1
        if op == OP['OP_SETGLOBAL']:
            v = self.pop()
            self._declare(len(self.stack))
            self._note(v, 'stored', ('global', self.kstr[u]))
            self.emit(f"{self.kstr[u]} = {render(v)}")
            return pc + 1
        if op == OP['OP_SETTABLE']:
            v = self.pop()
            key = self.pop()
            t = self.pop()
            self._declare(len(self.stack))
            self._note(t, 'tableset')
            self._note(v, 'stored', self.sig(('index', t, key)))
            self.emit(f"{render(('index', t, key))} = {render(v)}")
            return pc + 1
        if op == OP['OP_SETLIST']:
            # SETLIST A B: the B values on top are the next list items
            vals = [self.pop() for _ in range(b)][::-1]
            self.peek_table()[1].extend(vals)
            return pc + 1
        if op == OP['OP_SETMAP']:
            # SETMAP U: the U key/value pairs on top are record fields
            pairs = []
            for _ in range(u):
                v = self.pop()
                key = self.pop()
                pairs.append((key, v))
            self.peek_table()[2].extend(pairs[::-1])
            return pc + 1
        if op in BINOPS:
            r = ('const', s) if op == OP['OP_ADDI'] else self.pop()
            l = self.pop()
            self._note(l, 'arith', BINOPS[op])
            self._note(r, 'arith', BINOPS[op])
            self.push(('binop', BINOPS[op], l, r))
            return pc + 1
        if op == OP['OP_CONCAT']:
            vals = [self.pop() for _ in range(u)][::-1]
            for v in vals:
                self._note(v, 'concat')
            e = vals[0]
            for v in vals[1:]:
                e = ('binop', '..', e, v)
            self.push(e)
            return pc + 1
        if op == OP['OP_MINUS']:
            self.push(('unop', '-', self.pop()))
            return pc + 1
        if op == OP['OP_NOT']:
            self.push(('unop', 'not', self.pop()))
            return pc + 1

        if op == OP['OP_CLOSURE']:
            # CLOSURE A B: prototype A, closing over the B values on top
            for _ in range(b):
                self.pop()
            proto = self.kproto[a] if a < len(self.kproto) else None
            if proto is None:
                self.push(('func', "function() end", None))
            elif self.analyze:
                # the first pass only needs the prototype, not its text
                self.push(('func', "function() end", proto))
            else:
                self.push(('func', closure_source(proto), proto))
            return pc + 1

        return pc + 1

    def _note_call(self, call):
        """Evidence from a call: a local passed as an argument or called."""
        callee = self.callee(call)
        args = call[2] if call[0] == 'call' else call[3]
        consts = tuple(a[1] if a[0] in ('string', 'const') else None for a in args)
        for i, arg in enumerate(args):
            self._note(arg, 'arg', callee, i, consts)
            if arg[0] == 'binop':
                for side in (arg[2], arg[3]):
                    self._note(side, 'argpart', callee, i, consts)
        if call[0] == 'call':
            self._note(call[1], 'called', len(args))

    def peek_table(self):
        # find the nearest table constructor on the stack (for SETLIST/SETMAP)
        for e in reversed(self.stack):
            if e[0] == 'table':
                return e
        t = ('table', [], [])
        return t

    def _make_call(self, func, args):
        if func[0] == 'method':
            return ('method', func[1], func[2], args)
        return ('call', func, args)


# ----------------------------------------------------------------------

def decompile_function(fn):
    """Decompile one prototype in two passes: the first records how each
    local slot is used, lua_names.infer turns that into names, and the second
    renders with them."""
    probe = Decompiler(fn, analyze=True)
    probe.decompile()
    d = Decompiler(fn, names=lua_names.infer(probe))
    stmts = d.decompile()
    return ["    " * lev + text for lev, text in stmts], d


def closure_source(proto):
    lines, d = decompile_function(proto)
    params = ", ".join([d.name_of(('param', i)) for i in range(proto['numparams'])]
                       + (["..."] if proto['is_vararg'] else []))
    body = "\n".join("    " + line for line in lines)
    return f"function({params})\n" + body + "\nend"


def decompile_function_source(fn):
    return "\n".join(decompile_function(fn)[0])


# ----------------------------------------------------------------------

def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    flags = [a for a in sys.argv[1:] if a.startswith("--")]
    if not args:
        print(__doc__)
        return
    path = args[0]
    data = open(path, "rb").read()

    out_dir = None
    entry_filter = None
    for f in flags:
        if f.startswith("--out="):
            out_dir = f.split("=", 1)[1]
        if f.startswith("--entry="):
            entry_filter = int(f.split("=", 1)[1])

    if out_dir:
        os.makedirs(out_dir, exist_ok=True)

    # parse AFS
    count = struct.unpack("<I", data[4:8])[0]
    entries = [struct.unpack("<II", data[8 + i * 8: 16 + i * 8]) for i in range(count)]

    total = 0
    for eidx, (off, size) in enumerate(entries):
        if entry_filter is not None and eidx != entry_filter:
            continue
        blob = data[off:off + size]
        i = 0
        chunk_idx = 0
        while True:
            j = blob.find(b"\x1bLua", i)
            if j < 0:
                break
            try:
                main, sz = parse_chunk(blob, j)
            except Exception:
                i = j + 1
                continue
            src = decompile_function_source(main)
            if out_dir:
                edir = os.path.join(out_dir, f"entry_{eidx:04d}")
                os.makedirs(edir, exist_ok=True)
                fname = os.path.join(edir, f"chunk_{chunk_idx:04d}.lua")
                with open(fname, "w") as fh:
                    fh.write(src + "\n")
            else:
                print(f"=== entry {eidx} chunk {chunk_idx} @0x{j:x} ===")
                print(src)
            total += 1
            chunk_idx += 1
            i = j + 1
    print(f"decompiled {total} chunks" + (f" -> {out_dir}" if out_dir else ""))


if __name__ == "__main__":
    main()
