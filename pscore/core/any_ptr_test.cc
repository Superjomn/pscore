#define CATCH_CONFIG_MAIN
#include "pscore/core/any_ptr.h"

#include <catch2/catch.hpp>

namespace pscore {

TEST_CASE("test_any_ptr") {
  int a = 0;
  AnyPtr ptr(&a);

  REQUIRE(ptr.get<int>() == &a);
  REQUIRE(ptr.get<float>() == nullptr);
}

}  // namespace pscore
