// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* SdiFrameBuilder.h *#*#*#*#*#*#*#*#*# (C) 2021 DekTec
//

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <memory>
#include <stdint.h>
#include <vector>

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
    UNDEFINED=-1,
    UYVY422_8B,
    UYVY422_10B,
    UYVY422_16B,
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

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class IFrameBuffer +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
using FrameBuffer = std::unique_ptr<class IFrameBuffer>;
class IFrameBuffer
{
    // Operations
public:
    virtual uint8_t* Data(void)=0;
    virtual VideoStandard Standard() const { return VidStd; }
    virtual PixelFormat PxFmt() const { return PxFormat; }
    virtual size_t Size(void) const=0;

    static FrameBuffer Make(VideoStandard, PixelFormat);
    static FrameBuffer Make(VideoStandard, PixelFormat, size_t);
    static FrameBuffer Make(VideoStandard, PixelFormat, uint8_t*, size_t);

    // Data / Attributes
private:
    VideoStandard VidStd=VideoStandard::STD_UNKNOWN;
    PixelFormat PxFormat=PixelFormat::UNDEFINED;

    // Constructor
protected:
    IFrameBuffer(VideoStandard Std, PixelFormat Fmt) : VidStd(Std), PxFormat(Fmt) {}
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

struct Fraction
{
    int Num=0, Den=1;
    Fraction(int N=0, int D=1) : Num(N), Den(D) {}
};

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ struct Video +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//
struct Video
{
    size_t Width=0, Height=0;       // Width and height in pixels
    size_t LineSizeInBytes=0;
    PixelFormat PxFmt=PixelFormat::UNDEFINED;
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
        size_t NumLines() const;
        size_t NumLinesVideo() const;
    };

    // Operations
public:
    bool Init(VideoStandard);
    bool IsInterlaced() const;
    size_t LineNumSymbols() const;
    size_t LineSizeInBytes(PixelFormat) const;
    size_t LineSizeInBytes_Hanc(PixelFormat, bool IncludeEavSav=true);
    size_t NumLines() const;
    size_t SizeInBytes(PixelFormat) const;
    static Fraction ToFramePerSecond(VideoStandard);

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
    size_t Size() const;
    void Swap(FrameBuffer&);

    //void Anc_GetToc(void);
    void Anc_Get(void);
    void Audio_Get(void);
    void Video_Get(Video&) const;

    // Data / Attributes
protected:
    FrameBuffer FrameBuf;

    // Constructor / Destructor
public:
    Frame()=default;
    Frame(VideoStandard, PixelFormat);
    Frame(VideoStandard, PixelFormat, size_t);
    Frame(VideoStandard, PixelFormat, uint8_t*, size_t);
    Frame(FrameBuffer&&);
};

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ class FrameBuilder +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
class FrameBuilder
{
    // Operations
public:
    void Anc_Add(void);
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
};

}; // namespace DtSdi