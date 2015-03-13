import FWCore.ParameterSet.Config as cms

#------------------------------------------------
#AlCaReco filtering for HCAL Iterative Phi Symmetry:
#------------------------------------------------

from Calibration.HcalAlCaRecoProducers.alcaiterativephisym_cfi import *


import HLTrigger.HLTfilters.hltHighLevel_cfi
hcalphisymHLT =  HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
#    HLTPaths = ['HLT_HcalPhiSym'],
    eventSetupPathsKey='HcalCalIterativePhiSym',
    throw = False #dont throw except on unknown path name 
)

seqALCARECOHcalCalMinBias = cms.Sequence(hcalphisymHLT*IterativePhiSym)

