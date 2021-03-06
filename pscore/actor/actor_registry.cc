#include "pscore/actor/actor_registry.h"

#include "pscore/actor/actor.h"

namespace pscore {

ActorRegistry::~ActorRegistry() {
  for (auto& item : data_) {
    delete item.second;
  }
}

}  // namespace pscore
