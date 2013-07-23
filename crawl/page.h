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
extern const int g_k_n_search_deepth;
class Url;
class Page
{
    public:
        explicit Page(const Url &url);
        void VisitUrl();
        void GetUnvisitedUrl(UrlSet &unvisited_sites);

    private:
            Url url_;
            string http_header_;
            string html_data_;
            static int OpenRawFile();
            static int raw_file_fd_;
            static void WriteToRawFile(const void *buf, size_t count);
            bool IfIncludeUTF8(const string &src_str);
};
#endif
