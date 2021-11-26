#include "node.h"

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
    switch (cmp)
    {
        case Comparison::Less:
            return date < node_date;
            break;
        case Comparison::LessOrEqual:
            return date <= node_date;
            break;
        case Comparison::Greater:
            return date > node_date;
            break;
        case Comparison::GreaterOrEqual:
            return date >= node_date;
            break;
        case Comparison::Equal:
            return date == node_date;
            break;
        case Comparison::NotEqual:
            return date != node_date;
            break;
    }

    return false;
}


bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
    switch (cmp)
    {
        case Comparison::Less:
            return event < node_event;
            break;
        case Comparison::LessOrEqual:
            return event <= node_event;
            break;
        case Comparison::Greater:
            return event > node_event;
            break;
        case Comparison::GreaterOrEqual:
            return event >= node_event;
            break;
        case Comparison::Equal:
            return event == node_event;
            break;
        case Comparison::NotEqual:
            return event != node_event;
            break;
    }

    return false;
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
    if (operation == LogicalOperation::And)
    {
        return left->Evaluate(date, event) && right->Evaluate(date, event);
    }

    if (operation == LogicalOperation::Or)
    {
        return left->Evaluate(date, event) or right->Evaluate(date, event);
    }

    return false;
}
