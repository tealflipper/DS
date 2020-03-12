/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _COMPLEX_RPC_H_RPCGEN
#define _COMPLEX_RPC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct COMPLEX complex;

struct COMPLEX {
	double fReal;
	double fImg;
};
typedef struct COMPLEX COMPLEX;

struct scsuma_1_argument {
	complex a;
	complex b;
};
typedef struct scsuma_1_argument scsuma_1_argument;

struct scproductoconescalar_1_argument {
	complex a;
	double c;
};
typedef struct scproductoconescalar_1_argument scproductoconescalar_1_argument;

#define COMPLEX_OPERACIONES 0x20000001
#define COMPLEX_OPER_1 1

#if defined(__STDC__) || defined(__cplusplus)
#define scSuma 1
extern  complex * scsuma_1(complex , complex , CLIENT *);
extern  complex * scsuma_1_svc(complex , complex , struct svc_req *);
#define scProductoConEscalar 2
extern  complex * scproductoconescalar_1(complex , double , CLIENT *);
extern  complex * scproductoconescalar_1_svc(complex , double , struct svc_req *);
extern int complex_operaciones_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define scSuma 1
extern  complex * scsuma_1();
extern  complex * scsuma_1_svc();
#define scProductoConEscalar 2
extern  complex * scproductoconescalar_1();
extern  complex * scproductoconescalar_1_svc();
extern int complex_operaciones_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_complex (XDR *, complex*);
extern  bool_t xdr_COMPLEX (XDR *, COMPLEX*);
extern  bool_t xdr_scsuma_1_argument (XDR *, scsuma_1_argument*);
extern  bool_t xdr_scproductoconescalar_1_argument (XDR *, scproductoconescalar_1_argument*);

#else /* K&R C */
extern bool_t xdr_complex ();
extern bool_t xdr_COMPLEX ();
extern bool_t xdr_scsuma_1_argument ();
extern bool_t xdr_scproductoconescalar_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_COMPLEX_RPC_H_RPCGEN */
