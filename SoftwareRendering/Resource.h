#pragma once
#include "Texture.h"

struct Resource
{
    char*  m_Data  = nullptr;
    size_t m_Size  = 0;
    bool   m_InUse = false;
};

struct BufferInfo : public Resource
{
};

struct TextureInfo : public Resource
{
    Texture m_Texture;
};