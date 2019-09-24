#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <cstdint>
#include <sstream>
#include <limits>
#include <queue>
#include <map>
#include <list>
#include <stack>
#include <random>
#include <tuple>

typedef intptr_t int_t;

class Rand
{
public:
	int_t operator ()()  { return static_cast<int_t>(_rand()); };

	void seed(int_t v = 0) { _rand.seed(static_cast<std::default_random_engine::result_type>(v)); }
	
private:
	std::default_random_engine _rand;
};



#ifdef _DEBUG
#define PRINT_ERROR(textMsg) std::cout << textMsg << std::endl;
#else
#define PRINT_ERROR(textMsg)
#endif

#include "Math/Vector2d.h"


using namespace  std;

using namespace std::chrono_literals;

using time_point = std::chrono::steady_clock::time_point;

typedef int64_t time_span;

typedef pair<int64_t, int64_t> ID;

//typedef tuple<int64_t, int64_t> ID;
//
//inline bool operator < (const ID& lId, const ID& rId)
//{
//	if(get<0>(lId) < get<0>(rId))
//	{
//		return true;
//	}
//	if(get<0>(lId) == get<0>(rId))
//	{
//		return get<1>(lId) < get<1>(rId);
//	}
//	return false;
//}

#include "Entity.h"


