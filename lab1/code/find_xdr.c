/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "find.h"

bool_t
xdr_operandos (XDR *xdrs, operandos *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->vet, 10,
		sizeof (float), (xdrproc_t) xdr_float))
		 return FALSE;
	return TRUE;
}
