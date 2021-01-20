// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* PixelFormatProps.cpp *#*#*#*#*#*#*#*#* (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include "SdiFrameBuilder.h"

using namespace std;

namespace DtSdi
{

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+ PixelFormatProps implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// -.-.-.-.-.-.-.-.-.-.- PixelFormatProps::PixelFormatProps -.-.-.-.-.-.-.-.-.-.-.
//
PixelFormatProps::PixelFormatProps(PixelFormat  Fmt)
    : Fmt(Fmt),
      SymbolSize(0),
      SymbolPackRatio(1,1),
      //ChromaFmt(DT_CHROMAFMT_NONE),
      NumSymPerPixel(0)
{
    Init(Fmt);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::Fmt_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
PixelFormat PixelFormatProps::Fmt_Get() const
{ 
    return Fmt; 
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsFmt -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::IsFmt(PixelFormat  Fmt) const
{
    return (Fmt == Fmt);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsValid -.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool  PixelFormatProps::IsValid() const
{ 
    return (Fmt!=PixelFormat::INVALID); 
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::Is8Bit -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::Is8Bit() const
{
    return IsValid() ? (SymbolSize==8) : false;
}
bool  PixelFormatProps::Is8Bit(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.Is8Bit();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::Is10Bit -.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool  PixelFormatProps::Is10Bit() const
{
    return IsValid() ? (SymbolSize==10) : false;
}
bool  PixelFormatProps::Is10Bit(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.Is10Bit();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::Is16Bit -.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool  PixelFormatProps::Is16Bit() const
{
    return IsValid() ? (SymbolSize==16) : false;
}
bool  PixelFormatProps::Is16Bit(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.Is16Bit();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsRgb -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::IsRgb() const
{
    if (!IsValid())
        return false;

    switch(Fmt)
    {
    case PixelFormat::BGR_8B:
    case PixelFormat::BGR_10B:
    case PixelFormat::BGR_16B:
        return true;
    }

    return false;
}
bool  PixelFormatProps::IsRgb(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsRgb();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsUyvy -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::IsUyvy() const
{
    if (!IsValid())
        return false;

    switch(Fmt)
    {
    case PixelFormat::UYVY422_8B:
    case PixelFormat::UYVY422_10B:
    case PixelFormat::UYVY422_16B:
        return true;
    }

    return false;
}
bool  PixelFormatProps::IsUyvy(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsUyvy();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsV210 -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::IsV210() const
{
    if (!IsValid())
        return false;
    return (Fmt == PixelFormat::V210);
}
bool  PixelFormatProps::IsV210(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsV210();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsY -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool  PixelFormatProps::IsY() const
{
    if (!IsValid())
        return false;

    switch(Fmt)
    {
    case PixelFormat::Y_8B:
    case PixelFormat::Y_10B:
    case PixelFormat::Y_16B:
        return true;
    }

    return false;
}
bool  PixelFormatProps::IsY(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsY();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsYuv420P2 -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::IsYuv420P2() const
{
    if (!IsValid())
        return false;

    switch(Fmt)
    {
    case PixelFormat::YUV420P2_8B:
    case PixelFormat::YUV420P2_10B:
    case PixelFormat::YUV420P2_16B:
        return true;
    }

    return false;
}
bool  PixelFormatProps::IsYuv420P2(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsYuv420P2();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsYuv422P -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::IsYuv422P() const
{
    if (!IsValid())
        return false;

    switch(Fmt)
    {
    case PixelFormat::YUV422P_8B:
    case PixelFormat::YUV422P_10B:
    case PixelFormat::YUV422P_16B:
        return true;
    }

    return false;
}
bool  PixelFormatProps::IsYuv422P(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsYuv422P();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsYuv422P2 -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::IsYuv422P2() const
{
    if (!IsValid())
        return false;

    switch(Fmt)
    {
    case PixelFormat::YUV422P2_8B:
    case PixelFormat::YUV422P2_10B:
    case PixelFormat::YUV422P2_16B:
        return true;
    }

    return false;
}
bool  PixelFormatProps::IsYuv422P2(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsYuv422P2();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsYuyv -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool  PixelFormatProps::IsYuyv() const
{
    if (!IsValid())
        return false;

    switch(Fmt)
    {
    case PixelFormat::YUYV422_8B:
    case PixelFormat::YUYV422_10B:
    case PixelFormat::YUYV422_16B:
        return true;
    }

    return false;
}
bool  PixelFormatProps::IsYuyv(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsYuyv();
}


// -.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsPacked -.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool  PixelFormatProps::IsPacked() const
{
    // If the format only has one plane it is packed
    return IsValid() ? (Planes.size()==1) : false;
}
bool  PixelFormatProps::IsPacked(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsPacked();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::IsPlanar -.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool  PixelFormatProps::IsPlanar() const
{
    // If the format has more than one plane it is planar
    return IsValid() ? (Planes.size()>1) : false;
}
bool  PixelFormatProps::IsPlanar(PixelFormat  Fmt)
{
    PixelFormatProps  Props(Fmt);
    return Props.IsPlanar();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::ToName -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
const char* PixelFormatProps::ToName() const
{
    switch(Fmt)
    {
    case PixelFormat::UYVY422_8B:       return "UYVY422_8B";
    case PixelFormat::UYVY422_10B:      return "UYVY422_10B";
    case PixelFormat::UYVY422_16B:      return "UYVY422_16B";
    case PixelFormat::UYVY422_10B_NBO:  return "UYVY422_10B_NBO";
    case PixelFormat::YUYV422_8B:       return "YUYV422_8B";
    case PixelFormat::YUYV422_10B:      return "YUYV422_10B";
    case PixelFormat::YUYV422_16B:      return "YUYV422_16B";
    case PixelFormat::Y_8B:             return "Y_8B";
    case PixelFormat::Y_16B:            return "Y_16B";
    case PixelFormat::YUV422P_8B:       return "YUV422P_8B";
    case PixelFormat::YUV422P_16B:      return "YUV422P_16B";
    case PixelFormat::YUV422P2_8B:      return "YUV422P2_8B";
    case PixelFormat::YUV422P2_16B:     return "YUV422P2_16B";
    case PixelFormat::YUV420P2_8B:      return "YUV420P2_8B";
    case PixelFormat::BGR_8B:           return "BGR_8B";
    case PixelFormat::BGRX_8B:          return "BGRX_8B";
    case PixelFormat::V210:             return "V210";
    case PixelFormat::Y_10B:            return "Y_10B";
    case PixelFormat::YUV422P_10B:      return "YUV422P_10B";
    case PixelFormat::YUV422P2_10B:     return "YUV422P2_10B";
    case PixelFormat::YUV420P2_10B:     return "YUV420P2_10B";
    case PixelFormat::YUV420P2_16B:     return "YUV420P2_16B";
    case PixelFormat::BGR_10B:          return "BGR_10B";
    case PixelFormat::BGR_16B:          return "BGR_16B";
    case PixelFormat::BGRX_10B:         return "BGRX_10B";
    case PixelFormat::BGRX_16B:         return "BGRX_16B";
    case PixelFormat::PLANE_Y:          return "PLANE_Y";
    case PixelFormat::PLANE_U:          return "PLANE_U";
    case PixelFormat::PLANE_V:          return "PLANE_V";
    case PixelFormat::PLANE_UV:         return "PLANE_UV";
    case PixelFormat::INVALID:          return "INVALID";
    }
    assert(false);
    return "???";
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::Init -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void  PixelFormatProps::Init(PixelFormat Fmt)
{
    // Init to safe initial values
    Fmt = Fmt;
    //ChromaFmt = DT_CHROMAFMT_NONE;
    NumSymPerPixel = 0;
    Planes.clear();
    SymbolSize = 0;

    if (Fmt == PixelFormat::INVALID)
        return;

    switch(Fmt)
    {
    case PixelFormat::UYVY422_8B:
    case PixelFormat::UYVY422_10B:
    case PixelFormat::UYVY422_16B:
        if (Fmt == PixelFormat::UYVY422_8B)         SymbolSize = 8;
        else if (Fmt == PixelFormat::UYVY422_10B)   SymbolSize = 10;
        else if (Fmt == PixelFormat::UYVY422_16B)   SymbolSize = 16;
        assert(SymbolSize > 0);

        //ChromaFmt = DT_CHROMAFMT_422;
        NumSymPerPixel = 2;
        SymbolPackRatio = Fraction(SymbolSize, SymbolSize);
        Planes.push_back(Fmt);
        break;

    case PixelFormat::YUYV422_8B:
    case PixelFormat::YUYV422_10B:
    case PixelFormat::YUYV422_16B:
        if (Fmt == PixelFormat::YUYV422_8B)         SymbolSize = 8;
        else if (Fmt == PixelFormat::YUYV422_10B)   SymbolSize = 10;
        else if (Fmt == PixelFormat::YUYV422_16B)   SymbolSize = 16;
        assert(SymbolSize > 0);
    
        //ChromaFmt = DT_CHROMAFMT_422;
        NumSymPerPixel = 2;
        SymbolPackRatio = Fraction(SymbolSize, SymbolSize);
        Planes.push_back(Fmt);
        break;
    
    case PixelFormat::V210:
        SymbolSize = 10;
        //ChromaFmt = DT_CHROMAFMT_422;
        NumSymPerPixel = 2;
        SymbolPackRatio = Fraction(30, 32);
        Planes.push_back(Fmt);
        break;
    
    case PixelFormat::YUV420P2_8B:
    case PixelFormat::YUV420P2_10B:
    case PixelFormat::YUV420P2_16B:
        if (Fmt == PixelFormat::YUV420P2_8B)        SymbolSize = 8;
        else if (Fmt == PixelFormat::YUV420P2_10B)  SymbolSize = 10;
        else if (Fmt == PixelFormat::YUV420P2_16B)  SymbolSize = 16;
        assert(SymbolSize > 0);
    
        //ChromaFmt = DT_CHROMAFMT_420;
        NumSymPerPixel = 2;
        SymbolPackRatio = Fraction(SymbolSize, SymbolSize);
        Planes.push_back(PixelFormat::PLANE_Y);
        Planes.push_back(PixelFormat::PLANE_UV);
        break;
    
    case PixelFormat::YUV422P2_8B:
    case PixelFormat::YUV422P2_10B:
    case PixelFormat::YUV422P2_16B:
        if (Fmt == PixelFormat::YUV422P2_8B)        SymbolSize = 8;
        else if (Fmt == PixelFormat::YUV422P2_10B)  SymbolSize = 10;
        else if (Fmt == PixelFormat::YUV422P2_16B)  SymbolSize = 16;
        assert(SymbolSize > 0);
    
        //ChromaFmt = DT_CHROMAFMT_422;
        NumSymPerPixel = 2;
        SymbolPackRatio = Fraction(SymbolSize, SymbolSize);
        Planes.push_back(PixelFormat::PLANE_Y);
        Planes.push_back(PixelFormat::PLANE_UV);
        break;
    
    case PixelFormat::YUV422P_8B:
    case PixelFormat::YUV422P_10B:
    case PixelFormat::YUV422P_16B:
        if (Fmt == PixelFormat::YUV422P_8B)        SymbolSize = 8;
        else if (Fmt == PixelFormat::YUV422P_10B)  SymbolSize = 10;
        else if (Fmt == PixelFormat::YUV422P_16B)  SymbolSize = 16;
        assert(SymbolSize > 0);
    
        //ChromaFmt = DT_CHROMAFMT_422;
        NumSymPerPixel = 2;
        SymbolPackRatio = Fraction(SymbolSize, SymbolSize);
        Planes.push_back(PixelFormat::PLANE_Y);
        Planes.push_back(PixelFormat::PLANE_U);
        Planes.push_back(PixelFormat::PLANE_V);
        break;
    
    case PixelFormat::BGR_8B:
    case PixelFormat::BGR_10B:
    case PixelFormat::BGR_16B:
        if (Fmt == PixelFormat::BGR_8B)         SymbolSize = 8;
        else if (Fmt == PixelFormat::BGR_10B)   SymbolSize = 10;
        else if (Fmt == PixelFormat::BGR_16B)   SymbolSize = 16;
        assert(SymbolSize > 0);
    
        //ChromaFmt = DT_CHROMAFMT_444;
        NumSymPerPixel = 3;
        SymbolPackRatio = Fraction(SymbolSize, SymbolSize);
        Planes.push_back(Fmt);
        break;
    
    case PixelFormat::BGRX_8B:
    case PixelFormat::BGRX_10B:
    case PixelFormat::BGRX_16B:
        if (Fmt == PixelFormat::BGRX_8B)         SymbolSize = 8;
        else if (Fmt == PixelFormat::BGRX_10B)   SymbolSize = 10;
        else if (Fmt == PixelFormat::BGRX_16B)   SymbolSize = 16;
        assert(SymbolSize > 0);
    
        //ChromaFmt = DT_CHROMAFMT_NONE;
        NumSymPerPixel = 4;
        SymbolPackRatio = Fraction(SymbolSize, SymbolSize);
        Planes.push_back(Fmt);
        break;
    
    case PixelFormat::Y_8B:
    case PixelFormat::Y_10B:
    case PixelFormat::Y_16B:
        if (Fmt == PixelFormat::Y_8B)           SymbolSize = 8;
        else if (Fmt == PixelFormat::Y_10B)     SymbolSize = 10;
        else if (Fmt == PixelFormat::Y_16B)     SymbolSize = 16;
        assert(SymbolSize > 0);
    
        //ChromaFmt = DT_CHROMAFMT_422;
        NumSymPerPixel = 1;
    
        SymbolPackRatio = Fraction(SymbolSize, SymbolSize);
        Planes.push_back(PixelFormat::PLANE_Y);
        break;

    default:
        Fmt = PixelFormat::INVALID;  // Mark as invalid
        break;
    }
    assert(Fmt != PixelFormat::INVALID);
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::NumPlanes -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
int  PixelFormatProps::NumPlanes() const
{
    return IsValid() ? static_cast<int>(Planes.size()) : 0;
}

// .-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::operator== -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool PixelFormatProps::operator==(const PixelFormatProps&  Oth) const
{
    if (this == &Oth)
        return true;

    return (/*ChromaFmt==Oth.ChromaFmt && Fmt==Oth.Fmt 
           &&*/ NumSymPerPixel==Oth.NumSymPerPixel && Planes==Oth.Planes 
           && SymbolPackRatio==Oth.SymbolPackRatio && SymbolSize==Oth.SymbolSize);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.- PixelFormatProps::operator!= -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool PixelFormatProps::operator!=(const PixelFormatProps&  Oth) const
{
    return !(*this == Oth);
}

};  // namespace DtSdi
