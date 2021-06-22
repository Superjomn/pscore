#pragma once

#include "pscore/actor/actor.h"

namespace pscore {

class MyActor : public Actor {
 public:
  MyActor(absl::string_view name) : Actor(name) {}

  Status Receive(Message &&message) override {
    if (message.IsType<int>()) {
      ACTOR_LOG(INFO) << "get an int: " << message.data<int>();
    } else if (message.IsType<float>()) {
      ACTOR_LOG(INFO) << "get a float: " << message.data<float>();
    } else {
      ACTOR_LOG(ERROR) << "get unexpected message type";
      return Status(Status::code_t::UNKNOWN, "get unexpected message type");
    }

    return Status::OK();
  }
};

}  // namespace pscore
