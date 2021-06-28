#define CATCH_CONFIG_MAIN
#include "pscore/actor/actor_path.h"

#include <catch2/catch.hpp>

namespace pscore {

TEST_CASE("AbsPath") {
  SECTION("basic") {
    std::string acase = "./././abc/./";
    REQUIRE(AbsPath(acase) == "abc");
  }

  SECTION("upper") {
    std::string acase = "./a/b/c/../b/././abc/../../abc";
    REQUIRE(AbsPath(acase) == "a/b/abc");
  }
}

TEST_CASE("PathJoin") {
  SECTION("basic") {
    std::string a = "./././abc/./";
    std::string b = "./a/b/c/../b/././abc/../../abc";
    REQUIRE(PathJoin(a, b) == "abc/a/b/abc");
  }
}

}  // namespace pscore
