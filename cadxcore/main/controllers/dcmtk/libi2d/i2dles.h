/*
 * This file is part of Ginkgo CADx
 *
 *
 *
 *  Code addapted from DCMTK
 *  Copyright (C) 2001-2007, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmdata
 *
 *  Author:  Michael Onken
 *
 *  Purpose: Class for conversion of image file into new DICOM SC Image IODs
 *
 *  Last Update:      $Author: onken $
 *  Update Date:      $Date: 2009-01-16 09:51:55 $
 *  CVS/RCS Revision: $Revision: 1.2 $
 *  Status:           $State: Exp $

 *
 */
#pragma once

#ifdef verify
#define MACRO_QUE_ESTORBA verify
#undef verify
#endif

#include <dcmtk/dcmdata/dctk.h>
#include <api/dicom/idicomizador.h>
#include "i2dimgs.h"

#ifdef MACRO_QUE_ESTORBA
#define verify MACRO_QUE_ESTORBA
#endif

class I2DLittleEndianSource : public I2DImgSource
{

public:

        /** Constructor
         */
        I2DLittleEndianSource(GIL::DICOM::IDICOMImg2DCM::TImageFile& imgFile): m_ImgFile(imgFile) {}

        /** Virtual Destructor
        */
        virtual ~I2DLittleEndianSource() {}


        /** true if pixeldata is compressed
        */
        virtual bool IsCompressed() const
        {
                return false;
        }

        /*true if pixeldata has to be compressed*/
        virtual bool Recompress() const
        {
                return m_ImgFile.recompress;
        }

        /** Returns identifier for the image input format the plugin imports.
         *  @return A short identifier (e. g. "JPEG")
         */
        virtual OFString inputFormat() const;

        /** Extracts the raw JPEG pixel data stream from a JPEG file and returns some
         *  image information about this pixel data.
         *  Raw means here that all APP markers (e.g. JFIF information) are removed from the JPEG stream.
         *  The pixel data returned is a JPEG stream in JPEG interchange format.
         *  This function allocates memory for the pixel data returned to the user. The caller of this
         *  function is responsible for deleting the memory buffer
         *  @param rows - [out] Rows of image
         *  @param cols - [out] Columns of image
         *  @param samplesPerPixel - [out] Number of components per pixel
         *  @param photoMetrInt - [out] The DICOM color model used for the compressed data
         *  @param bitsAlloc - [out] Bits Allocated for one sample
         *  @param bitsStored - [out] Bits Stored, number of bits stored within Bits Allocated
         *  @param highBit - [out] High Bit, hightest bit position set within Bits Allocated
         *  @param pixelRepr - [out] Pixel Representation (0=unsigned, 1=signed)
         *  @param planConf - [out] Planar Configuration
         *  @param pixAspectH - [out] Horizontal value of pixel aspect ratio
         *  @param pixAspectV - [out] Vertical value of pixel aspect ratio
         *  @param pixData - [out] Pointer to the pixel data in JPEG Interchange Format (but without APPx markers).
         *  @param length - [out] Length of pixel data
         *  @param ts - [out] The transfer syntax imposed by the imported pixel pixel data.
                              This is necessary for the JPEG importer that needs to report
                              which TS must be used for the imported JPEG data (ie. baseline, progressive, ...).
                              If pixel data is uncompressed, EXS_Unknown is returned
         *  @return EC_Normal, if successful, error otherwise
         */
        virtual OFCondition readPixelData( Uint16& rows,
                                           Uint16& cols,
                                           Uint16& samplesPerPixel,
                                           OFString& photoMetrInt,
                                           Uint16& bitsAlloc,
                                           Uint16& bitsStored,
                                           Uint16& highBit,
                                           Uint16& pixelRepr,
                                           Uint16& planConf,
                                           Uint16& pixAspectH,
                                           Uint16& pixAspectV,
                                           char*&  pixData,
                                           Uint32& length,
                                           E_TransferSyntax& ts);



        GIL::DICOM::IDICOMImg2DCM::TImageFile m_ImgFile;
};
