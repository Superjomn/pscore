#define CATCH_CONFIG_MAIN
#include "pscore/actor/actor_registry.h"

#include <catch2/catch.hpp>

#include "pscore/actor/actor_test_utils.h"
#include "pscore/actor/actor_context.h"

namespace pscore {

TEST_CASE("ActorRegistry.Register") {
  ActorContext ctx;
  ActorRegistry registry;
  auto res = registry.Register<MyActor>("./myactor", &ctx, "myactor");
  REQUIRE(res.ok());

  res = registry.Register<MyActor>("./myactor", &ctx, "myactor");
  CHECK(!res.ok());
}

TEST_CASE("ActorRegistry.Lookup") {
  ActorRegistry registry;
  ActorContext ctx;
  auto res = registry.Register<MyActor>("/myactor", &ctx, "myactor");
  REQUIRE(res.ok());

  auto* actor = registry.Lookup("/myactor");
  REQUIRE(actor != nullptr);
}

TEST_CASE("ActorRegister.Erase") {
  ActorRegistry registry;
  ActorContext ctx;
  auto res = registry.Register<MyActor>("/myactor", &ctx, "myactor");
  REQUIRE(res.ok());
  registry.Erase("/myactor");

  auto* actor = registry.Lookup("/myactor");
  REQUIRE(actor == nullptr);
}

}  // namespace pscore
