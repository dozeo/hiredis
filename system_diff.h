#ifdef _MSC_VER
# define INLINE __inline
# define snprintf _snprintf
# define strcasecmp _stricmp
# define strncasecmp _strnicmp
# define strerror_r(errno,buf,len) strerror_s(buf,len,errno)
# define close(_x) closesocket((SOCKET)_x)
# define wrap_sockopt(_x) (char*)(_x)
# define wrap_sockopt_len(_x) (int*)(_x)
# define read(_fd, _buf, _bufsize) recv((SOCKET)(_fd), (char*)_buf, (int)_bufsize, 0)
# define write(_fd, _buf, _bufsize) send((SOCKET)(_fd), (const char*)_buf, (int)_bufsize, 0)
# ifndef va_copy
#  define va_copy(_d, _s) ((_d) = (_s))
# endif
# define zu "%u"
#else
#define INLINE inline
#define wrap_sockopt(_x) (_x)
#define wrap_sockopt_len(_x) (_x)
# define zu "%zu"
#endif
