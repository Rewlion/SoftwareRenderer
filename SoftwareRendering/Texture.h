#pragma once

#include "Math.hpp"
#include "Color.h"

#include <Windows.h>
#include <Gdiplus.h>
#include <string>

class Texture
{
public:
    ~Texture()
    {
        if (m_Bitmap)
        {
            m_Bitmap->UnlockBits(&m_Data);
            delete m_Bitmap;
        }
    }

    inline bool LoadTexture(const WCHAR* file)
    {
        if (m_Bitmap)
        {
            m_Bitmap->UnlockBits(&m_Data);
            delete m_Bitmap;
        }

        m_Bitmap = Gdiplus::Bitmap::FromFile(file);
        if (m_Bitmap != nullptr)
        {
            Gdiplus::Rect rect{ 0,0, static_cast<INT>(m_Bitmap->GetWidth()), static_cast<INT>(m_Bitmap->GetHeight()) };
            m_Bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppRGB, &m_Data);
            return true;
        }
        else
            return false;
    }

    RGB GetPixel(const Math::fVec2& uv)
    {
        const unsigned int x = uv[0] * (m_Data.Width - 1);
        const unsigned int y = uv[1] * (m_Data.Height - 1);
        return reinterpret_cast<uint32_t*>(m_Data.Scan0)[y * m_Data.Stride / 4 + x];
    }

private:
    Gdiplus::Bitmap*    m_Bitmap = nullptr;
    Gdiplus::BitmapData m_Data;
};