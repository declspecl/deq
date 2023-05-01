#pragma once

#include <vector>
#include <memory>

struct ASTNode
{
	int value;
	ASTNode* parent;
	std::vector<std::unique_ptr<ASTNode>> children;

	ASTNode(int value, ASTNode* parent = nullptr, std::vector<std::unique_ptr<ASTNode>> children = {})
		: value(value), parent(parent), children(children) {}
};

typedef ASTNode AST;