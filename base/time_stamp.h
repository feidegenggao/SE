/*
 * ============================================================================
 *
 *       Filename:  Timestamp.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/21/2012 10:40:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     BASE_TIMESTAMP_H
#define     BASE_TIMESTAMP_H
#include    <boost/operators.hpp>
#include    <iostream>
#include    <string>
using std::string;
namespace base 
{
    //This Timestamp will output local time not UTC
    class Timestamp : public boost::less_than_comparable<Timestamp>
    {
        public:
            Timestamp()
                :microSecondsSinceEpoch_(0)
            {
            }
            void swap(Timestamp& that)
            {
                std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
            }
            explicit Timestamp(int64_t microSecondsSinceEpoch);
            string toString() const;
            string toFormattedString() const;
            int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_;}
            time_t seconedsSinceEpoch() const 
            {
                return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
            }
            static Timestamp now();
            static const int kMicroSecondsPerSecond = 1000 * 1000;
        private:
            int64_t microSecondsSinceEpoch_;
    };

    inline int64_t timeDifference(Timestamp high, Timestamp low)
    {
        return high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    }

    inline bool operator < (Timestamp lhs, Timestamp rhs)
    {
        return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
    }

    inline bool operator == (Timestamp lhs, Timestamp rhs)
    {
        return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
    }

    inline Timestamp addTime(Timestamp timestamp, double seconds)
    {
        int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
        return Timestamp(delta + timestamp.microSecondsSinceEpoch());
    }
}
#endif
