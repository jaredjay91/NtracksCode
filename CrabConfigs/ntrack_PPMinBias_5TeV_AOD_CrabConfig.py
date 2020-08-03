from CRABClient.UserUtilities import config
config = config()

config.section_('General')
config.General.requestName = 'Ntracks_Run2017G_AOD_20200729_1635_pp'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ntrack_PPMinBias_5TeV_AOD.py'
config.JobType.maxMemoryMB = 2000
config.JobType.outputFiles = ['ntrack_PPMinBias_5TeV_AOD.root']
config.JobType.allowUndistributedCMSSW = True #allow use of SL7

config.section_('Data')
config.Data.inputDataset = '/HIZeroBias2/Run2017G-09Aug2019_UL2017_LUM-v2/AOD'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 15 
config.Data.splitting = 'LumiBased'
#pp 2017G
#config.Data.runRange = '306546-306657'
config.Data.runRange = '306553'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/5TeV/PromptReco/Cert_306546-306657_5TeV_PromptReco_Collisions17_JSON.txt'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/jjay/NtracksData/%s' % (config.General.requestName)
config.Data.publication = False

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
