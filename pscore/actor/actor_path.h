#pragma once
#include <absl/strings/string_view.h>

#include <string>

namespace pscore {

std::string AbsPath(absl::string_view path);

std::string PathJoin(absl::string_view base, absl::string_view newpath);

}  // namespace pscore
