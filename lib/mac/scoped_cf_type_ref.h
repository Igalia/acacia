#ifndef LIB_MAC_SCOPED_CF_TYPE_REF_H_
#define LIB_MAC_SCOPED_CF_TYPE_REF_H_

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
  ScopedCFTypeRef(ScopedCFTypeRef& other) : ref_(other.ref_) { CFRetain(ref_); }

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

  // If you need to pass the reference to something else which should retain it,
  // use this rather than get().
  T Retain() { return CFRetain(ref_); }

  ScopedCFTypeRef& operator=(ScopedCFTypeRef other) {
    if (ref_)
      CFRelease(ref_);
    ref_ = other.ref_;
    return *this;
  }

 private:
  T ref_{NULL};
};

#endif  // LIB_MAC_SCOPED_CF_TYPE_REF_H_
