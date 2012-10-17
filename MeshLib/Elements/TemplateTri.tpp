/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.net)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/LICENSE.txt
 *
 * \file TemplateTri.tpp
 *
 *  Created on  Sep 27, 2012 by Thomas Fischer
 */

// MathLib
#include "AnalyticalGeometry.h"

namespace MeshLib {

template <unsigned NNODES, FEMElemType::type FEMTRITYPE>
TemplateTri<NNODES,FEMTRITYPE>::TemplateTri(Node* nodes[NNODES], unsigned value) :
	Face(value)
{
	_nodes = nodes;
	_neighbors = new Element*[3];
	for (unsigned i=0; i<3; i++)
		_neighbors[i] = NULL;
	this->_area = this->computeVolume();
}

template <unsigned NNODES, FEMElemType::type FEMTRITYPE>
TemplateTri<NNODES,FEMTRITYPE>::TemplateTri(const TemplateTri<NNODES,FEMTRITYPE> &tri) :
	Face(tri.getValue())
{
	_nodes = new Node*[NNODES];
	for (unsigned i=0; i<NNODES; i++)
	{
		_nodes[i] = tri._nodes[i];
	}

	_neighbors = new Element*[3];
	for (unsigned i=0; i<3; i++) {
		_neighbors[i] = tri._neighbors[i];
	}

	_area = tri.getArea();
}

template <unsigned NNODES, FEMElemType::type FEMTRITYPE>
TemplateTri<NNODES,FEMTRITYPE>::~TemplateTri()
{}

template <unsigned NNODES, FEMElemType::type FEMTRITYPE>
bool TemplateTri<NNODES,FEMTRITYPE>::isEdge(unsigned idx1, unsigned idx2) const
{
	for (unsigned i(0); i<3; i++)
	{
		if (_edge_nodes[i][0]==idx1 && _edge_nodes[i][1]==idx2) return true;
		if (_edge_nodes[i][1]==idx1 && _edge_nodes[i][0]==idx2) return true;
	}
	return false;
}

template <unsigned NNODES, FEMElemType::type FEMTRITYPE>
bool TemplateTri<NNODES,FEMTRITYPE>::isPntInside(GeoLib::Point const& pnt, double eps) const
{
	return MathLib::isPointInTriangle(pnt, *_nodes[0], *_nodes[1], *_nodes[2], eps);
}

template <unsigned NNODES, FEMElemType::type FEMTRITYPE>
Element* TemplateTri<NNODES,FEMTRITYPE>::reviseElement() const
{
	// try to create an edge
	if (_nodes[0] == _nodes[1] || _nodes[1] == _nodes[2]) {
		Node** nodes = new Node*[2];
		nodes[0] = _nodes[0];
		nodes[1] = _nodes[2];
		return new Edge(nodes, _value);
	}

	if (_nodes[0] == _nodes[2]) {
		Node** nodes = new Node*[2];
		nodes[0] = _nodes[0];
		nodes[1] = _nodes[1];
		return new Edge(nodes, _value);
	}

	return NULL;
}

template <unsigned NNODES, FEMElemType::type FEMTRITYPE>
unsigned TemplateTri<NNODES,FEMTRITYPE>::identifyFace(Node* nodes[3]) const
{
	for (unsigned i=0; i<3; i++)
	{
		unsigned flag(0);
		for (unsigned j=0; j<2; j++)
			for (unsigned k=0; k<2; k++)
				if (_nodes[_edge_nodes[i][j]] == nodes[k])
					flag++;
		if (flag==2)
			return i;
	}
	return std::numeric_limits<unsigned>::max();
}

} // namespace MeshLib
