/*
 * ============================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/13/13 09:34:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "page.h"
#include    "types.h"

#include    "base/types.h"
#include    "base/log.h"
#include    <assert.h>
#include    <fstream>
#include    <iostream>
#include    <string>
using namespace std;
using namespace base;

const int g_k_n_search_deepth = 2;

void GetSiteSeed(UrlSet &sites_seeds, const string &file_name);
int visit_url(const Url &url, const UrlSet &visited_sites, UrlSet &unvisited_sites);

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        LOG_ERROR << "Usage:" << argv[0];
        return FAILED;
    }

    UrlSet sites_seeds;
    GetSiteSeed(sites_seeds, string("sites.seeds"));

    UrlSet unvisited_sites;
    UrlSet visited_sites;

    int cur_deepth = g_k_n_search_deepth;
    while(cur_deepth > 0)
    {
        UrlSetIt seeds_start = sites_seeds.begin();
        while (seeds_start != sites_seeds.end())
        {
            if (SUCCESSFUL == visit_url(*seeds_start, visited_sites, unvisited_sites))
            {
                visited_sites.insert(*seeds_start);
            }
            seeds_start++;
        }

        //unvisited_sites -->> sites_seeds
        sites_seeds = unvisited_sites;
        unvisited_sites.clear();

        cur_deepth--;
    }

    LOG_END;
    return SUCCESSFUL;
}

void GetSiteSeed(UrlSet &sites_seeds, const string &file_name)
{
    ifstream seeds_stream;
    seeds_stream.open(file_name.c_str());
    
    assert(seeds_stream);

    string url_temp;
    while (seeds_stream >> url_temp)
    {
        Url url(url_temp);
        sites_seeds.insert(url);
    }
}

//return:
//FAILED: we visited the url and so return FAILED;
//SUCCESSFUL: we not visited the url ever , and we try to visit the url
//but not guarantee get data from the url
int visit_url(const Url &url, const UrlSet &visited_sites, UrlSet &unvisited_sites)
{
    if (visited_sites.find(url) != visited_sites.end())
    {
        return FAILED;
    }

    Page cur_page(url);
    //get data from the url
    LOG_DEBUG << "Start visit :" << url.Str();
    cur_page.VisitUrl();
    LOG_DEBUG << "Finish visit " << url.Str();
    //analysis the hyperlink from the data that get from the url
    //and then insert into unvisited_sites
    //if no data ( we can't connect to the url) we will insert nothing into
    //unvisited_sites
    LOG_DEBUG << "Start get unvisit url from html of " << url.Str();
    cur_page.GetUnvisitedUrl(unvisited_sites);
    LOG_DEBUG << "Finish get unvisit url from html of " << url.Str();
    return SUCCESSFUL;
}
