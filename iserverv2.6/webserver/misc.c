
#include "iserver.h"

const char	*_ctype_;
const short	*_tolower_tab_;
const short	*_toupper_tab_;

apti_module
void	_kbcopy(register char* src,register char *dest,
	int len)
{

	if(dest<src)
		while(len--)
		*dest++=*src++;
	else
	{
		char	*lasts=src+(len-1);
		char	*lastd=dest+(len-1);
		while(len--)
		*(char*)lastd--=*(char*)lasts--;
	}
}

apti_module
int	_kbcmp(char* from,char* to,int count)
{
	int	rtnval=0;
	
	while(count-->0){
		if(*from++!=*to++){
			rtnval=1;
			break;		
		}
	}
	return	(rtnval);
}

apti_module
void
_kbzero(char* to,int count)
{
	while(count-->0){
		*to++=0;
	}
}

apti_module
void *_kmemmove(void *dest,const void *src,size_t count)
{
    char *char_dest = (char *)dest;
    char *char_src = (char *)src;

    if ((char_dest <= char_src) || (char_dest >= (char_src+count)))
    {
        /*  non-overlapping buffers */
        while(count > 0)
	{
            *char_dest = *char_src;
            char_dest++;
            char_src++;
            count--;
	}
    }
    else
    {
        /* overlaping buffers */
        char_dest = (char *)dest + count - 1;
        char_src = (char *)src + count - 1;

        while(count > 0)
	{
           *char_dest = *char_src;
           char_dest--;
           char_src--;
           count--;
	}
    }

    return dest;
}
apti_module
void* _kmemcpy(void* to, const void* from, size_t count)
{
  register char *f = (char *)from;
  register char *t = (char *)to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
  return to;
}
apti_module
int   _kmemcmp(const void *s1, const void *s2, size_t n)
{
    if (n != 0) {
        const unsigned char *p1 = s1, *p2 = s2;
        do {
            if (*p1++ != *p2++)
	            return (*--p1 - *--p2);
        } while (--n != 0);
    }
    return 0;
}
apti_module
void* _kmemchr(const void *s, int c, size_t n)
{
  if (n)
  {
    const char *p = s;
    do {
      if (*p++ == c)
	return (void *)(p-1);
    } while (--n != 0);
  }
  return 0;
}
apti_module
void *_kmemccpy (void *to, const void *from,int c,size_t count)
{
  char t;
  size_t i;
  char *dst=(char*)to;
  const char *src=(const char*)from;

  for ( i = 0; i < count; i++ )
  {
    dst[i] = t = src[i];
    if ( t == '\0' )
      break;
    if ( t == c )
      return &dst[i+1];
  }
  return NULL; /* didn't copy c */
}
apti_module
void* _kmemset(void* src, int val, size_t count)
{
	char *char_src = (char *)src;

	while(count>0) {
		*char_src = val;
		char_src++;
		count--;
	}
	return src;
}



apti_module
char * _kstrcat(char * s, const char * append)
{
 char * save = s;

 for(; *s; ++s);

 while((*s++ = *append++));

 return save;
}

apti_module
char * _kstrchr(const char * s, int c)
{
 char cc = c;

 while(*s)
 {
  if(*s == cc) return (char *)s;

  s++;
 }

 if(cc == 0) return (char *)s;

 return 0;
}

apti_module
int    _kstrcmp(const char* s1, const char* s2)
{
 while(*s1 == *s2)
 {
  if(*s1 == 0) return 0;

  s1 ++;
  s2 ++;
 }

 return *s1 - *s2;
}

apti_module
char * _kstrcpy(char * to, const char * from)
{
 char *save = to;

 for (; (*to = *from); ++from, ++to);

 return save;
}

apti_module
size_t _kstrlen(const char * str)
{
 const char * s;

 if(str == 0) return 0;

 for(s = str; *s; ++ s);

 return s - str;
}



typedef unsigned char u_char;
apti_module
int _kstrcasecmp(const char *s1, const char *s2)
{
	const short *cm = _tolower_tab_ + 1;
	const u_char *us1 = (const u_char *)s1;
	const u_char *us2 = (const u_char *)s2;

	while (cm[*us1] == cm[*us2++])
		if (*us1++ == '\0')
			return (0);
	return (cm[*us1] - cm[*--us2]);
}
apti_module
int _kstrncasecmp(const char *s1, const char *s2, size_t n)
{
	const short *cm = _tolower_tab_ + 1;
	const u_char *us1 = (const u_char *)s1;
	const u_char *us2 = (const u_char *)s2;

	if (n != 0) {
		do {
			if (cm[*us1] != cm[*us2++])
				return (cm[*us1] - cm[*--us2]);
			if (*us1++ == '\0')
				break;
		} while (--n != 0);
	}
	return (0);
}

apti_module
char * _kstrncat(char * dst, const char * src, size_t n)
{
 if(n != 0)
 {
  char * d = dst;
  const char * s = src;

  while(*d != 0) ++ d;

  do
  {
   if((*d = *s++) == 0) break;

   ++ d;
  }
  while (--n != 0);

  *d = 0;
 }

 return dst;
}

apti_module
int    _kstrncmp(const char * s1, const char * s2, size_t n)
{
 if(n == 0) return 0;

 do
 {
  if(*s1 != *s2 ++) return *s1 - *-- s2;
  if(*s1 ++ == 0) break;
 }
 while (-- n != 0);

 return 0;
}

apti_module
char * _kstrncpy(char * dst, const char * src, size_t n)
{
 if(n != 0)
 {
  char * d = dst;
  const char * s = src;

  do
  {
   if((*d ++ = *s ++) == 0)
   {
    while (-- n != 0) *d ++ = 0;
    break;
   }
  }
  while(-- n != 0);
 }

 return dst;
}

apti_module
size_t _kstrnlen(const char *str, size_t count)
{
 const char * s;

 if(str == 0) return 0;

 for(s = str; *s && count; ++ s, -- count);

 return s - str;
}

apti_module
char * _kstrrchr(const char * s, int c)
{
 char cc = c;
 const char * sp = (char *)0;

 while(*s)
 {
  if(*s == cc) sp = s;
  s ++;
 }

 if(cc == 0) sp = s;

 return (char *)sp;
}


apti_module
char * _kstrstr(const char *s,const char *find)
{
  char c, sc;
  size_t len;

  if ((c = *find++) != 0)
  {
    len = _kstrlen(find);
    do {
      do {
	if ((sc = *s++) == 0)
	  return 0;
      } while (sc != c);
    } while (_kstrncmp(s, find, len) != 0);
    s--;
  }
  return (char *)((size_t)s);
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////
#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	32		/* 0x */
#define LARGE	64		/* use 'ABCDEF' instead of 'abcdef' */

#define do_div(n,base) ({ \
int __res; \
__res = ((unsigned long long) n) % (unsigned) base; \
n = ((unsigned long long) n) / (unsigned) base; \
__res; })

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

static int _kskip_atoi(const char **s)
{
	int i=0;

	while (isdigit(**s))
		i = i*10 + *((*s)++) - '0';
	return i;
}

static int _kmstrlen( const char *str )
{
	int i=0;
	if( str == NULL )
		return 0;
	while( *str++ )
		i++;
	return i;
}

char * _knumber(
char * buf, char * end, long long num, int base, int size, int precision, int type)
{
	char c,sign,tmp[66];
	const char *digits;
	const char small_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	const char large_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;

	digits = (type & LARGE) ? large_digits : small_digits;
	if (type & LEFT)
		type &= ~ZEROPAD;
	if (base < 2 || base > 36)
                return NULL;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	if (type & SIGN) {
		if (num < 0) {
			sign = '-';
			num = -num;
			size--;
		} else if (type & PLUS) {
			sign = '+';
			size--;
		} else if (type & SPACE) {
			sign = ' ';
			size--;
		}
	}
	if (type & SPECIAL) {
		if (base == 16)
			size -= 2;
		else if (base == 8)
			size--;
	}
	i = 0;
	if (num == 0)
		tmp[i++]='0';
	else while (num != 0)
		tmp[i++] = digits[do_div(num,base)];
	if (i > precision)
		precision = i;
	size -= precision;
	if (!(type&(ZEROPAD+LEFT))) {
		while(size-->0) {
			if (buf <= end)
				*buf = ' ';
			++buf;
		}
	}
	if (sign) {
		if (buf <= end)
			*buf = sign;
		++buf;
	}
	if (type & SPECIAL) {
		if (base==8) {
			if (buf <= end)
				*buf = '0';
			++buf;
		} else if (base==16) {
			if (buf <= end)
				*buf = '0';
			++buf;
			if (buf <= end)
				*buf = digits[33];
			++buf;
		}
	}
	if (!(type & LEFT)) {
		while (size-- > 0) {
			if (buf <= end)
				*buf = c;
			++buf;
		}
	}
	while (i < precision--) {
		if (buf <= end)
			*buf = '0';
		++buf;
	}
	while (i-- > 0) {
		if (buf <= end)
			*buf = tmp[i];
		++buf;
	}
	while (size-- > 0) {
		if (buf <= end)
			*buf = ' ';
		++buf;
	}
	return buf;
}
apti_module
int _kvprintf(const char *format, _kva_list args)
{
    char  buf[1024];
    size_t size; //, written = 0;
    //Error e;
    
    /* Write formatted string. */
    size = _KFIX(vsnprintf)(buf, sizeof(buf), format, args);
    if(size >=0)
      printf((char*)buf);
    /* All done. */
    return size;
}


apti_module
int _kvsprintf(char *buf, const char *fmt, _kva_list args)
{
	
	return _kvsnprintf(buf, (~0U)>>1, fmt, args);

}
apti_module
int _ksprintf(char * buf, const char *fmt, ...)
{
	_kva_list args;
	int i;

	_kva_start(args, fmt);
	i=_KFIX(vsprintf)(buf,fmt,args);
	_kva_end(args);
	return i;
}
apti_module
int _KFIX(vsnprintf)(char *buf, size_t size, const char *fmt, _kva_list args)
{
	int len;
	unsigned long long num;
	int i, base;
	char *str, *end, c;
	const char *s;

	int flags;		/* flags to number() */

	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
				   number of chars for from string */
	int qualifier;		/* 'h', 'l', or 'L' for integer fields */
				/* 'z' support added 23/7/1999 S.H.    */
				/* 'z' changed to 'Z' --davidm 1/25/99 */

	str = buf;
	end = buf + size - 1;

	if (end < buf - 1) {
		end = ((void *) -1);
		size = end - buf + 1;
	}

	for (; *fmt ; ++fmt) {
		if (*fmt != '%') {
			if (str <= end)
				*str = *fmt;
			++str;
			continue;
		}

		/* process flags */
		flags = 0;
		repeat:
			++fmt;		/* this also skips first '%' */
			switch (*fmt) {
				case '-': flags |= LEFT; goto repeat;
				case '+': flags |= PLUS; goto repeat;
				case ' ': flags |= SPACE; goto repeat;
				case '#': flags |= SPECIAL; goto repeat;
				case '0': flags |= ZEROPAD; goto repeat;
			}

		/* get field width */
		field_width = -1;
		if (isdigit(*fmt))
			field_width = _KFIX(skip_atoi)(&fmt);
		else if (*fmt == '*') {
			++fmt;
			/* it's the next argument */
			field_width = _kva_arg(args, int);
			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		/* get the precision */
		precision = -1;
		if (*fmt == '.') {
			++fmt;
			if (isdigit(*fmt))
				precision = _KFIX(skip_atoi)(&fmt);
			else if (*fmt == '*') {
				++fmt;
				/* it's the next argument */
				precision = _kva_arg(args, int);
			}
			if (precision < 0)
				precision = 0;
		}

		/* get the conversion qualifier */
		qualifier = -1;
		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L' ||
		    *fmt =='Z' || *fmt == 'z') {
			qualifier = *fmt;
			++fmt;
			if (qualifier == 'l' && *fmt == 'l') {
				qualifier = 'L';
				++fmt;
			}
		}

		/* default base */
		base = 10;

		switch (*fmt) {
			case 'c':
				if (!(flags & LEFT)) {
					while (--field_width > 0) {
						if (str <= end)
							*str = ' ';
						++str;
					}
				}
				c = (unsigned char) _kva_arg(args, int);
				if (str <= end)
					*str = c;
				++str;
				while (--field_width > 0) {
					if (str <= end)
						*str = ' ';
					++str;
				}
				continue;

			case 's':
				s = _kva_arg(args, char *);
				if ((unsigned long)s < PAGE_SIZE)
					s = "<NULL>";

#if 0
                                len = _KFIX(strnlen)(s, precision);
#else
                                len = _KFIX(mstrlen)(s);
                                if( precision > len )
                                    len = precision;
#endif
				if (!(flags & LEFT)) {
					while (len < field_width--) {
						if (str <= end)
							*str = ' ';
						++str;
					}
				}
				for (i = 0; i < len; ++i) {
					if (str <= end)
						*str = *s;
					++str; ++s;
				}
				while (len < field_width--) {
					if (str <= end)
						*str = ' ';
					++str;
				}
				continue;

			case 'p':
				if (field_width == -1) {
					field_width = 2*sizeof(void *);
					flags |= ZEROPAD;
				}
				str = _KFIX(number)(str, end,
						(unsigned long)_kva_arg(args, void *),
						16, field_width, precision, flags);
				continue;


			case 'n':
				/* FIXME:
				* What does C99 say about the overflow case here? */
				if (qualifier == 'l') {
					long * ip = _kva_arg(args, long *);
					*ip = (str - buf);
				} else if (qualifier == 'Z' || qualifier == 'z') {
					size_t * ip = _kva_arg(args, size_t *);
					*ip = (str - buf);
				} else {
					int * ip = _kva_arg(args, int *);
					*ip = (str - buf);
				}
				continue;

			case '%':
				if (str <= end)
					*str = '%';
				++str;
				continue;

				/* integer number formats - set up the flags and "break" */
			case 'o':
				base = 8;
				break;

			case 'X':
				flags |= LARGE;
			case 'x':
				base = 16;
				break;

			case 'd':
			case 'i':
				flags |= SIGN;
			case 'u':
				break;

			default:
				if (str <= end)
					*str = '%';
				++str;
				if (*fmt) {
					if (str <= end)
						*str = *fmt;
					++str;
				} else {
					--fmt;
				}
				continue;
		}
		if (qualifier == 'L')
			num = _kva_arg(args, long long);
		else if (qualifier == 'l') {
			num = _kva_arg(args, unsigned long);
			if (flags & SIGN)
				num = (signed long) num;
		} else if (qualifier == 'Z' || qualifier == 'z') {
			num = _kva_arg(args, size_t);
		} else if (qualifier == 'h') {
			num = (unsigned short) _kva_arg(args, int);
			if (flags & SIGN)
				num = (signed short) num;
		} else {
			num = _kva_arg(args, unsigned int);
			if (flags & SIGN)
				num = (signed int) num;
		}
		str = _KFIX(number)(str, end, num, base,
				field_width, precision, flags);
	}
	if (str <= end)
		*str = '\0';
	else if (size > 0)
		/* don't write out a null byte if the buf size is zero */
		*end = '\0';
	/* the trailing null byte doesn't count towards the total
	* ++str;
	*/
	return str-buf;
}
apti_module
int _KFIX(snprintf)(char * buf, size_t size, const char *fmt, ...)
{
	_kva_list args;
	int i;

	_kva_start(args, fmt);
	i=_KFIX(vsnprintf)(buf,size,fmt,args);
	_kva_end(args);
	return i;
}
apti_module
//int _vprintf(char *format, va_list args);
int _KFIX(printf)(const char *fmt, ...)
{
    _kva_list args;
    int ret = 0;
    
    _kva_start(args, fmt);
    ret = _KFIX(vprintf)(fmt, args);
    _kva_end(args);
    
    return ret;
}


apti_module
long 
_KFIX(atol)(const char *p)
{
	int digit, isneg;
	long value;

	isneg = 0;
	value = 0;
	for (; isspace (*p); p++);

	if (*p == '-') {
		isneg = 1;
		p++;
	}
	else if (*p == '+')
		p++;

	for (; *p; p++) {
		if (*p >= '0' && *p <= '9')
			digit = *p - '0';
		else
			break;
		value *= 10;
		value += digit;
	}

	if (isneg)
		value = 0 - value;
	return (value);
}

apti_module
int
_KFIX(atoi)(const char *p)
{
	int digit, isneg;
	int value;

	isneg = 0;
	value = 0;
	for (; isspace (*p); p++);	/* gobble up leading whitespace */

	/* do I have a sign? */
	if (*p == '-') {
		isneg = 1;
		p++;
	}
	else if (*p == '+')
		p++;

	for (; *p; p++) {
		if (*p >= '0' && *p <= '9')
			digit = *p - '0';
		else
			break;
		value *= 10;
		value += digit;
	}

	if (isneg)
		value = 0 - value;
	return (value);
}



apti_module
char * _KFIX(strdup)(const char * s)
{
	char *ptr=(char *) malloc( kstrlen(s)+1);
	if(ptr == NULL){
		return NULL;
	}
	kstrcpy(ptr, s);
	return ptr;
}

