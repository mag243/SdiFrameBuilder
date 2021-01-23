// *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* FrameProperties.cpp *#*#*#*#*#*#*#*#* (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include <map>
#include "SdiFrameBuilder.h"

using namespace std;

namespace DtSdi
{

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+ FrameProperties implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+=
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// .-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::FrameProperties -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
FrameProperties::FrameProperties(VideoStandard Std)
{
    Init(Std);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::Init -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool FrameProperties::Init(VideoStandard Std)
{
    // Invalidate properties
    VidStd = VideoStandard::STD_UNKNOWN;
    Fields.clear();
    LineNumSymEav = LineNumSymHanc = LineNumSymSav = LineNumSymVanc = 0;
    VideoWidth = VideoHeight = 0;
    Fps = ToFramePerSecond(Std);

    switch (Std)
    {
    case VideoStandard::STD_525I59_94:
        Fields.resize(2);

        Fields[0].FirstLine         = 1;        Fields[0].LastLine          = 262;
        Fields[0].FirstLineVideo    = 17;       Fields[0].LastLineVideo     = 260;
        Fields[0].SwitchingLine     = 7;

        Fields[1].FirstLine         = 263;      Fields[1].LastLine          = 525;
        Fields[1].FirstLineVideo    = 280;      Fields[1].LastLineVideo     = 522;
        Fields[1].SwitchingLine     = 270;

        LineNumSymEav = 4;
        LineNumSymHanc = 268;
        LineNumSymSav = 4;
        LineNumSymVanc = 720*2;
        break;

    case VideoStandard::STD_625I50:
        Fields.resize(2);

        Fields[0].FirstLine         = 1;        Fields[0].LastLine          = 312;
        Fields[0].FirstLineVideo    = 23;       Fields[0].LastLineVideo     = 310;
        Fields[0].SwitchingLine     = 6;

        Fields[1].FirstLine         = 313;      Fields[1].LastLine          = 625;
        Fields[1].FirstLineVideo    = 336;      Fields[1].LastLineVideo     = 623;
        Fields[1].SwitchingLine     = 319;

        LineNumSymEav = 4;
        LineNumSymHanc = 280;
        LineNumSymSav = 4;
        LineNumSymVanc = 720*2;
        break;

    case VideoStandard::STD_1080P60:
    case VideoStandard::STD_1080P60B:
    case VideoStandard::STD_1080P59_94:
    case VideoStandard::STD_1080P59_94B:
    case VideoStandard::STD_1080P50:
    case VideoStandard::STD_1080P50B:
        Fields.resize(1);

        Fields[0].FirstLine         = 1;        Fields[0].LastLine          = 1125;
        Fields[0].FirstLineVideo    = 42;       Fields[0].LastLineVideo     = 1121;
        Fields[0].SwitchingLine     = 7;

        LineNumSymEav = 8*2;
        if (Fps.Num==60 || Fps.Num==60000)
            LineNumSymHanc = 268*2;
        else if (Fps.Num==50)
            LineNumSymHanc = 708*2;
        else
            assert(false);

        LineNumSymSav = 4*2;
        LineNumSymVanc = 1920*2;
        break;

    case VideoStandard::STD_1080P30:
    case VideoStandard::STD_1080P29_97:
    case VideoStandard::STD_1080P25:
    case VideoStandard::STD_1080P24:
    case VideoStandard::STD_1080P23_98:
        Fields.resize(1);

        Fields[0].FirstLine         = 1;        Fields[0].LastLine          = 1125;
        Fields[0].FirstLineVideo    = 42;       Fields[0].LastLineVideo     = 1121;
        Fields[0].SwitchingLine     = 7;

        LineNumSymEav = 8*2;
        if (Fps.Num==30 || Fps.Num==30000)
            LineNumSymHanc = 268*2;
        else if (Fps.Num==25)
            LineNumSymHanc = 708*2;
        if (Fps.Num==24 || Fps.Num==24000)
            LineNumSymHanc = 818*2;
        else
            assert(false);
        
        LineNumSymSav = 4*2;
        LineNumSymVanc = 1920*2;
        break;

    case VideoStandard::STD_1080I60:
    case VideoStandard::STD_1080I59_94:
    case VideoStandard::STD_1080I50:
        Fields.resize(2);

        Fields[0].FirstLine         = 1;        Fields[0].LastLine          = 563;
        Fields[0].FirstLineVideo    = 21;       Fields[0].LastLineVideo     = 560;
        Fields[0].SwitchingLine     = 7;

        Fields[1].FirstLine         = 564;      Fields[1].LastLine          = 1125;
        Fields[1].FirstLineVideo    = 584;      Fields[1].LastLineVideo     = 1123;
        Fields[1].SwitchingLine     = 569;

         LineNumSymEav = 8*2;
        if (Fps.Num==30 || Fps.Num==30000)
            LineNumSymHanc = 268*2;
        else if (Fps.Num==25)
            LineNumSymHanc = 708*2;
        else
            assert(false);

        LineNumSymSav = 4*2;
        LineNumSymVanc = 1920*2;
        break;

    case VideoStandard::STD_720P60:
    case VideoStandard::STD_720P59_94:
    case VideoStandard::STD_720P50:
    case VideoStandard::STD_720P30:
    case VideoStandard::STD_720P29_97:
    case VideoStandard::STD_720P25:
    case VideoStandard::STD_720P24:
    case VideoStandard::STD_720P23_98:
        Fields.resize(1);

        Fields[0].FirstLine         = 1;        Fields[0].LastLine          = 750;
        Fields[0].FirstLineVideo    = 26;       Fields[0].LastLineVideo     = 745;
        Fields[0].SwitchingLine     = 7;

        LineNumSymEav = 8*2;
        if (Fps.Num==60 || Fps.Num==60000)
            LineNumSymHanc = 358*2;
        else if (Fps.Num==50)
            LineNumSymHanc = 688*2;
        else if (Fps.Num==30 || Fps.Num==30000)
            LineNumSymHanc = 2008*2;
        else if (Fps.Num==25)
            LineNumSymHanc = 2668*2;
        else if (Fps.Num==24 || Fps.Num==24000)
            LineNumSymHanc = 2833*2;
        else
            assert(false);

        LineNumSymSav = 4*2;
        LineNumSymVanc = 1280*2;
        break;

    default:
        assert(false);
        return false;
    }
    VidStd = Std;


    VideoWidth = LineNumSymVanc / 2;
    VideoHeight = 0;
    for (const auto& F : Fields)
        VideoHeight += F.NumLinesVideo();

    return true;
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::IsInterlaced -.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool FrameProperties::IsInterlaced() const 
{ 
    return (Fields.size()>1); 
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::IsVanc -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
bool FrameProperties::IsVanc(size_t Line) const
{
    for (const auto& F : Fields)
    {
        if (F.IsVanc(Line))
            return true;
    }
    return false;
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::IsSd -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool FrameProperties::IsSd() const
{
    return (VidStd==VideoStandard::STD_525I59_94 || VidStd==VideoStandard::STD_625I50);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::IsHd -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool FrameProperties::IsHd() const
{
    switch (VidStd)
    {
    case DtSdi::VideoStandard::STD_720P23_98:
    case DtSdi::VideoStandard::STD_720P24:
    case DtSdi::VideoStandard::STD_720P25:
    case DtSdi::VideoStandard::STD_720P29_97:
    case DtSdi::VideoStandard::STD_720P30:
    case DtSdi::VideoStandard::STD_720P50:
    case DtSdi::VideoStandard::STD_720P59_94:
    case DtSdi::VideoStandard::STD_720P60:
    case DtSdi::VideoStandard::STD_1080P23_98:
    case DtSdi::VideoStandard::STD_1080P24:
    case DtSdi::VideoStandard::STD_1080P25:
    case DtSdi::VideoStandard::STD_1080P29_97:
    case DtSdi::VideoStandard::STD_1080P30:
    case DtSdi::VideoStandard::STD_1080P50:
    case DtSdi::VideoStandard::STD_1080P50B:
    case DtSdi::VideoStandard::STD_1080P59_94:
    case DtSdi::VideoStandard::STD_1080P59_94B:
    case DtSdi::VideoStandard::STD_1080P60:
    case DtSdi::VideoStandard::STD_1080P60B:
    case DtSdi::VideoStandard::STD_1080I50:
    case DtSdi::VideoStandard::STD_1080I59_94:
    case DtSdi::VideoStandard::STD_1080I60:
        return true;
    }
    return false;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::IsUhd -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
bool FrameProperties::IsUhd() const
{
    switch (VidStd)
    {
    case DtSdi::VideoStandard::STD_2160P23_98:
    case DtSdi::VideoStandard::STD_2160P24:
    case DtSdi::VideoStandard::STD_2160P25:
    case DtSdi::VideoStandard::STD_2160P29_97:
    case DtSdi::VideoStandard::STD_2160P30:
    case DtSdi::VideoStandard::STD_2160P50:
    case DtSdi::VideoStandard::STD_2160P50B:
    case DtSdi::VideoStandard::STD_2160P59_94:
    case DtSdi::VideoStandard::STD_2160P59_94B:
    case DtSdi::VideoStandard::STD_2160P60:
    case DtSdi::VideoStandard::STD_2160P60B:
        return true;
    }
    return false;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::Line2Field -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
size_t FrameProperties::Line2Field(size_t Line) const
{
    if (Line<1 || Line>NumLines_Get())
        return -1;
    return Fields[0].IsLineInField(Line) ? 1 : 2;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::LineNumSymbols -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
size_t FrameProperties::LineNumSymbols_Get() const
{
    return (LineNumSymEav + LineNumSymHanc + LineNumSymSav + LineNumSymVanc);
}

// .-.-.-.-.-.-.-.-.-.-.- FrameProperties::LineNumSymbols_Hanc_Get -.-.-.-.-.-.-.-.-.-.-.-
//
size_t FrameProperties::LineNumSymbols_Hanc_Get(bool IncludeEavSav) const
{
    size_t NumSyms = LineNumSymHanc;
    NumSyms += IncludeEavSav ? (LineNumSymEav+LineNumSymSav) : 0;
    return NumSyms;
}

// .-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::LineSizeInBytes -.-.-.-.-.-.-.-.-.-.-.-.-.-
//
size_t FrameProperties::LineNumBytes_Get(PixelFormat Fmt) const
{
    PixelFormatProps PP(Fmt);
    return (((LineNumSymbols_Get() * PP.SymbolSize) + 7) / 8);
}
size_t FrameProperties::LineNumBytes_Hanc_Get(PixelFormat Fmt, bool IncludeEavSav)
{
    PixelFormatProps PP(Fmt);
    size_t NumSymbols = LineNumSymbols_Hanc_Get(IncludeEavSav);
    return (((NumSymbols * PP.SymbolSize) + 7) / 8);
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::NumLines -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
size_t FrameProperties::NumLines_Get() const
{
    size_t TotalNumLines = 0;
    for (const auto& F : Fields)
        TotalNumLines += F.NumLines();
    return TotalNumLines;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::NumSymbols -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
size_t FrameProperties::NumSymbols_Get() const
{
    return NumLines_Get() * LineNumSymbols_Get();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.- FrameProperties::SizeInBytes -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
size_t FrameProperties::SizeInBytes(PixelFormat Fmt) const
{
    return NumLines_Get() * LineNumBytes_Get(Fmt);
}

Fraction FrameProperties::ToFramePerSecond(VideoStandard Std)
{
    switch (Std)
    {
            // 23.98fps
    case VideoStandard::STD_720P23_98:
    case VideoStandard::STD_1080P23_98:
    //case VideoStandard::STD_1080PSF23_98:
    case VideoStandard::STD_2160P23_98:
        return Fraction(24000, 1001);

        // 24fps
    case VideoStandard::STD_720P24:
    case VideoStandard::STD_1080P24:
    //case VideoStandard::STD_1080PSF24:
    case VideoStandard::STD_2160P24:
        return Fraction(24000, 1000);

        // 25fps
    case VideoStandard::STD_625I50:
    case VideoStandard::STD_1080I50:
    case VideoStandard::STD_720P25:
    case VideoStandard::STD_1080P25:
    //case VideoStandard::STD_1080PSF25:
    case VideoStandard::STD_2160P25:
        return Fraction(25000, 1000);

        // 29.97fps
    case VideoStandard::STD_525I59_94:
    case VideoStandard::STD_1080I59_94:
    case VideoStandard::STD_720P29_97:
    case VideoStandard::STD_1080P29_97:
    //case VideoStandard::STD_1080PSF29_97:
    case VideoStandard::STD_2160P29_97:
        return Fraction(30000, 1001);

        // 30fps
    case VideoStandard::STD_720P30:
    case VideoStandard::STD_1080I60:
    case VideoStandard::STD_1080P30:
    //case VideoStandard::STD_1080PSF30:
    case VideoStandard::STD_2160P30:
        return Fraction(30000, 1000);

        // 50fps
    case VideoStandard::STD_720P50:
    case VideoStandard::STD_1080P50:
    case VideoStandard::STD_1080P50B:
    case VideoStandard::STD_2160P50:
    case VideoStandard::STD_2160P50B:
        return Fraction(50000, 1000);

        // 59.94fps
    case VideoStandard::STD_720P59_94:
    case VideoStandard::STD_1080P59_94:
    case VideoStandard::STD_1080P59_94B:
    case VideoStandard::STD_2160P59_94:
    case VideoStandard::STD_2160P59_94B:
        return Fraction(60000, 1001);

        // 60fps
    case VideoStandard::STD_720P60:
    case VideoStandard::STD_1080P60:
    case VideoStandard::STD_1080P60B:
    case VideoStandard::STD_2160P60:
    case VideoStandard::STD_2160P60B:
        return Fraction(60000, 1000);

        // Unknown video standard
    default:  assert(false); break;
    }
    return Fraction(0,1);
}

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+ FrameProperties::FieldProperties implementation +=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// -.-.-.-.-.-.-.-.-.- FrameProperties::FieldProperties::IsLineInField -.-.-.-.-.-.-.-.-.-
//
bool FrameProperties::FieldProperties::IsLineInField(size_t Line) const
{
    return (Line>=FirstLine && Line<=LastLine);
}

// .-.-.-.-.-.-.-.-.-.-.- FrameProperties::FieldProperties::IsVideo -.-.-.-.-.-.-.-.-.-.-.
//
bool FrameProperties::FieldProperties::IsVideo(size_t Line) const
{
    return (Line>=FirstLineVideo && Line<=LastLineVideo);
}
bool FrameProperties::FieldProperties::IsVanc(size_t Line) const
{
    return IsLineInField(Line) && !IsVideo(Line);
}

// -.-.-.-.-.-.-.-.-.-.- FrameProperties::FieldProperties::NumLines -.-.-.-.-.-.-.-.-.-.-.
//
size_t FrameProperties::FieldProperties::NumLines() const 
{ 
    return (LastLine-FirstLine) + 1;
}
// -.-.-.-.-.-.-.-.-.- FrameProperties::FieldProperties::NumLinesVideo -.-.-.-.-.-.-.-.-.-
//
size_t FrameProperties::FieldProperties::NumLinesVideo() const 
{ 
    return (LastLineVideo-FirstLineVideo) + 1; 
}

};  // namespace DtSdi
