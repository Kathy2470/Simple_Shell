#include <stdio.h>
#include <unistd.h>

int main(void)
{
	fork();
	printf("%u This is my pid\n", getpid());
	
	return (0);
}
