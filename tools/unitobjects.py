"""Explicit ownership of additional functions emitted by a compiler unit.

An owner is a normal top-level source definition. Its generated members have
stable retail addresses and explicit compiler symbols. Every emitted body must
be verified and placed; unregistered additional text is still an error.

Two further declarations extend the ownership of one compiler object without
weakening that rule (see docs/engine/emitted-functions.md):

* ``duplicates`` are compiler-emitted copies of functions that retail contains
  once, placed by another unit (a destructor or inline helper that several
  translation units instantiate; the linker keeps one copy). Each copy must match
  the retail body, but is never placed or given source ownership.
* ``exceptions`` binds the unit's exception index record and exception table to
  their retail addresses so that data is verified byte for byte.
"""
from dataclasses import dataclass
from functools import lru_cache
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_PATH = "config/SLUS-20836/unit-objects.json"


@dataclass(frozen=True)
class Group:
    owner: int
    emitted: tuple
    externals: tuple
    duplicates: tuple = ()
    exceptions: tuple = ()      # (index_address, table_address, table_size) or ()
    # Destructor bodies the compiler emits out of line although every use is inlined, and
    # that the retail linker dead-stripped (no retail function has them). tools/verify.py
    # accepts them only unreferenced, absent from retail and complete; they are never linked.
    stripped: tuple = ()
    # A stock library file: the source compiles whole, never split per function. Its `stripped`
    # names are any functions the retail linker dropped, and its `data` rows are the (symbol,
    # retail address) of each datum it defines or references (docs/engine/emitted-functions.md).
    whole_file: bool = False
    data: tuple = ()
    # The owner's compiler symbol when it differs from symbols.txt: a C++ whole-file unit's names
    # are mangled, while the symbol map keeps the plain name that its source and callers use.
    symbol: str = ""

    @property
    def addresses(self):
        return (self.owner,) + tuple(address for _, address in self.emitted)

    @property
    def members(self):
        """Every function body of the compiler object, placed or verify-only."""
        return self.addresses + tuple(address for _, address in self.duplicates)


def resolve_path(path):
    path = Path(path)
    return path if path.is_absolute() else ROOT / path


def address(value):
    result = int(value, 0)
    if result <= 0 or result > 0xffffffff or result % 4:
        raise ValueError("expected an aligned, nonzero function address")
    return result


@lru_cache(maxsize=8)
def load(path=None):
    path = resolve_path(path or DEFAULT_PATH)
    if not path.exists():
        return ()
    def unique(pairs):
        result = {}
        for key, value in pairs:
            if key in result:
                raise ValueError("duplicate unit-object key")
            result[key] = value
        return result
    data = json.loads(path.read_text(), object_pairs_hook=unique)
    if not isinstance(data, dict):
        raise ValueError("unit objects must be an object keyed by owner address")
    groups, owned = [], set()
    for key, row in data.items():
        if (not isinstance(row, dict)
                or set(row) - {"emitted", "externals", "duplicates", "exceptions", "stripped",
                               "whole_file", "data", "symbol"}
                or not isinstance(row.get("whole_file", False), bool)
                or not isinstance(row.get("data", {}), dict)
                or ("data" in row and not row.get("whole_file"))
                or not isinstance(row.get("stripped", []), list)
                or not isinstance(row.get("emitted", {}), dict)
                or not isinstance(row.get("duplicates", {}), dict)
                or not isinstance(row.get("externals", {}), dict)
                # A row must bind something the linker saw: an emitted or duplicate body, or
                # (a unit whose RAII helpers are out of line in retail) externals together
                # with the exception record whose table names them.
                or not (row.get("whole_file") or row.get("emitted") or row.get("duplicates") or row.get("stripped")
                        or (row.get("externals") and "exceptions" in row))):
            raise ValueError("unit object requires emitted or duplicate symbols, or externals with an "
                             "exception record, and optional externals")
        owner = address(key)
        emitted = tuple((symbol, address(value)) for symbol, value in row.get("emitted", {}).items())
        duplicates = tuple((symbol, address(value)) for symbol, value in row.get("duplicates", {}).items())
        externals = tuple((symbol, address(value)) for symbol, value in row.get("externals", {}).items())
        whole_file = row.get("whole_file", False)
        # a datum has no alignment rule: a string can start on any byte
        data = tuple((symbol, int(value, 0)) for symbol, value in row.get("data", {}).items())
        if any(not symbol or any(c.isspace() for c in symbol)
               for symbol, _ in emitted + duplicates + externals + data):
            raise ValueError("invalid compiler symbol")
        exceptions = ()
        if "exceptions" in row:
            record = row["exceptions"]
            if (not isinstance(record, dict) or set(record) != {"index", "table", "table_size"}
                    or not all(isinstance(value, str) for value in record.values())):
                raise ValueError("exceptions require index, table and table_size")
            size = int(record["table_size"], 0)
            if size <= 0 or size % 4:
                raise ValueError("exception table size must be a positive word multiple")
            exceptions = (address(record["index"]), address(record["table"]), size)
        stripped = tuple(row.get("stripped", []))
        if any(not isinstance(symbol, str) or not (whole_file or symbol.startswith("__dt__"))
               or any(c.isspace() for c in symbol) for symbol in stripped):
            raise ValueError("a stripped symbol must be a compiler destructor name (__dt__...)")
        group = Group(owner, emitted, externals, duplicates, exceptions, stripped, whole_file, data,
                      row.get("symbol", ""))
        if len(set(group.members)) != len(group.members) or owned.intersection(group.addresses):
            raise ValueError("function belongs to multiple compiler bodies")
        names = [symbol for symbol, _ in emitted + duplicates + externals + data] + list(stripped)
        if len(set(names)) != len(names):
            raise ValueError("compiler symbol is declared twice in one unit")
        owned.update(group.addresses)
        groups.append(group)
    return tuple(groups)


def group_for(va, path=None):
    return next((group for group in load(path) if va in group.addresses), None)


@lru_cache(maxsize=8)
def names(symbols="config/SLUS-20836/symbols.txt"):
    by_name, by_va = {}, {}
    for line in resolve_path(symbols).read_text().splitlines():
        if not line.strip() or line.startswith("#"):
            continue
        va, size, name = line.split()[:3]
        va, size = int(va, 16), int(size, 16)
        by_name[name] = (va, size)
        by_va[va] = (name, size)
    return by_name, by_va


def source_owner(name, symbols="config/SLUS-20836/symbols.txt", path=None):
    by_name, by_va = names(str(symbols))
    if name not in by_name:
        return name
    group = group_for(by_name[name][0], path)
    return by_va[group.owner][0] if group else name


def is_whole_file(name, symbols="config/SLUS-20836/symbols.txt", path=None):
    by_name, _ = names(str(symbols))
    group = group_for(by_name[name][0], path) if name in by_name else None
    return bool(group and group.whole_file)


def is_shared_static(name, symbols="config/SLUS-20836/symbols.txt", path=None):
    """True when several sources may define `name`: retail has no such symbol, or a whole-file
    row owns it and places it in one of them."""
    by_name, _ = names(str(symbols))
    return name not in by_name or is_whole_file(name, symbols, path)


def augment_sources(index, symbols="config/SLUS-20836/symbols.txt", path=None):
    _, by_va = names(str(symbols))
    for group in load(path):
        owner = by_va[group.owner][0]
        if owner not in index:
            continue
        for _, va in group.emitted:
            name = by_va[va][0]
            if index.get(name, index[owner]) != index[owner]:
                raise ValueError(f"{name} has both an explicit and emitted definition")
            index[name] = index[owner]
    return index
