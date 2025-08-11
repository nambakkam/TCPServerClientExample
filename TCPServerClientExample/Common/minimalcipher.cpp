#include "minimalcipher.h"
#include <atomic>
#include <openssl/evp.h>

namespace MinimalCipher {

static unsigned char g_key[32];
static std::atomic<uint64_t> g_counter{0};
static bool g_initialized = false;

bool initialize(const QByteArray &passphrase) {
  EVP_MD_CTX *ctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
  EVP_DigestUpdate(ctx, passphrase.constData(), passphrase.size());
  unsigned int len;
  EVP_DigestFinal_ex(ctx, g_key, &len);
  EVP_MD_CTX_free(ctx);

  g_initialized = true;
  return true;
}

QByteArray encrypt(const QByteArray &plaintext) {
  if (!g_initialized)
    return QByteArray();

  uint64_t counter = g_counter.fetch_add(1);
  QByteArray result;
  result.resize(8 + plaintext.size()); // 8 bytes for counter + data

  // Copy counter
  memcpy(result.data(), &counter, 8);

  // Simple stream cipher using key + counter
  for (int i = 0; i < plaintext.size(); ++i) {
    int key_idx = (i + counter) % 32;
    result[8 + i] = plaintext[i] ^ g_key[key_idx] ^ (counter >> (i % 8));
  }

  return result;
}

QByteArray decrypt(const QByteArray &encryptedData) {
  if (!g_initialized || encryptedData.size() < 8)
    return QByteArray();

  uint64_t counter;
  memcpy(&counter, encryptedData.constData(), 8);

  QByteArray result;
  result.resize(encryptedData.size() - 8);

  for (int i = 0; i < result.size(); ++i) {
    int key_idx = (i + counter) % 32;
    result[i] = encryptedData[8 + i] ^ g_key[key_idx] ^ (counter >> (i % 8));
  }

  return result;
}

void cleanup() {
  OPENSSL_cleanse(g_key, 32);
  g_initialized = false;
}

} // namespace MinimalCipher
