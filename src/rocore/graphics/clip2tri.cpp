/*
 * clip2tri.h
 *
 * Authors: kaen, raptor, sam686, watusimoto
 *
 * Originally from the bitfighter source code
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Bitfighter developers
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "rocore/graphics/clip2tri.hpp"
#include "poly2tri/poly2tri.h"

#include <cstdio>


using namespace rocore::graphics;

namespace c2t
{


static const double CLIPPER_SCALE_FACT = 1000000.0;
static const double CLIPPER_SCALE_FACT_INVERSE = 1/CLIPPER_SCALE_FACT;


/////////////////////////////////

clip2tri::clip2tri()
{
   // Do nothing!
}

clip2tri::~clip2tri()
{
   // Do nothing!
}


void clip2tri::triangulate(const std::vector<std::vector<Point> > inputPolygons,
						   std::vector<Point> &outputTriangles,
      						const std::vector<Point> boundingPolygon) {
	// Use clipper to clean.  This upscales the floating point input
	ClipperLib::PolyTree solution;
	mergePolysToPolyTree(inputPolygons, solution);

	ClipperLib::Path bounds = upscaleClipperPoints(boundingPolygon);

	// This will downscale the Clipper output and use poly2tri to triangulate
	triangulateComplex(outputTriangles, bounds, solution);
}


ClipperLib::Path clip2tri::upscaleClipperPoints(const std::vector<Point> &inputPolygon)
{
	ClipperLib::Path outputPolygon;
   outputPolygon.resize(inputPolygon.size());

   for(size_t i = 0; i < inputPolygon.size(); i++) {
	   outputPolygon[i] = ClipperLib::IntPoint(S64(inputPolygon[i].x * CLIPPER_SCALE_FACT),
								   S64(inputPolygon[i].y * CLIPPER_SCALE_FACT));
   }

   return outputPolygon;
}


ClipperLib::Paths clip2tri::upscaleClipperPoints(const std::vector<std::vector<Point>> &inputPolygons)
{
	ClipperLib::Paths outputPolygons;

   outputPolygons.resize(inputPolygons.size());

   for(size_t i = 0; i < inputPolygons.size(); i++)
   {
      outputPolygons[i].resize(inputPolygons[i].size());

      for(size_t j = 0; j < inputPolygons[i].size(); j++) {
		  outputPolygons[i][j] = ClipperLib::IntPoint(S64(inputPolygons[i][j].x * CLIPPER_SCALE_FACT),
													  S64(inputPolygons[i][j].y * CLIPPER_SCALE_FACT));
	  }
   }

   return outputPolygons;
}


std::vector<std::vector<Point>> clip2tri::downscaleClipperPoints(const ClipperLib::Paths &inputPolygons)
{
	std::vector<std::vector<Point> > outputPolygons;

	outputPolygons.resize(inputPolygons.size());

	for(U32 i = 0; i < inputPolygons.size(); i++)
	{
		outputPolygons[i].resize(inputPolygons[i].size());

		for(U32 j = 0; j < inputPolygons[i].size(); j++) {
			outputPolygons[i][j] = Point(F32(inputPolygons[i][j].X) * CLIPPER_SCALE_FACT_INVERSE,
									   F32(inputPolygons[i][j].Y) * CLIPPER_SCALE_FACT_INVERSE);
		}
	}

   return outputPolygons;
}


// Use Clipper to merge inputPolygons, placing the result in a Polytree
// NOTE: this does NOT downscale the Clipper points.  You must do this afterwards
//
// Here you add all your non-navigatable objects (e.g. walls, barriers, etc.)
bool clip2tri::mergePolysToPolyTree(const std::vector<std::vector<Point> > &inputPolygons, ClipperLib::PolyTree &solution)
{
	ClipperLib::Paths input = upscaleClipperPoints(inputPolygons);

	// Fire up clipper and union!
	ClipperLib::Clipper clipper;
	clipper.StrictlySimple(true);

	try  // there is a "throw" in AddPolygon
	{
		clipper.AddPaths(input, ClipperLib::ptSubject, true);
	}
	catch(...)
	{
		printf("clipper.AddPaths, something went wrong\n");
	}

	return clipper.Execute(ClipperLib::ctUnion, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);
}


// Delete all poly2tri points from a vector and clear the vector
static void deleteAndClear(std::vector<p2t::Point*> &vec)
{
	for(size_t i = 0; i < vec.size(); i++) {
		delete vec[i];
	}

	vec.clear();
}


// Shrink large polygons by reducing each coordinate by 1 in the
// general direction of the last point as we wind around
//
// This normally wouldn't work in every case, but our upscaled-by-1000 polygons
// have little chance to create new duplicate points with this method.
//
// For information on why this was needed, see:
//
//    https://code.google.com/p/poly2tri/issues/detail?id=90
//
static void edgeShrink(ClipperLib::Path &path)
{
   U32 prev = path.size() - 1;
   for(size_t i = 0; i < path.size(); i++)
   {
      // Adjust coordinate by 1 depending on the direction
      path[i].X - path[prev].X > 0 ? path[i].X-- : path[i].X++;
      path[i].Y - path[prev].Y > 0 ? path[i].Y-- : path[i].Y++;

      prev = i;
   }
}


// This uses poly2tri to triangulate.  poly2tri isn't very robust so clipper needs to do
// the cleaning of points before getting here.
//
// A tree structure of polygons is required for doing complex polygons-within-polygons.
// For reference discussion on how this started to be developed, see here:
//
//    https://code.google.com/p/poly2tri/issues/detail?id=74
//
// For assistance with a special case crash, see this utility:
//    http://javascript.poly2tri.googlecode.com/hg/index.html
//
// FIXME: what is ignoreFills and ignoreHoles for?  kaen?
bool clip2tri::triangulateComplex(std::vector<Point> &outputTriangles,
      const ClipperLib::Path &outline,
      const ClipperLib::PolyTree &polyTree,
       bool ignoreFills, bool ignoreHoles)
{
   // Keep track of memory for all the poly2tri objects we create
   std::vector<p2t::CDT*> cdtRegistry;
   std::vector<std::vector<p2t::Point*> > holesRegistry;
   std::vector<std::vector<p2t::Point*> > polylinesRegistry;


   // Let's be tricky and add our outline to the root node (it should have none), it'll be
   // our first Clipper hole
	ClipperLib::PolyNode *rootNode = NULL;

	ClipperLib::PolyNode tempNode;
   if(polyTree.Total() == 0)  // Polytree is empty with no root node, e.g. on an empty level
      rootNode = &tempNode;
   else
      rootNode = polyTree.GetFirst()->Parent;

   rootNode->Contour = outline;

   // Now traverse our polyline nodes and triangulate them with only their children holes
	ClipperLib::PolyNode *currentNode = rootNode;
   while(currentNode != NULL)
   {
      // A Clipper hole is actually what we want to build zones for; they become our bounding
      // polylines.  poly2tri holes are therefore the inverse
      if((!ignoreHoles && currentNode->IsHole()) ||
         (!ignoreFills && !currentNode->IsHole()))
      {
         // Build up this polyline in poly2tri's format (downscale Clipper points)
         std::vector<p2t::Point*> polyline;
         for(U32 j = 0; j < currentNode->Contour.size(); j++)
            polyline.push_back(new p2t::Point(F64(currentNode->Contour[j].X), F64(currentNode->Contour[j].Y)));

         polylinesRegistry.push_back(polyline);  // Memory

         // Set our polyline in poly2tri
         p2t::CDT* cdt = new p2t::CDT(polyline);
         cdtRegistry.push_back(cdt);

         for(U32 j = 0; j < currentNode->Childs.size(); j++)
         {
			 ClipperLib::PolyNode *childNode = currentNode->Childs[j];

            // Slightly modify the polygon to guarantee no duplicate points
            edgeShrink(childNode->Contour);

            std::vector<p2t::Point*> hole;
            for(U32 k = 0; k < childNode->Contour.size(); k++) {
				hole.push_back(new p2t::Point(F64(childNode->Contour[k].X), F64(childNode->Contour[k].Y)));
			}

            holesRegistry.push_back(hole);  // Memory

            // Add the holes for this polyline
            cdt->AddHole(hole);
         }

         cdt->Triangulate();

         // Add current output triangles to our total
         std::vector<p2t::Triangle*> currentOutput = cdt->GetTriangles();

         // Copy our data to TNL::Point and to our output Vector
         p2t::Triangle *currentTriangle;
         for(U32 j = 0; j < currentOutput.size(); j++)
         {
            currentTriangle = currentOutput[j];
            outputTriangles.push_back(Point(currentTriangle->GetPoint(0)->x * CLIPPER_SCALE_FACT_INVERSE, currentTriangle->GetPoint(0)->y * CLIPPER_SCALE_FACT_INVERSE));
            outputTriangles.push_back(Point(currentTriangle->GetPoint(1)->x * CLIPPER_SCALE_FACT_INVERSE, currentTriangle->GetPoint(1)->y * CLIPPER_SCALE_FACT_INVERSE));
            outputTriangles.push_back(Point(currentTriangle->GetPoint(2)->x * CLIPPER_SCALE_FACT_INVERSE, currentTriangle->GetPoint(2)->y * CLIPPER_SCALE_FACT_INVERSE));
         }
      }

      currentNode = currentNode->GetNext();
   }


	// Clean up memory used with poly2tri
	//
	// Clean-up workers
	for(size_t i = 0; i < cdtRegistry.size(); i++) {
	   delete cdtRegistry[i];
	}

	// Free the polylines
	for(size_t i = 0; i < polylinesRegistry.size(); i++) {
		std::vector<p2t::Point*> polyline = polylinesRegistry[i];
		deleteAndClear(polyline);
	}

	// Free the holes
	for(size_t i = 0; i < holesRegistry.size(); i++) {
	  std::vector<p2t::Point*> hole = holesRegistry[i];
	  deleteAndClear(hole);
	}

	// Make sure we have output data
	if(outputTriangles.size() == 0) {
		return false;
	}

	return true;
}


} /* namespace c2t */
