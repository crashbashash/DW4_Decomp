typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union { double value; struct { __uint32_t lsw; __uint32_t msw; } parts; } ieee_double_shape_type;
extern const double DAT_004d3c78;
#define huge DAT_004d3c78

double FUN_00122590(double x)
{
	__int32_t i0,i1,j0;
	__uint32_t i,j;
	do { ieee_double_shape_type ew_u; ew_u.value = x; i0 = ew_u.parts.msw; i1 = ew_u.parts.lsw; } while (0);
	j0 = ((i0>>20)&0x7ff)-0x3ff;
	if(j0<20) {
	    if(j0<0) {
		if(x+huge>0.0) {
		    if(i0>=0) {i0=i1=0;}
		    else if(((i0&0x7fffffff)|i1)!=0) { i0=0xbff00000;i1=0;}
		}
	    } else {
		i = (0x000fffff)>>j0;
		if(((i0&i)|i1)==0) return x;
		if(x+huge>0.0) {
		    if(i0<0) i0 += (0x00100000)>>j0;
		    i0 &= (~i); i1=0;
		}
	    }
	} else if (j0>51) {
	    if(j0==0x400) return x+x;
	    else return x;
	} else {
	    i = ((__uint32_t)(0xffffffff))>>(j0-20);
	    if((i1&i)==0) return x;
	    if(x+huge>0.0) {
		if(i0<0) {
		    if(j0==20) i0+=1;
		    else {
			j = i1 + (1<<(52-j0));
			if(j<(__uint32_t)i1) i0+=1;
			i1 = j;
		    }
		}
		i1 &= (~i);
	    }
	}
	do { ieee_double_shape_type iw_u; iw_u.parts.msw = i0; iw_u.parts.lsw = i1; x = iw_u.value; } while (0);
	return x;
}
