// #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* SdiFile.h *#*#*#*#*#*#*#*#*#*#*# (C) 2021 DekTec
//

#pragma once

// .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#include <cassert>
#include <stdint.h>


namespace DtSdi
{


struct DtSdiFileHeader
{
    uint32_t MagicCode1;        // Magic code 1, identifies file type
    uint32_t MagicCode2;        // Magic code 2,     "       "    "
    uint32_t MagicCode3;        // Magic code 3,     "       "    "
    uint8_t  FmtVersion;        // Version number of .dtsdi file format
    uint8_t  DataType;          // Type of data
    uint16_t Flags;             // Additional data-format flags
    uint32_t FrameSize;         // Size of frames (incl. padding)
    uint32_t NumFrames;         // Number of frames stored in file
};

// Magic codes - Identify a file as an ".dtsdi file"
#define DTSDI_MAGIC_CODE1 0x546B6544  // Magic code part 1
#define DTSDI_MAGIC_CODE2 0x642E6365  // Magic code part 2
#define DTSDI_MAGIC_CODE3 0x69647374  // Magic code part 3

// (Current) format version
#define DTSDI_FMT_VERSION  0
#define DTSDI_FMT_VERSION2 1


struct SdiFormat
{
    enum class LineRate : int
    {
        SDI_SD=0x0,
        SDI_ED,
        SDI_HD,
        SDI_3G,
        SDI_12G,
        SDI_24G,
    } Rate;

    enum class MultLinkType : int
    {
        LINK_2SI=0,
        LINK_QUADRANT,
    } LinkType;

    enum class SdiLevel : int
    {
        A=0,
        B,
    } Level;
    
    enum class SdiSubLevel : int
    {
        B_DL=0,
        B_DS,
    } NumStreams;
};

struct LogicalFrameProperties
{
    uint32_t PictureRateNumerator;
    uint32_t PictureRateDenominator;
    uint8_t AspectRatioNumerator;
    uint8_t AspectRatioDenominator;
    bool InterlacedOrProgressive;
    enum class SamplingStructure : int
    {
        YCBCR_422=0,
    } SamplingStructure;
    bool IsStereoscopic;
    uint8_t BitDepth;
    uint16_t PictureWidth;
    uint16_t PictureHeight;
};

struct PhysicalFrameProperties
{
    uint32_t NumFields          : 2;
    uint32_t Reseverd1          : 6;
    uint32_t NumLinesFrame      : 16;
    uint32_t NumSymsHanc        : 16;
    uint32_t NumSymsVancVideo   : 16;
};

struct SdiFileHeader
{
    uint32_t MagicCode;         // Magic code
    uint8_t Version;
    uint16_t HeaderSize;
    uint8_t NumPhysicalLinks;
    uint32_t FrameSize;
    SdiFormat Format;
    LogicalFrameProperties LogicalProps;
    PhysicalFrameProperties PhysicalProps;
};


};  // namespace DtSdi
