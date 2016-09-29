#ifndef QIGERBER_HPP
#define QIGERBER_HPP

#if defined(_WIN32) || defined(WIN32)
# ifdef qigerber_EXPORTS
#  define QIGERBER_EXPORT __declspec(dllexport)
# else
#  define QIGERBER_EXPORT __declspec(dllimport)
# endif
#else
# define QIGERBER_EXPORT
#endif

#endif