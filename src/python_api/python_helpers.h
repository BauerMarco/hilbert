#ifndef PYTHON_HELPERS_H
#define PYTHON_HELPERS_H

#include "../v2rdm_doci/v2rdm_solver.h"
#include "../doci/doci_solver.h"
#include "../pp2rdm/pp2rdm_solver.h"

namespace psi{ 

class DOCIHelper{

  public:

    DOCIHelper(SharedWavefunction reference_wavefunction,Options & options);
    ~DOCIHelper();
    void common_init();
    double compute_energy();

  protected:

    /// the DOCISolver 
    std::shared_ptr<doci::DOCISolver> doci;

};

class pp2RDMHelper{

  public:

    pp2RDMHelper(SharedWavefunction reference_wavefunction,Options & options);
    ~pp2RDMHelper();
    void common_init();
    double compute_energy();

  protected:

    /// the pp2RDMSolver 
    std::shared_ptr<pp2rdm::pp2RDMSolver> pp2rdm;

};

class v2RDMHelper{

  public:

    v2RDMHelper(SharedWavefunction reference_wavefunction,Options & options);
    ~v2RDMHelper();
    void common_init();
    double compute_energy();

  protected:

    /// the v2RDMSolver 
    std::shared_ptr<v2rdm_doci::v2RDMSolver> v2rdm;

};

}

#endif