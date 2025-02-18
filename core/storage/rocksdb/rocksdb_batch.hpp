/**
 * Copyright Quadrivium LLC
 * All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <rocksdb/write_batch.h>
#include "storage/rocksdb/rocksdb.hpp"

namespace kagome::storage {

  class RocksDbBatch : public BufferBatch {
   public:
    ~RocksDbBatch() override = default;

    explicit RocksDbBatch(RocksDbSpace &db);

    outcome::result<void> commit() override;

    void clear() override;

    outcome::result<void> put(const BufferView &key,
                              BufferOrView &&value) override;

    outcome::result<void> remove(const BufferView &key) override;

   private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
    RocksDbSpace &db_;
    rocksdb::WriteBatch batch_;
  };
}  // namespace kagome::storage
