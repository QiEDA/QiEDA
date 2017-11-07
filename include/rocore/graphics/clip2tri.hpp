/*
 * clip2tri.h
 *
 * Authors: kaen, raptor, sam686, watusimoto
 *
 * Originally from the bitfighter source code
 */

#ifndef CLIP2TRI_H_
#define CLIP2TRI_H_

#include <vector>
#include "rocore/graphics/Point.hpp"
#include "clipper.hpp"

namespace c2t
{

typedef signed int       S32;
typedef signed long long S64;
typedef unsigned int     U32;
typedef float            F32;
typedef double           F64;


class clip2tri
{
private:
   //
   ClipperLib::Path upscaleClipperPoints(const std::vector<rocore::graphics::Point> &inputPolygon);

   // These operate on a vector of polygons
   ClipperLib::Paths upscaleClipperPoints(const std::vector<std::vector<rocore::graphics::Point> > &inputPolygons);
    std::vector<std::vector<rocore::graphics::Point> > downscaleClipperPoints(const ClipperLib::Paths &inputPolygons);

   bool mergePolysToPolyTree(const std::vector<std::vector<rocore::graphics::Point> > &inputPolygons, ClipperLib::PolyTree &solution);

   bool triangulateComplex(std::vector<rocore::graphics::Point> &outputTriangles, const ClipperLib::Path &outline,
         const ClipperLib::PolyTree &polyTree, bool ignoreFills = true, bool ignoreHoles = false);

public:
   clip2tri();
   virtual ~clip2tri();

   void triangulate(const std::vector<std::vector<rocore::graphics::Point> > inputPolygons,
                    std::vector<rocore::graphics::Point> &outputTriangles,
                     const std::vector<rocore::graphics::Point> boundingPolygon);
};

} /* namespace c2t */

#endif /* CLIP2TRI_H_ */
