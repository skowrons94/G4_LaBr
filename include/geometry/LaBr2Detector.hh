
#ifndef LaBr2Detector_h
#define LaBr2Detector_h

#include "geometry/GeometryObject.hh"

class G4VPhysicalVolume;

#include <memory>
using std::shared_ptr;

class G4MultiFunctionalDetector;
class G4PSEnergyDeposit;

class LaBr2Detector : public GeometryObject
{
  public:
    LaBr2Detector() : GeometryObject("LaBr2Detector") {}
    ~LaBr2Detector() {}

    G4VPhysicalVolume* Construct();

    void ConstructSDandField();

    virtual void SetupOutput();
    virtual void FillOutput(const G4Event *event);

  private:
    int fHCID = -1; /// Hit collection ID for energy deposition scorer
    int fTupleID = -1; /// tuple ID for energy deposition output

};

#endif

