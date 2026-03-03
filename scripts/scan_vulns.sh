#!/bin/bash
set -e
SBOM_FILE=${1:-sbom/holistic-sbom-signed.json}
mkdir -p reports

echo "[1/2] Running Grype vulnerability scan..."
grype sbom:$SBOM_FILE \
  --output json \
  --file reports/vuln-report.json

grype sbom:$SBOM_FILE \
  --output table \
  --file reports/vuln-report.txt

echo "[2/2] Generating HTML analysis report..."
python3 scripts/vuln_summary.py \
  --input reports/vuln-report.json \
  --output reports/vuln-analysis-report.html

echo "[DONE] Reports written to reports/"
