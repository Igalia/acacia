#ifndef LIB_MAC_SCOPED_CF_TYPE_REF_H_
#define LIB_MAC_SCOPED_CF_TYPE_REF_H_

namespace mac_inspect {
// Container to handle CFRelease-ing CFTypeRefs at the end of a scope. See:
// https://developer.apple.com/library/archive/documentation/CoreFoundation/Conceptual/CFMemoryMgmt/Concepts/Ownership.html
//
// This should be used when a method with "Create" or "Copy" is used to obtain
// a CFTypeRef, to ensure CFRelease is called appropriately.
//
// Use CreateFromUnownedRef() for references obtained using methods with "Get"
// in the name.
template <typename T>
class ScopedCFTypeRef {
 public:
  ScopedCFTypeRef() = default;
  ScopedCFTypeRef(const ScopedCFTypeRef& other)
      : ref_((T)CFRetain(other.ref_)) {}

  explicit ScopedCFTypeRef(T ref) : ref_(ref) {}

  static ScopedCFTypeRef CreateFromUnownedRef(T ref) {
    CFRetain(ref);
    return ScopedCFTypeRef(ref);
  }

  ~ScopedCFTypeRef() {
    if (ref_)
      CFRelease(ref_);
  }

  T get() { return ref_; }
  T* get_ptr() { return &ref_; }

  void reset(T ref) {
    if (ref_)
      CFRelease(ref_);
    ref_ = ref;
  }

  ScopedCFTypeRef& operator=(const ScopedCFTypeRef& other) {
    if (ref_)
      CFRelease(ref_);
    ref_ = (T)CFRetain(other.ref_);
    return *this;
  }

 private:
  T ref_{nullptr};
};

}  // namespace mac_inspect

#endif  // LIB_MAC_SCOPED_CF_TYPE_REF_H_
