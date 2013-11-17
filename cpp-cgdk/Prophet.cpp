#include "Prophet.h"
#include "ActionChain.h"

Prophet::Prophet()
{
}


Prophet::~Prophet()
{
}

ActionChain* Prophet::chooseBest(std::list<ActionChain*> chains){
	//TODO: implement mega cool algorithm here
	return chains.empty() ? NULL : *(chains.begin());
}