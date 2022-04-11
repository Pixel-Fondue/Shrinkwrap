#include "shrinkwrap_MOP.h"
#include "modo_simplelog.h"
#include "modo_matrix.h"

//#include "lx_log.hpp"
#include <string>
#include <utility>

#include <iostream>
using namespace std;









/*
*	The Package and PackageInstance define the item that is added to the
*	procedural mesh operation stack.
*/

void SWrap_Instance::initialize()
{
	CLxGenericPolymorph	*srv = NULL;

	srv = new CLxPolymorph						<SWrap_Instance>;
	srv->AddInterface(new CLxIfc_PackageInstance	<SWrap_Instance>);

	lx::AddSpawner(SWRAP_SERVER_NAME_INST, srv);
}


void SWrap_Package::initialize()
{
	CLxGenericPolymorph	*srv = NULL;

	srv = new CLxPolymorph						<SWrap_Package>;
	srv->AddInterface(new CLxIfc_Package		<SWrap_Package>);
	srv->AddInterface(new CLxIfc_SceneItemListener		<SWrap_Package>);
	srv->AddInterface(new CLxIfc_ChannelUI		<SWrap_Package>);
	srv->AddInterface(new CLxIfc_StaticDesc		<SWrap_Package>);

	lx::AddServer(SWRAP_SERVER_NAME, srv);
}


	
LxResult
	SWrap_Package::pkg_TestInterface(
	const LXtGUID		 *guid)			
{
	return _inst_spawn.TestInterfaceRC(guid);
}

	LxResult
	SWrap_Package::pkg_Attach(
	void			**ppvObj)		
{
	_inst_spawn.Alloc(ppvObj);

	return ppvObj[0] ? LXe_OK : LXe_FAILED;
}


	LxResult 
	SWrap_Package::pkg_SetupChannels(
	ILxUnknownID		 addChan)
{

	CLxUser_AddChannel	 ac(addChan);

	ac.NewChannel("wrap", LXsTYPE_PERCENT);
	ac.SetDefault(1.0, 0);
	static LXtTextValueHint  factorMinMaxHint[] = {
		0, "%min", //  0%
		10000, "%max", //100%
		-1, NULL
	};
	ac.SetHint(factorMinMaxHint);

	ac.NewChannel("offset", LXsTYPE_DISTANCE);
	ac.SetDefault(0.0, 0);

	ac.NewChannel("wrapType", LXsTYPE_INTEGER);
	ac.SetDefault(0.0, 1);
	static LXtTextValueHint  wrapTypeHint[] = {
		0, "Vector", 
		1, "Point", 
		-1, NULL
	};
	ac.SetHint(wrapTypeHint);

	ac.NewChannel("projectionAxis", LXsTYPE_AXIS);
	ac.SetDefault(0.0, 1);
	ac.NewChannel("invertAxis", LXsTYPE_BOOLEAN);
	ac.SetDefault(0.0, 0);
	ac.NewChannel("doubleSided", LXsTYPE_BOOLEAN);
	ac.SetDefault(0.0, 1);

	ac.NewChannel("maxDistance", LXsTYPE_DISTANCE);
	ac.SetDefault(0.0, 0);
	static LXtTextValueHint  maxDistanceHint[] = {
		0, "%min", //  0%
		-1, NULL
	};
	ac.SetHint(maxDistanceHint);

	return LXe_OK;
}


	/* Enabled method will be called to query whether a channel of given name
	* (first argument) should be enabled or disabled.
	* Returning LXe_OK means enabled, LXe_CMD_DISABLED otherwise.
	*/
	LxResult
		SWrap_Package::cui_Enabled(
		const char 		*channelName,
		ILxUnknownID 		 msg,
		ILxUnknownID		 item,
		ILxUnknownID		 read)
	{
		LxResult		 result = LXe_OK;

		if (0 == strcmp(channelName, "projectionAxis") || 0 == strcmp(channelName, "invertAxis") || 0 == strcmp(channelName, "doubleSided") ) {
			CLxUser_Item		 chanItem(item);
			CLxUser_ChannelRead	 chanRead(read);

			int wrapType = chanRead.IValue(chanItem, "wrapType");
			if (wrapType == 1) {
				result = LXe_CMD_DISABLED;
			}
		}

		return result;
	}

	/*
	* We need to set up dependencies between channels which will take care of notifications
	* and Enabled() method will be called correctly, whenever our channel needs to update
	* its enabled/disabled state.
	* Note that notifications work for setting up dependencies between channels on the same item.
	* If you need to make one of custom item's channels dependent on a channel from a different item
	* you will have to handle notifications yourself.
	*/

	/*
	* DependencyCount() needs to return a number of channels given channel
	* (which name is passed as first argument) will depend on.
	* In our case we make the channel dependent on one other channel.
	*/
	LxResult
		SWrap_Package::cui_DependencyCount(const char* channelName, unsigned* count)
	{
		if (0 == strcmp(channelName, "projectionAxis")) {
			count[0] = 1;
		}
		else if (0 == strcmp(channelName, "invertAxis")) {
			count[0] = 1;
		}
		else if (0 == strcmp(channelName, "doubleSided")) {
			count[0] = 1;
		}
		else {
			count[0] = 0;
		}
		return LXe_OK;
	}

	/*
	* This method will be called for every channel that has dependency count of at least 1
	* and it will be called for every dependency index. So if a channel depends on 2 other channels
	* this method will be called twice for a given channel, once with index 0 and once with index 1.
	* You need to return name of a channel queried channel depends on for every index.
	* You also have to set the item type properly (to your custom item type).
	*/
	LxResult
		SWrap_Package::cui_DependencyByIndex(
		const char		*channelName,
		unsigned		 index,
		LXtItemType		*depItemType,
		const char	       **depChannelName)
	{
		LxResult	result = LXe_OUTOFBOUNDS;

		if (0 == strcmp(channelName, "projectionAxis") || 0 == strcmp(channelName, "invertAxis") || 0 == strcmp(channelName, "doubleSided"))
		{
			depItemType[0] = cit_swrap_self;
			depChannelName[0] = "wrapType";
			result = LXe_OK;
		}


		return result;
	}


		LXtTagInfoDesc SWrap_Package::descInfo[] =
{
	{ LXsPKG_SUPERTYPE, LXsITYPE_MESHOP },
	{ LXsPKG_GRAPHS, SWRAP_GRAPH_BG_MESH ";" SWRAP_FALLOFF_GRAPH },
	{ 0 }
};



// How to add plugs to your node
// https://community.foundry.com/discuss/topic/82826
// https://community.foundry.com/discuss/topic/128781/c-sdk-schematic-link-inter-item-relations-how-to
// Code From
// https://pastebin.com/RHUXDaCr
//
	void SWrap_BgGraph::initialize()
{
	CLxGenericPolymorph                *srv;

	srv = new CLxPolymorph                              <SWrap_BgGraph>;
	srv->AddInterface(new CLxIfc_SchematicConnection    <SWrap_BgGraph>);
	srv->AddInterface(new CLxIfc_StaticDesc             <SWrap_BgGraph>);
	lx::AddServer(SWRAP_SCHM_BG_MESH, srv);
}

LxResult SWrap_BgGraph::schm_AllowConnect(ILxUnknownID itemFrom_obj, ILxUnknownID itemTo_obj) 
{
	/*
	*    The AllowConnect method specifies if a connection
	*    is allowed or not. This is completely arbitrary.
	*    You could for example only allow connections on
	*    Tuesdays.
	*
	*    In this code, if the item has a mesh channel, then we
	*    allow the connection, otherwise we don't. If the
	*    connection is allowed, the link turn green and the
	*    connection is made, otherwise the link turns red and
	*    is denied.
	*/
	CLxUser_Item itemFrom(itemFrom_obj);

	if (itemFrom.test())
		if (itemFrom.ChannelIndex(LXsICHAN_MESH_MESH) > 0)
			return LXe_TRUE;

	return LXe_FALSE;
}

	int SWrap_BgGraph::schm_BaseFlags() 
{
	//return LXfSCON_USESERVER | LXfSCON_REVERSE;
	return LXfSCON_ORDERED | LXfSCON_MULTIPLE;
}

	LxResult SWrap_BgGraph::schm_Count(ILxUnknownID item, unsigned *count) 
{
	count[0] = 0; //For debugging
	return LXe_OK;
}


	LxResult SWrap_BgGraph::schm_ItemFlags(ILxUnknownID item_obj, unsigned *flags) 
{
	/*
	*    This ItemFlags method dictates if the connection is added
	*    to particular item type. The returned value specifies if
	*    a single connection is added, a multiple connection...etc.
	*    Again, the connection type can vary item to item and can
	*    be a completely arbitrary decision.
	*
	*    In this code, we check the item type. If it's a light, then
	*    we allow a single connection, if it's a camera, we allow
	*    multiple connections, otherwise we don't add the
	*    connection to the item.
	*/

	CLxUser_Item        item(item_obj);

	//if (item.TestType(CLxItemType(LXsICHAN_MESH_MESH)) == LXe_OK)
	if (item.TestType(CLxItemType(SWRAP_SERVER_NAME)) == LXe_OK)
		flags[0] = LXfSCON_MULTIPLE;
	else
		flags[0] = 0;

	return LXe_OK;
}

	LxResult SWrap_BgGraph::schm_GraphName(const char **name) 
{
	/*
	*    This specifies the name of the graph that this server
	*    will manipulate. This is the graph that was added as a
	*    tag to a package/item.
	*/
	name[0] = SWRAP_GRAPH_BG_MESH;
	return LXe_OK;
}


LXtTagInfoDesc SWrap_BgGraph::descInfo[] =
{
	{ LXsSRV_USERNAME, "Bg Mesh" },
	{ 0 }
};








class SWRAP_VertexVisitor : public CLxVisitor
{
public:

	SWRAP_VertexVisitor();

	void			 evaluate()	LXx_OVERRIDE;

	//void			 getPositions();

	LxResult				rc;
	CLxUser_Mesh			mesh;
	CLxUser_Mesh			bg_mesh;
	CLxUser_Polygon			polygon, bg_polygon;
	CLxUser_Point			point;
	CLxArray<CLxUser_Falloff> falloffs;

	double			 _wrap;
	int				 _wrapType;
	double			 _offset;
	double			 _maxDistance;
	LXtVector		 _dir;
	bool			 _invert;
	bool			 _doubleSided;
	unsigned int	 nverts;
	LXtMatrix4		 item_matrix;
	LXtMatrix4		 pre_matrix;
	LXtMatrix4		 post_matrix;
	bool		     is_identity_matrix = true;
	bool			 edit_any;

};


// Visitor Constructor
SWRAP_VertexVisitor::SWRAP_VertexVisitor(){
	edit_any = false;
	_offset = 0.0;
	_wrapType = 1;
	_maxDistance = 0.0;
	_dir[0] = 0.0; _dir[1] = -1.0; _dir[2] = 0.0; // Y dir
	_invert = false;
	_doubleSided = false;
	makeIdentity4(item_matrix);
	makeIdentity4(pre_matrix);
	makeIdentity4(post_matrix);
}




void double3_to_LXtVector(double a[3], LXtVector  &b){
	b[0] = a[0];
	b[1] = a[1];
	b[2] = a[2];
}

double _linear_blend(double a, double b, double blend) {
	double delta = b - a;
	return delta*blend + a;
}


void
SWRAP_VertexVisitor::evaluate(){

	if (_wrap == 0){
		edit_any = false;
		return;
	}

	LXtFVector fpos;
	point.Pos(fpos);

	LXtVector pos = { fpos[0], fpos[1], fpos[2] };
	LXtVector hitPos;
	LXtVector hitNorm;
	double hitDist;

	if (!is_identity_matrix){
		// Convert to bg space
		mulPtByMatrix(pos, pre_matrix);
		//Simple_log{}("pos: " + to_string(pos[0]) + " " + to_string(pos[1]) + " " + to_string(pos[2]));
	}

	// This method finds the closest polygon from the given position. 
	// If it finds a polygon, it sets the current polygon, the hit position, the distance to the hit position and the surface normal, and returns LXe_TRUE. 

	if (_wrapType == 0){
		// Projection
		LXtVector dir = {_dir[0], _dir[1], _dir[2]};
		LXtMatrix4		 rotmatrix;
		get_rotation_matrix4(pre_matrix, rotmatrix);
		mulPtByMatrix(dir, rotmatrix);

		rc = bg_polygon.IntersectRay(pos, dir, hitNorm, &hitDist);

		if (rc != LXe_OK) return;

		if (_maxDistance > 0.0)
			if (hitDist > _maxDistance) return;

		if (!_doubleSided){
			double dp = dir[0] * hitNorm[0] + dir[1] * hitNorm[1] + dir[2] * hitNorm[2];
			if (!_invert){
				if (dp < 0.0) return;
			}
			else{
				if (dp > 0.0) return; 
			}
		}

		if (_offset != 0.0){

			double dir_offset[3] = { dir[0] * _offset, dir[1] * _offset, dir[2] * _offset };
			if (_invert){
				dir_offset[0] = -dir_offset[0]; dir_offset[1] = -dir_offset[1]; dir_offset[2] = -dir_offset[2];
			}

			hitPos[0] = pos[0] + dir[0] * hitDist + dir_offset[0];
			hitPos[1] = pos[1] + dir[1] * hitDist + dir_offset[1];
			hitPos[2] = pos[2] + dir[2] * hitDist + dir_offset[2];
		}
		else{
			hitPos[0] = pos[0] + dir[0] * hitDist;
			hitPos[1] = pos[1] + dir[1] * hitDist;
			hitPos[2] = pos[2] + dir[2] * hitDist;
		}
	}
	else {
		// Closest Point
		if (_maxDistance > 0.0){
			rc = bg_polygon.Closest(_maxDistance, pos, hitPos, hitNorm, &hitDist);
			if (rc != LXe_OK) return;
		}
		else{
			rc = bg_polygon.Closest(NULL, pos, hitPos, hitNorm, &hitDist);
			if (rc != LXe_OK) return;
		}

		if (_offset != 0.0){
			double dir[3] = { pos[0] - hitPos[0], pos[1] - hitPos[1], pos[2] - hitPos[2] };
			double dir_slen = (dir[0] * dir[0]) + (dir[1] * dir[1]) + (dir[2] * dir[2]);
			if (dir_slen > 0.0){
				double dir_len = sqrt(dir_slen);
				double multiplier = 1.0 / dir_len * _offset;
				dir[0] *= multiplier;
				dir[1] *= multiplier;
				dir[2] *= multiplier;
			}

			hitPos[0] += dir[0];
			hitPos[1] += dir[1];
			hitPos[2] += dir[2];
		}
	}



	//LXx_VSCL(hitNorm, -_wrap * hitDist); // Invert and scale by e_factor
	//LXx_VADD(pos, hitNorm);

	// Falloff Item Weight
	double factor = _wrap;
	if (falloffs.size > 0){
		float pos_weight = 0.0;
		for (unsigned f = 0; f < falloffs.size; f++)
		{
			CLxUser_Falloff fo = falloffs[f];
			if (fo.test()){
				mulPtByMatrix(fpos, item_matrix);
				pos_weight += fo.WeightF(fpos);
			}
		}
		pos_weight /= falloffs.size;
		factor *= pos_weight;
	}

	pos[0] = _linear_blend(pos[0], hitPos[0], factor);
	pos[1] = _linear_blend(pos[1], hitPos[1], factor);
	pos[2] = _linear_blend(pos[2], hitPos[2], factor);

	if (!is_identity_matrix){
		// Convert back to layer space
		mulPtByMatrix(pos, post_matrix);
		//Simple_log{}("pos post: " + to_string(pos[0]) + " " + to_string(pos[1]) + " " + to_string(pos[2]));
	}

	point.SetPos(pos);
			

	// Some points have been edited
	edit_any = true;

}


/*
*	The Mesh Operation is spawned by the modifier and generates a plane in
*	the procedural mesh.
*/
void SWrap_MeshOp::initialize()
{
	CLxGenericPolymorph	*srv = NULL;

	srv = new CLxPolymorph						<SWrap_MeshOp>;
	srv->AddInterface(new CLxIfc_MeshOperation	<SWrap_MeshOp>);

	lx::AddSpawner(SWRAP_SERVER_NAME_OP, srv);
}


LxResult
SWrap_MeshOp::mop_SetTransform(const LXtMatrix4 matrix){
	_mop_matrix[0][0] = matrix[0][0]; _mop_matrix[0][1] = matrix[0][1]; _mop_matrix[0][2] = matrix[0][2]; _mop_matrix[0][3] = matrix[0][3];
	_mop_matrix[1][0] = matrix[1][0]; _mop_matrix[1][1] = matrix[1][1]; _mop_matrix[1][2] = matrix[1][2]; _mop_matrix[1][3] = matrix[1][3];
	_mop_matrix[2][0] = matrix[2][0]; _mop_matrix[2][1] = matrix[2][1]; _mop_matrix[2][2] = matrix[2][2]; _mop_matrix[2][3] = matrix[2][3];
	_mop_matrix[3][0] = matrix[3][0]; _mop_matrix[3][1] = matrix[3][1]; _mop_matrix[3][2] = matrix[3][2]; _mop_matrix[3][3] = matrix[3][3];
	return LXe_OK;
}




LxResult
	SWrap_MeshOp::mop_Evaluate(
	ILxUnknownID		 mesh_obj,
	LXtID4			 type,
	LXtMarkMode		 mode)			
{
	CLxUser_Mesh				mesh(mesh_obj);
	CLxUser_Mesh				inMesh;
	CLxUser_MeshService			msh_svc;
	CLxUser_Polygon				polygon;
	CLxUser_Point				point;
	SWRAP_VertexVisitor			vis;
	
	LxResult rc = LXe_FAILED;

	// wrap
	vis._wrap = _wrap;
	// offset
	vis._offset = _offset;

	// wrap type
	if (_wrapType>=0 && _wrapType<2)
		vis._wrapType = _wrapType;
	else 
		vis._wrapType = 1; // Projection
	// max distance
	if (_maxDistance > 0.0)
		vis._maxDistance = _maxDistance;
	else
		vis._maxDistance = 0.0;
	// projection axis
	double ax = 1.0;
	if (_invertAxis)
		ax = -1.0;
	if (_projectionAxis == 0){
		vis._dir[0] = ax; vis._dir[1] = 0.0; vis._dir[2] = 0.0; // X Axis
	}
	else if (_projectionAxis == 1){
		vis._dir[0] = 0.0; vis._dir[1] = ax; vis._dir[2] = 0.0; // Y Axis
	}
	else if (_projectionAxis == 2){
		vis._dir[0] = 0.0; vis._dir[1] = 0.0; vis._dir[2] = ax; // Z Axis
	}

	// invert
	vis._invert = _invertAxis;
	// cull back faces
	vis._doubleSided = _doubleSided;


	LXtMatrix4 bg_wmat;
	LXtMatrix4 bg_wmat_inverse;

	bool	   is_bgmat_identity = true;

	// Get the first mesh only.
	// I hope in the future to support multiple meshes
	if (_bgMeshArray.size > 0){
		vis.bg_mesh = _bgMeshArray[0];

		if (vis.bg_mesh.test()){
			// Get the first matrix only.
			// I hope in the future to support multiple meshes
			if (_bgMeshMatrixArray.size > 0)
				copyMatrix4(_bgMeshMatrixArray[0], bg_wmat);
			else
				makeIdentity4(bg_wmat);

			is_bgmat_identity = isIdentity4(bg_wmat);
			if (!is_bgmat_identity) {
				bool success = inverse(bg_wmat, bg_wmat_inverse);
			}
		} else
			// this meshOp NEEDS a background mesh to operate
			return LXe_OK;
	}
	else{
		// this meshOp NEEDS a background mesh to operate
		return LXe_OK;
	}



	vis.falloffs.Free();
	if (_falloffs.size>0){
		vis.falloffs.Alloc(_falloffs.size);
		for (unsigned f = 0; f < _falloffs.size; f++){

			vis.falloffs[f] = _falloffs[f];
		}
	}


	LXtMatrix4 wmat;
	LXtMatrix4 wmat_inverse;
	LXtMatrix4 vis_mat;
	bool	   is_mat_identity = true;

	vis.mesh = mesh;
	vis.point.fromMeshObj(vis.mesh);
	vis.polygon.fromMeshObj(vis.mesh);
	vis.bg_polygon.fromMeshObj(vis.bg_mesh);

	// Set Visitor Matrix
	copyMatrix4(_mop_matrix, vis.item_matrix);
	is_mat_identity = isIdentity4(_mop_matrix);
	if (!is_bgmat_identity || !is_mat_identity) {
		//CLxMatrix4 cl_wmat(wmat);
		bool success = inverse(_mop_matrix, wmat_inverse);
		if (success){
			if (is_bgmat_identity){
				makeIdentity4(bg_wmat_inverse);
			}
			product4(_mop_matrix, bg_wmat_inverse, vis.pre_matrix);
			product4(bg_wmat, wmat_inverse, vis.post_matrix);

			vis.is_identity_matrix = false;
		}
	}

	vis.edit_any = false;

	vis.point.Enumerate(mode, vis, 0);

	if (vis.edit_any)
		//scan.SetMeshChange(i, LXf_MESHEDIT_GEOMETRY);
		// Because of the way the Closest() method works,
		// It is better to set the mesh change after all the modifications
		// are done.
		vis.mesh.SetMeshEdits(LXf_MESHEDIT_POSITION);

	
	return LXe_OK;
}



/*
*	The Modifier is associated with the all items of our type, and it reads
*	time as an input, spawns the mesh operation and writes it to the mesh
*	operation object channel.
*/


SWrap_ModElement::SWrap_ModElement(
	CLxUser_Evaluation	&eval,
	ILxUnknownID		 item_obj)
{
	CLxUser_Item		 item(item_obj);

	_time_index = -1;
	_wrap_idx = -1;
	_wrapType_idx = -1;
	_offset_idx = -1;
	_projectionAxis_idx = -1;
	_invertAxis_idx = -1;
	_maxDistance_idx = -1;
	_doubleSided_idx = -1;

	_output_index = -1;

	if (item.test())
	{
		/*
		*	Allocate time as an input and the mesh
		*	operation object as an output.
		*/

		// good read for later
		//
		// http://www.matt-cox.co.uk/blog/2014/8/7/writing-a-channel-modifier-for-modo
		// 

		_time_index = eval.AddTime();
		_output_index = eval.AddChan(item, LXsICHAN_MESHOP_OBJ, LXfECHAN_WRITE);
		_wrap_idx = eval.AddChan(item, "wrap", LXfECHAN_READ);
		_wrapType_idx = eval.AddChan(item, "wrapType", LXfECHAN_READ);
		_offset_idx = eval.AddChan(item, "offset", LXfECHAN_READ);
		_projectionAxis_idx = eval.AddChan(item, "projectionAxis", LXfECHAN_READ);
		_invertAxis_idx = eval.AddChan(item, "invertAxis", LXfECHAN_READ);
		_maxDistance_idx = eval.AddChan(item, "maxDistance", LXfECHAN_READ);
		_doubleSided_idx = eval.AddChan(item, "doubleSided", LXfECHAN_READ);

		// Add mesh souce item channel
		CLxUser_ItemGraph meshGraph;
		unsigned int meshRevCount;

		// Very important read about graphs, plugs and channels
		// See also the Graph : CLxImpl_SchematicConnection implemented above
		// https://community.foundry.com/discuss/topic/82826
		if (meshGraph.from(item, SWRAP_GRAPH_BG_MESH));
		{
			LxResult result = meshGraph.RevCount(item, &meshRevCount);
			if (result != LXe_OK){
				return;
			}

			_bgmesh_ids.clear();
			CLxUser_Item meshItem;
			for (unsigned i = 0; i < meshRevCount; i++)
			{
				int idx = -1;
				int xfrm_idx = -1;
				meshGraph.Reverse(item, i, meshItem);
				if (meshItem.test()){
					idx = eval.AddChan(meshItem, LXsICHAN_MESH_MESH);
					xfrm_idx = eval.AddChan(meshItem, LXsICHAN_XFRMCORE_WORLDMATRIX, LXfECHAN_READ); // this will trigger the evaluation if the world transformation of the BG mesh changes.
					// update our mesh/matrix indices vectors
					_bgmesh_ids.push_back(idx);
					_bgmesh_wmats_ids.push_back(xfrm_idx);
				}
			}
			// Update private var with number of connections.
			_n_bgmeshes = meshRevCount;
		}

		// Add falloff item channel
		CLxUser_ItemGraph falloffGraph;
		unsigned int falloffRevCount;

		if (falloffGraph.from(item, SWRAP_FALLOFF_GRAPH));
		{
			LxResult result = falloffGraph.RevCount(item, &falloffRevCount);
			if (result != LXe_OK){
				return;
			}

			_falloffs_ids.clear();
			CLxUser_Item falloffItem;
			for (unsigned i = 0; i < falloffRevCount; i++)
			{
				int idx = -1;
				falloffGraph.Reverse(item, i, falloffItem);
				if (falloffItem.test()){
					idx = eval.AddChan(falloffItem, LXsICHAN_FALLOFF_FALLOFF, LXfECHAN_READ);
					_falloffs_ids.push_back(idx);
				}
			}
			// Update private var with number of connections.
			_n_connected_falloffs = falloffRevCount;
		}

	}
}


	// Override modifier.Test()
	bool SWrap_ModElement::Test(ILxUnknownID item_obj) 
	{

		CLxUser_Item item(item_obj);

		if (item.test())
		{
			CLxUser_Scene            scene;
			CLxUser_ItemGraph        graph;

			scene.from(item);

			if (scene.GetGraph(SWRAP_GRAPH_BG_MESH, graph))
			{
				//Check if the number of locator connections has changed
				if (graph.Reverse(item) != _n_bgmeshes)
				{
					return false;
				}
			}
			if (scene.GetGraph(SWRAP_FALLOFF_GRAPH, graph))
			{
				//Check if the number of locator connections has changed
				if (graph.Reverse(item) != _n_connected_falloffs)
				{
					return false;
				}
			}
		}


	
		return false;
	}



	void
		SWrap_ModElement::Eval(
		CLxUser_Evaluation	&eval,
		CLxUser_Attributes	&attr)			
	{
		CLxUser_ValueReference	 val_ref;
		SWrap_MeshOp			*meshOp = NULL;
		ILxUnknownID		 meshOp_obj = NULL;
		double			 time = 0.0;
		double			wrap = 0.0;
		double			wrapType = 0.0;
		double			offset = 0.0;
		int				projectionAxis = 1;
		bool			invertAxis = false;
		double			maxDistance = 0.0;
		bool			doubleSided = false;

		LXtMatrix4		wmat;

		CLxSpawner <SWrap_MeshOp>	 spawner(SWRAP_SERVER_NAME_OP);

		if (_output_index < 0)
			return;

		if (_time_index >= 0)
			time = attr.Float(_time_index);

		if (_wrap_idx >= 0)
			wrap = attr.Float(_wrap_idx);
		
		if (_wrapType_idx >= 0)
			wrapType = attr.Int(_wrapType_idx);

		if (_offset_idx >= 0)
			offset = attr.Float(_offset_idx);

		if (_projectionAxis_idx >= 0)
			projectionAxis = attr.Int(_projectionAxis_idx);

		if (_invertAxis_idx>=0)
			invertAxis = attr.Bool(_invertAxis_idx);

		if (_doubleSided_idx >= 0)
			doubleSided = attr.Bool(_doubleSided_idx);

		if (_maxDistance_idx >= 0)
			maxDistance = attr.Float(_maxDistance_idx);
		/*
		*	Spawn the mesh operation and copy the time channel to
		*	it for the size.
		*/

		meshOp = spawner.Alloc(meshOp_obj);
		if (meshOp){
			meshOp->_time = time;
			meshOp->_wrap = wrap;
			meshOp->_wrapType = wrapType;
			meshOp->_offset = offset;
			meshOp->_projectionAxis = projectionAxis;
			meshOp->_invertAxis = invertAxis;
			meshOp->_maxDistance = maxDistance;
			meshOp->_doubleSided = doubleSided;

			// Pass the background meshes to our meshOp
			if (_bgmesh_ids.size() > 0)
			{
				meshOp->_bgMeshArray.Alloc(_n_bgmeshes);
				for (unsigned i = 0; i < _n_bgmeshes; ++i)
				{
					unsigned int index = _bgmesh_ids[i];

					CLxUser_MeshFilter mf;
					if (attr.ObjectRO(index, mf))
						mf.GetMesh(meshOp->_bgMeshArray[i]);
				}
			}
			// The following is to trigger the eval when the matrix changes
			unsigned n_bgmats = _bgmesh_wmats_ids.size();
			if (n_bgmats > 0)
			{
				meshOp->_bgMeshMatrixArray.Alloc(n_bgmats);
				for (unsigned i = 0; i < n_bgmats; ++i)
				{
					unsigned int index = _bgmesh_wmats_ids[i];

					CLxUser_Matrix mt;
					if (attr.ObjectRO(index, mt)){
						mt.Get4(wmat);
						copyMatrix4(wmat, meshOp->_bgMeshMatrixArray[i]);
					}
				}
			}


			// Read falloff items
			int nfalloffs = _falloffs_ids.size();
			meshOp->_falloffs.Alloc(nfalloffs);
			for (unsigned i = 0; i < nfalloffs; ++i)
			{
				unsigned int f_idx = _falloffs_ids[i];

				CLxUser_ValueReference val_ref;
				if (attr.ObjectRO(f_idx, val_ref))
				{
					CLxUser_Falloff loc_falloff;
					if (val_ref.GetObject(loc_falloff)){
						meshOp->_falloffs[i] = loc_falloff;
					}
				}
			}
		}

		/*
		*	Write the mesh operation into the mesh operation item
		*	output channel.
		*/

		if (attr.ObjectRW(_output_index, val_ref))
			val_ref.SetObject(meshOp_obj);

		/*
		*	Release the mesh operation COM object, as we spawned
		*	the item directly.
		*/

		lx::UnkRelease(meshOp_obj);
	}



void SWrap_ModServer::initialize()
{
	CLxExport_ItemModifierServer <SWrap_ModServer>(SWRAP_SERVER_NAME_MOD);
}

const char *
	SWrap_ModServer::ItemType()
{
	/*
	*	Associate the modifier with all items of our type.
	*/

	return SWRAP_SERVER_NAME;
}

// GRAPH NAMES
const char* SWrap_ModServer::GraphNames() 
{
	/*
	* List of space - separated graph names that trigger this modifier to update(optional)
	*/
	// Example
	// return LOCATOR_GRAPH_NAME " " CURVE_GUIDE_GRAPH_NAME;
	return SWRAP_GRAPH_BG_MESH " " SWRAP_FALLOFF_GRAPH;
}


	CLxItemModifierElement *
		SWrap_ModServer::Alloc(
	CLxUser_Evaluation	&eval,
	ILxUnknownID		 item_obj)		
{
	return new SWrap_ModElement(eval, item_obj);
}


void initialize()
{
	SWrap_Package::initialize();
	SWrap_Instance::initialize();
	SWrap_MeshOp::initialize();
	SWrap_ModServer::initialize();
	FalloffGraph::initialize();
	SWrap_BgGraph::initialize();
}