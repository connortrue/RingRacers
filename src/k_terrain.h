// DR. ROBOTNIK'S RING RACERS
//-----------------------------------------------------------------------------
// Copyright (C) 1998-2021 by ZDoom + GZDoom teams, and contributors
// Copyright (C) 2021 by Sally "TehRealSalt" Cochenour
// Copyright (C) 2021 by Kart Krew
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  k_terrain.h
/// \brief Implementation of a TERRAIN-style lump for DRRR, ala GZDoom's codebase.

#ifndef __K_TERRAIN_H__
#define __K_TERRAIN_H__

#include "doomdata.h"
#include "doomdef.h"
#include "doomtype.h"
#include "m_fixed.h"
#include "p_mobj.h"

#define TERRAIN_NAME_LEN 32

typedef struct t_splash_s
{
	// Splash definition.
	// These are particles spawned when hitting the floor.

	char name[TERRAIN_NAME_LEN];	// Lookup name.

	UINT16 objType;			// Thing type. MT_NULL to not spawn anything.
	UINT16 sound;			// Sound to play.
} t_splash_t;

typedef struct t_footstep_s
{
	// Footstep definition.
	// These are particles spawned when moving fast enough on a floor.

	char name[TERRAIN_NAME_LEN];	// Lookup name.

	UINT16 objType;			// Thing type. MT_NULL to not spawn anything.
	UINT16 sound;			// Sound to play.
} t_footstep_t;

typedef enum
{
	// Terrain flag values.
	TRF_LIQUID = 1, // Texture water properties (wavy, slippery, etc)
	TRF_SNEAKERPANEL = 1<<1 // Texture is a booster
} terrain_flags_t;

typedef struct terrain_s
{
	// Terrain definition.
	// These are all of the properties that the floor gets.

	char name[TERRAIN_NAME_LEN];	// Lookup name.

	UINT16 splashID;		// Splash defintion ID.
	UINT16 footstepID;		// Footstep defintion ID.

	fixed_t friction;		// The default friction of this texture.
	UINT8 offroad;			// The default offroad level of this texture.
	INT16 damageType;		// The default damage type of this texture. (Negative means no damage).
	UINT8 trickPanel;		// Trick panel strength
	UINT32 flags;			// Flag values (see: terrain_flags_t)
} terrain_t;

typedef struct t_floor_s
{
	// Terrain floor definition.
	// Ties texture names to a .

	// (Could be optimized by using texture IDs instead of names,
	// but was concerned because I recall sooomething about those not being netsafe?
	// Someone confirm if I just hallucinated that. :V)

	char textureName[9];	// Floor texture name.
	UINT16 terrainID;		// Terrain definition ID.
} t_floor_t;

// Arrays for all terrain definitions.
extern t_splash_t *splashDefs;
extern UINT16 numSplashDefs;

extern t_footstep_t *footstepDefs;
extern UINT16 numFootstepDefs;

extern terrain_t *terrainDefs;
extern UINT16 numTerrainDefs;

extern t_floor_t *terrainFloorDefs;
extern UINT16 numTerrainFloorDefs;

// Default terrain definition ID.
extern UINT16 defaultTerrain;

terrain_t *K_GetTerrainByIndex(UINT16 checkIndex);
terrain_t *K_GetTerrainByName(const char *checkName);
terrain_t *K_GetDefaultTerrain(void);
terrain_t *K_GetTerrainForTextureName(const char *checkName);
terrain_t *K_GetTerrainForTextureNum(INT32 textureNum);

void K_UpdateMobjTerrain(mobj_t *mo, INT32 flatID);
void K_SetDefaultFriction(mobj_t *mo);

void K_InitTerrain(UINT16 wadNum);

#endif // __K_TERRAIN_H__
