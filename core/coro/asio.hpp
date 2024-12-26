/**
 * Copyright Quadrivium LLC
 * All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <boost/asio/as_tuple.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>
#include <libp2p/common/asio_buffer.hpp>
#include <qtils/bytes.hpp>

#include "coro/coro.hpp"

namespace kagome {
  constexpr auto useCoroOutcome =
      boost::asio::as_tuple(boost::asio::use_awaitable);

  inline outcome::result<void> coroOutcome(
      std::tuple<boost::system::error_code> &&t) {
    auto &[ec] = t;
    if (ec) {
      return ec;
    }
    return outcome::success();
  }
  template <typename T>
  outcome::result<T> coroOutcome(std::tuple<boost::system::error_code, T> &&t) {
    auto &[ec, r] = t;
    if (ec) {
      return ec;
    }
    return outcome::success(std::move(r));
  }

  CoroOutcome<void> coroWrite(auto &w, qtils::BytesIn buf) {
    CO_TRY(coroOutcome(co_await boost::asio::async_write(
        w, libp2p::asioBuffer(buf), useCoroOutcome)));
    co_return outcome::success();
  }
  CoroOutcome<void> coroRead(auto &r, qtils::BytesOut buf) {
    CO_TRY(coroOutcome(co_await boost::asio::async_read(
        r, libp2p::asioBuffer(buf), useCoroOutcome)));
    co_return outcome::success();
  }
}  // namespace kagome
