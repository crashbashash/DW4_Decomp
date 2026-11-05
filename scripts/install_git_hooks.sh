#!/bin/sh
# Enable the repository's git hooks for this clone:
#   pre-commit / commit-msg  — host-detail checks (docs/host-details-policy.md)
#   pre-push                 — host details in the pushed lines and messages, and the
#                              oracle-change rule; the byte oracle runs on the oracle runner
set -e
cd "$(git rev-parse --show-toplevel)"
chmod +x .githooks/pre-commit .githooks/commit-msg .githooks/pre-push
git config core.hooksPath .githooks
echo "git hooks enabled: core.hooksPath=$(git config core.hooksPath) (pre-commit, commit-msg, pre-push)"
