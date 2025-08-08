#ifndef COMMON_ENCRYPTION_H
#define COMMON_ENCRYPTION_H

#include <QByteArray>

namespace Common {
QByteArray xorEncrypt(const QByteArray &data, const QByteArray &key);
inline QByteArray xorDecrypt(const QByteArray &data, const QByteArray &key) {
  return xorEncrypt(data, key);
}
} // namespace Common

#endif // COMMON_ENCRYPTION_H
