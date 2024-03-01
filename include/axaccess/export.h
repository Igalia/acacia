
#ifndef AXA_EXPORT_H
#define AXA_EXPORT_H

// clang-format off
#ifdef WIN32
#  ifndef AXA_EXPORT
#    ifdef axaccess_EXPORTS
        /* We are building this library */
#      define AXA_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define AXA_EXPORT __declspec(dllimport)
#    endif
#  endif
#else
#  define AXA_EXPORT
#endif

#ifndef AXA_NO_EXPORT
#  define AXA_NO_EXPORT
#endif
// clang-format on

#endif /* AXA_EXPORT_H */
