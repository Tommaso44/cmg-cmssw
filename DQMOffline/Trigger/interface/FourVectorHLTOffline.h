#ifndef FOURVECTORHLTOFFLINE_H
#define FOURVECTORHLTOFFLINE_H
// -*- C++ -*-
//
// Package:    FourVectorHLTOffline
// Class:      FourVectorHLTOffline
// 
/**\class FourVectorHLTOffline FourVectorHLTOffline.cc DQM/FourVectorHLTOffline/src/FourVectorHLTOffline.cc

 Description: This is a DQM source meant to plot high-level HLT trigger
 quantities as stored in the HLT results object TriggerResults

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Jeffrey Berryhill
//         Created:  June 2008
// $Id: FourVectorHLTOffline.h,v 1.7 2009/02/26 21:59:00 berryhil Exp $
//
//


// system include files
#include <memory>
#include <unistd.h>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <iostream>
#include <fstream>
#include <vector>


class FourVectorHLTOffline : public edm::EDAnalyzer {
   public:
      explicit FourVectorHLTOffline(const edm::ParameterSet&);
      ~FourVectorHLTOffline();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // BeginRun
      void beginRun(const edm::Run& run, const edm::EventSetup& c);

      // EndRun
      void endRun(const edm::Run& run, const edm::EventSetup& c);


      // ----------member data --------------------------- 
      int nev_;
      DQMStore * dbe_;

      MonitorElement* total_;

      bool plotAll_;
      bool resetMe_;
      int currentRun_;
 
      unsigned int nBins_; 
      double ptMin_ ;
      double ptMax_ ;
      
      double electronEtaMax_;
      double electronEtMin_;
      double muonEtaMax_;
      double muonEtMin_;
      double tauEtaMax_;
      double tauEtMin_;
      double jetEtaMax_;
      double jetEtMin_;
      double bjetEtaMax_;
      double bjetEtMin_;
      double photonEtaMax_;
      double photonEtMin_;
      double trackEtaMax_;
      double trackEtMin_;
      double metMin_;
      double htMin_;
      double sumEtMin_;

      std::vector<std::pair<std::string, std::string> > custompathnamepairs_;


      std::string dirname_;
      std::string processname_;
      bool monitorDaemon_;
      int theHLTOutputType;
      edm::InputTag triggerSummaryLabel_;
      edm::InputTag triggerResultsLabel_;
      HLTConfigProvider hltConfig_;
      // data across paths
      MonitorElement* scalersSelect;
      // helper class to store the data path

      class PathInfo {
	PathInfo():
	  pathIndex_(-1), denomPathName_("unset"), pathName_("unset"), l1pathName_("unset"), filterName_("unset"), processName_("unset"), objectType_(-1)
	  {};
      public:
	void setHistos(
                       MonitorElement* const NOn, 
                       MonitorElement* const onEtOn, 
                       MonitorElement* const onEtavsonPhiOn,  
                       MonitorElement* const NOff, 
                       MonitorElement* const offEtOff, 
                       MonitorElement* const offEtavsoffPhiOff,
                       MonitorElement* const NL1, 
                       MonitorElement* const l1EtL1, 
		       MonitorElement* const l1Etavsl1PhiL1,
                       MonitorElement* const NL1On, 
                       MonitorElement* const l1EtL1On, 
		       MonitorElement* const l1Etavsl1PhiL1On,
                       MonitorElement* const NL1Off,   
                       MonitorElement* const offEtL1Off, 
		       MonitorElement* const offEtavsoffPhiL1Off,
                       MonitorElement* const NOnOff, 
                       MonitorElement* const offEtOnOff, 
		       MonitorElement* const offEtavsoffPhiOnOff) {
          NOn_ = NOn;
	  onEtOn_ = onEtOn;
	  onEtavsonPhiOn_ = onEtavsonPhiOn;
          NOff_ = NOff;
	  offEtOff_ = offEtOff;
	  offEtavsoffPhiOff_ = offEtavsoffPhiOff;
          NL1_ = NL1;
	  l1EtL1_ = l1EtL1;
	  l1Etavsl1PhiL1_ = l1Etavsl1PhiL1;
          NL1On_ = NL1On;
	  l1EtL1On_ = l1EtL1On;
	  l1Etavsl1PhiL1On_ = l1Etavsl1PhiL1On;
          NL1Off_ = NL1Off;
	  offEtL1Off_ = offEtL1Off;
	  offEtavsoffPhiL1Off_ = offEtavsoffPhiL1Off;
          NOnOff_ = NOnOff;
	  offEtOnOff_ = offEtOnOff;
	  offEtavsoffPhiOnOff_ = offEtavsoffPhiOnOff;
	}
	MonitorElement * getNOnHisto() {
	  return NOn_;
	}
	MonitorElement * getOnEtOnHisto() {
	  return onEtOn_;
	}
	MonitorElement * getOnEtaVsOnPhiOnHisto() {
	  return onEtavsonPhiOn_;
	}
	MonitorElement * getNOffHisto() {
	  return NOff_;
	}
	MonitorElement * getOffEtOffHisto() {
	  return offEtOff_;
	}
	MonitorElement * getOffEtaVsOffPhiOffHisto() {
	  return offEtavsoffPhiOff_;
	}
	MonitorElement * getNL1Histo() {
	  return NL1_;
	}
	MonitorElement * getL1EtL1Histo() {
	  return l1EtL1_;
	}
	MonitorElement * getL1EtaVsL1PhiL1Histo() {
	  return l1Etavsl1PhiL1_;
	}
	MonitorElement * getNL1OnHisto() {
	  return NL1On_;
	}
	MonitorElement * getL1EtL1OnHisto() {
	  return l1EtL1On_;
	}
	MonitorElement * getL1EtaVsL1PhiL1OnHisto() {
	  return l1Etavsl1PhiL1On_;
	}
	MonitorElement * getNL1OffHisto() {
	  return NL1Off_;
	}
	MonitorElement * getOffEtL1OffHisto() {
	  return offEtL1Off_;
	}
	MonitorElement * getOffEtaVsOffPhiL1OffHisto() {
	  return offEtavsoffPhiL1Off_;
	}
	MonitorElement * getNOnOffHisto() {
	  return NOnOff_;
	}
	MonitorElement * getOffEtOnOffHisto() {
	  return offEtOnOff_;
	}
	MonitorElement * getOffEtaVsOffPhiOnOffHisto() {
	  return offEtavsoffPhiOnOff_;
	}
	const std::string getLabel(void ) const {
	  return filterName_;
	}
	void setLabel(std::string labelName){
	  filterName_ = labelName;
          return;
	}
	const std::string getPath(void ) const {
	  return pathName_;
	}
	const std::string getl1Path(void ) const {
	  return l1pathName_;
	}
	const std::string getDenomPath(void ) const {
	  return denomPathName_;
	}
	const std::string getProcess(void ) const {
	  return processName_;
	}
	const int getObjectType(void ) const {
	  return objectType_;
	}

        const edm::InputTag getTag(void) const{
	  edm::InputTag tagName(filterName_,"",processName_);
          return tagName;
	}
	~PathInfo() {};
	PathInfo(std::string denomPathName, std::string pathName, std::string l1pathName, std::string filterName, std::string processName, size_t type, float ptmin, 
		 float ptmax):
	  denomPathName_(denomPathName), pathName_(pathName), l1pathName_(l1pathName), filterName_(filterName), processName_(processName), objectType_(type),
          NOn_(0), onEtOn_(0), onEtavsonPhiOn_(0),
	  NOff_(0), offEtOff_(0), offEtavsoffPhiOff_(0),
	  NL1_(0), l1EtL1_(0), l1Etavsl1PhiL1_(0),
          NL1On_(0), l1EtL1On_(0), l1Etavsl1PhiL1On_(0),
	  NL1Off_(0), offEtL1Off_(0), offEtavsoffPhiL1Off_(0),
	  NOnOff_(0), offEtOnOff_(0), offEtavsoffPhiOnOff_(0),
	  ptmin_(ptmin), ptmax_(ptmax)
	  {
	  };
	  PathInfo(std::string denomPathName, std::string pathName, std::string l1pathName, std::string filterName, std::string processName, size_t type,
		   MonitorElement *NOn,
		   MonitorElement *onEtOn,
		   MonitorElement *onEtavsonPhiOn,
		   MonitorElement *NOff,
		   MonitorElement *offEtOff,
		   MonitorElement *offEtavsoffPhiOff,
		   MonitorElement *NL1,
		   MonitorElement *l1EtL1,
		   MonitorElement *l1Etavsl1PhiL1,
		   MonitorElement *NL1On,
		   MonitorElement *l1EtL1On,
		   MonitorElement *l1Etavsl1PhiL1On,
		   MonitorElement *NL1Off,
		   MonitorElement *offEtL1Off,
		   MonitorElement *offEtavsoffPhiL1Off,
		   MonitorElement *NOnOff,
		   MonitorElement *offEtOnOff,
		   MonitorElement *offEtavsoffPhiOnOff,
		   float ptmin, float ptmax
		   ):
	    denomPathName_(denomPathName), pathName_(pathName), l1pathName_(l1pathName), filterName_(filterName), processName_(processName), objectType_(type),
            NOn_(NOn), onEtOn_(onEtOn), onEtavsonPhiOn_(onEtavsonPhiOn),
	    NOff_(NOff), offEtOff_(offEtOff), offEtavsoffPhiOff_(offEtavsoffPhiOff),
	    NL1_(NL1), l1EtL1_(l1EtL1), l1Etavsl1PhiL1_(l1Etavsl1PhiL1),
            NL1On_(NL1On), l1EtL1On_(l1EtL1On), l1Etavsl1PhiL1On_(l1Etavsl1PhiL1On),
	    NL1Off_(NL1Off), offEtL1Off_(offEtL1Off), offEtavsoffPhiL1Off_(offEtavsoffPhiL1Off),
	    NOnOff_(NOnOff), offEtOnOff_(offEtOnOff), offEtavsoffPhiOnOff_(offEtavsoffPhiOnOff),
	    ptmin_(ptmin), ptmax_(ptmax)
	    {};
	    bool operator==(const std::string v) 
	    {
	      return v==filterName_;
	    }
      private:
	  int pathIndex_;
	  std::string denomPathName_;
	  std::string pathName_;
	  std::string l1pathName_;
	  std::string filterName_;
	  std::string processName_;
	  int objectType_;

	  // we don't own this data
          MonitorElement *NOn_, *onEtOn_, *onEtavsonPhiOn_;
	  MonitorElement *NOff_, *offEtOff_, *offEtavsoffPhiOff_;
	  MonitorElement *NL1_, *l1EtL1_, *l1Etavsl1PhiL1_;
	  MonitorElement *NL1On_, *l1EtL1On_, *l1Etavsl1PhiL1On_;
	  MonitorElement *NL1Off_, *offEtL1Off_, *offEtavsoffPhiL1Off_;
	  MonitorElement *NOnOff_, *offEtOnOff_, *offEtavsoffPhiOnOff_;

	  float ptmin_, ptmax_;

	  const int index() { 
	    return pathIndex_;
	  }
	  const int type() { 
	    return objectType_;
	  }
      public:
	  float getPtMin() const { return ptmin_; }
	  float getPtMax() const { return ptmax_; }
      };

      // simple collection - just 
      class PathInfoCollection: public std::vector<PathInfo> {
      public:
	PathInfoCollection(): std::vector<PathInfo>() 
	  {};
	  std::vector<PathInfo>::iterator find(std::string pathName) {
	    return std::find(begin(), end(), pathName);
	  }
      };
      PathInfoCollection hltPaths_;


};
#endif
