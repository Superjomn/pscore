#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "pscore/actor/actor_context.h"
#include "pscore/actor/actor_test_utils.h"

namespace pscore {

TEST_CASE("ActorContext") {
  ActorContext ctx;
  auto* myactor = ctx.ActorOf<MyActor>("myactor", &ctx, "myactor");
  REQUIRE(myactor->name() == "myactor");
  REQUIRE(myactor->address() == "ROOT/myactor");

  REQUIRE(ctx.ActorFor("ROOT/myactor") == myactor);

}

}  // namespace pscore
