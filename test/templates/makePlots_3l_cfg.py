import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.processesBackground = cms.vstring(
    ##"TT",
    "TTW",
    "TTZ",
    "EWK",
    "Rares",
    "conversions",
    "fakes_data"
)
process.makePlots.processSignal = cms.string("signal")

process.makePlots.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("3l_OS_Tight"),
        label = cms.string("3l")
    )
)

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_3l"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("N")
    )
])
