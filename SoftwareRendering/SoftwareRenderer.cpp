#include "SoftwareRenderer.h"
#include "Vertex.h"

#include <assert.h>
#include <cstring>
#include <iostream>

SoftwareRenderer::SoftwareRenderer()
    : m_VertexBufferID(0)
    , m_FVF(FVF_XYZ | FVF_RGB)
    , m_RenderTarget(nullptr)
    , m_MVP(nullptr)
{
}

SoftwareRenderer::~SoftwareRenderer()
{
}

unsigned int SoftwareRenderer::CreateBuffer(const size_t size)
{
    BufferInfo newBuffer;
    newBuffer.m_Data = new char[size];
    newBuffer.m_Size = size;
    newBuffer.m_InUse = true;

    for(unsigned int i = 0; i < m_Buffers.size(); ++i)
    {
        BufferInfo& buffer = m_Buffers[i];
        if (buffer.m_InUse == false)
        {
            buffer = newBuffer;
            return i;
        }
    }

    const unsigned id = m_Buffers.size();
    m_Buffers.push_back(newBuffer);

    return id;
}

void SoftwareRenderer::FreeBuffer(const unsigned int id)
{
    BufferInfo& buffer = m_Buffers[id];
    delete[] buffer.m_Data;
    buffer.m_Data = nullptr;
    buffer.m_Size = 0;
    buffer.m_InUse = false;
}

void SoftwareRenderer::LoadBuffer(const unsigned int bufferID, const char* from, const size_t size, const size_t offset)
{
    BufferInfo& buffer = m_Buffers[bufferID];
    std::memcpy(buffer.m_Data + offset, from, size);
}

bool SoftwareRenderer::LoadTexture(const unsigned int id, const WCHAR* fromFile)
{
    Texture& texture = m_Textures[id];
    return texture.LoadTexture(fromFile);
}

void SoftwareRenderer::DrawPrimitives(const PrimitiveType type, const size_t startVertex, const unsigned int primitivesCount)
{
    switch (type)
    {
    case PrimitiveType::TriangleList:
        DrawTriangleList(startVertex, primitivesCount);
        break;

    default:
        assert(!"unknown primitive type.");
    }
}

void SoftwareRenderer::DrawTriangleList(const size_t startVertex, const unsigned int primitivesCount)
{
    struct Triangle
    {
        Vertex Points[3];
    };

    auto* triangles = reinterpret_cast<Triangle*>(m_Buffers[m_VertexBufferID].m_Data + sizeof(Vertex) * startVertex);

    Gdiplus::BitmapData bd;
    m_RenderTarget->LockBits(&m_RenderTargetSize, Gdiplus::ImageLockModeWrite, PixelFormat32bppRGB, &bd);

    ShaderContext context;
    context.MVP = m_MVP;
    context.Height = m_RenderTargetSize.Height;
    context.Width = m_RenderTargetSize.Width;
    context.Textures = m_Textures.data();
    SimpleTextureShader shader{ &context };
    //SimpleShader shader{ &context };

    uint32_t* bitmap = reinterpret_cast<uint32_t*>(bd.Scan0);

    for (int i = 0; i < primitivesCount; ++i)
    {
        float f[3];
        Math::fVec4 A = shader.ProcessVertex(0, triangles->Points[0]); f[0] = A[3]; A /= A[3]; A = m_ViewportTransform * A;
        Math::fVec4 B = shader.ProcessVertex(1, triangles->Points[1]); f[1] = B[3]; B /= B[3]; B = m_ViewportTransform * B;
        Math::fVec4 C = shader.ProcessVertex(2, triangles->Points[2]); f[2] = C[3]; C /= C[3]; C = m_ViewportTransform * C;

        if (A[2] < 0 || B[2] < 0 || C[2] < 0)
            continue;

        const Math::fVec2 a = A;
        const Math::fVec2 b = B;
        const Math::fVec2 c = C;

        const Math::fVec2 ab = b - a;
        const Math::fVec2 bc = c - b;

        const float S_ABC = Math::CalculateArea(ab, bc);
        Math::RectBorder border = Math::FindRectBorder(a, b, c);

        for (int x = border.TopLeft[0]; x <= border.BottomRight[0]; ++x)
            for (int y = border.TopLeft[1]; y <= border.BottomRight[1]; ++y)
            {
                const Math::fVec2 p{ static_cast<float>(x), static_cast<float>(y) };

                const Math::fVec2 pb = b - p;
                float u = Math::CalculateArea(pb, bc) / S_ABC;

                const Math::fVec2 ap = p - a;
                const Math::fVec2 pc = c - p;
                float w = Math::CalculateArea(ap,pc) / S_ABC;

                const Math::fVec2 bp = p - b;
                float v = Math::CalculateArea(ab, bp) / S_ABC;

                if (u < 0 || w < 0 || v < 0)
                    continue;

                const float z = 1/ (u / f[0] + w/f[1] + v/f[2]);
                u = u / f[0] * z;
                w = w / f[1] * z;
                v = v / f[2] * z;

                float& gbufZ = m_GBuffer[y * m_RenderTargetSize.Width + x];
                if (z < gbufZ)
                {
                    gbufZ = z;

                    const Math::fVec3 uwv{ u,w,v };
                    const RGB color = shader.ProcessFragment(uwv);
                    bitmap[y * bd.Stride / 4 + x] = static_cast<uint32_t>(color);
                }
            }
        ++triangles;
    }

    m_RenderTarget->UnlockBits(&bd);
}