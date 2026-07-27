// waveform_test.h
// Extended waveform header for HRPPD multi-channel analysis.
// Adds to waveform.h:
//   - AnalysisConfig struct  (runtime-configurable analysis parameters)
//   - loadConfig()           (populate AnalysisConfig from a JSON file)
//   - ChannelResult struct   (per-channel pulse analysis output)
//   - ChannelHistos struct   (all per-channel histograms)
//   - initChannelHistos()    (create and name histograms for one channel)
//   - analyzeChannel()       (analyse one HRPPD channel, fill histograms)

#ifndef WAVE_FORM_ANALYSIS_UTIL_H
#define WAVE_FORM_ANALYSIS_UTIL_H

#include <array>
#include <string>

#include <waveformUtil.h>
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

//--------------------------------------------------
// Number of HRPPD signal channels (compile-time; affects array sizing)
//--------------------------------------------------
const int NCHANNELS = 5;

//--------------------------------------------------
// Runtime-configurable analysis parameters.
// Default values match the original hard-coded constants so that
// the program behaves identically when no config file is supplied.
//--------------------------------------------------
struct AnalysisConfig {
    // Trigger
    double trgThreshold                = -0.2;
    int    trgPulseWindow              = 100;
    int    trgBaselineWindowOffsetUp   = 450;
    int    trgBaselineWindowOffsetDown = 700;
    int    trgBaselineWindowWidth      = 150;
    int    trgEdgeSearchLimit          = 800;
    // HRPPD channels
    int    hrppdPulseWindow            = 25;
    int    hrppdBaselineWindowOffset   = 150;
    int    hrppdBaselineWindowWidth    = 50;
    int    hrppdEdgeSearchLimit        = 150;
    // Oscilloscope branch name for each HRPPD channel (e.g. "CH2".."CH6")
    std::array<std::string, NCHANNELS> channelBranches = {"CH2","CH2","CH2","CH2","CH2"};
    // Oscilloscope branch used as the trigger input
    std::string triggerChannel = "CH1";
    // Trigger detector type: "NIM" or "FPD" — selects analysis path
    std::string triggerType    = "NIM";
};

//--------------------------------------------------
// Load analysis parameters from a JSON config file.
// Any key absent from the file retains its default value.
// Throws std::runtime_error if the file cannot be opened or parsed.
//--------------------------------------------------
AnalysisConfig loadConfig(const std::string& path);

//--------------------------------------------------
// Trigger analysis result
//--------------------------------------------------
struct TriggerResult {
  unsigned tok          = 0;
  double   tbottom      = 0.;
  unsigned tbottomIndex = 0;
  double   tbaseUp      = 0.;
  double   tbaseDown    = 0.;
  unsigned tpoints      = 0;
  double   tamp         = 0.;
  double   t50Time      = 0.;
};

//--------------------------------------------------
// Per-channel pulse analysis result
//--------------------------------------------------
struct ChannelResult {
    unsigned ok        = 0;
    int      peakIndex = -1;
    unsigned points    = 0;
    unsigned width     = 0;
    double   base      = 0.;
    double   amp       = 0.;
    double   charge    = 0.;
    double   time10    = 0.;
    double   time50    = 0.;
    double   time90    = 0.;
};

//--------------------------------------------------
// Trigger histogram bundle
// Covers pulse-shape histograms.
//--------------------------------------------------
struct TriggerHistos {
  TH1D *trgIdx;
  TH1D *trgBottom, *trgBottomIdx; // Used when trigger is fast photo-diode pulse from elmo laser
  TH1D *trgBaseUp, *trgBaseDwn; // Used when trigger is NIM pulse
  TH1D *trgAmp;
  TH1D *trgFitPts;
  TH2D *trgEdgeEndVsBeginIdx;
};

//--------------------------------------------------
// Per-channel histogram bundle
// Covers calibration, pulse-shape, and timing histograms.
//--------------------------------------------------
struct ChannelHistos {
    // Calibration: signal-to-trigger offset
    TH1D *sigTrigOffset;
    TH2D *ampVsSigTrigOffset;
    // Pulse shape
    TH1D *bottom, *bottomIdx, *baseline, *amplitude;
    TH2D *ampVsIdx;
    TH1D *ptsInFit, *pulseWidth, *pulseCharge;
    TH2D *edgeEndVsBegin;
    // Timing
    TH2D *timeDiffVsAmp;
};

//--------------------------------------------------
// Create and name all histograms for trigger.
// Histograms are owned by the current ROOT directory.
//--------------------------------------------------
void initTriggerHistos(TriggerHistos& h);

//--------------------------------------------------
// Create and name all histograms for channel ch (1-indexed).
// Histograms are owned by the current ROOT directory.
//--------------------------------------------------
void initChannelHistos(int ch, ChannelHistos& h);

//--------------------------------------------------
// Analyze the Trigger Channel - NOTE: This logic assumes a NIM-style trigger pulse
// Returns a TriggerResult with all derived quantities
//--------------------------------------------------
TriggerResult analyzeTriggerNIM(waveform& trg,
				 int trgTriggerIndex,
				 TriggerHistos& h,
				 const AnalysisConfig& cfg);

//--------------------------------------------------
// Analyse one HRPPD channel:
//   - finds peak, computes baseline and amplitude
//   - fits leading edge, computes 10/50/90% times
//   - integrates charge
//   - fills histograms in h
// Returns a ChannelResult with all derived quantities.
//--------------------------------------------------
ChannelResult analyzeChannel(waveform& hrppd,
                              int trgTriggerIndex, int signalOffset,
                              ChannelHistos& h,
                              const AnalysisConfig& cfg);

#endif
