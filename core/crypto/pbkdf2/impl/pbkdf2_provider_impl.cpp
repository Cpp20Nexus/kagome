/**
 * Copyright Quadrivium LLC
 * All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 */

#include "crypto/pbkdf2/impl/pbkdf2_provider_impl.hpp"

#include <openssl/evp.h>

namespace kagome::crypto {

  outcome::result<SecureBuffer<>> Pbkdf2ProviderImpl::deriveKey(
      common::BufferView data,
      common::BufferView salt,
      size_t iterations,
      size_t key_length) const {
    SecureBuffer<> out(key_length, 0);
    const auto *digest = EVP_sha512();

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    int res = PKCS5_PBKDF2_HMAC(reinterpret_cast<const char *>(data.data()),
                                data.size(),
                                salt.data(),
                                salt.size(),
                                iterations,
                                digest,
                                key_length,
                                out.data());
    if (res != 1) {
      return Pbkdf2ProviderError::KEY_DERIVATION_FAILED;
    }

    return out;
  }
}  // namespace kagome::crypto

OUTCOME_CPP_DEFINE_CATEGORY(kagome::crypto, Pbkdf2ProviderError, error) {
  using Error = kagome::crypto::Pbkdf2ProviderError;
  switch (error) {
    case Error::KEY_DERIVATION_FAILED:
      return "failed to derive key";
  }
  return "unknown Pbkdf2ProviderError";
}
