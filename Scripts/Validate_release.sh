#!/usr/bin/env bash
set -euo pipefail

BINARY="build/solc_contract.so"
# After building once, run: sha256sum "$BINARY" > expected.sha256
EXPECTED_FILE="expected.sha256"

echo "→ Validating release binary at $BINARY"

# 1) Exists?
if [[ ! -f "$BINARY" ]]; then
  echo "✗ ERROR: $BINARY not found"
  exit 1
fi

# 2) SHA-256 checksum
echo -n "• Computing SHA-256… "
SHA=$(sha256sum "$BINARY" | awk '{print $1}')
echo "$SHA"

if [[ -f "$EXPECTED_FILE" ]]; then
  EXPECTED=$(awk '{print $1}' "$EXPECTED_FILE")
  if [[ "$SHA" != "$EXPECTED" ]]; then
    echo "✗ ERROR: checksum mismatch (expected $EXPECTED)"
    exit 1
  else
    echo "✓ Checksum matches $EXPECTED_FILE"
  fi
else
  echo "⚠️  No $EXPECTED_FILE found; to pin this checksum, run:"
  echo "    sha256sum \"$BINARY\" > $EXPECTED_FILE"
fi

# 3) Confirm ELF & BPF
echo -n "• Checking ELF header… "
readelf -h "$BINARY" | awk '
  /Class:/     {print $2}
  /Machine:/   {machine=$2}
  /OS\/ABI:/   {print machine, $2}
  ' | {
    read cls machine osabi
    if [[ "$cls" != "ELF64" ]]; then
      echo "✗ Not ELF64 (got $cls)"
      exit 1
    fi
    if [[ "$machine" != "BPF" ]]; then
      echo "✗ Not BPF target (got $machine)"
      exit 1
    fi
    echo "✓ ELF64 + BPF + $osabi"
  }

# 4) Ensure symbols are stripped
echo -n "• Verifying symbol table is empty… "
if readelf -s "$BINARY" | awk 'NR>3 && $2!~"NUM" { print }' | grep -q '[[:alnum:]]'; then
  echo "✗ Found symbols—run with -s to strip them"
  exit 1
else
  echo "✓ No symbols"
fi

echo
echo "🎉 Binary validation passed!"
