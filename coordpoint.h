#ifndef COORDPOINT_H
#define COORDPOINT_H

/**
* @author Hirokazu Yokoyama
*/
#include <iostream>
#include <stdexcept>
#ifndef Q_MOC_RUN
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/deque.hpp>
#endif

struct ColorPoint {
    int x;
    int y;
    ColorPoint(): x(0), y(0) {}
    ColorPoint(int _x, int _y): x(_x), y(_y) {}    
};

struct DepthPoint {
    int x;
    int y;
    unsigned char depth;
    DepthPoint(): x(0), y(0), depth(0) {}
    DepthPoint(int _x, int _y, unsigned char _depth): x(_x), y(_y), depth(_depth) {}
};

/**
* 点の座標を保持するための構造体です．
*/
struct CoordPoint {
    /** 深度画像上でのX座標を示します． */
    int depthX;

    /** 深度画像上でのY座標を示します． */
    int depthY;

    /** 深度値を示します．この値は画像上及びワールド座標で共通です． */
    int depthZ;
    
    /** ワールド座標系でのX座標を示します */
    float worldX;

    /** ワールド座標系でのY座標を示します */
    float worldY;

    float worldZ;

    CoordPoint() : depthX(0), depthY(0), depthZ(0), worldX(0), worldY(0), worldZ(0) {}
    
    CoordPoint(int _depthX, int _depthY, float _depthZ, float _worldX, float _worldY, float _worldZ)
    : depthX(_depthX), depthY(_depthY), depthZ(_depthZ), worldX(_worldX), worldY(_worldY), worldZ(_worldZ) {}
    
    CoordPoint(const CoordPoint& cp): depthX(cp.depthX), depthY(cp.depthY), depthZ(cp.depthZ), worldX(cp.worldX), worldY(cp.worldY), worldZ(cp.worldZ) {}

    bool operator == (CoordPoint& a) {
        bool retval = true;
        retval &= (depthX == a.depthX);
        retval &= (depthY == a.depthY);
        retval &= (depthZ == a.depthZ);
        retval &= (worldX == a.worldX);
        retval &= (worldY == a.worldY);
        retval &= (worldZ == a.worldZ);
        return retval;
    }
};

/**
* 点の座標とその色情報を保持するための構造体です．
*/
struct CoordPointWithColor: public CoordPoint {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct CoordPointTimeSec: public CoordPoint {
    /** 秒　*/
    int timeSec;
    
    CoordPointTimeSec(): CoordPoint(), timeSec(0) {}
    CoordPointTimeSec(int _depthX, int _depthY, float _depthZ, float _worldX, float _worldY, float _worldZ, int _timeSec)
    : CoordPoint(_depthX, _depthY, _depthZ, _worldX, _worldY, _worldZ), timeSec(_timeSec) {}
    CoordPointTimeSec(const CoordPoint& cp): CoordPoint(cp), timeSec(0) {}
    CoordPointTimeSec(const CoordPoint& cp, int _timeSec): CoordPoint(cp), timeSec(_timeSec) {}
    CoordPointTimeSec(const CoordPointTimeSec& cpts): CoordPoint(cpts), timeSec(cpts.timeSec) {}
    
    bool operator == (CoordPointTimeSec& a) {
        return (CoordPoint::operator==(a) && timeSec == a.timeSec);
    }
    
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & boost::serialization::make_nvp("depthX", depthX);
        ar & boost::serialization::make_nvp("depthY", depthY);
        ar & boost::serialization::make_nvp("depthZ", depthZ);
        ar & boost::serialization::make_nvp("worldX", worldX);
        ar & boost::serialization::make_nvp("worldY", worldY);
        ar & boost::serialization::make_nvp("worldZ", worldZ);
        ar & boost::serialization::make_nvp("timesec", timeSec);
    }
};

/**
 * 点の座標と時間を保持するための構造体です．
 */
struct CoordPointTime: public CoordPoint {
    boost::posix_time::ptime time;
    void copyFrom(const CoordPoint& src) {
        depthX = src.depthX;
        depthY= src.depthY;
        depthZ = src.depthZ;
        worldX = src.worldX;
        worldY = src.worldY;
        worldZ = src.worldZ;
    }
};

/**
* 点の座標とフレームを保持するための構造体です．
*/
struct CoordPointFrame: public CoordPoint {
    int frameIndex;
};


#endif // COORDPOINT_H
