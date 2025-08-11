#ifndef MINIMAL_CIPHER_H
#define MINIMAL_CIPHER_H

#include <QByteArray>

namespace MinimalCipher {

bool initialize(const QByteArray &passphrase);
QByteArray encrypt(const QByteArray &plaintext);
QByteArray decrypt(const QByteArray &encryptedData);
void cleanup();

} // namespace MinimalCipher

#endif
