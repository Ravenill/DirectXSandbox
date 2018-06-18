#include "CPR_Framework.h"
#include "Game.h"

//Mesh* g_mesh = 0;
//float g_angle = 0.0f;

Game game;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	This file contains the main loop of the program and works as follows:

		OnInit();

		while( !shouldShutDown )
		{
			OnUpdate( deltaTime );
			OnRender();
		}

		OnShutdown();

	For vector & matrix math we're using the D3DX Library. 
	Here are some useful classes & functions (that may or may not be handy):

		D3DXVECTOR3		- x, y, z (floats)
		D3DXMATRIX		- 16 float values
		D3DXQUATERNION	- x, y, z, w (floats)

		D3DXVECTOR3*	D3DXVec3Normalize( D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV );
		FLOAT			D3DXVec3Length( const D3DXVECTOR3 *pV );
		FLOAT			D3DXVec3Dot( const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2 );
		D3DXVECTOR3*	D3DXVec3Cross( D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV1, const D3DXVECTOR3 *pV2 );

	You can find these and more in the DX SDK documentation.

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//----------------------------------------------------------------------------
void OnInit()
{
	// NOTE: there is also unitbox.x, unitsphere.x & unitcylinder.x to use.
    // teapot.x
	// g_mesh = LoadFromFile( "resources/meshes/unitcylinder.x" );

    game.init();
}

//----------------------------------------------------------------------------
void OnShutdown()
{
	// Release( g_mesh );
}

//----------------------------------------------------------------------------
void OnUpdate( float _deltaTime )
{
	// update camera
	// g_angle += _deltaTime;
	// LookAt( D3DXVECTOR3( cosf( g_angle ) * 2.0f, 1.0f, sinf( g_angle ) * 2.0f ), D3DXVECTOR3( 0.0f, 0.5f, 0.0f ) );

    game.update();
}

//----------------------------------------------------------------------------
void OnRender()
{
	// render mesh
	// D3DXVECTOR3 pos( 0.0f, 0.0f, 0.0f );
	// D3DXVECTOR3 rot( 0.0f, 0.0f, 0.0f );
	// D3DXVECTOR3 sca( 1.0f, 1.0f, 1.0f );
	// D3DXVECTOR4 color( 1.0f, 0.5f, 0.0f, 1.0f );
	// Render( g_mesh, pos, rot, sca, color );

    game.render();
}

CPR_MAIN(OnInit, OnShutdown, OnUpdate, OnRender)


