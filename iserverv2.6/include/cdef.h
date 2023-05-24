
#ifndef _CDEF_H_
#define _CDEF_H_

#define AR_EXTERN_C extern 
#define AR_API 
#define AR_FUNCDECL(func,rettype,parameters_and_attributes)\
AR_EXTERN_C	rettype AR_API func parameters_and_attributes

#if CBUILDING_DLL
#define DLLRUN 
#else
#define DLLRUN 
#endif

#if BUILDING_DLL
# define DLLIMPORT 
#else /* Not BUILDING_DLL */
# define DLLIMPORT
#endif /* Not BUILDING_DLL */

#endif
