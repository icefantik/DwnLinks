#include "dir.h"
#include "href.h"
#include "flink.h"

int main()
{
	
	setlocale(LC_ALL, "Rus");
	selcFile("html", DIRLINKS); // search file on exten 
	selcFile("html", DOWNDIR);	
	return 0;
}
