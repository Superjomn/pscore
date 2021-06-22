#include "pscore/actor/actor_path.h"

#include <glog/logging.h>

#include <stack>

namespace pscore {

std::string AbsPath(absl::string_view path) {
  std::vector<absl::string_view> stack;

  size_t p = 0;
  while (p != std::string::npos && p < path.size()) {
    auto slash = path.find('/', p);
    absl::string_view part;

    if (slash != std::string::npos) {
      part = path.substr(p, slash - p);
    } else {
      part = path.substr(p);
    }

    if (part == ".") {
    } else if (part == "..") {
      if (!stack.empty()) stack.pop_back();
    } else if (!part.empty()) {
      stack.push_back(part);
    }

    p = slash + 1;
    if (slash == std::string::npos) break;
  }

  std::string res;
  for (auto &w : stack) {
    res.append(w.data(), w.size());
    res.push_back('/');
  }

  res.pop_back();

  return res;
}

std::string PathJoin(absl::string_view base, absl::string_view newpath) {
  auto res = std::string(base) + '/' + std::string(newpath);
  return AbsPath(res);
}

}  // namespace pscore
