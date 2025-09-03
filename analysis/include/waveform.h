// Define Waveform Object and Functions

#ifndef WAVE_FORM_H
#define WAVE_FORM_H

#include <string>

#include <TTreeReaderArray.h>

class waveform {
 public:
 waveform(const char *name, TTreeReaderArray<double> &sigTime, TTreeReaderArray<double> &ampl): mName(name), mTime(sigTime), mVal(ampl) {
    mConsistent = mTime.GetSize() == mVal.GetSize();
  };
  ~waveform() {};

  inline double getTime(unsigned i) const { return (i < mTime.GetSize() ? mTime[i] : 0.0); };
  inline double getValue(unsigned i) const { return (i < mVal.GetSize() ? mVal[i] : 0.0); };

  int findMinimum(unsigned from, unsigned to);
  int getThresholdIndex(double threshold);
  double getBaseline(unsigned from, unsigned to);
  int getLeadingEdgeIndex(unsigned start, double threshold, unsigned limit);
  int getTrailingEdgeIndex(unsigned start, double threshold, unsigned limit);
  double fitLeadingEdge(unsigned from, unsigned to, double amp, double base, double wkpt);

 private:
  bool mConsistent;
  std::string mName;

  TTreeReaderArray<double> &mTime;
  TTreeReaderArray<double> &mVal;
};

#endif

