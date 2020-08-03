import FWCore.ParameterSet.Config as cms

process = cms.Process("nTrack")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/eos/cms/store/hidata/PARun2016C/PAMinimumBias7/AOD/PromptReco-v1/000/286/496/00000/FA4A1ADC-A0BD-E611-A4C8-02163E013619.root')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.GlobalTag.globaltag = cms.string('80X_dataRun2_Prompt_v15')


## ==== Filters ====
### pPb Event Selection
process.load('HeavyIonsAnalysis.Configuration.hfCoincFilter_cff')
process.primaryVertexFilterPA = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
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
process.triggerResultsFilter.triggerConditions = cms.vstring('L1_MinimumBiasHF0_OR_BptxAND','HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part*')#'HLT_PAL3Mu*_v*')#, 'HLT_PAL2Mu*_v*')
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults","","HLT")
process.triggerResultsFilter.l1tResults = cms.InputTag("gtStage2Digis") #O: needs to be this for PA
process.triggerResultsFilter.throw = False
### Filter sequence
process.fastFilter = cms.Sequence(process.hfCoincFilter + process.primaryVertexFilterPA + process.noScraping + process.triggerResultsFilter)



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
    fileName = cms.untracked.string("ntrack_PAMinBias_5TeV_AOD.root"),
    outputCommands = cms.untracked.vstring(
              "drop *",
              "keep recoCentrality_hi*_*_*"
    ),
    dropMetaData=cms.untracked.string("ALL")
)
process.o= cms.EndPath(process.out)

