#define CATCH_CONFIG_MAIN
#include "pscore/actor/actor.h"

#include <catch2/catch.hpp>

#include "pscore/actor/actor_test_utils.h"
#include "pscore/actor/actor_context.h"

namespace pscore {

TEST_CASE("test_actor.Receive") {
  ActorContext ctx;
  MyActor actor(&ctx, "myactor");
  actor.Start();

  int val = 2008;
  Message message(std::move(val));
  auto status = actor.Receive(std::move(message));
  actor.Stop();
}

TEST_CASE("Actor.Send") {
  ActorContext ctx;
  MyActor actor(&ctx, "myactor2");
  actor.Start();

  // auto status = actor.Receive(std::move(message));
  actor.Send(&actor, Message(2008));
  actor.Send(&actor, Message(2.008f));
  actor.Stop();
}

}  // namespace pscore
