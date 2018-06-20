#include "Crosshair.h"
#include "Defines.h"

ID3DXLine *pLine = NULL;

Crosshair::Crosshair(HWND& window_)
: window(window_)
, device(nullptr)
{

}

Crosshair::~Crosshair()
{
    device->Release();
}

void Crosshair::init()
{
    IDirect3D9Ex *pDirect3DEx;
    DWORD behaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.BackBufferWidth = 1;
    d3dpp.BackBufferHeight = 1;
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.hDeviceWindow = window;
    d3dpp.Flags = D3DPRESENTFLAG_VIDEO;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

    Direct3DCreate9Ex(D3D_SDK_VERSION, &pDirect3DEx);
    pDirect3DEx->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, behaviorFlags, &d3dpp, NULL, &device);

    D3DXCreateLine(device, &pLine);
    pDirect3DEx->Release();
}

void Crosshair::render()
{
    drawRectangle(static_cast<int>(CENTER_OF_SCREEN.x - 20), static_cast<int>(CENTER_OF_SCREEN.y), 40, 2);
    drawRectangle(static_cast<int>(CENTER_OF_SCREEN.x), static_cast<int>(CENTER_OF_SCREEN.y - 20), 2, 40);
}

void Crosshair::drawRectangle(int x, int y, int w, int h)
{
    D3DRECT rectangle = { x, y, x + w, y + h };
    HRESULT result = device->Clear(1, &rectangle, D3DCLEAR_TARGET, CROSSHAIR_COLOR, 0, 0);
}
