#include "encryption.h"
#include <openssl/evp.h>
#include <openssl/rand.h>

namespace CommonEncryptor {

static constexpr int KEY_LEN = 32;  // AES-256
static constexpr int IV_LEN = 12;   // recommended for GCM
static constexpr int TAG_LEN = 16;  // 128-bit tag
static constexpr int SALT_LEN = 16; // 128-bit salt
static constexpr int PBKDF2_ITERS =
    200000; // adjust for your platform (higher = slower/stronger)

static bool deriveKeyFromPassword(const QByteArray &passphrase,
                                  const unsigned char *salt, int saltLen,
                                  int iterations, unsigned char *outKey,
                                  int outKeyLen) {
  // Using PKCS5_PBKDF2_HMAC (PBKDF2-HMAC-SHA256)
  int rc =
      PKCS5_PBKDF2_HMAC(passphrase.constData(), passphrase.size(), salt,
                        saltLen, iterations, EVP_sha256(), outKeyLen, outKey);
  return rc == 1;
}

QByteArray encryptWithPassword(const QByteArray &plaintext,
                               const QByteArray &passphrase,
                               const QByteArray &aad) {
  if (passphrase.isEmpty())
    return QByteArray();

  // generate salt and iv
  unsigned char salt[SALT_LEN];
  unsigned char iv[IV_LEN];
  if (RAND_bytes(salt, SALT_LEN) != 1)
    return QByteArray();
  if (RAND_bytes(iv, IV_LEN) != 1)
    return QByteArray();

  unsigned char key[KEY_LEN];
  if (!deriveKeyFromPassword(passphrase, salt, SALT_LEN, PBKDF2_ITERS, key,
                             KEY_LEN)) {
    return QByteArray();
  }

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx)
    return QByteArray();

  const EVP_CIPHER *cipher = EVP_aes_256_gcm();
  if (EVP_EncryptInit_ex(ctx, cipher, nullptr, nullptr, nullptr) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }
  if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, nullptr) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }
  if (EVP_EncryptInit_ex(ctx, nullptr, nullptr, key, iv) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }

  if (!aad.isEmpty()) {
    int outlen;
    if (EVP_EncryptUpdate(
            ctx, nullptr, &outlen,
            reinterpret_cast<const unsigned char *>(aad.constData()),
            aad.size()) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      return QByteArray();
    }
  }

  QByteArray cipherText;
  cipherText.resize(plaintext.size());
  int outlen = 0;
  if (EVP_EncryptUpdate(
          ctx, reinterpret_cast<unsigned char *>(cipherText.data()), &outlen,
          reinterpret_cast<const unsigned char *>(plaintext.constData()),
          plaintext.size()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }
  int ciphertext_len = outlen;

  if (EVP_EncryptFinal_ex(
          ctx, reinterpret_cast<unsigned char *>(cipherText.data()) + outlen,
          &outlen) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }
  ciphertext_len += outlen;
  cipherText.resize(ciphertext_len);

  unsigned char tag[TAG_LEN];
  if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, TAG_LEN, tag) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }

  EVP_CIPHER_CTX_free(ctx);

  // Package: SALT || IV || TAG || CIPHERTEXT
  QByteArray out;
  out.append(reinterpret_cast<const char *>(salt), SALT_LEN);
  out.append(reinterpret_cast<const char *>(iv), IV_LEN);
  out.append(reinterpret_cast<const char *>(tag), TAG_LEN);
  out.append(cipherText);

  // zero sensitive memory
  OPENSSL_cleanse(key, KEY_LEN);

  return out.toBase64();
}

QByteArray decryptWithPassword(const QByteArray &base64Input,
                               const QByteArray &passphrase,
                               const QByteArray &aad) {
  if (passphrase.isEmpty())
    return QByteArray();

  QByteArray input = QByteArray::fromBase64(base64Input);
  if (input.size() < (SALT_LEN + IV_LEN + TAG_LEN))
    return QByteArray();

  const unsigned char *salt =
      reinterpret_cast<const unsigned char *>(input.constData());
  const unsigned char *iv =
      reinterpret_cast<const unsigned char *>(input.constData() + SALT_LEN);
  const unsigned char *tag = reinterpret_cast<const unsigned char *>(
      input.constData() + SALT_LEN + IV_LEN);
  const unsigned char *cipherText = reinterpret_cast<const unsigned char *>(
      input.constData() + SALT_LEN + IV_LEN + TAG_LEN);
  int cipherTextLen = input.size() - SALT_LEN - IV_LEN - TAG_LEN;

  unsigned char key[KEY_LEN];
  if (!deriveKeyFromPassword(passphrase, salt, SALT_LEN, PBKDF2_ITERS, key,
                             KEY_LEN)) {
    return QByteArray();
  }

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx)
    return QByteArray();

  const EVP_CIPHER *cipher = EVP_aes_256_gcm();
  if (EVP_DecryptInit_ex(ctx, cipher, nullptr, nullptr, nullptr) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }
  if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LEN, nullptr) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }
  if (EVP_DecryptInit_ex(ctx, nullptr, nullptr, key, iv) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }

  if (!aad.isEmpty()) {
    int outlen;
    if (EVP_DecryptUpdate(
            ctx, nullptr, &outlen,
            reinterpret_cast<const unsigned char *>(aad.constData()),
            aad.size()) != 1) {
      EVP_CIPHER_CTX_free(ctx);
      return QByteArray();
    }
  }

  QByteArray plaintext;
  plaintext.resize(cipherTextLen);
  int outlen = 0;
  if (EVP_DecryptUpdate(ctx,
                        reinterpret_cast<unsigned char *>(plaintext.data()),
                        &outlen, cipherText, cipherTextLen) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }
  int plaintext_len = outlen;

  if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, TAG_LEN,
                          const_cast<unsigned char *>(tag)) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    return QByteArray();
  }

  // This will verify tag
  int rc = EVP_DecryptFinal_ex(
      ctx, reinterpret_cast<unsigned char *>(plaintext.data()) + outlen,
      &outlen);
  EVP_CIPHER_CTX_free(ctx);

  if (rc <= 0) {
    // auth failed
    OPENSSL_cleanse(key, KEY_LEN);
    return QByteArray();
  }

  plaintext_len += outlen;
  plaintext.resize(plaintext_len);

  OPENSSL_cleanse(key, KEY_LEN);
  return plaintext;
}

} // namespace CommonEncryptor
