#pragma once

#ifndef DELETE_MACROS_H

#define DELETE_MACROS_H

// removing of instances.
// Delete ptr
#define DELETE_PTR(PTR) if(PTR != nullptr) { delete PTR; PTR = nullptr; }

// Delete vector and clear pointer
#define DELETE_VECTOR(VECTOR){			              \
	for (unsigned int i = 0; i < VECTOR.size(); i++)  \
		delete VECTOR.at(i);						  \
    VECTOR.clear();									  }

// Delete map
#define DELETE_MAP(MAP){							  \
	for(auto it = MAP.begin(); it != MAP.end(); ++it) \
		delete it->second;							  \
	MAP.clear();									  }

#endif // !DELETE_MACROS_H

