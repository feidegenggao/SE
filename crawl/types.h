/*
 * ============================================================================
 *
 *       Filename:  types.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 20:16:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     TYPES_HEADER
#define     TYPES_HEADER
#include    <set>
using std::set;
#include    "url.h"
typedef set<Url> UrlSet;
typedef UrlSet::iterator UrlSetIt;
#endif
