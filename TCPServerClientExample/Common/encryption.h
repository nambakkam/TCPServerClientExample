#ifndef COMMON_ENCRYPTION_H
#define COMMON_ENCRYPTION_H

#include <QByteArray>

namespace CommonEncryptor {
QByteArray encryptWithPassword(const QByteArray &plaintext,
                               const QByteArray &passphrase,
                               const QByteArray &aad = QByteArray());

/// Decrypt Base64 produced by encryptWithPassword. Returns empty QByteArray on
/// failure.
QByteArray decryptWithPassword(const QByteArray &base64Input,
                               const QByteArray &passphrase,
                               const QByteArray &aad = QByteArray());
} // namespace CommonEncryptor

#endif // COMMON_ENCRYPTION_H
