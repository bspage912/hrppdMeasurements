//

#include <waveform.h>

int waveform::findMinimum(unsigned from, unsigned to)
{
  if(from > to || to >=mVal.GetSize()) return -1;

  int peak = 0;
  for(unsigned i=from; i<=to; i++)
    {
      if(i == from || mVal[i] < mVal[peak])
	peak = i;
    }

  return peak;
} // findMinimum()
