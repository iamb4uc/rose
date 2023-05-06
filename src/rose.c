#include "client.h"
#include "lua.h"
#include <stdlib.h>
#include <signal.h>

void at_exit()
{
	rose_client_destroy_all();
}

int main()
{
	/* Setup */
#if GTK == 3
	gtk_init(0, NULL);
#elif GTK == 4
	gtk_init();
#endif
	srand(time(NULL));
	atexit(at_exit);

	signal(SIGINT, (void *)rose_client_destroy_all);
	signal(SIGTERM, (void *)rose_client_destroy_all);
	signal(SIGKILL, (void *)rose_client_destroy_all);

	rose_lua_state_get();
	rose_client_new();

	while (1)
		g_main_context_iteration(NULL, TRUE);

	return 0;
}
