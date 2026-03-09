#!/usr/bin/env bash
set -u

make -j2 >/tmp/cpm_make.log || {
  cat /tmp/cpm_make.log
  exit 1
}

run_group() {
  local label="$1"
  local expected="$2"
  local pattern="$3"
  local opts="$4"
  local total=0
  local failed=0

  echo "$label"
  for f in $pattern; do
    [ -f "$f" ] || continue
    total=$((total + 1))
    ./compiler $opts "$f" >/tmp/cpm_test.out 2>/tmp/cpm_test.err
    rc=$?
    if [ "$rc" -eq "$expected" ]; then
      printf '  PASS %s\n' "$f"
    else
      printf '  FAIL %s (got %s, expected %s)\n' "$f" "$rc" "$expected"
      if [ -s /tmp/cpm_test.err ]; then
        sed -n '1,40p' /tmp/cpm_test.err
      fi
      failed=$((failed + 1))
    fi
  done
  echo "  Summary: $((total - failed))/$total passed"
  echo
  return "$failed"
}

status=0
run_group "Valid" 0 "test_files/valid/*.cpm" "--no-vm" || status=1
run_group "Semantic" 4 "test_files/semantic_errors/*.cpm" "--no-vm" || status=1
run_group "Syntax" 2 "test_files/syntax_errors/*.cpm" "--no-vm" || status=1
run_group "Lexical" 1 "test_files/lexical_errors/*.cpm" "--no-vm" || status=1
run_group "TreeValidation" 0 "test_files/tree_validation/*.cpm" "--no-vm" || status=1

exit "$status"
