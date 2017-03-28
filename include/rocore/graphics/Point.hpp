//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_POINT_HPP
#define QIEDA_POINT_HPP

#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
    struct ROCORE_EXPORT Point{
        double x;
        double y;

        Point(double a, double b)
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
