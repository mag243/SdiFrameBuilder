// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* Frame.cpp *#*#*#*#*#*#*#*#*#*#*# (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include "SdiFrameBuilder.h"
#include "SymbolPtr.h"

namespace DtSdi
{

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Frame implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Frame -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
Frame::Frame(VideoStandard Std, PixelFormat Fmt)
{
    RawFrame = IFrameBuffer::Make(Std, Fmt);
}
Frame::Frame(VideoStandard Std, PixelFormat Fmt, size_t Size)
{
    RawFrame = IFrameBuffer::Make(Std, Fmt, Size);
}
Frame::Frame(VideoStandard Std, PixelFormat Fmt, uint8_t* Data, size_t Size)
{
    RawFrame = IFrameBuffer::Make(Std, Fmt, Data, Size);
}
Frame::Frame(FrameBuffer&& FrmBuf) : RawFrame(std::move(FrmBuf))
{
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Clone -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void Frame::Clone(const Frame& OthFrame)
{
    Clone(OthFrame.RawFrame);
}
void Frame::Clone(const FrameBuffer& OthBuf)
{
    RawFrame = IFrameBuffer::Make(OthBuf->Standard(), OthBuf->PxFmt_Get(),
                                                                          OthBuf->Size());
    std::memcpy(RawFrame->Data(), OthBuf->Data(), OthBuf->Size());
    Parse();
}


// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Commit -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void Frame::Commit()
{
    if (!IsDirty)
        return;
    IsDirty = false;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Data -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
uint8_t* Frame::Data() const
{
    if (RawFrame == nullptr)
        return nullptr;
    return RawFrame->Data();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Parse -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame::Parse()
{
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Props_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
FrameProperties Frame::Props_Get() const
{
    FrameProperties  FP;
    FP.Init(RawFrame->Standard());
    return FP;
}

PixelFormat Frame::PxFmt_Get() const
{
    if (RawFrame == nullptr)
        return PixelFormat::INVALID;
    return RawFrame->PxFmt_Get();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Size -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
size_t Frame::Size() const
{
    if (RawFrame==nullptr || RawFrame->Data()==nullptr)
        return 0;
    return RawFrame->Size();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Swap -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame::Swap(FrameBuffer& NewFrame)
{
    Commit();
    RawFrame.swap(NewFrame);
    Parse();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Anc_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void Frame::Anc_Get(void)
{
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Audio_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame::Audio_Get(void)
{
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame::Video_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame::Video_Get(Video& V) const
{
    FrameProperties  FP(RawFrame->Standard());

    V.Lines.clear();

    V.PxFmt = RawFrame->PxFmt_Get();
    V.Width = FP.VideoWidth;
    V.Height = FP.VideoHeight;
    V.LineSizeInBytes = FP.LineNumBytes_Get(RawFrame->PxFmt_Get());

    for (const auto& Fld : FP.Fields)
    {
        uint8_t* Line = RawFrame->Data() + (V.LineSizeInBytes * (Fld.FirstLineVideo-1));
        Line += FP.LineNumBytes_Hanc_Get(RawFrame->PxFmt_Get());
        for (size_t l=Fld.FirstLineVideo; l<=Fld.LastLineVideo; l++)
        {
            V.Lines.push_back(Line);
            Line += V.LineSizeInBytes;
            assert(Line < (RawFrame->Data() + RawFrame->Size()));
        }
    }
}

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Frame_Raw implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Raw::Frame_Raw -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
Frame_Raw::Frame_Raw(VideoStandard Std, PixelFormat Fmt)
{
    FrameBuf = IFrameBuffer::Make(Std, Fmt);
}
Frame_Raw::Frame_Raw(VideoStandard Std, PixelFormat Fmt, size_t Size)
{
    FrameBuf = IFrameBuffer::Make(Std, Fmt, Size);
}
Frame_Raw::Frame_Raw(VideoStandard Std, PixelFormat Fmt, uint8_t* Data, size_t Size)
{
    FrameBuf = IFrameBuffer::Make(Std, Fmt, Data, Size);
}
Frame_Raw::Frame_Raw(FrameBuffer&& FrmBuf) : FrameBuf(std::move(FrmBuf))
{
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Raw::Data -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
uint8_t* Frame_Raw::Data() const
{
    if (FrameBuf == nullptr)
        return nullptr;
    return FrameBuf->Data();
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Raw::Props_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
FrameProperties Frame_Raw::Props_Get() const
{
    FrameProperties  FP;
    FP.Init(FrameBuf->Standard());
    return FP;
}

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Raw::PxFmt_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
PixelFormat Frame_Raw::PxFmt_Get() const
{
    if (FrameBuf == nullptr)
        return PixelFormat::INVALID;
    return FrameBuf->PxFmt_Get();
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Raw::Size -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
size_t Frame_Raw::Size() const
{
    if (FrameBuf == nullptr)
        return 0;
    return FrameBuf->Size();
}

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Frame_Parsed implementation +=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Parsed::Anc_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
void Frame_Parsed::Anc_Get() const
{
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Parsed::Audio_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame_Parsed::Audio_Get(void) const
{
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Parsed::Video_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame_Parsed::Video_Get(Video&) const
{
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Parsed::Parse -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame_Parsed::Parse(const Frame_Raw& RawFrame)
{
    // Get frame properties
    FrameProps = RawFrame.Props_Get();

    Split(RawFrame);
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Parsed::Props_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
const FrameProperties& Frame_Parsed::Props_Get() const
{
    return FrameProps;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Parsed::PxFmt_Get -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
PixelFormat Frame_Parsed::PxFmt_Get() const
{
    return PixelFormat::INVALID;
}

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Frame_Parsed::Split -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
void Frame_Parsed::Split(const Frame_Raw& RawFrame)
{
    const FrameProperties FP = RawFrame.Props_Get();

    if (FP.IsSd())
        Split_SD(RawFrame, FP);
    else if (FP.IsHd())
        Split_HD(RawFrame, FP);
    else if (FP.IsUhd())
        Split_UHD(RawFrame, FP);
}
void Frame_Parsed::Split_SD(const Frame_Raw& RawFrame, const FrameProperties& FP)
{

}
void Frame_Parsed::Split_HD(const Frame_Raw& RawFrame, const FrameProperties& FP)
{
    const PixelFormatProps PP(RawFrame.PxFmt_Get());
    static const std::vector<SymbolStreamType> HancVancStreams = 
    {
        SymbolStreamType::CHROM0, SymbolStreamType::LUMA0,
    };

    // Split HANC
    HancStreams.clear();
    const auto NumSymbolsHanc = FP.LineNumSymbols_Hanc_Get() * FP.NumLines_Get();
    for (const auto& S : HancVancStreams)
        HancStreams[S].reserve(NumSymbolsHanc/2);

    VancStreams.clear();
    const auto NumSymbolsVanc = FP.LineNumSymVanc * (FP.NumLines_Get()-FP.VideoHeight);
    for (const auto& S : HancVancStreams)
        VancStreams[S].reserve(NumSymbolsVanc/2);

    const auto NumSymbolsVideo = FP.LineNumSymVanc * FP.VideoHeight;
    VideoStreams.clear();
    VideoStreams[SymbolStreamType::VIDEO0].Init(FP.VideoHeight, FP.LineNumSymVanc);

    const uint16_t* Line = reinterpret_cast<uint16_t*>(RawFrame.Data());
    size_t VideoLineIndex=0;
    for (size_t l=0; l<FP.NumLines_Get(); l++)
    {
        for (size_t i=0; i<FP.LineNumSymbols_Hanc_Get(); i+=2)
        {
            HancStreams[SymbolStreamType::CHROM0].push_back(*Line++);
            HancStreams[SymbolStreamType::LUMA0].push_back(*Line++);
        }
        if (FP.IsVanc(l+1))
        {
            for (size_t i=0; i<FP.LineNumSymVanc; i+=2)
            {
                VancStreams[SymbolStreamType::CHROM0].push_back(*Line++);
                VancStreams[SymbolStreamType::LUMA0].push_back(*Line++);
            }
        }
        else
        {
            VideoStreams[SymbolStreamType::VIDEO0].Copy(VideoLineIndex++, Line, FP.LineNumSymVanc);
            Line += FP.LineNumSymVanc;
        }
    }
}
void Frame_Parsed::Split_UHD(const Frame_Raw& RawFrame, const FrameProperties& FP)
{
}

};  // namespace DtSdi