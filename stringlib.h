/*
 * stringlib.h, part of "stringlib" project.
 *
 *  Created on: 19 мая 2015 г.
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#ifndef STRINGLIB_H_
#define STRINGLIB_H_

/*
 * OS and compiler dependent stuff here. Make own if needed.
 */
#include "../klib/config.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

size_t chomp( char * s );
char * rnd_string( char * string, size_t size );

#define STR_DEFAULT_LEN 128

typedef struct _string
{
    size_t bsz;
    size_t len;
    char * str;
}*string;

/*
 * snewn() create string with initial buffer size
 */
string snewn( size_t sz );
/*
 * sfromstr(), sfromchar() create string and copy content from 'src'
 */
string sfromchar( const char * src );
string sfromstr( const string src );
/*
 * sfromnstr(), sfromchar() create string and copy N bytes of 'src'
 */
string sfromnstr( const string src, size_t N );
string sfromnchar( const char * src, size_t sz );
/*
 * sclr() clear string
 */
string sclr( string s );
/*
 * sdel() delete string
 */
void sdel( string src );

/*
 * snew()       create new string with default buffer size
 * slen()       return string length
 * sstr()       return char data of string
 * sat()        return char at zero-based position 'at' or \0
 * sset()       set char at zero-based position 'at' to 'c'
 * scmp() etc   see below
 *
 * Warning! No NULL pointer checking for non-DEBUG macro!
 *
 */
#if defined(DEBUG)
string snew( void );
size_t slen( const string s );
const char * sstr( const string s );
char sat( const string src, size_t at );
string sset( string src, size_t at, char c );
int scmp( const string a, const string b );
int scasemp( const string a, const string b );
#else
# define snew() snewn((STR_DEFAULT_LEN))
# define slen( s ) (s)->len
# define sstr( s ) (s)->str
# define sat( s, at ) ((at) > (s)->len ? 0 : (s)->str[(at)])
# define sset( s, at, c ) ( (at) > (s)->len ? (void)0 : (s)->str[(at)] = c )
# define scmp( a, b ) scmpc( (a), (b)->str )
# define scasemp( a, b ) scasempc( (a), (b)->str )
#endif

size_t schomp( string s );
/*
 * scmp(), scmpc(), scasecmp(), scasecmpc() compare strings
 */
int scmpc( string a, const char * b );
int scasempc( string a, const char * b );
/*
 * scpy(), scpyc(), sncpy(), sncpyc() copy string or 'n' bytes of string
 */
string scpy( string dest, const string src );
string sncpy( string dest, const string src, size_t n );
string scpyc( string dest, const char * src );
/*
 * scat(), scatc() sppend string 'src'
 */
string scat( string dest, const string src );
string scatc( string dest, const char * src );
/*
 * scatch() add char 'c' to string
 */
string scatch( string dest, char c );
/*
 * scrop() reduce string length to 'n' bytes
 */
string scrop(string s, size_t n);
/*
 * strim() remove 'n' bytes from string TAIL
 */
string strim(string s, size_t n);
/*
 * strim() remove 'n' bytes from string HEAD
 */
string sltrim(string s, size_t n);
/*
 * sprint() make format string
 */
string sprint( string src, const char * fmt, ... );
/*
 * sfgets() read string from FILE
 */
size_t sfgets( string src, FILE * fin );

/*
 * sexpand() expand internal string buffer to new size
 */
string sexpand( string s, size_t sz );

#ifdef __cplusplus
}
#endif

#endif /* STRINGLIB_H_ */