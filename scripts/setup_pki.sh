#!/bin/bash
set -e
mkdir -p keys/{ca,signing,public}

echo "[1/4] Generating Root CA private key (EC P-384)..."
openssl ecparam -name secp384r1 -genkey -noout -out keys/ca/ca-root.key

echo "[2/4] Self-signing Root CA certificate..."
openssl req -new -x509 \
  -key keys/ca/ca-root.key \
  -out keys/ca/ca-root.crt \
  -days 3650 \
  -subj "/C=US/ST=Maryland/O=LM Senior Design/CN=SBOM Root CA"

echo "[3/4] Generating SBOM signing key and CSR..."
openssl ecparam -name secp384r1 -genkey -noout -out keys/signing/sbom-signing.key
openssl req -new \
  -key keys/signing/sbom-signing.key \
  -out keys/signing/sbom-signing.csr \
  -subj "/C=US/ST=Maryland/O=LM Senior Design/CN=SBOM Signer"

echo "[4/4] Signing certificate with Root CA..."
openssl x509 -req \
  -in keys/signing/sbom-signing.csr \
  -CA keys/ca/ca-root.crt \
  -CAkey keys/ca/ca-root.key \
  -CAcreateserial \
  -out keys/signing/sbom-signing.crt \
  -days 365

openssl ec -in keys/signing/sbom-signing.key \
  -pubout -out keys/public/sbom-public.pem

echo "[DONE] PKI setup complete."
echo "  CA cert:      keys/ca/ca-root.crt"
echo "  Signing key:  keys/signing/sbom-signing.key  <-- NEVER COMMIT"
echo "  Public key:   keys/public/sbom-public.pem    <-- safe to commit"
