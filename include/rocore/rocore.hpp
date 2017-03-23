#ifndef __EXPORT_H
#define __EXPORT_H

#if defined(_WIN32) || defined(WIN32)
# ifdef rocore_EXPORTS
#  define ROCORE_EXPORT __declspec(dllexport)
# else
#  define ROCORE_EXPORT __declspec(dllimport)
# endif
#else
# define ROCORE_EXPORT
#endif

#endif