#include <string.h>
#include <stdio.h>
#include <time.h>

#if 1
#include <gperftools/tcmalloc.h>
#define ALLOC	tc_malloc
#define FREE	tc_free
#else
#include <stdlib.h>
#define ALLOC	malloc
#define FREE	free
#endif

int main()
{
	const char checkbuf[256] = { 1, 2, 3, 4 };

	auto stt = clock();
	size_t loops = 0;
	for (;;)
	{
		void *p = ALLOC(sizeof(checkbuf));
		memcpy(p, checkbuf, sizeof(checkbuf));
		if (memcmp(p, checkbuf, sizeof(checkbuf)) != 0)
		{
			printf("Fail!\n");
			break;
		}
		FREE(p);
		++loops;

		auto cut = clock();
		if (cut - stt >= 5000)
			break;
	}
	printf("Loops: %u\n", loops);

	return 0;
}
