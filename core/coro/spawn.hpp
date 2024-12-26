/**
 * Copyright Quadrivium LLC
 * All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>

#include "coro/coro.hpp"

namespace kagome {
  void coroSpawn(auto executor, auto f) {
    boost::asio::co_spawn(
        executor,
        [](decltype(f) f) -> Coro<void> { co_await f(); }(std::move(f)),
        boost::asio::detached);
  }
}  // namespace kagome
