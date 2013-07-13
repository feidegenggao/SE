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
#include    "types.h"
using namespace base;
#include    "log.h"
using namespace base::log;

const int g_k_n_search_deepth = 5;
const string g_k_s_sites_seeds_file_name = "./sites.seeds";

typedef set<string> UrlSet;
typedef UrlSet::iterator UrlSetIt;

void GetSiteSeed(UrlSet &sites_seeds, const string &file_name);
int visit_url(const string &url, const UrlSet &visited_sites, UrlSet &unvisited_sites);

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        LOG_ERR << "Usage:" << argv[0];
        return FAILED;
    }

    UrlSet sites_seeds;
    GetSiteSeed(sites_seeds, g_k_s_sites_seeds_file_name);

    UrlSet unvisited_sites;
    UrlSet visited_sites;

    int cur_deepth = g_k_n_search_deepth;
    while(cur_deepth > 0)
    {
        UrlSetIt seeds_start = sites_seeds.begin();
        const UrlSetIt seeds_end = sites_seeds.end();
        while (seeds_start != seeds_end)
        {
            if (SUCCESSFUL == visit_url(*seeds_start, visited_sites, unvisited_sites))
            {
                visited_sites.insert(*seeds_start);
            }
            seeds_start++;
        }

        //unvisited_sites --> sites_seeds
        sites_seeds = unvisited_sites;
        unvisited_sites.clear();

        cur_deepth--;
    }

    return SUCCESSFUL;
}
