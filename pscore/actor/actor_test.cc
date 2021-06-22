#define CATCH_CONFIG_MAIN
#include "pscore/actor/actor.h"

#include <catch2/catch.hpp>

#include "pscore/actor/actor_test_utils.h"

namespace pscore {

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
