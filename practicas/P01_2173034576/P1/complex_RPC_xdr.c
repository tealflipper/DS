/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "complex_RPC.h"

bool_t
xdr_complex (XDR *xdrs, complex *objp)
{
	register int32_t *buf;

	 if (!xdr_COMPLEX (xdrs, objp))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_COMPLEX (XDR *xdrs, COMPLEX *objp)
{
	register int32_t *buf;

	 if (!xdr_double (xdrs, &objp->fReal))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->fImg))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_scsuma_1_argument (XDR *xdrs, scsuma_1_argument *objp)
{
	 if (!xdr_complex (xdrs, &objp->a))
		 return FALSE;
	 if (!xdr_complex (xdrs, &objp->b))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_scproductoconescalar_1_argument (XDR *xdrs, scproductoconescalar_1_argument *objp)
{
	 if (!xdr_complex (xdrs, &objp->a))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->c))
		 return FALSE;
	return TRUE;
}