#include "encryption.h"

QByteArray Common::xorEncrypt(const QByteArray &data, const QByteArray &key) {
  QByteArray out = data;
  if (key.isEmpty())
    return out;
  for (int i = 0; i < out.size(); ++i)
    out[i] = out[i] ^ key.at(i % key.size());
  return out;
}
