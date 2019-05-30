#include "SoftwareRenderer.h"
#include "WindowManager.h"
#include "Vertex.h"

#include <windows.h>
#include <ctime>
#include <string>
#include <assert.h>

#undef RGB

Vertex Cube[] = {
       { { -0.5f, -0.5f, -0.5f}, {}, RGB(Color::BlueViolet), {0.0f, 0.0f} },
       { {  0.5f, -0.5f, -0.5f}, {}, RGB(Color::Pink),       {1.0f, 0.0f} },
       { {  0.5f,  0.5f, -0.5f}, {}, RGB(Color::LimeGreen),  {1.0f, 1.0f} },
       { {  0.5f,  0.5f, -0.5f}, {}, RGB(Color::Green),      {1.0f, 1.0f} },
       { { -0.5f,  0.5f, -0.5f}, {}, RGB(Color::SandyBrown), {0.0f, 1.0f} },
       { { -0.5f, -0.5f, -0.5f}, {}, RGB(Color::BlueViolet), {0.0f, 0.0f} },
       
       { { -0.5f, -0.5f,  0.5f}, {}, RGB(Color::Pink), { 0.0f, 0.0f} },
       { {  0.5f, -0.5f,  0.5f}, {}, RGB(Color::Pink), { 1.0f, 0.0f} },
       { {  0.5f,  0.5f,  0.5f}, {}, RGB(Color::Pink), { 1.0f, 1.0f} },
       { {  0.5f,  0.5f,  0.5f}, {}, RGB(Color::Pink), { 1.0f, 1.0f} },
       { { -0.5f,  0.5f,  0.5f}, {}, RGB(Color::Pink), { 0.0f, 1.0f} },
       { { -0.5f, -0.5f,  0.5f}, {}, RGB(Color::Pink), { 0.0f, 0.0f} },
       
       { { -0.5f,  0.5f,  0.5f}, {}, RGB(Color::LimeGreen), { 1.0f, 0.0f} },
       { { -0.5f,  0.5f, -0.5f}, {}, RGB(Color::LimeGreen), { 1.0f, 1.0f} },
       { { -0.5f, -0.5f, -0.5f}, {}, RGB(Color::LimeGreen), { 0.0f, 1.0f} },
       { { -0.5f, -0.5f, -0.5f}, {}, RGB(Color::LimeGreen), { 0.0f, 1.0f} },
       { { -0.5f, -0.5f,  0.5f}, {}, RGB(Color::LimeGreen), { 0.0f, 0.0f} },
       { { -0.5f,  0.5f,  0.5f}, {}, RGB(Color::LimeGreen), { 1.0f, 0.0f} },
       
       { {  0.5f,  0.5f,  0.5f}, {}, RGB(Color::Green), { 1.0f, 0.0f} },
       { {  0.5f,  0.5f, -0.5f}, {}, RGB(Color::Green), { 1.0f, 1.0f} },
       { {  0.5f, -0.5f, -0.5f}, {}, RGB(Color::Green), { 0.0f, 1.0f} },
       { {  0.5f, -0.5f, -0.5f}, {}, RGB(Color::Green), { 0.0f, 1.0f} },
       { {  0.5f, -0.5f,  0.5f}, {}, RGB(Color::Green), { 0.0f, 0.0f} },
       { {  0.5f,  0.5f,  0.5f}, {}, RGB(Color::Green), { 1.0f, 0.0f} },
       
       { { -0.5f, -0.5f, -0.5f}, {}, RGB(Color::SandyBrown), { 0.0f, 1.0f} },
       { {  0.5f, -0.5f, -0.5f}, {}, RGB(Color::SandyBrown), { 1.0f, 1.0f} },
       { {  0.5f, -0.5f,  0.5f}, {}, RGB(Color::SandyBrown), { 1.0f, 0.0f} },
       { {  0.5f, -0.5f,  0.5f}, {}, RGB(Color::SandyBrown), { 1.0f, 0.0f} },
       { { -0.5f, -0.5f,  0.5f}, {}, RGB(Color::SandyBrown), { 0.0f, 0.0f} },
       { { -0.5f, -0.5f, -0.5f}, {}, RGB(Color::SandyBrown), { 0.0f, 1.0f} },
       
       { { -0.5f,  0.5f, -0.5f}, {}, RGB(Color::PaleVioletRed), { 0.0f, 1.0f} },
       { {  0.5f,  0.5f, -0.5f}, {}, RGB(Color::PaleVioletRed), { 1.0f, 1.0f} },
       { {  0.5f,  0.5f,  0.5f}, {}, RGB(Color::PaleVioletRed), { 1.0f, 0.0f} },
       { {  0.5f,  0.5f,  0.5f}, {}, RGB(Color::PaleVioletRed), { 1.0f, 0.0f} },
       { { -0.5f,  0.5f,  0.5f}, {}, RGB(Color::PaleVioletRed), { 0.0f, 0.0f} },
       { { -0.5f,  0.5f, -0.5f}, {}, RGB(Color::PaleVioletRed), { 0.0f, 1.0f} },
};


//int N_Triangles = 2;
//int N_Triangles = 3;

int N_Triangles = 6 * 2;
int N_Vertices = N_Triangles * 3;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    SoftwareRenderer renderer;
    
    WindowSize size{ 800, 600 };
    WindowManager window{ hInstance, pCmdLine, nCmdShow, "Software Rendering", size };
    renderer.SetRenderTarget(window.GetBitmap());
    
    renderer.SetFVF(FVF_XYZ_RGB);
    const unsigned int vertexBufferID = renderer.CreateBuffer(sizeof(Vertex) * N_Vertices);
    renderer.LoadBuffer(vertexBufferID, reinterpret_cast<char*>(Cube), sizeof(Vertex) * N_Vertices, 0);
    renderer.SetVertexBuffer(vertexBufferID);
    
    assert(renderer.LoadTexture(0, L"container.jpg"));

    Math::Mat4x4 T = Math::Mat4x4::E();
    Math::Mat4x4 P = Math::CalculatePerspectiveTransformation(Math::ToRadians(90), 800/600, 0.1f, 100.0f);
    Math::Mat4x4 V = Math::CalculateTranslationTransformation({0,0,2});
    Math::Mat4x4 MVP = Math::Mat4x4::E();
    renderer.SetMVPTransform(&MVP);
    float dt = 0;
    while (window.ShouldWindowClose() == false)
    {
        T = Math::CalculateXRotation(dt) * Math::CalculateYRotation(dt);
        MVP = P * V * T;
        std::clock_t t1 = std::clock();

        renderer.Clear(Color::Black);
        renderer.DrawPrimitives(PrimitiveType::TriangleList, 0, N_Triangles);
        std::wstring str = std::to_wstring(dt);
        window.Blt();

        window.PollEvents();
        std::clock_t t2 = std::clock();
        dt += (t2 - t1) / (float)CLOCKS_PER_SEC;
    }
}