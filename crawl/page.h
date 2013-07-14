/*
 * ============================================================================
 *
 *       Filename:  page.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 18:26:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     PAGE_HEADER
#define     PAGE_HEADER
#include    "types.h"
class Url;
class Page
{
    public:
        explicit Page(const Url &url);
        void VisitUrl();
        void GetUnvisitedUrl(UrlSet &unvisited_sites);

    private:
            Url url_;
};
#endif
