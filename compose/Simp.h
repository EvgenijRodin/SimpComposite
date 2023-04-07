#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>

struct SimplexContent
{
    int dimLimit = 0;
    size_t combLimit = 0;
    std::vector<int> id{};

    SimplexContent(){}
    SimplexContent(const int inDimLimit, const std::vector<int>& inId) :dimLimit(inDimLimit), combLimit(inId.size()), id(inId) {};
    SimplexContent(const int inDimLimit, const std::initializer_list<int>& inId) :dimLimit(inDimLimit), combLimit(inId.size()), id(inId) {};

    void printRest() { std::cout << "dim Limit = " << dimLimit << ", combLimit = " << combLimit << "\n"; }

    friend std::ostream& operator << (std::ostream& os, SimplexContent& cont)
    {
        os << "[ ";

        for (int item : cont.id)
        {
            os << item << " ";
        }
        os << "]\n";
        return os;
    }
};


class SimplexBase
{   
protected:
    
public:
    SimplexContent content;

    virtual void addChild(SimplexBase& child) = 0;
    virtual void addParent(SimplexBase& parent) = 0;
    virtual void removeChild(std::vector<int>& id) = 0;
    virtual void removeParent(std::vector<int>& id) = 0;
    virtual SimplexBase& getChild(std::vector<int>& id) = 0;
    virtual SimplexBase& getFirstChild() = 0;
    virtual SimplexBase& getParent(std::vector<int>& id) = 0;
    virtual SimplexBase& getFirstParent() = 0;
    virtual void setContent (const int inDimLimit, const std::initializer_list<int>& inId) = 0;
    virtual void setContent(const int inDimLimit, const std::vector<int>& inId) = 0;
    virtual bool isEmpty() = 0;
};

class Simplex : public SimplexBase
{
protected:
    std::vector<SimplexBase*> parents;
    std::vector<SimplexBase*> children;
    
public:
    Simplex() {}
    Simplex(const int inDimLimit, const std::initializer_list<int>& inId) { setContent(inDimLimit, inId); }
    Simplex(const int inDimLimit, const std::vector<int>& inId) { setContent(inDimLimit, inId); }

    void addChild(SimplexBase& child) override;
    void addParent(SimplexBase& parent) override;
    void removeChild(std::vector<int>& id) override;
    void removeParent(std::vector<int>& id) override;
    SimplexBase& getFirstChild() override;
    SimplexBase& getChild(std::vector<int>& id) override;
    SimplexBase& getFirstParent() override;
    SimplexBase& getParent(std::vector<int>& id) override;
    void setContent(const int inDimLimit, const std::initializer_list<int>& inId) override;
    void setContent(const int inDimLimit, const std::vector<int>& inId) override;
    bool isEmpty() override;

    friend std::ostream& operator << (std::ostream& os, Simplex& simp)
    {
        os << simp.content;
        return os;
    }

    friend bool operator < (const Simplex& lhs, const Simplex& rhs)
    {
        auto lhsLim = lhs.content.combLimit;
        auto rhsLim = rhs.content.combLimit;

        if (lhsLim < rhsLim)
        {
            return true;
        }

        if (lhsLim == rhsLim)
        {
            for (size_t i = 0; i < lhsLim; i++)
            {
                if (lhs.content.id[i] < rhs.content.id[i])
                {
                    return true;
                }
                else if (lhs.content.id[i] > rhs.content.id[i])
                {
                    return false;
                }
                else
                {
                    // we skip to the next entry
                }
            }

            return false;
        }


        return false;
    }
    friend bool operator > (const Simplex& lhs, const Simplex& rhs) { return rhs < lhs; }
    friend bool operator <= (const Simplex& lhs, const Simplex& rhs) { return !(lhs > rhs); }
    friend bool operator >= (const Simplex& lhs, const Simplex& rhs) { return !(lhs < rhs); }
    friend bool operator == (const Simplex& lhs, const Simplex& rhs) { return lhs.content.id == rhs.content.id; }
    friend bool operator != (const Simplex& lhs, const Simplex& rhs) { return !(lhs == rhs); }
};

class EmptySimplex : public Simplex
{
private:
    EmptySimplex() {}
protected:
    void addChild(SimplexBase& child) override {};
    void addParent(SimplexBase& parent) override {};
    void removeChild(std::vector<int>& id) override {};
    void removeParent(std::vector<int>& id) override {};
    SimplexBase& getChild(std::vector<int>& id) override { return get(); };
    SimplexBase& getFirstChild() override { return get(); };
    SimplexBase& getParent(std::vector<int>& id) override { return get(); };
    SimplexBase& getFirstParent() override { return get(); };
    void setContent(const int inDimLimit, const std::initializer_list<int>& inId) override {};
    void setContent(const int inDimLimit, const std::vector<int>& inId) override {};
    bool isEmpty() override { return true; };
public:
    EmptySimplex(EmptySimplex const&) = delete;
    void operator = (EmptySimplex const&) = delete;

    static EmptySimplex& get()
    {
        static EmptySimplex empty;
        return empty;
    }
};






