/*
 * ============================================================================
 *
 *       Filename:  page.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 20:02:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "page.h"
Page::Page(const Url &url):url_(url)
{

}

void Page::VisitUrl()
{
    url_.Resolution();
}

void Page::GetUnvisitedUrl(UrlSet &unvisited_sites)
{

}
