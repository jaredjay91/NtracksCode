from CRABClient.UserUtilities import config
config = config()

config.section_('General')
config.General.requestName = 'Ntracks_HIRun2016C_PromptReco_v5_AOD_20200625_pPb'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ntrack_PAMinBias_8TeV_AOD.py'
config.JobType.maxMemoryMB = 2000
config.JobType.outputFiles = ['ntrack_PAMinBias_8TeV_AOD.root']
config.JobType.allowUndistributedCMSSW = True #allow use of SL7

config.section_('Data')
config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.unitsPerJob = 15 
config.Data.splitting = 'LumiBased'
#Pbp (1st run)
#config.Data.runRange = '285479-285832'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/HI/Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
#pPb (2nd run)
config.Data.runRange = '285952-286496'
#config.Data.runRange = '285952-285962'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/HI/Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/jjay/NtracksData/%s' % (config.General.requestName)
config.Data.publication = False

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
