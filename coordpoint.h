#ifndef COORDPOINT_H
#define COORDPOINT_H

/**
* @author Hirokazu Yokoyama
*/

#include <OpenNI.h>
#include "imageconverter.h"
#ifndef Q_MOC_RUN
#include <boost/date_time/posix_time/posix_time.hpp>
#endif

/**
* 点の座標を保持するための構造体です．
*/
struct CoordPoint {
    /** 深度画像上でのX座標を示します． */
    int depthX;

    /** 深度画像上でのY座標を示します． */
    int depthY;

    /** ワールド座標系でのX座標を示します */
    float worldX;

    /** ワールド座標系でのY座標を示します */
    float worldY;

    /** 深度値を示します．この値は画像上及びワールド座標で共通です． */
    float depthZ;
    
    template <typename T_num>
    void setDepthZFrom8bit(T_num val) {
        depthZ = (float)((double)val / ImageConverter::MaxDistance * 255.0);
    }

    bool operator == (CoordPoint& a) {
        bool retval = true;
        retval &= (depthX == a.depthX);
        retval &= (depthY == a.depthY);
        retval &= (depthZ == a.depthZ);
        retval &= (worldX == a.worldX);
        retval &= (worldY == a.worldY);
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
    }
};

/**
* 点の座標とフレームを保持するための構造体です．
*/
struct CoordPointFrame: public CoordPoint {
    int frameIndex;
};


#endif // COORDPOINT_H
