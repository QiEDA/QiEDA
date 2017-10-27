//
// Created by mroszko on 10/23/2017.
//

#ifndef ROEDA_GRAPHICDOCUMENT_HPP
#define ROEDA_GRAPHICDOCUMENT_HPP

#include <list>
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	class GraphicLayer;
	class GridLayer;

	/**
	 * @brief Container for a set of layers compromising what essentially is one document
	 */
	class ROCORE_EXPORT GraphicDocument {
	public:
		GraphicDocument();
		~GraphicDocument();

		void AddLayer(GraphicLayer* layer);
		void RemoveLayer(GraphicLayer* layer);

		std::list<GraphicLayer*>& GetLayers() {
			return layers_;
		}

		bool GetMirror() {
			return mirror_;
		}

		void SetMirror(bool mirror) {
			mirror_ = mirror;
		}
	protected:
		std::list<GraphicLayer*> layers_;
		GridLayer* gridLayer_;
		bool mirror_;
	};
}
}

#endif //ROEDA_GRAPHICDOCUMENT_HPP
