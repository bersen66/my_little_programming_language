#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stack>

#include "objects/object.h"

class VirtualMachine {
public:

    VirtualMachine() = default;
    VirtualMachine(const VirtualMachine&) = delete;
    VirtualMachine& operator=(const VirtualMachine&) = delete;

    void CreateVar(const std::string& name, ObjPtr value);

    void Push(ObjPtr value);
    void Push(const std::string& varname);

    ObjPtr Top();

    const std::unordered_map<std::string, ObjPtr>& GetResults() const;

private:

    std::unordered_map<std::string, ObjPtr> var_map_;
    std::stack<ObjPtr> run_stack_;
};
