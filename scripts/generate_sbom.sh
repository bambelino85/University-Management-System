#!/bin/bash
set -e
APP_VERSION=${CI_APP_VERSION:-1.0.0}
SBOM_DIR=./sbom
mkdir -p $SBOM_DIR

echo "[1/4] Generating SBOM from filesystem (Syft)..."
syft dir:. --output cyclonedx-json@1.4=$SBOM_DIR/syft-cots.json

echo "[2/4] Generating SBOM from OS packages (Trivy)..."
trivy filesystem --format cyclonedx --output $SBOM_DIR/trivy-os.json .

echo "[3/4] Generating custom component SBOM from CSV..."
python3 scripts/csv_to_sbom.py \
  --input sbom-components.csv \
  --output $SBOM_DIR/custom-components.json \
  --version $APP_VERSION

echo "[4/4] Merging all SBOMs into holistic SBOM..."
cyclonedx merge \
  --input-files $SBOM_DIR/syft-cots.json $SBOM_DIR/trivy-os.json $SBOM_DIR/custom-components.json \
  --output-file $SBOM_DIR/holistic-sbom.json \
  --output-format json

echo "[DONE] SBOM generation complete: $SBOM_DIR/holistic-sbom.json"

echo "[5/4] Patching specVersion to 1.4 for tool compatibility..."
python3 -c "
import json
with open('$SBOM_DIR/holistic-sbom.json') as f:
    d = json.load(f)
d['specVersion'] = '1.4'
d.pop('annotations', None)
with open('$SBOM_DIR/holistic-sbom.json', 'w') as f:
    json.dump(d, f, indent=2)
print('[patch] specVersion set to 1.4')
"
