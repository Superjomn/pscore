#pragma once

#include <absl/strings/str_format.h>
#include "pscore/common/macros.h"
#include "pscore/core/any_ptr.h"
#include "pscore/core/status.h"

namespace pscore {

/**
 * An abstraction for an object that manages the lifecycle of a Servable. A specific Servable implementation should hold
 * its configuration and resource in the constructor, and offer the standard APIs to interect with the core framework.
 */
class Loader {
 public:
  virtual ~Loader() = default;

  //! Fetches any resource that needs for a servable.
  virtual Status Load() { return errors::Unimplemented("Load isn't implemented"); }

  //! Frees any resources allocated during the live time of the target Servable.
  virtual void Unload() = 0;

  //! Returns an opaque interface to the underlying servable object.
  virtual AnyPtr servable() = 0;
};

}  // namespace pscore
