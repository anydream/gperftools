#include <string.h>
#include <stdio.h>
#include <time.h>
#include <thread>

#if 1
#include <gperftools/tcmalloc.h>
#define ALLOC	tc_malloc
#define FREE	tc_free
#else
#include <stdlib.h>
#define ALLOC	malloc
#define FREE	free
#endif

static int g_AllocSize = 0;
static void PerfProc()
{
	char *checkbuf = (char*)alloca(g_AllocSize);
	for (int i = 0; i < g_AllocSize; ++i)
		checkbuf[i] = (char)(rand() % 256);

	auto stt = clock();
	size_t loops = 0;
	for (;;)
	{
		void *p = ALLOC(g_AllocSize);
		memcpy(p, checkbuf, g_AllocSize);
		if (memcmp(p, checkbuf, g_AllocSize) != 0)
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
}

int main()
{
	printf("Input size: ");
	scanf("%d", &g_AllocSize);

	std::thread thd1(&PerfProc);
	std::thread thd2(&PerfProc);
	thd1.join();
	thd2.join();
	getchar();
	return 0;
}
