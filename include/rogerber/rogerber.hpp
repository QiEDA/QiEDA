#ifndef QIGERBER_HPP
#define QIGERBER_HPP

#if defined(_WIN32) || defined(WIN32)
# ifdef rogerber_EXPORTS
#  define ROGERBER_EXPORT __declspec(dllexport)
# else
#  define ROGERBER_EXPORT __declspec(dllimport)
# endif
#else
# define ROGERBER_EXPORT
#endif

#endif