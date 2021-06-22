#define CATCH_CONFIG_MAIN
#include "pscore/actor/actor_registry.h"

#include <catch2/catch.hpp>

#include "pscore/actor/actor_test_utils.h"

namespace pscore {

TEST_CASE("ActorRegistry.Register") {
  ActorRegistry registry;
  auto res = registry.Register<MyActor>("./myactor", "myactor");
  REQUIRE(res.ok());

  res = registry.Register<MyActor>("./myactor", "myactor");
  CHECK(!res.ok());
}

TEST_CASE("ActorRegistry.Lookup") {
  ActorRegistry registry;
  auto res = registry.Register<MyActor>("/myactor", "myactor");
  REQUIRE(res.ok());

  auto* actor = registry.Lookup("/myactor");
  REQUIRE(actor != nullptr);
}

TEST_CASE("ActorRegister.Erase") {
  ActorRegistry registry;
  auto res = registry.Register<MyActor>("/myactor", "myactor");
  REQUIRE(res.ok());
  registry.Erase("/myactor");

  auto* actor = registry.Lookup("/myactor");
  REQUIRE(actor == nullptr);
}

}  // namespace pscore
