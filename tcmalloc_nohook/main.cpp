
#include <gperftools/tcmalloc.h>

int main()
{
	void *p = tc_malloc(256);
	tc_free(p);
	return 0;
}
