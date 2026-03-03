#!/bin/bash
set -e
APP_VERSION=${CI_APP_VERSION:-1.0.0}
SBOM_DIR=./sbom
mkdir -p $SBOM_DIR

echo "[1/4] Generating SBOM from filesystem (Syft)..."
syft dir:. --output cyclonedx-json=$SBOM_DIR/syft-cots.json

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
