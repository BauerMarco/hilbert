/* 
 *  @BEGIN LICENSE
 * 
 *  Hilbert: a space for quantum chemistry plugins to Psi4 
 * 
 *  Copyright (c) 2020 by its authors (LICENSE).
 * 
 *  The copyrights for code used from other parties are included in
 *  the corresponding files.
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 * 
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see http://www.gnu.org/licenses/.
 * 
 *  @END LICENSE
 */

#ifndef RRSDP_SOLVER_H
#define RRSDP_SOLVER_H

#include <psi4/libmints/vector.h>
#include <psi4/liboptions/liboptions.h>

#include <misc/cg_solver.h>

#include <lbfgs.h>

using namespace psi;

namespace hilbert {

typedef void (*RRSDPCallbackFunction)(std::shared_ptr<Vector>,std::shared_ptr<Vector>,void *);

class RRSDPSolver{

  public:

    /// RRSDPSolver constructor
    RRSDPSolver(long int n_primal, long int n_dual, Options & options);

    /// RRSDPSolver destructor
    ~RRSDPSolver();

    /// solve the sdp problem
    void solve(std::shared_ptr<Vector> x, 
               std::shared_ptr<Vector> b, 
               std::shared_ptr<Vector> c,
               std::vector<int> primal_block_dim,
               int maxiter,
               RRSDPCallbackFunction evaluate_Au,
               RRSDPCallbackFunction evaluate_ATu,
               void * data);

    double evaluate_gradient(const lbfgsfloatval_t * r, lbfgsfloatval_t * g);

    void set_iiter(int iiter) { iiter_ = iiter; }

    int iiter_total() { return iiter_total_; }
    int oiter_total() { return oiter_; }

    void set_mu(double mu) { mu_ = mu; }
    void set_y(std::shared_ptr<Vector> y) { y_->copy(y.get()); }

    double get_mu() { return mu_; }
    std::shared_ptr<Vector> get_y() { return y_; }

    bool is_converged(){ return is_converged_; }

  protected:

    /// pointer to input data
    void * data_;

    /// copy of Au callback function
    RRSDPCallbackFunction evaluate_Au_;

    /// copy of ATu callback function
    RRSDPCallbackFunction evaluate_ATu_;

    /// copy of list of block sizes
    std::vector<int> primal_block_dim_;


    /// Options object
    Options& options_;

    /// the error in the primal constraints
    double primal_error_;

    /// is the solver converged?
    bool is_converged_;

    /// the number of outer iterations
    int oiter_;

    /// the number of inner iterations
    int iiter_;

    /// the total number of inner iterations
    int iiter_total_;

    /// the penalty parameter
    double mu_;

    /// copy of the input c vector
    std::shared_ptr<Vector> c_;

    /// copy of the input x vector
    std::shared_ptr<Vector> x_;

    /// copy of the input b vector
    std::shared_ptr<Vector> b_;

    /// the lagrange multipliers
    std::shared_ptr<Vector> y_;

    /// temporary container the size of Au
    std::shared_ptr<Vector> Au_;

    /// temporary container the size of ATu
    std::shared_ptr<Vector> ATu_;

    /// extra workspace
    std::shared_ptr<Vector> tmp_;

    /// the requested convergence of the primal dual gap
    double e_convergence_;

    /// the requested convergence of the primal and dual errors
    double r_convergence_;

    /// the dimension of the primal vector
    long int n_primal_;

    /// the dimension of the dual vector
    long int n_dual_;

};

}

#endif
