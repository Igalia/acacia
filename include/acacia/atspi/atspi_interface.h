#ifndef INCLUDE_ACACIA_ATSPI_ATSPI_INTERFACE_H_
#define INCLUDE_ACACIA_ATSPI_ATSPI_INTERFACE_H_

#include <iostream>
#include <memory>
#include <string>

#include <atspi/atspi.h>

namespace acacia {

/**
 * Objects descending from this class wrap an
 * [AtspiObject](https://docs.gtk.org/atspi2/class.Object.html) of a specific
 * type. See descendants of this class for more information about each type.
 */
template <typename T>
class AtspiInterface {
 public:
  explicit AtspiInterface(T* interface) : interface_(interface, Deleter()) {}

  AtspiInterface() {}
  virtual ~AtspiInterface() {}

  /**
   * Tests whether the underlying interface pointer is null.
   */
  bool isNull() const { return !interface_; }

  /**
   * Helper function to print commonly needed values associated with this
   * interface.
   */
  virtual std::string toString() const = 0;

 protected:
  class Deleter {
   public:
    void operator()(T* ptr) {
      if (ptr == nullptr)
        return;
      g_object_unref(ptr);
    }
  };

  std::shared_ptr<T> interface_{nullptr};
};

}  // namespace acacia

#endif  // INCLUDE_ACACIA_ATSPI_ATSPI_INTERFACE_H_
