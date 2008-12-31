// Includes
#include "GameInfo.h"

namespace info {
	char* theName;
	char* theCreator;

	GameInfo::GameInfo(char* aName, char* aCreator) {
		theName = aName;
		theCreator = aCreator;
	}

	GameInfo::~GameInfo(void) {}
	
	// getters
	char* GameInfo::getName() {
		return theName;
	}
	char* GameInfo::getCreator() {
		return theCreator;
	}
		
}



