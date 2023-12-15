#ifndef __UTILS_H__
#define __UTILS_H__


#define UNUSED(x) (void)(x)

#define MIN(__x, __y) \
  ((__x) < (__y) ? (__x) : (__y))

#define MAX(__x, __y) \
  ((__x) > (__y) ? (__x) : (__y))

/*
	Used to use a display function only if _x is true
*/
#define DISPLAY(_x, _y)\
	(_x) ? (_y) : UNUSED(_x);



#endif
