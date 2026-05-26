#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cassert>
#include <memory>
#include <algorithm>
#include "Core/GameInstance.h"

#define GInput (*GameInstance::GetInstance().GetInputManager())
#define GLog (GameInstance::GetInstance().GetLogManager())

#endif //PCH_H
