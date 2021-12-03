#pragma once

#include "node.h"

#include <iostream>
#include <memory>

#include "test_runner.h"

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();
