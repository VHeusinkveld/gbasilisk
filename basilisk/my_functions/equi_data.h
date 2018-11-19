int diaglevel = 3;
double *equifield = NULL;

struct sEquiDia {
    scalar * list;
};

struct sEquiOut {
    scalar * list;
    FILE * fp;
    int n;
};



void equi_diag (struct sEquiDia p){  
    int len = list_len(p.list);
    int n = 1<<diaglevel;

    if(!equifield) {
        equifield = calloc(len*n*n*n, sizeof(double)); // Init with zeros
    } 	

    double dDelta = 0.9999999*L0/n;  
    int l = 0;  
    for(scalar s in p.list){
    foreach_level_or_leaf(diaglevel) {
        if(is_leaf(cell)){
	    double pn = Delta/dDelta;
	    fprintf(stderr, "%g, %d, %g, %g", pn, (int)pn, Delta, dDelta);
        } else {
	    int ii = (int)((x-dDelta/2)/dDelta);
	    int jj = (int)((y-dDelta/2)/dDelta);
            int kk = (int)((z-dDelta/2)/dDelta);

	    int place = ii*n*n + jj*n + kk*len + l;
	    equifield[place] += s[];

	}
    }
    }
    //int place = i*p.n*p.n + j*p.n + k*len + l;

}
/*    
    if (pid() == 0) {
@if _MPI
    MPI_Reduce (MPI_IN_PLACE, equifield, len*p.n*p.n*p.n, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
@endif

    }
@if _MPI
    else // slave
    MPI_Reduce (equifield, NULL, len*p.n*p.n*p.n, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
@endif


void equi_output (struct sEquiOut p){
   if(pid() == 0){
   int len = list_len(p.list);
   int ja = 0.;
    for(int i = 0; i < p.n; i++){
        for(int j = 0; j < p.n; j++){
            for(int k = 0; k < p.n; k++){
		int l = 0;
		for (scalar s in p.list){
		    int place = i*p.n*p.n + j*p.n + k*len + l;
		    fprintf(p.fp, "%g\t", equifield[place]);
		    l++;
		    ja++;
   		}
	    }
	}    
    }
    fprintf(stderr, "%d\n", ja);
}
}*/

