#if !defined(mroipac_extensions_dopiq_f_h)
#define mroipac_extensions_dopiq_f_h

#if defined(NEEDS_F77_TRANSLATION)

#define dopiq_f FORTRAN_NAME(dopiq, DOPIQ)
#define setLineLength_f FORTRAN_NAME(setlinelength, SETLINELENGTH)
#define setLineHeaderLength_f FORTRAN_NAME(setlineheaderlength, SETLINEHEADERLENGTH)
#define setLastSample_f FORTRAN_NAME(setlastsample, SETLASTSAMPLE)
#define setStartLine_f FORTRAN_NAME(setstartline, SETSTARTLINE)
#define setNumberOfLines_f FORTRAN_NAME(setnumberoflines, SETNUMBEROFLINES)
#define setMean_f FORTRAN_NAME(setmean, SETMEAN)
#define setPRF_f FORTRAN_NAME(setprf, SETPRF)
#define getAcc_f FORTRAN_NAME_(get_acc, GET_ACC)
#define inuse_acc_f FORTRAN_NAME_(inuse_acc, INUSE_ACC)
#define allocate_acc_f FORTRAN_NAME_(allocate_acc, ALLOCATE_ACC)
#define deallocate_acc_f FORTRAN_NAME_(deallocate_acc, DEALLOCATE_ACC)

#endif

#if defined(__cplusplus)
extern "C" {
#endif
    /* the declarations */
    void dopiq_f(uint64_t *);
    void setLineLength_f(int *);
    void setLineHeaderLength_f(int *);
    void setLastSample_f(int *);
    void setStartLine_f(int *);
    void setNumberOfLines_f(int *);
    void setMean_f(double *);
    void setPRF_f(double *);
    void getAcc_f(double *,int *);
    int inuse_acc_f();
    void allocate_acc_f(int *);
    void deallocate_acc_f();
#if defined(__cplusplus)
}
#endif

#endif
