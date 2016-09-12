//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_POINT_HPP
#define QIEDA_POINT_HPP

#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
struct QICORE_EXPORT Point{
        float x;
        float y;

        Point(float a, float b)
        {
            x = a;
            y = b;
        }

        Point()
        {

        }

        Point operator-( const Point& p ) const
        {
            return Point(x - p.x, y - p.y);
        }

        Point operator-( const float& s ) const
        {
            return Point(x - s, y - s);
        }

        Point operator*( const float& s ) const
        {
            return Point(x * s, y * s);
        }
};

}
}

#endif //QIEDA_POINT_HPP
