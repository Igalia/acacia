#ifndef LIB_ATSPI_SCOPED_G_LIB_PTR_H_
#define LIB_ATSPI_SCOPED_G_LIB_PTR_H_

#include <iostream>
#include <memory>

#include <glib.h>

namespace acacia {

template <typename T>
class ScopedGLibPtr {
 public:
  ScopedGLibPtr() = default;
  explicit ScopedGLibPtr(T* ptr) : ptr_(ptr, Deleter()) {}

  T* get() { return ptr_.get(); }
  T* release() { return ptr_.release(); }

 private:
  class Deleter {
   public:
    void operator()(T* ptr) {
      if (ptr == nullptr)
        return;
      g_free(ptr);
    }
  };

  std::unique_ptr<T, Deleter> ptr_{nullptr};
};

template <typename T, void (*f)(T*)>
class ScopedGTypePtr {
 public:
  ScopedGTypePtr() = default;
  explicit ScopedGTypePtr(T* ptr) : ptr_(ptr, Deleter()) {}

  T* get() { return ptr_.get(); }
  T* release() { return ptr_.release(); }

  T* operator->() { return ptr_.get(); }

 private:
  class Deleter {
   public:
    void operator()(T* ptr) {
      if (ptr == nullptr)
        return;

      f(ptr);
    }
  };

  std::unique_ptr<T, Deleter> ptr_{nullptr};
};

template <typename T>
class ScopedGObjectPtr {
 public:
  ScopedGObjectPtr() = default;
  explicit ScopedGObjectPtr(T* ptr) : ptr_(ptr, Deleter()) {}

  ScopedGObjectPtr(const ScopedGObjectPtr& other) : ptr_(other.ptr_) {
    if (ptr_.get())
      g_object_ref(ptr_.get());
  }

  T* get() { return ptr_.get(); }
  T* release() { return ptr_.release(); }

  T* operator->() { return ptr_.get(); }

 private:
  class Deleter {
   public:
    void operator()(T* ptr) {
      if (ptr == nullptr)
        return;
      g_object_unref(ptr);
    }
  };

  std::unique_ptr<T, Deleter> ptr_{nullptr};
};

}  // namespace acacia

#endif  // LIB_ATSPI_SCOPED_G_LIB_PTR_H_
