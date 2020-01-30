/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _REMOTECALLS_RPC_H_RPCGEN
#define _REMOTECALLS_RPC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct STR str;

struct STR {
	char arr[100];
	int ln;
};
typedef struct STR STR;

typedef struct DATA data;

struct DATA {
	int arr[1000];
	int ln;
	int key;
};
typedef struct DATA DATA;

struct issubstring_1_argument {
	str s1;
	str s2;
};
typedef struct issubstring_1_argument issubstring_1_argument;

#define REMOTECALLS 0x20000001
#define REMOTECALLS_1 1

#if defined(__STDC__) || defined(__cplusplus)
#define isSubstring 1
extern  int * issubstring_1(str , str , CLIENT *);
extern  int * issubstring_1_svc(str , str , struct svc_req *);
#define search 2
extern  int * search_1(data , CLIENT *);
extern  int * search_1_svc(data , struct svc_req *);
#define sort 3
extern  data * sort_1(data , CLIENT *);
extern  data * sort_1_svc(data , struct svc_req *);
#define printArray 4
extern  void * printarray_1(data , CLIENT *);
extern  void * printarray_1_svc(data , struct svc_req *);
#define fact 5
extern  long * fact_1(int , CLIENT *);
extern  long * fact_1_svc(int , struct svc_req *);
extern int remotecalls_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define isSubstring 1
extern  int * issubstring_1();
extern  int * issubstring_1_svc();
#define search 2
extern  int * search_1();
extern  int * search_1_svc();
#define sort 3
extern  data * sort_1();
extern  data * sort_1_svc();
#define printArray 4
extern  void * printarray_1();
extern  void * printarray_1_svc();
#define fact 5
extern  long * fact_1();
extern  long * fact_1_svc();
extern int remotecalls_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_str (XDR *, str*);
extern  bool_t xdr_STR (XDR *, STR*);
extern  bool_t xdr_data (XDR *, data*);
extern  bool_t xdr_DATA (XDR *, DATA*);
extern  bool_t xdr_issubstring_1_argument (XDR *, issubstring_1_argument*);

#else /* K&R C */
extern bool_t xdr_str ();
extern bool_t xdr_STR ();
extern bool_t xdr_data ();
extern bool_t xdr_DATA ();
extern bool_t xdr_issubstring_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_REMOTECALLS_RPC_H_RPCGEN */