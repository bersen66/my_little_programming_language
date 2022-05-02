#pragma once

#include <string>
#include <memory>

#include "virtual_machine.h"
#include "objects/object.h"
#include "parsers/parsing_stuff.h"


struct Instruction;

using InstructionHolder = std::unique_ptr<Instruction>;

struct Instruction {

    enum class Type {
        ADD,
        MUL,
        DIV,
        SUB,
        ASN,
        CRT,
        LT,
        GT,
        LTOE,
        GTOE,
        OR,
        AND,
        EQ,
        NEQ,
        PUSH,

        GET,
        ISVAL,
        HSNXT,
        HSPRV,
        INSA,
        INSB,
        ERS,
    };

    Instruction(Type t) : type(t) {}

    virtual void ParseFrom(std::string_view &input) = 0;

    virtual void Process(VirtualMachine &vm) = 0;

    virtual ~Instruction() = default;

    const Type type;
};


const std::unordered_map<std::string_view, Instruction::Type> STRING_TO_INSTRUCTION = {
        {"ADD",   Instruction::Type::ADD},
        {"ASN",   Instruction::Type::ASN},
        {"DIV",   Instruction::Type::DIV},
        {"MUL",   Instruction::Type::MUL},
        {"SUB",   Instruction::Type::SUB},

        {"LT",    Instruction::Type::LT},
        {"GT",    Instruction::Type::GT},
        {"LTOE",  Instruction::Type::LTOE},
        {"GTOE",  Instruction::Type::GTOE},
        {"OR",    Instruction::Type::OR},
        {"AND",   Instruction::Type::AND},
        {"EQ",    Instruction::Type::EQ},
        {"NEQ",   Instruction::Type::NEQ},

        {"CRT",   Instruction::Type::CRT},
        {"PUSH",  Instruction::Type::PUSH},

        {"GET",   Instruction::Type::GET},
        {"ISVAL", Instruction::Type::ISVAL},
        {"HSNXT", Instruction::Type::HSNXT},
        {"HSPRV", Instruction::Type::HSPRV},
        {"INSA",  Instruction::Type::INSA},
        {"INSB",  Instruction::Type::INSB},
        {"ERS",   Instruction::Type::ERS},
};

struct AddInstruction : public Instruction {
    AddInstruction() : Instruction(Type::ADD) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs + rhs);
    }


    void ParseFrom(std::string_view &input) override {
        return;
    }

};

struct SubInstruction : public Instruction {
    SubInstruction() : Instruction(Type::SUB) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs - rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct MulInstruction : public Instruction {
    MulInstruction() : Instruction(Type::MUL) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs * rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct DivInstruction : public Instruction {
    DivInstruction() : Instruction(Type::DIV) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs / rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct LTInstruction : public Instruction {
    LTInstruction() : Instruction(Type::LT) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs < rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct GTInstruction : public Instruction {
    GTInstruction() : Instruction(Type::GT) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs > rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct GTOEInstruction : public Instruction {
    GTOEInstruction() : Instruction(Type::GTOE) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs >= rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct LTOEInstruction : public Instruction {
    LTOEInstruction() : Instruction(Type::LTOE) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs <= rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct ORInstruction : public Instruction {
    ORInstruction() : Instruction(Type::OR) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(OR(lhs, rhs));
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct ANDInstruction : public Instruction {
    ANDInstruction() : Instruction(Type::AND) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(AND(lhs, rhs));
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct EQInstruction : public Instruction {
    EQInstruction() : Instruction(Type::EQ) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs == rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct NEQInstruction : public Instruction {
    NEQInstruction() : Instruction(Type::NEQ) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs != rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};


struct GETInstruction : public Instruction {
    GETInstruction() : Instruction(Type::GET) {}

    void Process(VirtualMachine &vm) override {
        const auto &iterator = vm.Top();
        vm.Push(GET(iterator));
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct ISVALInstruction : public Instruction {
    ISVALInstruction() : Instruction(Type::ISVAL) {}

    void Process(VirtualMachine &vm) override {
        const auto &iterator = vm.Top();
        vm.Push(ISVAL(iterator));
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct HSNXTInstruction : public Instruction {
    HSNXTInstruction() : Instruction(Type::HSNXT) {}

    void Process(VirtualMachine &vm) override {
        const auto &iterator = vm.Top();
        vm.Push(HSNXT(iterator));
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct HSPRVInstruction : public Instruction {
    HSPRVInstruction() : Instruction(Type::HSPRV) {}

    void Process(VirtualMachine &vm) override {
        const auto &iterator = vm.Top();
        vm.Push(HSPRV(iterator));
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct INSAInstruction : public Instruction {
    INSAInstruction() : Instruction(Type::INSA) {}

    void Process(VirtualMachine &vm) override {
        auto value = vm.Top();
        auto second_token = vm.Top();

        if (second_token->type == Obj::Type::BASIC_ITERATOR) {
            ObjPtr container = vm.Top();
            vm.Push(INSA(container, second_token, value));
        } else if (second_token->type == Obj::Type::BASIC_LINKED_LIST){
            vm.Push(INSA(second_token, value));
        }
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct INSBInstruction : public Instruction {
    INSBInstruction() : Instruction(Type::INSB) {}

    void Process(VirtualMachine &vm) override {
        auto value = vm.Top();
        auto second_token = vm.Top();

        if (second_token->type == Obj::Type::BASIC_ITERATOR) {
            auto container = vm.Top();
            vm.Push(INSB(container, second_token, value));
        } else if (second_token->type == Obj::Type::BASIC_LINKED_LIST){
            vm.Push(INSB(second_token, value));
        }
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

struct ERSInstruction : public Instruction {
    ERSInstruction() : Instruction(Type::ERS) {}

    void Process(VirtualMachine &vm) override {
        auto iterator = vm.Top();
        auto container = vm.Top();
        vm.Push(ERS(container, iterator));
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};


struct CrtInstruction : public Instruction {
    CrtInstruction() : Instruction(Type::CRT) {}

    void Process(VirtualMachine &vm) override {

        vm.CreateVar(name,
                     MakeObj(STRING_TO_TYPE.at(type))
        );
    }

    void ParseFrom(std::string_view &input) override {
        name = ReadToken(input);
        type = ReadToken(input);
    }

    std::string name;
    std::string type;
};

struct PushInstruction : public Instruction {
    PushInstruction() : Instruction(Type::PUSH) {}

    void Process(VirtualMachine &vm) override {
        if (STRING_TO_TYPE.contains(first_token)) {
            auto obj_type = STRING_TO_TYPE.at(first_token);

            switch (obj_type) {
                case Obj::Type::BASIC_INT: {
                    ObjPtr result = std::make_shared<Int>(
                            // std::atoi(second_token.c_str())
                            second_token
                    );

                    vm.Push(result);
                }
                    break;
                case Obj::Type::BASIC_BOOL: {
                    ObjPtr result = std::make_shared<Bool>(
                            second_token
                    );
                    vm.Push(result);
                }
                    break;
            }

        } else {
            vm.Push(second_token);
            //throw std::runtime_error("ERROR IN PUSHING. INVALID_TYPE");
        }
    }

    void ParseFrom(std::string_view &input) override {
        first_token = ReadToken(input);
        second_token = ReadToken(input);
    }

    std::string first_token;
    std::string second_token;

};

struct AsnInstruction : public Instruction {
    AsnInstruction() : Instruction(Type::ASN) {}

    void Process(VirtualMachine &vm) override {
        auto rhs = vm.Top();
        auto lhs = vm.Top();
        lhs->Assign(rhs);
    }

    void ParseFrom(std::string_view &input) override {
        return;
    }
};

InstructionHolder MakeInstruction(Instruction::Type type) {
    switch (type) {
        case Instruction::Type::DIV: {
            return std::make_unique<DivInstruction>();
        }
            break;

        case Instruction::Type::MUL: {
            return std::make_unique<MulInstruction>();
        }
            break;

        case Instruction::Type::ADD: {
            return std::make_unique<AddInstruction>();
        }
            break;

        case Instruction::Type::SUB: {
            return std::make_unique<SubInstruction>();
        }
            break;

        case Instruction::Type::ASN: {
            return std::make_unique<AsnInstruction>();
        }
            break;

        case Instruction::Type::LT: {
            return std::make_unique<LTInstruction>();
        }
            break;

        case Instruction::Type::LTOE: {
            return std::make_unique<LTOEInstruction>();
        }
            break;

        case Instruction::Type::GT: {
            return std::make_unique<GTInstruction>();
        }
            break;

        case Instruction::Type::GTOE: {
            return std::make_unique<GTOEInstruction>();
        }
            break;

        case Instruction::Type::OR: {
            return std::make_unique<ORInstruction>();
        }
            break;

        case Instruction::Type::AND: {
            return std::make_unique<ANDInstruction>();
        }
            break;

        case Instruction::Type::EQ: {
            return std::make_unique<EQInstruction>();
        }
            break;

        case Instruction::Type::NEQ: {
            return std::make_unique<NEQInstruction>();
        }
            break;

        case Instruction::Type::PUSH: {
            return std::make_unique<PushInstruction>();
        }
            break;

        case Instruction::Type::CRT: {
            return std::make_unique<CrtInstruction>();
        }
            break;

        case Instruction::Type::ERS: {
            return std::make_unique<ERSInstruction>();
        }
            break;

        case Instruction::Type::GET: {
            return std::make_unique<GETInstruction>();
        }
            break;

        case Instruction::Type::HSNXT: {
            return std::make_unique<HSNXTInstruction>();
        }
            break;

        case Instruction::Type::HSPRV: {
            return std::make_unique<HSPRVInstruction>();
        }
            break;

        case Instruction::Type::INSA: {
            return std::make_unique<INSAInstruction>();
        }
            break;

        case Instruction::Type::INSB: {
            return std::make_unique<INSBInstruction>();
        }
            break;

        case Instruction::Type::ISVAL: {
            return std::make_unique<ISVALInstruction>();
        }
            break;
    }
    throw std::runtime_error("NOT IMPLEMENTED INSTRUCTION");
}


std::vector<InstructionHolder> ReadInstructions(std::istream &in = std::cin) {
    std::vector<InstructionHolder> result;

    for (std::string command; getline(in, command);) {
        std::string_view cmd_view = command;
        auto cmd_type = STRING_TO_INSTRUCTION.at(ReadToken(cmd_view));
        auto instruction = MakeInstruction(cmd_type);
        instruction->ParseFrom(cmd_view);
        result.push_back(std::move(instruction));
    }

    return result;
}

void ProcessInstructions(std::vector<InstructionHolder> &&instructions, VirtualMachine &vm) {
    for (auto &instr: instructions) {
        instr->Process(vm);
    }
}