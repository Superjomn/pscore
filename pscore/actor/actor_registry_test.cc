#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "pscore/actor/actor_registry.h"
#include "pscore/actor/actor_test_utils.h"

namespace pscore {

TEST_CASE("ActorRegistry.Register") {
  ActorRegistry registry;
  auto res = registry.Register<MyActor>("./myactor", "myactor");
  CHECK(res.ok());

  res = registry.Register<MyActor>("./myactor", "myactor");
  CHECK(!res.ok());
}

TEST_CASE("ActorRegistry.Lookup") {
  ActorRegistry registry;
  auto res = registry.Register<MyActor>("/myactor", "myactor");
  CHECK(res.ok());

  auto* actor = registry.Lookup("/myactor");
  CHECK(actor != nullptr);
}

TEST_CASE("ActorRegister.Erase") {
  ActorRegistry registry;
  auto res = registry.Register<MyActor>("/myactor", "myactor");
  CHECK(res.ok());
  registry.Erase("/myactor");

  auto* actor = registry.Lookup("/myactor");
  CHECK(actor == nullptr);
}

}  // namespace pscore
