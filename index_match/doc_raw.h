/*
 * ============================================================================
 *
 *       Filename:  doc_raw.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/30/13 09:49:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     DOC_RAW_HEADER
#define     DOC_RAW_HEADER
#include    <string>
void OpenDocRaw(std::string raw_file_name);
bool GetRawDataAndUrl(std::string &raw_data, std::string &url);
off_t GetRawFileOffset();
#endif
