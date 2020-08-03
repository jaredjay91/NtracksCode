from CRABClient.UserUtilities import config
config = config()

config.section_('General')
config.General.requestName = 'Ntracks_HIRun2016D_PromptReco_v5_AOD_20200625_pPb'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ntrack_PAMinBias_5TeV_AOD.py'
config.JobType.maxMemoryMB = 2000
config.JobType.outputFiles = ['ntrack_PAMinBias_5TeV_AOD.root']
config.JobType.allowUndistributedCMSSW = True #allow use of SL7

config.section_('Data')
config.Data.inputDataset = '/PAMinimumBias1/PARun2016D-PromptReco-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 15 
config.Data.splitting = 'LumiBased'
#Pbp (2nd run)
config.Data.runRange = '286513-286520'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/HI/Cert_286513-286520_HI5TeV_PromptReco_Pbp_Collisions16_JSON_noL1T.txt'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/jjay/NtracksData/%s' % (config.General.requestName)
config.Data.publication = False

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
