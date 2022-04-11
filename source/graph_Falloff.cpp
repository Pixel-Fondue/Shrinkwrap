#include "graph_Falloff.h"
#include "defines.h"

void FalloffGraph::initialize()
{
	CLxGenericPolymorph                *srv;

	srv = new CLxPolymorph                              <FalloffGraph>;
	srv->AddInterface(new CLxIfc_SchematicConnection    <FalloffGraph>);
	srv->AddInterface(new CLxIfc_StaticDesc             <FalloffGraph>);
	lx::AddServer(SWRAP_FALLOFF_SCHM, srv);
}



LxResult FalloffGraph::schm_AllowConnect(ILxUnknownID itemFrom_obj, ILxUnknownID itemTo_obj)
{

	CLxUser_Item itemFrom(itemFrom_obj);
	if (itemFrom.test()){
		// Find item SuperType
		CLxItemType falloff_type(LXsITYPE_FALLOFF);
		CLxUser_SceneService scene_svc;
		LXtItemType item_type = itemFrom.Type();
		LXtItemType item_super;
		scene_svc.ItemTypeSuper(item_type, &item_super);
		if (item_super == falloff_type)
			return LXe_TRUE;
	}

	return LXe_FALSE;
}

int FalloffGraph::schm_BaseFlags()
{
	return LXfSCON_ORDERED | LXfSCON_MULTIPLE;
}

LxResult FalloffGraph::schm_Count(ILxUnknownID item, unsigned *count)
{
	count[0] = 0; //For debugging
	return LXe_OK;
}


LxResult FalloffGraph::schm_ItemFlags(ILxUnknownID item_obj, unsigned *flags)
{

	CLxUser_Item        item(item_obj);
	
	// If I don't specify the item here, every item will have a "Falloffs" field.
	if (item.TestType(CLxItemType(SWRAP_SERVER_NAME)) == LXe_OK)
		flags[0] = LXfSCON_MULTIPLE;
	else
		flags[0] = 0;

	return LXe_OK;
}

LxResult FalloffGraph::schm_GraphName(const char **name)
{
	name[0] = SWRAP_FALLOFF_GRAPH;
	return LXe_OK;
}


LXtTagInfoDesc FalloffGraph::descInfo[] =
{
	{ LXsSRV_USERNAME, "Falloffs" },
	{ 0 }
};
