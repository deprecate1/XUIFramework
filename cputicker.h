// TITLE:
// High-Resolution Counter Class.
//
// VERSION:
// 1.2
//
// AUTHORS:
// Created by J.M.McGuiness, http://www.hussar.demon.co.uk
//            PJ Naughter,   Email: pjn@indigo.ie Web: http://indigo.ie/~pjn
//
// DESCRIPTION:
// This file declares a class the wraps the Pentium-specific time stamp counter.
// This counter has a resolution in terms of PCLKS (processor clocks) so it can
// be used for direct instruction timings.
//
// VERSION HISTORY:
// 26/3/96 v1.0 J.M.McGuiness Initially created
// 16/7/97 v1.1 PJ Naughter,
//              1. A number of additions including:
//              2. Support for running on Windows NT
//              3. now uses the build-in 64 bit data type "__int64"
//              4. Improved diagnostic info thanks to the above
//              5. Usage of static variables to improve efficiency
//              6. Addition of a function which will convert from CPU ticks to seconds
//              7. Improved adhereance to the MFC coding style and standards
// 14/1/99 v1.2 PJ Naughter
//              1. Fixed a bug discovered by David Green-Seed where he was experiencing 
//                 access violations when the code was compiled with optimizations turned 
//                 on a Pentium II. The problem was that (on a PII) the RDTSC instruction 
//                 touches more registers than expected. This has now been fixed by saved 
//                 and restoring the EAX and EBX registers around the call to RDTSC,
//              2. General code tidy up of const functions, parameters etc.
//
// LEGALITIES:
// Copyright © 1996-1999 by J.M.McGuiness and PJ Naughter, all rights reserved.
//
// This file must not be distributed without the authors prior
// consent.
//
/////////////////////////////////////////////////////////////////////////////


////////////////////////////////// Macros ///////////////////////////////////

#ifndef __CPUTICKER_H__
#define __CPUTICKER_H__





////////////////////////// Classes //////////////////////////////////////////
class CCPUTicker : public CObject
{
public:
//constructors / Destructors
	CCPUTicker();
	CCPUTicker(const CCPUTicker& ticker);

//copy constructor
	inline CCPUTicker& operator=(const CCPUTicker& ticker);

//perform the actual measurement
  void Measure();

//accessors to the actual measurement value
  double GetTickCountAsSeconds() const;  
  inline __int64 GetTickCount() const { return m_TickCount; };  

//static methods
	static BOOL GetCPUFrequency(double& frequency, double& target_ave_dev, 
                              unsigned long interval = 1000,
                              unsigned int max_loops = 20);

//Is high resolution available on this CPU
	BOOL IsAvailable() const;

//Standard MFC diagnostics
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  __int64 m_TickCount;

 	static BOOL m_bHasRDTSC;
  static BOOL m_bRunningOnNT;
  static BOOL m_bStaticsCalculated;

  static double m_deviation;
  static double m_freq;
  static BOOL m_bFrequencyCalculated;

  static BOOL CheckHasRDTSC();
  static BOOL RunningOnNT();

	DECLARE_DYNAMIC(CCPUTicker)
};


#endif //__CPUTICKER_H__