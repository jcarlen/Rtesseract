
#include "Rtesseract.h"

SEXP
getPixAsArray(const Pix *pix)
{
    l_uint32 numEls = pix->w * pix->h * pix->d/8; // depth is in bits.
    SEXP ans;
    PROTECT(ans = NEW_NUMERIC(numEls));
    double *rels = REAL(ans);
    for(int i = 0; i < numEls; i++)
        rels[i] = pix->data[i];

    SEXP dims = NEW_INTEGER(3);
    PROTECT(dims);
    INTEGER(dims)[0] = pix->h;
    INTEGER(dims)[1] = pix->w;
    INTEGER(dims)[2] = pix->d/8;

    SET_DIM(ans, dims);
    
    UNPROTECT(2);
    return(ans);
}
