#include "grid/octree.h" // For 3D
#include "view.h"
#include "navier-stokes/centered.h"
#include "tracer.h"
#include "diffusion.h"

/* Global variables */
int minlevel, maxlevel; // Grid depths
double meps, eps;		// Maximum error and error in u fields

#include "physics.h"
#include "fan.h"
#include "diagnostics.h"
#include "data_process.h"

/* Initialisation */
int main() {
	
    	init_grid(2<<5);
   	L0 = 50.;
   	X0 = Y0 = Z0 = 0.;
	a = av; 

	u.x.refine = refine_linear; 
	u.y.refine = refine_linear;
	#if dimension == 3
		u.z.refine = refine_linear;
	#endif
	fan.prolongation = fraction_refine;
	p.refine = p.prolongation = refine_linear;
	b.gradient = minmod2; // Flux limiter 

  	minlevel = 2; 
  	maxlevel = 7;
  	meps = 0.1;

    	DT = 0.05;
	CFL = 0.5;

	init_physics();
	init_rotor();

    	run();
}

/* Initialisation */
event init(i = 0){
	refine (fan[] > 0. && level < maxlevel);
	eps = min(meps, 0.01*rot.cu);
}

/* Adaptivity function called */
event adapt(i++) {
	adapt_wavelet((scalar *){fan, u},(double []){0.,eps,eps,eps},maxlevel,minlevel);
}

/* Progress event */
event end(t+=2.; t <=10.) {
	printf("i=%d t=%g p=%d u=%d b=%d \n", i, t, mgp.i, mgu.i, mgb.i);
}
