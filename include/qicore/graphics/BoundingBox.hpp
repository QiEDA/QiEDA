//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_BOUNDINGBOX_HPP
#define QIEDA_BOUNDINGBOX_HPP

#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
class QICORE_EXPORT BoundingBox{
        private:
        Point origin;
        float width;
        float height;
        public:
        BoundingBox(const Point& o, float w, float h)
        {
            origin = o;
            width = w;
            height = h;
        }

        Point Center() const
        {
            return Point(origin.x + width / 2, origin.y + height / 2);
        }

        float Left() const
        {
            return origin.x;
        }

        float Right() const
        {
            return origin.x + width;
        }

        float Top() const
        {
            return origin.y;
        }

        float Bottom() const
        {
            return origin.y + height;
        }

        bool Contains(const Point& p)
        {
            if (Left() <= p.x &&
                p.x <= Right() &&
                Top() <= p.y &&
                p.y <= Bottom()) {
                return true;
            }
            return false;
        }
};
}
}
#endif //QIEDA_BOUNDINGBOX_HPP
