// A wrapper for the Fortran geolocation code
int geolocate_wrapper(double *pos, double *vel, double range, double squint, double a, double e2, 
		      double *llh, double *lookAngle, double *incidenceAngle)
{
   geolocate_(pos, vel, &range, &squint, &a, &e2, llh, lookAngle, incidenceAngle);
   return 1;
}
