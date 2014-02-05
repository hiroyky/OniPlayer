//
//  oniprofile.h
//  Medusa
//
//  Created by Hirokazu Yokoyama on 2014/02/02.
//
//

#ifndef Medusa_oniprofile_h
#define Medusa_oniprofile_h

#ifndef Q_MOC_RUN
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif
#include <string>

/**
 * ONIファイルのプロファイル
 */
struct OniProfile {
    
    OniProfile(): place(""), description(""), frameNum(-1) {}
    
    /**
     * 撮影開始時間
     */
    boost::posix_time::ptime startTime;
    
    /**
     * 撮影終了時刻
     */
    boost::posix_time::ptime endTime;
    
    /**
     * 場所
     */
    std::string place;
    
    /**
     * 概要
     */
    std::string description;
    
    /**
     * フレーム数
     */
    int frameNum;
    
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, unsigned int version) {
        static_cast<void>(version);
        ar & boost::serialization::make_nvp("startTime", startTime);
        ar & boost::serialization::make_nvp("endTime", endTime);
        ar & boost::serialization::make_nvp("place", place);
        ar & boost::serialization::make_nvp("description", description);
    }
};

#endif
