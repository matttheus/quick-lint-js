// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#ifndef QUICK_LINT_JS_EVENT_LOOP_H
#define QUICK_LINT_JS_EVENT_LOOP_H

#include <array>
#include <cstddef>
#include <optional>
#include <quick-lint-js/assert.h>
#include <quick-lint-js/char8.h>
#include <quick-lint-js/file-handle.h>
#include <quick-lint-js/have.h>
#include <quick-lint-js/narrow-cast.h>

#if QLJS_HAVE_WINDOWS_H
#include <Windows.h>
#endif

#if QLJS_HAVE_POLL
#include <poll.h>
#endif

#if defined(_WIN32)
#define QLJS_EVENT_LOOP_READ_PIPE_NON_BLOCKING 0
#else
#define QLJS_EVENT_LOOP_READ_PIPE_NON_BLOCKING 1
#endif

namespace quick_lint_js {
#if QLJS_HAVE_CXX_CONCEPTS
template <class Delegate>
concept event_loop_delegate = requires(Delegate d, const Delegate cd,
                                       string8_view data) {
  {cd.get_readable_pipe()};
  {d.append(data)};
};
#endif

// An event_loop implements I/O concurrency on a single thread.
//
// An event_loop manages the following types of I/O:
//
// * a readable pipe
//
// event_loop uses the CRTP pattern. Inherit from event_loop<your_class>.
// your_class must satisfy the event_loop_delegate concept.
//
// event_loop will never call non-const member functions in parallel.
template <class Derived>
class event_loop {
 public:
  void run() {
    while (!this->done_) {
      this->read_from_pipe();
      if (this->done_) {
        break;
      }

#if QLJS_HAVE_POLL
      platform_file_ref pipe = this->const_derived().get_readable_pipe();
      ::pollfd pollfds[] = {
#if QLJS_EVENT_LOOP_READ_PIPE_NON_BLOCKING
        {.fd = pipe.get(), .events = POLLIN, .revents = 0},
#endif
      };
      QLJS_ASSERT(std::size(pollfds) > 0);
      int rc = ::poll(pollfds, std::size(pollfds), /*timeout=*/-1);
      if (rc == -1) {
        QLJS_UNIMPLEMENTED();
      }
      QLJS_ASSERT(rc > 0);
#if QLJS_EVENT_LOOP_READ_PIPE_NON_BLOCKING
      if (pollfds[0].revents & POLLIN) {
        continue;
      }
      if (pollfds[0].revents & POLLERR) {
        QLJS_UNIMPLEMENTED();
      }
#endif
#elif defined(_WIN32)
      // Nothing to wait for.
      static_assert(!QLJS_EVENT_LOOP_READ_PIPE_NON_BLOCKING);
#else
#error "Unsupported platform"
#endif
    }
  }

 private:
  void read_from_pipe() {
    // TODO(strager): Pick buffer size intelligently.
    std::array<char8, 1024> buffer;
    platform_file_ref pipe = this->const_derived().get_readable_pipe();
#if QLJS_EVENT_LOOP_READ_PIPE_NON_BLOCKING
    QLJS_ASSERT(pipe.is_pipe_non_blocking());
#else
    QLJS_ASSERT(!pipe.is_pipe_non_blocking());
#endif
    file_read_result read_result = pipe.read(buffer.data(), buffer.size());
    if (read_result.at_end_of_file) {
      this->done_ = true;
    } else if (read_result.error_message.has_value()) {
#if QLJS_HAVE_UNISTD_H
      if (errno == EAGAIN) {
#if QLJS_EVENT_LOOP_READ_PIPE_NON_BLOCKING
        return;
#else
        QLJS_UNREACHABLE();
#endif
      }
#endif
      QLJS_UNIMPLEMENTED();
    } else {
      QLJS_ASSERT(read_result.bytes_read != 0);
      this->derived().append(string8_view(
          buffer.data(), narrow_cast<std::size_t>(read_result.bytes_read)));
    }
  }

#if QLJS_HAVE_CXX_CONCEPTS
  event_loop_delegate
#endif
      auto&
      derived() {
    return *static_cast<Derived*>(this);
  }

  const
#if QLJS_HAVE_CXX_CONCEPTS
      event_loop_delegate
#endif
      auto&
      const_derived() const {
    return *static_cast<const Derived*>(this);
  }

  bool done_ = false;
};
}

#endif

// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew "strager" Glazar
//
// This file is part of quick-lint-js.
//
// quick-lint-js is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// quick-lint-js is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
