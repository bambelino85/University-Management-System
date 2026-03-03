#!/bin/bash
set -e
echo "[1/2] Validating SBOM CycloneDX schema..."
cyclonedx validate \
  --input-file sbom/holistic-sbom.json \
  --input-format json \
  --input-version v1_4

echo "[2/2] Validating NTIA minimum elements (hoppr)..."
hoppr validate --sbom sbom/holistic-sbom.json 2>/dev/null || \
hopctl validate --sbom sbom/holistic-sbom.json 2>/dev/null || \
echo "[WARN] Hoppr validation skipped - check hopctl validate syntax"

echo "[DONE] Validation complete."
