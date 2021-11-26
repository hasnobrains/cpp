#pragma once

#include "date.h"
#include <memory>

using namespace std;

class Node
{
  public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node
{
  public:
    bool Evaluate(const Date& date, const string& event) const override
    {
        return true;
    }
};

enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

class DateComparisonNode : public Node
{
  public:
    DateComparisonNode(const Comparison cmp, const Date& date)
        : cmp(cmp), node_date(date)
    {
    }

    bool Evaluate(const Date& date, const string& event) const override;

  private:
    const Comparison cmp;
    const Date node_date;
};

class EventComparisonNode : public Node
{
  public:
    EventComparisonNode(const Comparison cmp, const string& event)
        : cmp(cmp), node_event(event)
    {
    }

    bool Evaluate(const Date& date, const string& event) const override;

  private:
    const Comparison cmp;
    const string node_event;
};

enum class LogicalOperation
{
    And,
    Or
};

class LogicalOperationNode : public Node
{
  public:
    LogicalOperationNode(LogicalOperation operation,
                         shared_ptr<const Node> left,
                         shared_ptr<const Node> right)
        : operation(operation), left(left), right(right)
    {
    }

    bool Evaluate(const Date& date, const string& event) const override;

  private:
    const LogicalOperation operation;
    shared_ptr<const Node> left, right;
};
