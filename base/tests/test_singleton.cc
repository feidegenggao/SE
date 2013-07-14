/*
 * ============================================================================
 *
 *       Filename:  test_singleton.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/14/13 19:55:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/singleton.h"
#include    "base/log.h"
using namespace base;

class A : public Singleton<A>
{
    public:
        int id;
};

int main()
{
    A::getInstance()->id = 3;

    LOG_DEBUG << A::getInstance()->id;

    LOG_DEBUG << "\n";
    return 0;
}
