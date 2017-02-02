/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** Copyright, 1995-2003, Samuel R. Blackburn
**
** "You can get credit for something or get it done, but not both."
** Dr. Richard Garwin
**
** BSD License follows.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** Redistributions of source code must retain the above copyright notice,
** this list of conditions and the following disclaimer. Redistributions
** in binary form must reproduce the above copyright notice, this list
** of conditions and the following disclaimer in the documentation and/or
** other materials provided with the distribution. Neither the name of
** the WFC nor the names of its contributors may be used to endorse or
** promote products derived from this software without specific prior
** written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** $Workfile: CBase64Coding.hpp $
** $Revision: 5 $
** $Modtime: 6/26/01 11:00a $
*/

#if ! defined( BASE_64_CODING_CLASS_HEADER )

#define BASE_64_CODING_CLASS_HEADER

#define CARRIAGE_RETURN (13)
#define LINE_FEED       (10)

class CBase64Coding
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CBase64Coding( const CBase64Coding& ) {};
      CBase64Coding& operator=( const CBase64Coding& ) { return( *this ); };

   protected:

      BYTE m_DecoderTable[ 256 ];

      virtual void m_InitializeDecoderTable( void );

   public:

      // Construction

      CBase64Coding();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CBase64Coding();

      virtual BOOL Decode( const CByteArray& source, CByteArray& destination );
      virtual BOOL Decode( const CString&    source, CByteArray& destination );
      virtual BOOL Encode( const CByteArray& source, CByteArray& destination );
      virtual BOOL Encode( const CByteArray& source, CString&    destination );
};

#endif // BASE_64_CODING_CLASS_HEADER
