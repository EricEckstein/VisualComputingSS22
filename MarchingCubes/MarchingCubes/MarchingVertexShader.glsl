#version 330 core

// This vertex shader is fed 95*95 points, one for each *cell* we'll run M.C. on.
// To generate > 1 slice in a single frame, we call DrawInstanced(N),
// and it repeats it N times, each time setting nInstanceID to [0 .. N-1].
// per-vertex input attributes: [never change]

struct vertexInput {
	float2 uv : POSITION; // 0..1 range
	uint nInstanceID : SV_InstanceID;
};

struct vsOutputGsInput 
{ 
	float3 wsCoord : POSITION; // coords for LOWER-LEFT corner of the cell
	float3 uvw : TEX;
	float4 f0123 : TEX1; // the density values
	float4 f4567 : TEX2; // at the 8 cell corners
	uint mc_case : TEX3; // 0-255
};

Texture3D tex; // our volume of density values. (+=rock, -=air)
SamplerState s; // trilinear interpolation; clamps on XY, wraps on Z.

cbuffer SliceInfos {
// Updated each frame. To generate 5 slices this frame,
// app has to put their world-space Y coords in slots [0..4] here.
float slice_world_space_Y_coord[256];
}

// converts a point in world space to 3D texture space (for sampling the 3D texture):
#define WS_to_UVW(ws) (float3(ws.xz*0.5+0.5, ws.y*WorldSpaceVolumeHeight).xzy)


v2gConnector main(vertexInput vtx)
{

	float3 wsCoord;
	wsCoord.xz = vtx.uv.xy*2-1;
	wsCoord.y = slice_world_space_Y_coord[ vtx.nInstanceID ];
	float3 uvw = WS_to_UVW( wsCoord );

	float2 step = float2(worldSpaceVoxelSize, 0);
	float4 f0123 = float4( tex.SampleLevel(s, uvw + step.yyy, 0).x,
	tex.SampleLevel(s, uvw + step.yyx, 0).x,
	tex.SampleLevel(s, uvw + step.xyx, 0).x,
	tex.SampleLevel(s, uvw + step.xyy, 0).x );
	float4 f4567 = float4( tex.SampleLevel(s, uvw + step.yxy, 0).x,
	tex.SampleLevel(s, uvw + step.yxx, 0).x,
	tex.SampleLevel(s, uvw + step.xxx, 0).x,
	tex.SampleLevel(s, uvw + step.xxy, 0).x );
	// determine which of the 256 marching cubes cases we have for this cell:
	uint4 n0123 = (uint4)saturate(f0123*99999);
	uint4 n4567 = (uint4)saturate(f4567*99999);
	uint mc_case = (n0123.x ) | (n0123.y << 1) | (n0123.z << 2) | (n0123.w << 3)
	| (n4567.x << 4) | (n4567.y << 5) | (n4567.z << 6) | (n4567.w << 7);

}