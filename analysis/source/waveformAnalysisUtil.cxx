// waveform_test.cxx
// Implements loadConfig(), initChannelHistos(), and analyzeChannel()
// declared in waveform_test.h.
//
// JSON parsing uses nlohmann/json (https://github.com/nlohmann/json).
// Install on RHEL/CentOS: sudo yum install nlohmann-json-devel
// Install on Debian/Ubuntu: sudo apt install nlohmann-json3-dev
// Or place json.hpp in the project include directory.

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include <waveformAnalysisUtil.h>

using json = nlohmann::json;

//--------------------------------------------------
// loadConfig
//--------------------------------------------------
AnalysisConfig loadConfig(const std::string& path)
{
    std::ifstream f(path);
    if (!f.is_open())
        throw std::runtime_error("Cannot open config file: " + path);

    json j;
    try {
        f >> j;
    } catch (const json::parse_error& e) {
        throw std::runtime_error(std::string("JSON parse error in ") + path + ": " + e.what());
    }

    AnalysisConfig cfg;   // starts from defaults defined in the struct

    // Helper lambda: read a value only if the key exists (missing keys keep default)
    auto get = [&](const json& node, const std::string& key, auto& dest) {
        if (node.contains(key)) dest = node.at(key).get<std::decay_t<decltype(dest)>>();
    };

    if (j.contains("trigger")) {
        const auto& t = j["trigger"];
        get(t, "threshold",                    cfg.trgThreshold);
        get(t, "pulse_window",                 cfg.trgPulseWindow);
        get(t, "baseline_window_offset_up",    cfg.trgBaselineWindowOffsetUp);
        get(t, "baseline_window_offset_down",  cfg.trgBaselineWindowOffsetDown);
        get(t, "baseline_window_width",        cfg.trgBaselineWindowWidth);
        get(t, "edge_search_limit",            cfg.trgEdgeSearchLimit);
    }

    if (j.contains("hrppd")) {
        const auto& h = j["hrppd"];
        get(h, "pulse_window",            cfg.hrppdPulseWindow);
        get(h, "baseline_window_offset",  cfg.hrppdBaselineWindowOffset);
        get(h, "baseline_window_width",   cfg.hrppdBaselineWindowWidth);
        get(h, "edge_search_limit",       cfg.hrppdEdgeSearchLimit);
    }

    if (j.contains("setup")) {
        const auto& s = j["setup"];
        get(s, "trigger_channel", cfg.triggerChannel);
        get(s, "trigger_type",    cfg.triggerType);
        if (s.contains("channel_branches")) {
            auto arr = s["channel_branches"].get<std::vector<std::string>>();
            if ((int)arr.size() != NCHANNELS)
                throw std::runtime_error("channel_branches must have exactly " +
                                         std::to_string(NCHANNELS) + " entries");
            for (int i = 0; i < NCHANNELS; i++)
                cfg.channelBranches[i] = arr[i];
        }
    }

    return cfg;
}

//--------------------------------------------------
// initTriggerHistos
//--------------------------------------------------
void initTriggerHistos(TriggerHistos& h)
{
  h.trgIdx               = new TH1D("hTRGTriggerIndex", "", 20000, 0., 20000.);
  h.trgBottom            = new TH1D("hTRGBottom", "", 200, -1., 1.);
  h.trgBottomIdx         = new TH1D("hTRGBottomIndex", "", 5000, 0., 5000.);
  h.trgBaseUp            = new TH1D("hTRGBaselineUp", "", 2000, -0.1, 0.1);
  h.trgBaseDwn           = new TH1D("hTRGBaselineDown", "", 2000, -1.0, -0.7);
  h.trgAmp               = new TH1D("hTRGAmplitude", "", 2000, 0., 1.);
  h.trgFitPts            = new TH1D("hTRGPointsInFit", "", 500, 0., 500.);
  h.trgEdgeEndVsBeginIdx = new TH2D("hTRGEdgeEndVsBeginIndex", "", 2000, 0., 2000., 2000, 0., 2000.);
}

//--------------------------------------------------
// initChannelHistos
//--------------------------------------------------
void initChannelHistos(int ch, ChannelHistos& h)
{
    // Calibration
    h.sigTrigOffset      = new TH1D(Form("sigTrigOffset%d",                ch), "", 10000,  0.,    10000.);
    h.ampVsSigTrigOffset = new TH2D(Form("ampVsSigTrigOffset%d",           ch), "", 10000,  0.,    10000., 200, 0., 0.1);

    // Pulse shape
    h.bottom             = new TH1D(Form("hHRPPDBottom%d",                 ch), "",   200, -0.1,   0.1);
    h.bottomIdx          = new TH1D(Form("hHRPPDBottomIndex%d",            ch), "",  5000,  0.,    5000.);
    h.baseline           = new TH1D(Form("hHRPPDBaseline%d",               ch), "",  2000, -0.1,   0.1);
    h.amplitude          = new TH1D(Form("hHRPPDAmplitude%d",              ch), "",  1000,  0.,    0.5);
    h.ampVsIdx           = new TH2D(Form("hHRPPDAmplitudeVsBottomIndex%d", ch), "",  5000,  0., 5000., 200, -1., 1.);
    h.ptsInFit           = new TH1D(Form("hHRPPDPointsInFit%d",            ch), "",   100,  0.,    100.);
    h.edgeEndVsBegin     = new TH2D(Form("hHRPPDEdgeEndVsBeginIndex%d",    ch), "",  2000,  0., 2000., 2000, 0., 2000.);
    h.pulseWidth         = new TH1D(Form("hHRPPDPulseWidth%d",             ch), "",   300,  0.,    300.);
    h.pulseCharge        = new TH1D(Form("hHRPPDPulseCharge%d",            ch), "",   900, -0.05,  0.25);

    // Timing
    h.timeDiffVsAmp      = new TH2D(Form("hHRPPDTRGTimeDiffVsAmp%d",      ch), "",  1000,  0.,    0.5, 30000, 100000., 130000.);
}

//--------------------------------------------------
// analyzeTrigger (NIM)
//--------------------------------------------------
TriggerResult analyzeTriggerNIM(waveform& trg,
				 int trgTriggerIndex,
				 TriggerHistos& h,
				 const AnalysisConfig& cfg)
{
  TriggerResult r;
  double trgBaselineUp = 1000., trgBaselineDown = 1000., trgAmplitude = 0., trg50Percent = 0.;
  int trgEdgeBeginIndex = -1, trgEdgeEndIndex = -1, pointsInTRGFit = 0;

  if(trgTriggerIndex > -1)
    {
      // Baseline before pulse
      unsigned baseUpLo = (trgTriggerIndex - cfg.trgBaselineWindowOffsetUp > 1)
	                    ? trgTriggerIndex - cfg.trgBaselineWindowOffsetUp : 1;
      trgBaselineUp     = trg.getBaseline(baseUpLo, baseUpLo + cfg.trgBaselineWindowWidth);

      // Baseline during pulse
      unsigned baseDnLo = trgTriggerIndex + cfg.trgBaselineWindowOffsetDown;
      trgBaselineDown   = trg.getBaseline(baseDnLo, baseDnLo + cfg.trgBaselineWindowWidth);
      
      trgAmplitude = trgBaselineUp - trgBaselineDown;

      h.trgIdx->Fill(trgTriggerIndex);
      h.trgBaseUp->Fill(trgBaselineUp);
      h.trgBaseDwn->Fill(trgBaselineDown);
      h.trgAmp->Fill(trgAmplitude);

      // Leading edge fit
      double trgThresh10 = trgBaselineUp - 0.1 * trgAmplitude;
      double trgThresh90 = trgBaselineUp - 0.9 * trgAmplitude;
      
      trgEdgeEndIndex   = trg.getLeadingEdgeIndex(trgTriggerIndex + cfg.trgBaselineWindowOffsetDown,
						   trgThresh90, cfg.trgEdgeSearchLimit);
      trgEdgeBeginIndex = trg.getLeadingEdgeIndex(trgTriggerIndex + cfg.trgBaselineWindowOffsetDown,
						   trgThresh10, cfg.trgEdgeSearchLimit);
      pointsInTRGFit    = trgEdgeEndIndex - trgEdgeBeginIndex + 1;

      h.trgFitPts->Fill(pointsInTRGFit);
      h.trgEdgeEndVsBeginIdx->Fill(trgEdgeBeginIndex, trgEdgeEndIndex);

      if(trgEdgeBeginIndex > -1 && trgEdgeEndIndex > -1)
	trg50Percent = trg.fitLeadingEdge(trgEdgeBeginIndex, trgEdgeEndIndex,
					   trgAmplitude, trgBaselineUp, 0.5);
    }

  // Fill Tree
  r.tok = (trgTriggerIndex > -1) ? 1 : 0;
  r.tbaseUp = trgBaselineUp;
  r.tbaseDown = trgBaselineDown;
  r.tpoints = pointsInTRGFit;
  r.tamp = trgAmplitude;
  r.t50Time = trg50Percent;

  return r;
}

//--------------------------------------------------
// analyzeChannel
//--------------------------------------------------
ChannelResult analyzeChannel(waveform& hrppd,
                              int trgTriggerIndex, int signalOffset,
                              ChannelHistos& h,
                              const AnalysisConfig& cfg)
{
    ChannelResult r;
    double bottom = 1000., baseline = 0., amplitude = 0.;
    int bottomIndex = -1;

    // 1. Find peak position and baseline
    if (trgTriggerIndex > -1) {
        bottomIndex = hrppd.findMinimum(trgTriggerIndex + signalOffset - cfg.hrppdPulseWindow,
                                        trgTriggerIndex + signalOffset + cfg.hrppdPulseWindow);
        bottom = hrppd.getValue(bottomIndex);

        if (bottomIndex > -1) {
            unsigned lo = (bottomIndex - cfg.hrppdBaselineWindowOffset > 1)
                           ? bottomIndex - cfg.hrppdBaselineWindowOffset : 1;
            unsigned hi = lo + cfg.hrppdBaselineWindowWidth;
            baseline  = hrppd.getBaseline(lo, hi);
            amplitude = baseline - bottom;

            h.bottom->Fill(bottom);
            h.bottomIdx->Fill(bottomIndex);
            h.baseline->Fill(baseline);
            h.amplitude->Fill(amplitude);
            h.ampVsIdx->Fill(bottomIndex, amplitude);
        }
    }

    // 2. Find leading/trailing edges, fit, integrate charge
    int edgeBegin = -1, edgeEnd = -1, beginning = -1, trailing = -1;
    int ptsInFit = 0, pulseWidth = 0;
    double charge = 0., t10 = 0., t50 = 0., t90 = 0.;

    if (bottomIndex > -1) {
        double thresh01 = baseline - 0.01 * amplitude;
        double thresh10 = baseline - 0.1  * amplitude;
        double thresh90 = baseline - 0.9  * amplitude;

        edgeEnd   = hrppd.getLeadingEdgeIndex(bottomIndex, thresh90, cfg.hrppdEdgeSearchLimit);
        edgeBegin = hrppd.getLeadingEdgeIndex(bottomIndex, thresh10, cfg.hrppdEdgeSearchLimit);
        beginning = hrppd.getLeadingEdgeIndex(bottomIndex, thresh01, cfg.hrppdEdgeSearchLimit + 100);
        trailing  = hrppd.getTrailingEdgeIndex(bottomIndex, thresh01, cfg.hrppdEdgeSearchLimit + 100);

        ptsInFit   = edgeEnd  - edgeBegin + 1;
        pulseWidth = trailing - beginning  + 1;

        if (trailing != -1) {
            for (unsigned i = (unsigned)beginning; i <= (unsigned)trailing; i++)
                charge += (baseline - hrppd.getValue(i));
            charge /= 50.0;
        }

        h.ptsInFit->Fill(ptsInFit);
        h.edgeEndVsBegin->Fill(edgeBegin, edgeEnd);
        h.pulseWidth->Fill(pulseWidth);
        h.pulseCharge->Fill(charge);

        if (edgeBegin > -1 && edgeEnd > -1) {
            t10 = hrppd.fitLeadingEdge(edgeBegin, edgeEnd, amplitude, baseline, 0.10);
            t50 = hrppd.fitLeadingEdge(edgeBegin, edgeEnd, amplitude, baseline, 0.50);
            t90 = hrppd.fitLeadingEdge(edgeBegin, edgeEnd, amplitude, baseline, 0.90);
        }
    }

    r.ok        = (bottomIndex > -1) ? 1 : 0;
    r.peakIndex = bottomIndex;
    r.points    = ptsInFit;
    r.base      = baseline;
    r.amp       = amplitude;
    r.width     = pulseWidth;
    r.charge    = charge;
    r.time10    = t10;
    r.time50    = t50;
    r.time90    = t90;
    return r;
}
