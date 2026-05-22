#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>

#include "Core/GameInstance.h"

#define GInput (*GameInstance::GetInstance().GetInputManager())

#endif //PCH_H
