#pragma once

#include "Math.hpp"
#include "Vertex.h"

struct ShaderContext
{
    const Math::Mat4x4* MVP;
    unsigned int        Width;
    unsigned int        Height;

    unsigned int        LightsCount;
    Math::fVec3         DirLights[10];

    Texture*            Textures;
};

class ShaderProgram
{
public:
    ShaderProgram(ShaderContext* context)
        : m_Context(context)
    {
    }

    virtual Math::fVec4 ProcessVertex(const unsigned int index, const Vertex& vertex ) = 0;
    virtual RGB ProcessFragment(const Math::fVec3 uwv) = 0;

protected:
    ShaderContext* m_Context;
};

class SimpleShader final : public ShaderProgram
{
public:
    SimpleShader(ShaderContext* context)
        : ShaderProgram(context)
    {
    }

    virtual Math::fVec4 ProcessVertex(const unsigned int index, const Vertex& vertex)
    {
        Colors[index] = vertex.Color;
        return (*m_Context->MVP) * vertex.XYZ;
    }
    
    virtual RGB ProcessFragment(const Math::fVec3 uwv)
    {
        //if ((uwv[2] <= 0.5) && (uwv[2] >= 0.4))
          //  return Color::LightBlue;
        //else
            return  uwv[0] * Colors[0] + uwv[1] * Colors[1] + uwv[2] * Colors[2];
    }

private:
    RGB Colors[3];
};

class SimpleTextureShader final : public ShaderProgram
{
public:
    SimpleTextureShader(ShaderContext* context)
        : ShaderProgram(context)
    {
    }

    virtual Math::fVec4 ProcessVertex(const unsigned int index, const Vertex& vertex)
    {
        Textures[index] = vertex.UV;
        return (*m_Context->MVP) * vertex.XYZ;
    }

    virtual RGB ProcessFragment(const Math::fVec3 uwv)
    {
        Math::fVec2 textureCoordinates = uwv[0] * Textures[0] + uwv[1] * Textures[1] + uwv[2] * Textures[2];
        return m_Context->Textures[0].GetPixel(textureCoordinates);
    }

private:
    Math::fVec2 Textures[3];
};