// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* SdiFrameBuilder.h *#*#*#*#*#*#*#*#*# (C) 2021 DekTec
//

#pragma once

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include <memory>
#include <stdint.h>
#include <vector>
#include <map>

namespace DtSdi
{

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class AncPacket +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
class AncPacket
{
    // Operations
public:

};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ enum class PixelFormat +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
enum class PixelFormat : int
{
    INVALID=-1,
    UYVY422_8B,
    UYVY422_10B,
    UYVY422_16B,
    UYVY422_10B_NBO,
    YUYV422_8B,
    YUYV422_10B,
    YUYV422_16B,
    Y_8B,
    Y_16B,
    YUV422P_8B,
    YUV422P_16B,
    YUV422P2_8B,
    YUV422P2_16B,
    YUV420P2_8B,
    BGR_8B,
    BGRX_8B,
    V210,
    Y_10B,
    YUV422P_10B,
    YUV422P2_10B,
    YUV420P2_10B,
    YUV420P2_16B,
    BGR_10B,
    BGR_16B,
    BGRX_10B,
    BGRX_16B,
    PLANE_Y,
    PLANE_U,
    PLANE_V,
    PLANE_UV,
};

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ enum class VideoStandard +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
enum class VideoStandard : int
{
    STD_UNKNOWN=-1,
    STD_525I59_94,
    STD_625I50,
    STD_720P23_98,
    STD_720P24,
    STD_720P25,
    STD_720P29_97,
    STD_720P30,
    STD_720P50,
    STD_720P59_94,
    STD_720P60,
    STD_1080P23_98,
    STD_1080P24,
    STD_1080P25,
    STD_1080P29_97,
    STD_1080P30,
    STD_1080P50,
    STD_1080P50B,
    STD_1080P59_94,
    STD_1080P59_94B,
    STD_1080P60,
    STD_1080P60B,
    STD_1080I50,
    STD_1080I59_94,
    STD_1080I60,
    STD_2160P23_98,
    STD_2160P24,
    STD_2160P25,
    STD_2160P29_97,
    STD_2160P30,
    STD_2160P50,
    STD_2160P50B,
    STD_2160P59_94,
    STD_2160P59_94B,
    STD_2160P60,
    STD_2160P60B,
};

// -.-.-.-.-.-.-.-.-.-.-.-.-.-.- enum class SymbolStreamType -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
enum class SymbolStreamType : uint8_t
{
    NONE    = 0x00,

    // Streams
    CHROM0  = 0x01,
    LUMA0   = 0x02,
    CHROM1  = 0x04,
    LUMA1   = 0x08,
    CHROM2  = 0x10,
    LUMA2   = 0x20,
    CHROM3  = 0x40,
    LUMA3   = 0x80,

    // Sub-images
    VIDEO0 = CHROM0|LUMA0,
    VIDEO1 = CHROM1|LUMA1,
    VIDEO2 = CHROM2|LUMA2,
    VIDEO3 = CHROM3|LUMA3,
};
inline constexpr SymbolStreamType operator|(
                                     const SymbolStreamType& A, const SymbolStreamType& B)
{
    return static_cast<SymbolStreamType>(
                            static_cast<std::underlying_type<SymbolStreamType>::type>(A) 
                          | static_cast<std::underlying_type<SymbolStreamType>::type>(B));
}
inline constexpr SymbolStreamType& operator|=(
                                      SymbolStreamType& Self, const SymbolStreamType& Oth)
{
    Self = Self | Oth;
    return Self;
}
inline constexpr SymbolStreamType operator&(
                                     const SymbolStreamType& A, const SymbolStreamType& B)
{
    return static_cast<SymbolStreamType>(
                            static_cast<std::underlying_type<SymbolStreamType>::type>(A) 
                          & static_cast<std::underlying_type<SymbolStreamType>::type>(B));
}
inline constexpr SymbolStreamType& operator&=(
                                      SymbolStreamType& Self, const SymbolStreamType& Oth)
{
    Self = Self & Oth;
    return Self;
}
inline constexpr SymbolStreamType operator~(const SymbolStreamType& Self)
{
    return static_cast<SymbolStreamType>(
                        ~static_cast<std::underlying_type<SymbolStreamType>::type>(Self));
}

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ struct Fraction +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
struct Fraction
{
    int Num=0, Den=1;

    // Operations
    void Normalize();
    double ToDouble() const;
    bool operator==(const Fraction&) const;
    bool operator!=(const Fraction&) const;

    // Constructor
    Fraction(int N=0, int D=1);
};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class PixelFormatProps +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
class PixelFormatProps
{
    // Operations
public:
    PixelFormat Fmt_Get() const;
    bool  IsFmt(PixelFormat) const;
    bool  IsValid() const;
    void  Init(PixelFormat);
    int  NumPlanes() const;
    bool  Is8Bit() const;
    static bool  Is8Bit(PixelFormat);
    bool  Is10Bit() const;
    static bool  Is10Bit(PixelFormat);
    bool  Is16Bit() const;
    static bool  Is16Bit(PixelFormat);
    bool  IsRgb() const;
    static bool  IsRgb(PixelFormat);
    bool  IsUyvy() const;
    static bool  IsUyvy(PixelFormat);
    bool  IsV210() const;
    static bool  IsV210(PixelFormat);
    bool  IsY() const;
    static bool  IsY(PixelFormat);
    bool  IsYuv420P2() const;
    static bool  IsYuv420P2(PixelFormat);
    bool  IsYuv422P() const;
    static bool  IsYuv422P(PixelFormat);
    bool  IsYuv422P2() const;
    static bool  IsYuv422P2(PixelFormat);
    bool  IsYuyv() const;
    static bool  IsYuyv(PixelFormat);
    bool  IsPacked() const;
    static bool  IsPacked(PixelFormat);
    bool  IsPlanar() const;
    static bool  IsPlanar(PixelFormat);
    const char* ToName() const;
    bool operator==(const PixelFormatProps&) const;
    bool operator!=(const PixelFormatProps&) const;

// Data / Attributes
public:
    std::vector<PixelFormat> Planes;
    // Format of planes. Size indicates #planes
    //DtMxChromaFormat ChromaFmt;  // Chroma format
    int SymbolSize=0;           // Size of the symbols
    int NumSymPerPixel=0;       // #symbol in a pixel
    Fraction SymbolPackRatio;   // Packing ratio for symbols.
                                //  - Numerator is #usable bits
                                //  - Denumerator is #bits used
                                // e.g. V210 stores 3x10-bit symbols in 32-bit => 
                                // num=30 and denum=32
protected:
    PixelFormat Fmt;            // The overall pixel format

    // Constructor / Destructor
public:
    PixelFormatProps(PixelFormat Fmt=PixelFormat::INVALID);
};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class IFrameBuffer +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
using FrameBuffer = std::unique_ptr<class IFrameBuffer>;
class IFrameBuffer
{
    // Operations
public:
    virtual uint8_t* Data(void)=0;
    virtual VideoStandard Standard() const { return VidStd; }
    virtual PixelFormat PxFmt_Get() const { return PxFmt; }
    virtual size_t Size(void) const=0;

    static FrameBuffer Make(VideoStandard, PixelFormat);
    static FrameBuffer Make(VideoStandard, PixelFormat, size_t);
    static FrameBuffer Make(VideoStandard, PixelFormat, uint8_t*, size_t);

    // Data / Attributes
private:
    VideoStandard VidStd=VideoStandard::STD_UNKNOWN;
    PixelFormat PxFmt=PixelFormat::INVALID;

    // Constructor
protected:
    IFrameBuffer(VideoStandard Std, PixelFormat Fmt) : VidStd(Std), PxFmt(Fmt) {}
};
//static FrameBuffer Make_Frame(size_t);
//static FrameBuffer Make_Frame(uint8_t*, size_t);

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- class FrameBufferImpl -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
class FrameBufferImpl : public IFrameBuffer
{
    // Operations
public:
    uint8_t* Data(void) override;
    size_t Size(void) const override;

    // Data / Attributes
private:
    std::vector<uint8_t> TheBuf;

    // Constructor / Destructor
public:
    FrameBufferImpl(VideoStandard, PixelFormat, size_t);
};

// +=+=+=+=+=+=+=+=+=+=+=+=+ class FrameBufferImpl_FromExternal +=+=+=+=+=+=+=+=+=+=+=+=+=
//
class FrameBufferImpl_FromExternal : public IFrameBuffer
{
    // Operations
public:
    uint8_t* Data(void) override;
    size_t Size(void) const override;

    // Data / Attributes
private:
    uint8_t* FrameData=nullptr;
    size_t FrameSize=0;

    // Constructor / Destructor
public:
    FrameBufferImpl_FromExternal(VideoStandard, PixelFormat, uint8_t*, size_t);
};

struct AncTocEntry
{
};


// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ struct Video +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
struct Video
{
    size_t Width=0, Height=0;       // Width and height in pixels
    size_t LineSizeInBytes=0;
    PixelFormat PxFmt=PixelFormat::INVALID;
    std::vector<uint8_t*> Lines;
};


// -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- struct FrameProperties -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
class FrameProperties
{
    // Types
public:
    struct FieldProperties
    {
        // Data / Attributes
        size_t FirstLine=0, LastLine=0; // Absolute line numbers, within the frame, 
                                        // marking the first and last of this field
        size_t FirstLineVideo=0, LastLineVideo=0;
                                        // Absolute line numbers, within the frame, 
                                        // marking the first and last of video
        size_t SwitchingLine=0;

        // Operations
        bool IsLineInField(size_t) const;
        bool IsVanc(size_t) const;
        bool IsVideo(size_t) const;
        size_t NumLines() const;
        size_t NumLinesVideo() const;
    };

    // Operations
public:
    bool Init(VideoStandard);
    bool IsInterlaced() const;
    bool IsVanc(size_t) const;
    bool IsVideo(size_t) const;
    bool IsSd() const;
    bool IsHd() const;
    bool IsUhd() const;
    size_t LineNumSymbols_Get() const;
    size_t LineNumSymbols_Hanc_Get(bool IncludeEavSav=true) const;
    size_t LineNumBytes_Get(PixelFormat) const;
    size_t LineNumBytes_Hanc_Get(PixelFormat, bool IncludeEavSav=true);
    size_t Line2Field(size_t) const;
    size_t NumLines_Get() const;
    size_t NumLines_Video_Get() const;
    size_t NumSymbols_Get() const;
    size_t SizeInBytes(PixelFormat) const;
    static Fraction ToFramePerSecond(VideoStandard);
    size_t ToRelativeVideoLine(size_t) const;

    // Data / Attributes
public:
    VideoStandard VidStd=VideoStandard::STD_UNKNOWN;
    std::vector<FieldProperties> Fields;
    size_t VideoWidth=0, VideoHeight=0;  // Video width and height in pixels
    size_t LineNumSymHanc=0;             // # of HANC symbols per line
    size_t LineNumSymVanc=0;             // # of VANC symbols per line
    size_t LineNumSymEav=0;              // # of EAV symbols per line
    size_t LineNumSymSav=0;              // # of SAV symbols per line
    Fraction Fps;

    // Constructor / Destructor
public:
    FrameProperties()=default;
    FrameProperties(VideoStandard);
};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class Frame +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
class Frame
{
    // Operations
public:
    void Clone(const Frame&);
    void Clone(const FrameBuffer&);
    void Commit();
    uint8_t* Data() const;
    FrameProperties Props_Get() const;
    PixelFormat PxFmt_Get() const;
    size_t Size() const;
    void Swap(FrameBuffer&);

    //void Anc_GetToc(void);
    void Anc_Get(void);
    void Audio_Get(void);
    void Video_Get(Video&) const;
protected:
    void Parse();

    // Data / Attributes
protected:
    FrameBuffer RawFrame;
private:
    bool IsDirty=false;

    // Constructor / Destructor
public:
    Frame()=default;
    Frame(VideoStandard, PixelFormat);
    Frame(VideoStandard, PixelFormat, size_t);
    Frame(VideoStandard, PixelFormat, uint8_t*, size_t);
    Frame(FrameBuffer&&);
};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class Frame_Raw +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
class Frame_Raw
{
    // Operations
public:
    uint8_t* Data() const;
    FrameProperties Props_Get() const;
    PixelFormat PxFmt_Get() const;
    size_t Size() const;
    void Swap(FrameBuffer&);

    // Data / Attributes
protected:
    FrameBuffer FrameBuf;

    // Constructor / Destructor
public:
    Frame_Raw() = default;
    Frame_Raw(VideoStandard, PixelFormat);
    Frame_Raw(VideoStandard, PixelFormat, size_t);
    Frame_Raw(VideoStandard, PixelFormat, uint8_t*, size_t);
    Frame_Raw(FrameBuffer&&);

    virtual ~Frame_Raw() = default;
};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class Frame_Parsed +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
class Frame_Parsed
{
    // Types
public:
    using SymbolStream = std::vector<uint16_t>;

    struct Video
    {
        SymbolStream Symbols;

        uint16_t* Line_Get(size_t RelativeLineIndex)
        {
            assert(RelativeLineIndex < NumLines);
            const size_t Offset = LineNumSymbols * RelativeLineIndex;
            return Symbols.data() + Offset;
        }

        void Copy(size_t DestLineIndex, const uint16_t* Src, size_t NumSymbols)
        {
            assert(DestLineIndex < NumLines);
            const size_t Offset = LineNumSymbols * DestLineIndex;
            assert((Offset+NumSymbols)<=Symbols.size());
            std::memcpy(Line_Get(DestLineIndex), Src, NumSymbols*sizeof(uint16_t));
        }

        void Init(size_t NumLines, size_t LineNumSymbols)
        {
            Symbols.resize(NumLines*LineNumSymbols);
            this->NumLines = NumLines;
            this->LineNumSymbols = LineNumSymbols;
        }
        size_t NumLines=0;
        size_t LineNumSymbols=0;
    };

    // Operations
public:
    void Parse(const Frame_Raw&);
    const FrameProperties& Props_Get() const;
    PixelFormat PxFmt_Get() const;

    //void Anc_GetToc(void);
    void Anc_Get(void) const;
    void Audio_Get(void) const;
    void Video_Get(Video&) const;
protected:
    void Split(const Frame_Raw&);
    void Split_SD(const Frame_Raw&, const FrameProperties&);
    void Split_HD(const Frame_Raw&, const FrameProperties&);
    void Split_UHD(const Frame_Raw&, const FrameProperties&);

    // Data / Attributes
protected:
    FrameProperties FrameProps;
private:
    std::map<SymbolStreamType, SymbolStream> HancStreams;
    std::map<SymbolStreamType, SymbolStream> VancStreams;
    std::map<SymbolStreamType, Video> VideoStreams;

    // Constructor / Destructor
public:
    Frame_Parsed() = default;
    virtual ~Frame_Parsed() = default;
};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class FrameBuilder +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
class FrameBuilder
{
    // Operations
public:
    void Anc_Add(void);
    void Frame_Init(Frame&);
    void Audio_Add(void);
    void Video_Add(void);
    void Line_Set(void);

    void Make(Frame&);
};

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class FrameParser +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
class FrameParser
{
    // Operations
public:
    void Anc_Get(void);
    void Audio_Get();
    void Video_Get(void);
    void Video_Read(void);

    void Parse(const Frame&);

    // Data / Attributes
private:


};

}; // namespace DtSdi