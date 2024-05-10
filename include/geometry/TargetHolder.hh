
#ifndef TargetHolder_h
#define TargetHolder_h

#include "geometry/GeometryObject.hh"

class G4VPhysicalVolume;

#include <memory>
using std::shared_ptr;

class G4MultiFunctionalDetector;
class G4PSEnergyDeposit;

class TargetHolder : public GeometryObject
{
  public:
    TargetHolder() : GeometryObject("TargetHolder") {}
    ~TargetHolder() {}

    G4VPhysicalVolume* Construct();

    void ConstructSDandField();

    virtual void SetupOutput();
    virtual void FillOutput(const G4Event *event);

  private:
    int fHCID = -1; /// Hit collection ID for energy deposition scorer
    int fTupleID = -1; /// tuple ID for energy deposition output

};

#endif

