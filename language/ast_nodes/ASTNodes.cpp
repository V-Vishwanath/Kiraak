
#include "ASTNodes.h"



std::string LiteralNode::toString() const {
    std::stringstream ss;
    ss << token;
    return ss.str();
}


std::string UnaryExprNode::toString() const {
    std::stringstream ss;
    ss << (opToken.type == TOKENTYPE::ADD ? "" : "-") << exprNode->toString();
    return ss.str();
}


std::string BinaryExprNode::toString() const {
    std::stringstream ss;

    ss << "(";
    ss << left->toString() << " " << opToken << " " << right->toString();
    ss <<")";

    return ss.str();
}


std::ostream& operator << (std::ostream &os, ASTNode* rootNode) {
    if (auto *node = dynamic_cast<LiteralNode*>(rootNode)) {
        return os << node->toString();
    }

    if (auto node = dynamic_cast<UnaryExprNode*>(rootNode)) {
        return os << node->toString();
    }

    if (auto node = dynamic_cast<BinaryExprNode*>(rootNode)) {
        return os << node->toString();
    }

    return os;
}
