#pragma once

#include <absl/strings/str_format.h>
#include <absl/strings/string_view.h>

#include "pscore/actor/actor.h"
#include "pscore/actor/actor_path.h"
#include "pscore/actor/actor_registry.h"

namespace pscore {

class ActorContext {
 public:
  explicit ActorContext(absl::string_view name = "ROOT") : name_(name) {}

  template <typename ActorT, typename... Args>
  Actor* ActorOf(absl::string_view name, Args... args) {
    auto path = PathJoin(this->name(), name);
    LOG(INFO) << "New Actor called " << path;

    Status res = registry_.Register<ActorT>(path, args...);
    if (!res.ok()) {
      LOG(ERROR) << absl::StrFormat("Failed to register actor [%s], error:\n%s", name, res.error_message());
      return nullptr;
    }
    auto* instance     = registry_.Lookup(path);
    CHECK(instance);
    instance->address_ = path;
    return instance;
  }

  Actor* ActorFor(absl::string_view path) {
    auto _path = AbsPath(path);
    return registry_.Lookup(_path);
  }

  const std::string& name() const { return name_; }

  std::string GenAddress(absl::string_view name) const { return PathJoin(this->name(), name); }
  std::string GenAddress(absl::string_view base, absl::string_view name) const { return PathJoin(base, name); }

 private:
  std::string name_;
  ActorRegistry registry_;
};

}  // namespace pscore
