#!/bin/bash
listOfFiles=
for filename in /eos/cms/store/group/phys_heavyions/dileptons/jjay/NtracksData/Ntracks_HIRun2018A_PromptReco_v3_AOD_20200702_PbPb_nomask/HIMinimumBiasReducedFormat1/crab_Ntracks_HIRun2018A_PromptReco_v3_AOD_20200702_PbPb_nomask/200702_171850/0000/ntrack_AAMinBias_5TeV_AOD*1.root; do
    listOfFiles="$listOfFiles $filename"
done

hadd -f ntrack_AAMinBias2018A_5TeV_AOD_merged1.root $listOfFiles
