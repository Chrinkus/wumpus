//
// Created by Chris Schick on 2018-06-18.
//

#ifndef WUMPUS_TEXT_TREE_H
#define WUMPUS_TEXT_TREE_H

#include <string>
#include <unordered_map>
#include <memory>

class Text_component {
public:
    using key_t = std::string;
    using value_t = std::string;

    virtual ~Text_component() = default;

    Text_component(Text_component&) = delete;
    Text_component& operator=(Text_component&) = delete;

    Text_component(Text_component&&) = default;
    Text_component& operator=(Text_component&&) = default;

    virtual void add(Text_component&&) { }
    virtual const key_t& get() const { return content; }
protected:
    explicit Text_component(key_t s) : content{std::move(s)} { }
private:
    key_t content;
};

/*
class Text_primitive : public Text_component {
public:
    explicit Text_primitive(key_t s) : Text_component{std::move(s)} { }
};

class Text_composite : public Text_component {
public:
    explicit Text_composite(key_t s = key_t{})
        : Text_component{std::move(s)} { }

    Text_composite(Text_composite&) = delete;
    Text_composite& operator=(Text_composite&) = delete;

    Text_composite(Text_composite&&) = default;
    Text_composite& operator=(Text_composite&&) = default;

    void add(Text_component&& tc) override
    {
        tree[tc.get()] = std::make_unique<Text_component>(tc);
    }

private:
    std::unordered_map<key_t,std::unique_ptr<Text_component>> tree;
};
*/

class Text_branch : public Text_component {
public:
    explicit Text_branch(key_t k) : Text_component{std::move(k)} { }

    Text_component& operator[](const key_t& k) { return table[k]; }

    void add(Text_component&& tc) override
    {
        tree[tc.get()]
    }
private:
    std::unordered_map<key_t,Text_component&> table;
};

class Text_root : public Text_branch {
public:
    Text_root() : Text_branch{key_t{}} { }

    const Text_component& operator()(std::initializer_list<key_t> lst)
    {
        Text_component* tc = this;
        for (auto& elem : lst)
            tc = &((*tc)[elem]);
    }
};

#endif //WUMPUS_TEXT_TREE_H
