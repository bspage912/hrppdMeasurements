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

int waveform::getThresholdIndex(double threshold)
{
  // Scan Waveform to find point the amplitude passes threshold
  // Assume negative values
  for(unsigned i=0; i<mVal.GetSize(); i++)
    {
      if(mVal[i] < threshold)
	return i;
    }

  return -1;
} // getThresholdIndex

double waveform::getBaseline(unsigned from, unsigned to)
{
  double sum = 0.;
  int num = 0;

  if(from > to || to > mVal.GetSize() || from < 0) return -999.;

  for(unsigned i=from; i<=to; i++)
    {
      sum += mVal[i];
      num++;
    }

  return sum/(1.0*num);
} // getBaseline

int waveform::getLeadingEdgeIndex(unsigned start, double threshold, unsigned limit)
{
  // Scan waveform to find index above threshold
  // Assume negative signal and work backward from start point until limit
  for(unsigned i=start; i>=start-limit; i--)
    {
      if(mVal[i] > threshold)
	return i;
    }

  return -1;
} // getLeadingEdgeIndex

int waveform::getTrailingEdgeIndex(unsigned start, double threshold, unsigned limit)
{
  // Scan waveform to find index above threshold
  // Assume negative signal and work forward from start point until limit
  for(unsigned i=start; i<start+limit; i++)
    {
      if(mVal[i] > threshold)
        return i;
    }

  return -1;
} // getTrailingEdgeIndex

double waveform::fitLeadingEdge(unsigned from, unsigned to, double amp, double base, double wkpt)
{
  // Do a linear least-squares fit to the pulse leading edge and return time (in ps) of the point wkpt% of the pulse amplitude
  if(from > to || to >= mVal.GetSize()) return -1.;
  
  double sumX = 0.;
  double sumX2 = 0.;
  double sumVal = 0.;
  double sumXVal = 0.;
  unsigned N = 0;
  for(int i=from; i<to+1; i++)
    {
      double time = mTime[i]*1E12; // convert scope time to ps

      sumX += time;
      sumX2 += time*time;
      sumVal += mVal[i];
      sumXVal += time*mVal[i];
      N++;
    }

  double delta = N*sumX2 - sumX*sumX;
  double a = (sumX2*sumVal - sumX*sumXVal)/delta;
  double b = (N*sumXVal - sumX*sumVal)/delta;

  return ((base - wkpt*amp) - a)/b;
} // fitLeadingEdge

