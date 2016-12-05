#ifndef _A_H_
#define _A_H_

#ifdef __cplusplus
extern "C"
{
#endif
int abs(int a)
{
   return a>0 ? a : -a;
}

double abs2(double a)
{
   return a>0 ? a : -a;
}

#ifdef __cplusplus
}
#endif

#endif
