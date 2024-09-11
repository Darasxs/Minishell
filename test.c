#include "minishell.h"

char	*find_path(const char *path)
{
	char	*result;

	result = getenv("PATH");
	return (result);
}

int main(void)
{
	const char	*result;

	result = find_path(result);
	printf("%s\n", result);
	return 0;
}