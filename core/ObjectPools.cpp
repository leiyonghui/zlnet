#include "ObjectPools.h"

namespace core
{
	std::map<std::string, std::function<void()>> CObjectPoolMonitor::ObjectPoolMap;

}