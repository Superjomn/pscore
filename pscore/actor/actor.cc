#include "pscore/actor/actor.h"

#include "pscore/actor/actor_context.h"

namespace pscore {

Actor::Actor(ActorContext *ctx, absl::string_view name)
    : ActorLogging(name), name_(name), ctx_(ctx), address_(ctx_->GenAddress(name)) {}

}  // namespace pscore
