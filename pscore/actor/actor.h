#pragma once
#include <absl/strings/str_format.h>
#include <absl/strings/string_view.h>
#include <absl/types/any.h>
#include <stdint.h>

#include <queue>
#include <string>
#include <thread>

#include "pscore/actor/actor_logging.h"
#include "pscore/common/channel.h"
#include "pscore/common/managed_thread.h"
#include "pscore/common/type_util.h"
#include "pscore/core/status.h"

namespace pscore {

struct Message {
  Message() = default;

  template <typename T>
  Message(T&& data) : data_(std::move(data)), type_id_(FastTypeId<typename std::decay<T>::type>()) {}

  template <typename T>
  bool IsType() const {
    return type_id_ == FastTypeId<T>();
  }

  template <typename T>
  const T& data() {
    CHECK(IsType<T>());
    return *absl::any_cast<T>(&data_);
  }

  absl::any data_;

 private:
  size_t type_id_{};
};

/**
 * Base class for all the actors.
 */
class Actor : public ActorLogging {
 public:
  explicit Actor(absl::string_view name) : ActorLogging(name), name_(name) {}

  /**
   * User should implement this, to handle different kind of messages.
   * e.g.
   *
   * Status Receive(Message&& message) {
   *   switch(message.type_id) {
   *     if (message.IsType<int>()): ACTOR_LOG(INFO) << "get an int!";
   *     else if (message.IsType<float>()) ACTOR_LOG(INFO) << "get a float!";
   *     else return Status(Status::code_t::UNKNOWN, "unexpected type");
   *   }
   *   return Status::OK();
   * }
   */
  virtual Status Receive(Message&& message) = 0;

  /**
   * Send a \p message to the \p destination identified by an Actor.
   */
  virtual Status Send(const Actor* destination, Message&& message) {
    if (!destination->channel_.WriteMove(std::move(message))) {
      return Status(
          Status::code_t::UNKNOWN, ""
          // absl::StrFormat("Actor [%s] send message to [%s] failed.", name().c_str(), destination->name().c_str())
      );
    }
    return Status::OK();
  }

  /**
   * The callback before starting the actor.
   */
  virtual Status PreStart() { return Status::OK(); }

  /**
   * The callback after the actor stops.
   */
  virtual Status PostStop() { return Status::OK(); }

  Status Start() {
    {
      auto res = PreStart();
      if (!res.ok()) return res;
    }

    thread_.Start([this] {
      Message message;
      while (channel_.Read(&message)) {
        auto status = Receive(std::move(message));
        if (!status.ok()) {
          ACTOR_LOG(ERROR) << status.error_message();
          continue;
        }
      }
    });

    {
      auto res = PostStop();
      if (!res.ok()) return res;
    }

    return Status::OK();
  }

  void Stop() {
    channel_.Close();
    thread_.Join();
  }

  const std::string& name() const { return name_; }

  virtual ~Actor() { thread_.Join(); }

 protected:
  /**
   * Send a \p message to the \p destination identified by a string.
   */
  virtual Status Send(absl::string_view destination, Message&& message) { ACTOR_LOG(FATAL) << "NotImplemented"; }

 private:
  mutable Channel<Message> channel_;

  ManagedThread thread_;

  std::string name_;
};

}  // namespace pscore
