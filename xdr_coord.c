#include <rpc/rpc.h>
#include "claves.h"

bool_t xdr_Coord(XDR *xdrs, struct Coord *objp) {
    if (!xdr_int(xdrs, &objp->x))
        return (FALSE);
    if (!xdr_int(xdrs, &objp->y))
        return (FALSE);
    return (TRUE);
}