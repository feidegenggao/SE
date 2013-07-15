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
#include    "base/log.h"
using namespace base;

Page::Page(const Url &url):url_(url)
{

}

void Page::VisitUrl()
{
    LOG_DEBUG << "visit url";
}

void Page::GetUnvisitedUrl(UrlSet &unvisited_sites)
{
    LOG_DEBUG << "get unvisited url";
}
