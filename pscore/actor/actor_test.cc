#define CATCH_CONFIG_MAIN
#include "pscore/actor/actor.h"

#include <catch2/catch.hpp>

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

TEST_CASE("test_actor.Receive") {
  MyActor actor("myactor");
  actor.Start();

  int val = 2008;
  Message message(std::move(val));
  auto status = actor.Receive(std::move(message));
  actor.Stop();
}

TEST_CASE("Actor.Send") {
  MyActor actor("myactor2");
  actor.Start();

  // auto status = actor.Receive(std::move(message));
  actor.Send(&actor, Message(2008));
  actor.Send(&actor, Message(2.008f));
  actor.Stop();
}

}  // namespace pscore
