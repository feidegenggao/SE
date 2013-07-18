/*
 * ============================================================================
 *
 *       Filename:  tool.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/18/13 14:42:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     BASE_TOOL_HEADER
#define     BASE_TOOL_HEADER
#include    <sstream>
namespace base
{
    template<typename DstT, typename SrcT>
        DstT Convert(const SrcT &a)
        {
            std::stringstream temp_stream;
            temp_stream << a;
            DstT result;
            temp_stream >> result;

            return result;
        }
}
#endif
