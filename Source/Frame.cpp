// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* Frame.cpp *#*#*#*#*#*#*#*#*#*#*# (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include "SdiFrameBuilder.h"

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
    V.LineSizeInBytes = FP.LineSizeInBytes(RawFrame->PxFmt_Get());

    for (const auto& Fld : FP.Fields)
    {
        uint8_t* Line = RawFrame->Data() + (V.LineSizeInBytes * (Fld.FirstLineVideo-1));
        Line += FP.LineSizeInBytes_Hanc(RawFrame->PxFmt_Get());
        for (size_t l=Fld.FirstLineVideo; l<=Fld.LastLineVideo; l++)
        {
            V.Lines.push_back(Line);
            Line += V.LineSizeInBytes;
            assert(Line < (RawFrame->Data() + RawFrame->Size()));
        }
    }
}

};  // namespace DtSdi