
#ifndef ACACIA_EXPORT_H
#define ACACIA_EXPORT_H

// clang-format off
#ifdef WIN32
#  ifndef ACACIA_EXPORT
#    ifdef acacia_EXPORTS
        /* We are building this library */
#      define ACACIA_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ACACIA_EXPORT __declspec(dllimport)
#    endif
#  endif
#else
#  define ACACIA_EXPORT
#endif

#ifndef ACACIA_NO_EXPORT
#  define ACACIA_NO_EXPORT
#endif
// clang-format on

#endif /* ACACIA_EXPORT_H */
