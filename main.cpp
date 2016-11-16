#include <iostream>
#include "src/glContext.h"

int main(int argc, char* argv[])
{
	glContext context = glContext("Hello World!", 500, 500, false);

	system("pause");
	return 0;
}