#ifndef __EXPORT_H
#define __EXPORT_H

#if defined(_WIN32) || defined(WIN32)
# ifdef qicore_EXPORTS
#  define QICORE_EXPORT __declspec(dllexport)
# else
#  define QICORE_EXPORT __declspec(dllimport)
# endif
#else
# define QICORE_EXPORT
#endif

#endif