import FWCore.ParameterSet.Config as cms

process = cms.Process("nTrack")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))#, SkipEvent = cms.untracked.vstring('ProductNotFound'))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:7CD4D24E-CC25-E843-ACAF-1ED233B5F77C.root'),
#    fileNames = cms.untracked.vstring('file:/eos/cms/store/data/Run2017G/SingleMuon/AOD/09Aug2019_UL2017-v1/20000/0226F689-13B6-4F48-B897-55BF5C73A15F.root'),
#    fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/data/Run2017G/HIZeroBias8/AOD/09Aug2019_UL2017_LUM-v2/110000/4EE9CD10-91D0-654E-988D-F53413D6976B.root')
#    fileNames = cms.untracked.vstring('file:/eos/cms/store/data/Run2017G/HIZeroBias8/AOD/09Aug2019_UL2017_LUM-v2/110000/4EE9CD10-91D0-654E-988D-F53413D6976B.root')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

#process.GlobalTag.globaltag = cms.string('94X_dataRun2_v11')
#process.GlobalTag.globaltag = cms.string('94X_dataRun2_ReReco_EOY17_v4')
process.GlobalTag.globaltag = cms.string('106X_dataRun2_v28')

## ==== Filters ====
### pp Event Selection
#process.load('HeavyIonsAnalysis.Configuration.hfCoincFilter_cff')
process.goodVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 25 && position.Rho <= 2"),
    filter = cms.bool(True),
)
process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False), ## Or 'True' to get some per-event info
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)
### Trigger selection
process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")
#process.triggerResultsFilter.triggerConditions = cms.vstring('L1_ZeroBias','HLT_HIZeroBias_part*')
process.triggerResultsFilter.triggerConditions = cms.vstring('L1_DoubleMu0','HLT_HIL1DoubleMu0_v1')
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")
process.triggerResultsFilter.l1tResults = cms.InputTag("gtStage2Digis") #O: needs to be this for PA
process.triggerResultsFilter.throw = False
### Filter sequence
process.fastFilter = cms.Sequence(#process.hfCoincFilter
     process.goodVertexFilter
    + process.noScraping
    + process.triggerResultsFilter
)



#####################   Actual stuff

### For Centrality
process.load("RecoHI.HiCentralityAlgos.HiCentrality_cfi")
process.hiCentrality.produceHFhits = False
process.hiCentrality.produceHFtowers = False
process.hiCentrality.produceEcalhits = False
process.hiCentrality.produceZDChits = False
process.hiCentrality.produceETmidRapidity = False
process.hiCentrality.producePixelhits = False
process.hiCentrality.produceTracks = True
#process.hiCentrality.srcTracks = cms.InputTag("hiGeneralTracks") #default for HI
#process.hiCentrality.srcVertex= cms.InputTag("hiSelectedVertex")
#process.hiCentrality.srcReUse = cms.InputTag("hiCentrality")
process.hiCentrality.srcTracks = cms.InputTag("generalTracks") #for pPb and pp
process.hiCentrality.srcVertex= cms.InputTag("offlinePrimaryVertices")
process.hiCentrality.srcReUse = cms.InputTag("pACentrality")

process.hiCentrality.producePixelTracks = False


process.ntr = cms.Path(
    process.fastFilter*
    process.hiCentrality
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("ntrack_PPMinBias_5TeV_AOD.root"),
    outputCommands = cms.untracked.vstring(
              "drop *",
              "keep recoCentrality_hi*_*_*",
              "keep recoTracks_generalTracks__RECO*"
    ),
    dropMetaData=cms.untracked.string("ALL")
)
process.o= cms.EndPath(process.out)

