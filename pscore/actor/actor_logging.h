#pragma once

#include <absl/strings/string_view.h>
#include <glog/logging.h>

#include "pscore/common/macros.h"

namespace pscore {

/**
 * Help actor log some details.
 */
class ActorLogging {
 public:
  ActorLogging(absl::string_view actor_name) : actor_name_(actor_name) {}

#define ACTOR_LOG(level__) LOG(level__) << "ACTOR[" << actor_name() << "] "

  const std::string& actor_name() const { return actor_name_; }

 private:
  std::string actor_name_;
};

}  // namespace pscore
