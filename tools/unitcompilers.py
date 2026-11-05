"""Content-pinned compiler overrides for individual functions (config/SLUS-20836/unit-compilers.tsv).

A unit's compiler is its profile in config/SLUS-20836/units.tsv (tools/unitprofiles.py). This
table holds per-function **overrides** of that profile: address, repository-relative
executable, SHA-256, status and an optional reason, tab-separated. A listed compiler
must exist and match its digest; falling back would hide a build error. Where a unit
covers the function the status must be `provisional` (the function has not been
reproduced under its unit's compiler; `make check` reports it as `foreign-profile`
debt). Unlisted addresses use the unit's compiler, or the caller's default outside
every unit.
"""
import hashlib
import os
from collections import namedtuple
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_PATH = "config/SLUS-20836/unit-compilers.tsv"

Row = namedtuple("Row", "executable digest status reason")


@lru_cache(maxsize=8)
def load_rows(path=DEFAULT_PATH):
    """-> {va: Row(executable, digest, status, reason)}; ValueError on a malformed row."""
    path = Path(path)
    if not path.is_absolute():
        path = ROOT / path
    if not path.exists():
        return {}
    rows = {}
    for number, line in enumerate(path.read_text().splitlines(), 1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        fields = [f.strip() for f in line.split("\t")] if "\t" in line else line.split()
        try:
            if len(fields) < 3:
                raise ValueError("expected address, executable and SHA-256")
            address, executable, digest = fields[:3]
            status = fields[3] if len(fields) > 3 and fields[3] else "-"
            reason = fields[4] if len(fields) > 4 else ""
            address = int(address, 0)
            relative = Path(executable)
            if relative.is_absolute() or ".." in relative.parts:
                raise ValueError("executable must be repository-relative")
            if len(digest) != 64 or any(c not in "0123456789abcdef" for c in digest):
                raise ValueError("expected lowercase SHA-256")
            if status not in ("-", "provisional"):
                raise ValueError("status must be provisional or -")
            if address in rows:
                raise ValueError("duplicate address")
        except ValueError as error:
            raise ValueError(f"{path.name}:{number}: invalid compiler entry: {error}") from error
        rows[address] = Row(executable, digest, status, reason)
    return rows


def load(path=DEFAULT_PATH):
    """-> {va: (executable, digest)} (the historical view; see load_rows for the status)."""
    return {va: (row.executable, row.digest) for va, row in load_rows(str(path)).items()}


load.cache_clear = load_rows.cache_clear      # tests clear the table cache through `load`


@lru_cache(maxsize=16)
def _digest(path, stamp, size, inode, device):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def checked_executable(executable, expected, root=ROOT):
    """Absolute path of `executable` under `root`, after its SHA-256 matched `expected`."""
    resolved = Path(root) / executable
    try:
        stat = resolved.stat()
        actual = _digest(str(resolved), stat.st_mtime_ns, stat.st_size,
                         stat.st_ino, stat.st_dev)
    except OSError as error:
        raise ValueError(f"required compiler missing: {executable}") from error
    if actual != expected:
        raise ValueError(f"required compiler SHA-256 mismatch: {executable}")
    return os.fspath(resolved)


def compiler_for(address, default, path=DEFAULT_PATH, root=ROOT):
    """The override compiler for `address`, or `default` when none is listed.

    Callers that know the unit profile use tools/unitprofiles.resolve instead; this
    remains for tools that only read the override table.
    """
    entry = load_rows(str(path)).get(address)
    if entry is None:
        return default
    return checked_executable(entry.executable, entry.digest, root)
