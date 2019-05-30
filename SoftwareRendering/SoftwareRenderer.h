#pragma once

#include "Resource.h"
#include "Color.h"
#include "Math.hpp"
#include "ShaderProgram.h"

#include <limits>
#include <vector>
#include <cstdint>
#include <Windows.h>
#include <Gdiplus.h>
#include <gdiplusgraphics.h>
#include <gdiplusheaders.h>

enum FVF
{
    FVF_XYZ = 0b1,
    FVF_RGB = 0b10,
    
    FVF_XYZ_RGB = FVF_XYZ | FVF_RGB,
};

enum class PrimitiveType
{
    TriangleList
};

struct FramebufferInfo
{
    char*        m_Data;
    unsigned int m_Width;
    unsigned int m_Height;
};

class SoftwareRenderer
{
public:
    SoftwareRenderer();
    ~SoftwareRenderer();

    inline void SetFVF(const unsigned int fvf)
    {
        if (fvf & FVF_XYZ)
            m_FVF = fvf;
        else
            throw "bad_FVF"; //todo: make exceptions.
    }

    void DrawPrimitives(const PrimitiveType type, const size_t startVertex, const unsigned int primitivesCount);

    unsigned int CreateBuffer(const size_t size);
    
    void FreeBuffer(const unsigned int id);
    
    void LoadBuffer(const unsigned int bufferID, const char* from, const size_t size, const size_t offset = 0);

    bool LoadTexture(const unsigned int textureBindingid, const WCHAR* fromFile);

    inline void SetVertexBuffer(const unsigned int id) { m_VertexBufferID = id; }

    inline void SetRenderTarget(Gdiplus::Bitmap* bitmap) 
    { 
        m_RenderTarget = bitmap; 
        m_RenderTargetSize = Gdiplus::Rect{0,0,static_cast<INT>(bitmap->GetWidth()), static_cast<INT>(bitmap->GetHeight())};
        m_ViewportTransform = Math::ConstructViewportMatrix(bitmap->GetWidth(), bitmap->GetHeight());

        delete[] m_GBuffer;
        m_GBuffer = new float[bitmap->GetWidth() * bitmap->GetHeight()];
    }

    inline void Clear(const ARGB color)
    {
        Gdiplus::BitmapData bd;
        m_RenderTarget->LockBits(&m_RenderTargetSize, Gdiplus::ImageLockModeWrite, PixelFormat32bppRGB, &bd);

        uint32_t* data = reinterpret_cast<uint32_t*>(bd.Scan0);

        for (int x = 0; x < m_RenderTargetSize.Width; ++x)
            for (int y = 0; y < m_RenderTargetSize.Height; ++y)
                data[y * bd.Stride / 4 + x] = color.Raw;

        m_RenderTarget->UnlockBits(&bd);

        for (int x = 0; x < m_RenderTargetSize.Width; ++x)
            for (int y = 0; y < m_RenderTargetSize.Height; ++y)
                m_GBuffer[y * bd.Stride / 4 + x] = FLT_MAX-1;
    }

    inline void SetMVPTransform(const Math::Mat4x4* transform)
    {
        m_MVP = transform;
    }

private:
    void DrawTriangleList(const size_t startVertex, const unsigned int primitivesCount);

private:
    std::vector<BufferInfo>  m_Buffers;
    std::array<Texture, 10>  m_Textures;

    FramebufferInfo          m_Framebuffer;
    unsigned int             m_VertexBufferID;
    unsigned int             m_FVF;

    float*                   m_GBuffer;
    Gdiplus::Bitmap*         m_RenderTarget;
    Gdiplus::Rect            m_RenderTargetSize;

    const Math::Mat4x4*      m_MVP;
    Math::Mat4x4             m_ViewportTransform;
};