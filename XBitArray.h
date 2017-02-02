#ifndef XBITARRAY_H
#define XBITARRAY_H

#pragma warning(push)
#pragma warning(disable : 4127)		// conditional expression is constant
									// (needed for _ASSERTE)

#include <math.h>

///////////////////////////////////////////////////////////////////////////////
// CXBitArray class
class CXBitArray
{

// Constructors / Destructors
public:

	CXBitArray()
	{
		m_bBigEndian = FALSE;
		m_pBitArray = NULL;
		Init();
	}


	CXBitArray(BYTE *pBitArray, size_t nArraySizeBits, BOOL bit_value)
	{
		m_bBigEndian = FALSE;
		m_pBitArray = NULL;
		Init(pBitArray, nArraySizeBits, bit_value);
	}


	CXBitArray(size_t nArraySizeBits, BOOL bit_value)
	{
		m_bBigEndian = FALSE;
		m_pBitArray = NULL;
		Init(NULL, nArraySizeBits, bit_value);
	}



	virtual ~CXBitArray()
	{
		TRACE(_T("in ~CXBitArray\n"));

		if (m_bDeleteArray && m_pBitArray)
			delete [] m_pBitArray;
		m_pBitArray = NULL;

		m_nArraySizeBytes = 0;
		m_nArraySizeBits = 0;
	}


	
	void Init(BYTE *pBitArray = NULL, 
			  size_t nArraySizeBits = 0, 
			  BOOL bit_value = FALSE)
	{
		TRACE(_T("in Init:  nArraySizeBits=%d\n"), nArraySizeBits);

		// if Init is being called again, delete the previous heap array
		if (m_bDeleteArray && m_pBitArray)
			delete [] m_pBitArray;

		m_bDeleteArray    = FALSE;
		m_pBitArray       = pBitArray;

		m_nArraySizeBits  = nArraySizeBits;
		if (m_nArraySizeBits == 0)
			m_nArraySizeBits = 1;
		m_nArraySizeBytes = (m_nArraySizeBits + 7) / 8;	// round up
		m_nArraySizeBits  = m_nArraySizeBytes * 8;

		if (m_pBitArray)
			SetAll(bit_value);

		if (m_pBitArray == NULL)
		{
			// allocate array if address is NULL
			TRACE(_T("Init: allocating bit array for %d bytes\n"), 
				m_nArraySizeBytes);
			m_pBitArray = new BYTE [m_nArraySizeBytes];
			_ASSERTE(m_pBitArray);
			m_bDeleteArray = TRUE;	// ensure array will be deallocated
			SetAll(bit_value);
		}

		if ((m_pBitArray != NULL) && (m_nArraySizeBytes > 0))
		{
			// one final check to ensure array is ok
			_ASSERTE(!IsBadWritePtr(m_pBitArray, m_nArraySizeBytes));
			if (IsBadWritePtr(m_pBitArray, m_nArraySizeBytes))
			{
				TRACE(_T("ERROR: bad pointer\n"));
			}
		}
	}


	
	BOOL Attach(BYTE *pBitArray, size_t nArraySizeBits)
	{
		TRACE(_T("in Attach:  nArraySizeBits=%d\n"),
			nArraySizeBits);

		// if already initialized, delete the previous heap array
		if (m_bDeleteArray && m_pBitArray)
			delete [] m_pBitArray;

		m_bDeleteArray = FALSE;
		m_pBitArray    = NULL;

		_ASSERTE(pBitArray);
		if (!pBitArray)
		{
			TRACE(_T("ERROR:  pBitArray is NULL\n"));
			return FALSE;
		}

		_ASSERTE(nArraySizeBits > 0);
		if (nArraySizeBits == 0)
		{
			TRACE(_T("ERROR:  nArraySizeBits = 0\n"));
			return FALSE;
		}

		_ASSERTE(((nArraySizeBits/8)*8) == nArraySizeBits);
		if (((nArraySizeBits/8)*8) != nArraySizeBits)
		{
			TRACE(_T("ERROR:  nArraySizeBits is not a multiple of 8\n"));
			return FALSE;
		}

		m_pBitArray = pBitArray;
		m_nArraySizeBits  = nArraySizeBits;
		if (m_nArraySizeBits == 0)
			m_nArraySizeBits = 1;
		m_nArraySizeBytes = (m_nArraySizeBits + 7) / 8;	// round up
		m_nArraySizeBits  = m_nArraySizeBytes * 8;

		// one final check to ensure array is ok
		_ASSERTE(!IsBadWritePtr(m_pBitArray, m_nArraySizeBytes));
		if (IsBadWritePtr(m_pBitArray, m_nArraySizeBytes))
		{
			TRACE(_T("ERROR: bad pointer\n"));
			return FALSE;
		}

		return TRUE;
	}


// Copy & Assignment - do not allow
private:
	CXBitArray(const CXBitArray&);
	CXBitArray& operator = (const CXBitArray&);


// Attributes
public:

	///////////////////////////////////////////////////////////////////////////////
	//
	// Count()
	//
	// Purpose:     Return counts of bits set to 0 and bits set to 1
	//
	// Parameters:  bits_set_to_zero - pointer to the variable where the count of
	//                                 bits set to 0 is returned.
	//              bits_set_to_one  - pointer to the variable where the count of
	//                                 bits set to 1 is returned.
	//
	// Returns:     BOOL - TRUE = success
	//
	BOOL Count(size_t *bits_set_to_zero, size_t *bits_set_to_one) const
	{
		_ASSERTE(bits_set_to_zero && bits_set_to_one);
		if ((bits_set_to_zero == NULL) || (bits_set_to_one == NULL))
			return FALSE;

		*bits_set_to_zero = 0;
		*bits_set_to_one  = 0;

		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));
		if ((m_pBitArray == NULL) || (m_nArraySizeBytes == 0))
		{
			TRACE(_T("ERROR:  bit array not initialized\n"));
			return FALSE;
		}

		for (size_t i = 0; i < m_nArraySizeBytes; i++)
		{
			BYTE b = m_pBitArray[i];

			if (b == 0)
			{
				*bits_set_to_zero += 8;
			}
			else if (b == 0xFF)
			{
				*bits_set_to_one += 8;
			}
			else
			{
				// count bits by table lookup
				static BYTE bittable[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 
											 1, 2, 2, 3, 2, 3, 3, 4 };

				// add count of bits in each nibble
				size_t n = bittable[ (int) (b & 0x0F) ] +
						   bittable[ (int)((b & 0xF0) >> 4) ];

				*bits_set_to_one  += n;
				*bits_set_to_zero += 8 - n;
			}
		}

		return TRUE;
	}


	///////////////////////////////////////////////////////////////////////////////
	//
	// Find()
	//
	// Purpose:     Find next bit that has the value specified by bit_value
	//
	// Parameters:  start_pos - bit number (0 - N);  the search for a bit will
	//                          start at this bit number.  If necessary, the search
	//                          will wrap to the beginning of the bit array.
	//              bit_value - value to look for (0 or 1)
	//              bit_pos   - pointer to variable where bit number will be 
	//                          returned
	//
	// Returns:     BOOL - TRUE = success
	//
	BOOL Find(size_t start_pos, BOOL bit_value, size_t *bit_pos) const
	{
		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));
		if ((m_pBitArray == NULL) || (m_nArraySizeBytes == 0))
		{
			TRACE(_T("ERROR:  bit array not initialized\n"));
			return FALSE;
		}

		_ASSERTE(bit_pos);
		if (!bit_pos)
		{
			TRACE(_T("ERROR:  bad parameter\n"));
			return FALSE;
		}

		
		return FALSE;
	}


	///////////////////////////////////////////////////////////////////////////////
	//
	// Get()
	//
	// Purpose:     Get bit value at a bit index
	//
	// Parameters:  pos  - bit number (0 - N)
	//
	// Returns:     BOOL - TRUE = bit is 1;  FALSE = bit is 0
	//
	BOOL Get(size_t pos) const
	{
		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));

		if ((m_pBitArray == NULL) || (m_nArraySizeBytes == 0))
		{
			TRACE(_T("ERROR:  bit array not initialized\n"));
			return 0;
		}

		BYTE* ptr = m_pBitArray;
		ptr += (pos / 8);	/* Knock up ptr to byte requested */
		pos %= 8;		    /* Get bit relative to its own byte */

		return (WORD)((*ptr >> (7 - pos)) & 1);
	}


	///////////////////////////////////////////////////////////////////////////////
	//
	// GetArraySizeBits()
	//
	// Purpose:     Get number of bits in bit array
	//
	// Parameters:  None
	//
	// Returns:     size_t - no. of bits in array
	//
	size_t GetArraySizeBits()  const	{ return m_nArraySizeBits; }


	///////////////////////////////////////////////////////////////////////////////
	//
	// GetArraySizeBytes()
	//
	// Purpose:     Get size of bit array in bytes
	//
	// Parameters:  None
	//
	// Returns:     size_t - no. of bytes in array
	//
	size_t GetArraySizeBytes() const	{ return m_nArraySizeBytes; }


	///////////////////////////////////////////////////////////////////////////////
	//
	// GetBitNo()
	//
	// Purpose:     Convert bit mask to bit number
	//
	// Parameters:  mask - mask of bit (00000001, 00000010, 00000100, etc.)
	//
	// Returns:     size_t - bit number (0 - 7) within byte
	//
	size_t GetBitNo(BYTE mask) const
	{
		size_t index = 0;
		while (mask != 1)
		{
			index++;
			mask = (BYTE) (mask >> 1);
		}
		return index;
	}



	///////////////////////////////////////////////////////////////////////////////
	//
	// operator []
	//
	// Purpose:     Get bit value at a bit index
	//
	// Parameters:  pos  - bit number (0 - N)
	//
	// Returns:     BOOL - TRUE = bit is 1;  FALSE = bit is 0
	//
	BOOL operator [] (size_t pos) const
	{
		return Get(pos);
	}


	///////////////////////////////////////////////////////////////////////////////
	//
	// operator LPBYTE
	//
	// Purpose:     Get address of bit array
	//
	// Parameters:  None
	//
	// Returns:     LPBYTE - address of bit array, or NULL
	//
	operator LPBYTE () const
	{
		return m_pBitArray;
	}


	///////////////////////////////////////////////////////////////////////////////
	//
	// Set()
	//
	// Purpose:     Set bit value
	//
	// Parameters:  pos       - bit number (0 - N)
	//              bit_value - 0 or 1
	//
	// Returns:     None
	//
	void Set(size_t pos, BOOL bit_value)
	{
		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));
		if ((m_pBitArray == NULL) || (m_nArraySizeBytes == 0))
		{
			TRACE(_T("ERROR:  bit array not initialized\n"));
			return;
		}

		WORD byteoffs;		/* Byte offset in string */
		BYTE mask;			/* Masking value */

		BYTE* ptr = m_pBitArray;
		ptr += (byteoffs = pos / 8);	/* Calc offset, reset ptr */

		if (byteoffs)
			pos %= (byteoffs * 8);	/* Find bit within byte */

		mask = 1 << (7 - pos);

		if (bit_value)		/* If turn-on bit, OR with mask */
			*ptr |= mask;
		else				/* Else, AND with inverse (ones-complement) of mask */
			*ptr &= ~mask;
	}

	
	void SetValue(size_t pos, int nArchSizeType, short nbits, DWORD dwValue)
	{
		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));
		if ((m_pBitArray == NULL) || (m_nArraySizeBytes == 0))
		{
			TRACE(_T("ERROR:  bit array not initialized\n"));
			return;
		}
		
		// Special Case : Boolean
		if (nArchSizeType == 1){
			Set(pos, dwValue);
			return;
		}

			// LITTLE ENDIAN - COMPATIBLE MODE - 
		// ONLY normal size (number with 8, 16,32 or 64 bits)
		if (m_bBigEndian == FALSE){

			int		nBytes = nArchSizeType / 8;
			BYTE	Num2Insert[4] = {0,0,0,0};

			memcpy(Num2Insert, &dwValue, 4);
			CXBitArray NumBitArray;
			NumBitArray.Attach(Num2Insert, 32);
			
			for (ULONG i = 0; i < nArchSizeType; i++){

				ULONG ulBitValue = NumBitArray.Get(i);
				Set(pos + i,  ulBitValue);
			}
		}


		// Calcul le nombre minimum de bits pour représenter dwValue
		//int nbBits = 0; //ceil(log((double)dwValue)/log(2.0));
		//while ( (dwValCopy = (dwValCopy / 2)) ){ nbBits++; }
		//nbBits++;
		//ULONG nbBytes = ceil( (double)nbBits / 8 );
		//_ASSERTE( (nbBits <= nbits) && (nbBytes <= 4) );


	}

	DWORD GetValue(size_t pos, int nArchSizeType, short nbits)
	{
		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));
		if ((m_pBitArray == NULL) || (m_nArraySizeBytes == 0))
		{
			TRACE(_T("ERROR:  bit array not initialized\n"));
			return 0;
		}
	
		DWORD	dwNum	= 0;	/* Initialize all bits to 0 */

		// Special Case : Boolean
		if (nArchSizeType == 1){
			return Get(pos);
		}

		// LITTLE ENDIAN - COMPATIBLE MODE - 
		// ONLY normal size (number with 8, 16,32 or 64 bits)
		if ( (nArchSizeType == nbits)){

			int		nBytes = nArchSizeType / 8; 
			BYTE	Num2Extract[4] = {0,0,0,0};

			for (ULONG i = 0; i < nBytes; i++){
					Num2Extract[i] = Bit8ToByte(pos);
					pos += 8;
			}

			memcpy(&dwNum, Num2Extract, sizeof( DWORD) );
			return dwNum;
		
		}
		// BIG ENDIAN - Every size allowed
		else{
		
			int		dwMult  = 1;
			int		bit;

			for (bit = nbits - 1; bit >= 0; bit--, dwMult *= 2)
				dwNum += ( Get(pos + bit) * dwMult);
			return dwNum;
		}

		
		return (0);
	}



	BYTE Bit8ToByte(ULONG pos)
	{
		BYTE	ucNum = 0;	/* Initialize all bits to 0 */
		DWORD	dwMult = 1;
		int		bit;
	
		for (bit = 8 - 1; bit >= 0; bit--, dwMult *= 2)
			ucNum += ( Get(pos + bit) * dwMult);

		return ucNum;
	}




	void SetString(size_t pos, short nStrLenInBits, const char* szText, int nbits = 8)
	{
		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));

		ULONG ulTextLen = strlen(szText);

		
		
		
		//for (ULONG i = 0; i < ulTextLen; i++)
		//{
		//	SetValue(pos + (i * 8), 8, szText[i]);
		//}
	}

	CString GetString(size_t pos, short nStrLenInBits, int nbits = 8)
	{
		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));

		short	nStringLen = nStrLenInBits / 8;
		int		nCharSize = nbits;

		char* pBuffer = new char [nStringLen+1];
		memset(pBuffer, 0, nStringLen+1);
		
		WORD	wNum	= 0;	/* Initialize all bits to 0 */
		int		dwMult	= 1;
		int		bit		= 0;
		
		for (ULONG i = 0; i < nStringLen; i++)
		{
			for (bit = nbits - 1; bit >= 0; bit--, dwMult *= 2)
				wNum += ( Get(pos + bit) * dwMult);
			
			pBuffer[i] = wNum; //GetValue(pos + (i * 8), 8);

			wNum = 0;
			dwMult = 1;
			pos += (nbits);
		}

		CString strText = pBuffer;
		delete [] pBuffer;

		return strText;
	}

	///////////////////////////////////////////////////////////////////////////////
	//
	// SetAll()
	//
	// Purpose:     Set all bits to a value
	//
	// Parameters:  bit_value - 0 or 1
	//
	// Returns:     None
	//
	void SetAll(BOOL bit_value)
	{
		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));
		if ((m_pBitArray == NULL) || (m_nArraySizeBytes == 0))
		{
			TRACE(_T("ERROR:  bit array not initialized\n"));
			return;
		}

		BYTE value = 0;

		if (bit_value)
			value = 0xFF;

		for (size_t i = 0; i < m_nArraySizeBytes; i++)
			m_pBitArray[i] = value;
	}


	
	///////////////////////////////////////////////////////////////////////////////
	//
	// ToString()
	//
	// Purpose:     Returns a string that represents the bit array
	//
	// Parameters:  None
	//
	// Returns:     LPTSTR - pointer to a string that has been allocated on the 
	//                       heap and must be freed by caller.  The string
	//                       contains one TCHAR for each bit in the array, plus
	//                       a trailing nul.  Returns NULL if failure.
	//
	LPTSTR ToString(ULONG pos, ULONG nNbBits = 0) const
	{
		LPTSTR s = NULL;

		_ASSERTE((m_pBitArray != NULL) && (m_nArraySizeBytes != 0));
		if ((m_pBitArray == NULL) || (m_nArraySizeBytes == 0))
		{
			TRACE(_T("ERROR:  bit array not initialized\n"));
		}
		else
		{
			s = new TCHAR [m_nArraySizeBits + 1];
			_ASSERTE(s);
			memset(s, 0, m_nArraySizeBits + 1);

			if (s)
			{
				ULONG i = 0;
				ULONG j = 0;

			j =	(nNbBits == 0)?m_nArraySizeBits:nNbBits;
				for (i = pos; i < pos + j; i++ )
				{
					if (Get( i ))
						s[i - pos] = _T('1');
					else
						s[i - pos] = _T('0');
				}
				s[i] = _T('\0');
			}
		}

		return s;
	}


// Implementation
private:
	BOOL	m_bBigEndian;
	BOOL	m_bDeleteArray;					// TRUE = delete array in dtor
	BYTE *	m_pBitArray;					// pointer to bit array
	size_t	m_nArraySizeBytes;				// no. of bytes in array
	size_t	m_nArraySizeBits;				// no. of bits in array (always
											// a multiple of 8)

};

#pragma warning(pop)

#endif //XBITARRAY_H

