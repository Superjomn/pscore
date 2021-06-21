#pragma once
#include <absl/strings/string_view.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "pscore/core/status.h"

namespace pscore {

struct Actor;

/**
 * ActorRegistry helps to manage all the Actor instances within a process. All the actors are owned by the
 * ActorRegistry. Each Actor should bind to an unique path (like an url) so that we can retrive an Actor instance by the
 * path.
 */
class ActorRegistry {
 public:
  template <typename ActorT, typename... Ts>
  Status Register(const std::string& path, Ts... args) {
    auto it = data_.find(path);
    if (it != data_.end()) {
      return Status(Status::code_t::UNKNOWN, "duplicate register Actor called [" + path + "]");
    }

    data_[path].reset(new ActorT(args...));
  }

  /**
   * Lookup an Actor instance given the \p path, return nullptr if not exists.
   */
  Actor* Lookup(const std::string& path) {
    auto it = data_.find(path);
    if (it != data_.end()) return it->second.get();
    return nullptr;
  }

  void Erase(const std::string& path) {
    auto it = data_.find(path);
    if (it != data_.end()) {
      data_.erase(it);
    }
  }

  //! Singleton ActorRegistry instance shared by the process.
  static ActorRegistry& Global() {
    static std::unique_ptr<ActorRegistry> x(new ActorRegistry);
    return *x;
  }

 private:
  std::unordered_map<std::string, std::unique_ptr<Actor>> data_;
};

}  // namespace pscore
