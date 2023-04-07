#include "Simp.h"
// Simplex

void Simplex::addChild(SimplexBase& child) 
{
	children.push_back(&child);
}

void Simplex::addParent(SimplexBase& parent) 
{
	parents.push_back(&parent);
}

void Simplex::removeChild(std::vector<int>& id)
{
	if (children.empty()) 
	{ 
		return;
	}

	for(auto it = children.begin();it != children.end();it++)
	{
		if((*it)->content.id == id)
		{
			children.erase(it);
			return;
		}
	}

	return;
}

void Simplex::removeParent(std::vector<int>& id)
{
	if (parents.empty())
	{
		return;
	}

	for (auto it = parents.begin(); it != parents.end(); it++)
	{
		if ((*it)->content.id == id)
		{
			parents.erase(it);
			return;
		}
	}

	return;
}

SimplexBase& Simplex::getChild(std::vector<int>& id)
{
	if (children.empty())
	{
		return EmptySimplex::get();
	}

	for (auto it = children.begin(); it != children.end(); it++)
	{
		if ((*it)->content.id == id)
		{
			return *(*(it));
		}
	}

	return EmptySimplex::get();
}

SimplexBase& Simplex::getFirstChild()
{
	if (children.empty())
	{
		return EmptySimplex::get();
	}
	return *children.front();
}

SimplexBase& Simplex::getParent(std::vector<int>& id)
{
	if (parents.empty())
	{
		return EmptySimplex::get();
	}

	for (auto it = parents.begin(); it != parents.end(); it++)
	{
		if ((*it)->content.id == id)
		{
			return *(*(it));
		}
	}

	return EmptySimplex::get();
}

SimplexBase& Simplex::getFirstParent()
{
	if (children.empty())
	{
		return EmptySimplex::get();
	}
	return *parents.front();
}

void Simplex::setContent(const int inDimLimit, const std::initializer_list<int>& inId)
{
	content = SimplexContent( inDimLimit, inId);
}

void Simplex::setContent(const int inDimLimit, const std::vector<int>& inId) 
{
	content = SimplexContent(inDimLimit, inId);
}

bool Simplex::isEmpty()
{
	return *this == EmptySimplex::get();
}