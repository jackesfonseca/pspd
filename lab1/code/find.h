/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _FIND_H_RPCGEN
#define _FIND_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct operandos {
	float vet[10];
};
typedef struct operandos operandos;

#define PROG 55555555
#define VERSAO 100

#if defined(__STDC__) || defined(__cplusplus)
#define BIGGER 1
extern  float * bigger_100(operandos *, CLIENT *);
extern  float * bigger_100_svc(operandos *, struct svc_req *);
#define SMALLER 2
extern  float * smaller_100(operandos *, CLIENT *);
extern  float * smaller_100_svc(operandos *, struct svc_req *);
extern int prog_100_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define BIGGER 1
extern  float * bigger_100();
extern  float * bigger_100_svc();
#define SMALLER 2
extern  float * smaller_100();
extern  float * smaller_100_svc();
extern int prog_100_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_operandos (XDR *, operandos*);

#else /* K&R C */
extern bool_t xdr_operandos ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_FIND_H_RPCGEN */