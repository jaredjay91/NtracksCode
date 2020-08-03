from CRABClient.UserUtilities import config
config = config()

config.section_('General')
config.General.requestName = 'Ntracks_HIRun2018A0_PromptReco_v3_AOD_20200702_PbPb_nomask'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ntrack_AAMinBias_5TeV_AOD.py'
config.JobType.maxMemoryMB = 2000
config.JobType.outputFiles = ['ntrack_AAMinBias_5TeV_AOD.root']
config.JobType.allowUndistributedCMSSW = True #allow use of SL7

config.section_('Data')
config.Data.inputDataset = '/HIMinimumBias0/HIRun2018A-04Apr2019-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBiasReducedFormat1/HIRun2018A-PromptReco-v2/AOD'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 15 
config.Data.splitting = 'LumiBased'
#PbPb 2018A
config.Data.runRange = '326381-327564'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/HI/PromptReco/Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/jjay/NtracksData/%s' % (config.General.requestName)
config.Data.publication = False

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
