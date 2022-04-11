#pragma once

#include <lx_mesh.hpp>
#include <lx_surface.hpp>

#include <lxu_attributes.hpp>
#include <lxu_math.hpp>

#include <lxu_package.hpp>
#include <lxu_modifier.hpp>
#include <lx_channelui.hpp>

#include <lx_schematic.hpp>   // To Use CLxImpl_SchematicConnection

#include <lx_action.hpp>   //
#include <lx_locator.hpp>  // Both required for reading the world matrix.

#include <vector>


#include "graph_Falloff.h"  // Falloff Graph
#include "defines.h"

class SWrap_Instance : public CLxImpl_PackageInstance
{
public:
	static void initialize();
};


//
// // needed by Package::cui_DependencyByIndex()
// https://gist.github.com/lukpazera/8239a7830430dc53c83e
//
static CLxItemType		 	cit_swrap_self(SWRAP_SERVER_NAME);



class  SWrap_Package : public CLxImpl_Package,
	public CLxImpl_SceneItemListener,
	public CLxImpl_ChannelUI

{
public:

	static void initialize();

	SWrap_Package() : _inst_spawn(SWRAP_SERVER_NAME_INST) {}




	LxResult
		pkg_TestInterface(
		const LXtGUID		 *guid)			LXx_OVERRIDE;

	LxResult
		pkg_Attach(
		void			**ppvObj)		LXx_OVERRIDE;

	LxResult
		pkg_SetupChannels(
		ILxUnknownID		 addChan)     LXx_OVERRIDE;

	/*
	void sil_ItemAddChannel
	(ILxUnknownID		  		item)  LXx_OVERRIDE;



	void	sil_ChannelValue (
	const char               *action,
	ILxUnknownID              item,
	unsigned                 index) LXx_OVERRIDE;
	*/

	LxResult    cui_Enabled(const char* channelName, ILxUnknownID msg, ILxUnknownID item, ILxUnknownID read) LXx_OVERRIDE;
	LxResult	cui_DependencyCount(const char* channelName, unsigned* count) LXx_OVERRIDE;
	LxResult	cui_DependencyByIndex(const char* channelName, unsigned index, LXtItemType* depItemType, const char** depChannelName) LXx_OVERRIDE;

	static LXtTagInfoDesc	 descInfo[];

private:
	CLxSpawner <SWrap_Instance>	 _inst_spawn;
};



class SWrap_BgGraph : public CLxImpl_SchematicConnection
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





/*
*	The Mesh Operation is spawned by the modifier and generates a plane in
*	the procedural mesh.
*/

class SWrap_MeshOp : public CLxImpl_MeshOperation
{
public:



	static void initialize();

	LxResult
		mop_Evaluate(
		ILxUnknownID		 mesh_obj,
		LXtID4			 type,
		LXtMarkMode		 mode)			LXx_OVERRIDE;

	LxResult
		mop_SetTransform(const LXtMatrix4 matrix)	LXx_OVERRIDE;

	/*
	int
	mop_Compare(
	ILxUnknownID		 other_obj)	LXx_OVERRIDE;

	LxResult
	mop_Convert(
	ILxUnknownID		 other_obj)	LXx_OVERRIDE;

	LxResult
	mop_ReEvaluate(
	ILxUnknownID		 mesh_obj,
	LXtID4			 type)			LXx_OVERRIDE;
	*/


	double		_time;
	double		_wrap;
	double		_offset;
	int			_wrapType;
	int			_projectionAxis;
	bool		_invertAxis;
	double		_maxDistance;
	bool		_doubleSided;
	CLxArray<CLxUser_Falloff> _falloffs;
	CLxArray<CLxUser_Mesh>  _bgMeshArray;
	CLxArray<LXtMatrix4>  _bgMeshMatrixArray;
	LXtMatrix4	_mop_matrix;
	LXtMatrix4  _mop_bg_matrix;
};






class SWrap_ModElement : public CLxItemModifierElement
{
public:
	SWrap_ModElement(
		CLxUser_Evaluation	&eval,
		ILxUnknownID		 item_obj);

	bool Test(ILxUnknownID item_obj) LXx_OVERRIDE;

	void Eval(CLxUser_Evaluation	&eval,
		CLxUser_Attributes	&attr)			LXx_OVERRIDE;

private:
	int			 _output_index, _time_index;
	int			 _wrap_idx, _wrapType_idx, _offset_idx, _projectionAxis_idx, _invertAxis_idx, _maxDistance_idx, _doubleSided_idx;

	int _n_bgmeshes;
	int _n_connected_falloffs;
	std::vector<int> _bgmesh_ids;
	std::vector<int> _bgmesh_wmats_ids;
	std::vector<int> _falloffs_ids;

};







class SWrap_ModServer : public CLxItemModifierServer
{
public:
	static void initialize();

	const char *
		ItemType()						LXx_OVERRIDE;

	// GRAPH NAMES
	const char* GraphNames() LXx_OVERRIDE;


	CLxItemModifierElement *
		Alloc(
		CLxUser_Evaluation	&eval,
		ILxUnknownID		 item_obj)		LXx_OVERRIDE;
};