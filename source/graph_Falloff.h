#ifndef FALLOFF_GRAPH_H
#define FALLOFF_GRAPH_H


#include <lx_deform.hpp> // Needed to read falloff items
#include <lx_schematic.hpp>   // To Use CLxImpl_SchematicConnection

#include "defines.h"



class FalloffGraph : public CLxImpl_SchematicConnection
{
public:
	CLxUser_SceneService    scn_svc;

	static void initialize();

	LxResult schm_AllowConnect(ILxUnknownID itemFrom_obj, ILxUnknownID itemTo_obj) LXx_OVERRIDE;

	int schm_BaseFlags() LXx_OVERRIDE;

	LxResult schm_Count(ILxUnknownID item, unsigned *count) LXx_OVERRIDE;


	LxResult schm_ItemFlags(ILxUnknownID item_obj, unsigned *flags) LXx_OVERRIDE;

	LxResult schm_GraphName(const char **name) LXx_OVERRIDE;

	static LXtTagInfoDesc  descInfo[];
};

#endif 