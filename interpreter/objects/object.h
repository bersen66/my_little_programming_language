#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>


#include <boost/multiprecision/cpp_int.hpp>

#include "../containers/linked_list.h"

struct Obj;

using ObjPtr = std::shared_ptr<Obj>;

struct Obj {

    enum class Type {
        BASIC_INT,
        BASIC_BOOL,
        BASIC_ITERATOR,
        BASIC_LINKED_LIST,
    };

    explicit Obj(Type t) : type(t) {}

    virtual std::string ToString() const = 0;

    // Арифметика
    virtual bool HasSUMOperator() const = 0;

    virtual bool HasDIVOperator() const = 0;

    virtual bool HasMULOperator() const = 0;

    virtual bool HasSUBOperator() const = 0;

    // Логика
    virtual bool HasLTOperator() const = 0;

    virtual bool HasGTOperator() const = 0;

    virtual bool HasLTOEOperator() const = 0;

    virtual bool HasGTOEOperator() const = 0;

    virtual bool HasEQOperator() const = 0;

    virtual bool HasNEQOperator() const = 0;

    virtual bool HasOROperator() const = 0;

    virtual bool HasANDOperator() const = 0;

    // Контейнерные штуки:
    virtual bool HasGETOperator() const = 0;

    virtual bool HasISVALOperator() const = 0;

    virtual bool HasHSNXTOperator() const = 0;

    virtual bool HasHSPRVOperator() const = 0;

    virtual bool HasINSAOperator() const = 0;

    virtual bool HasINSBOperator() const = 0;

    virtual bool HasERSOperator() const = 0;


    virtual std::size_t Hash() const = 0;

    virtual ~Obj() = default;

    virtual void Assign(ObjPtr other) = 0;

    friend std::ostream &operator<<(std::ostream &out, const ObjPtr &value);

    const Type type;
};

struct ObjectHasher {
    size_t operator()(ObjPtr value) const {
        return value->Hash();
    }
};


class Int : public Obj {
public:
    Int() = default;

    explicit Int(const boost::multiprecision::cpp_int &value) : Obj(Type::BASIC_INT), value_(value) {}

    explicit Int(boost::multiprecision::cpp_int &&value) : Obj(Type::BASIC_INT), value_(value) {}

    explicit Int(const std::string &value) : Obj(Type::BASIC_INT), value_(value) {}

    bool HasSUMOperator() const override;

    bool HasDIVOperator() const override;

    bool HasMULOperator() const override;

    bool HasSUBOperator() const override;

    std::size_t Hash() const override;

    std::string ToString() const override;

    void Assign(ObjPtr other) override;

    bool HasLTOperator() const override;

    bool HasGTOperator() const override;

    bool HasLTOEOperator() const override;

    bool HasGTOEOperator() const override;

    bool HasEQOperator() const override;

    bool HasNEQOperator() const override;

    bool HasOROperator() const override;

    bool HasANDOperator() const override;

    bool HasGETOperator() const override;

    bool HasISVALOperator() const override;

    bool HasHSNXTOperator() const override;

    bool HasHSPRVOperator() const override;

    bool HasINSAOperator() const override;

    bool HasINSBOperator() const override;

    bool HasERSOperator() const override;


    friend ObjPtr operator+(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator-(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator/(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator*(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator<(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator<=(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator>(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator>=(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator==(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator!=(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr AND(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr OR(const ObjPtr &lhs, const ObjPtr &rhs);

private:
    boost::multiprecision::cpp_int value_;
};

class Bool : public Obj {
public:

    explicit Bool(const std::string &value)
            : Obj(Type::BASIC_BOOL), value_(value == "True" ? true : false) {}

    explicit Bool(bool value) : Obj(Type::BASIC_BOOL), value_(value) {}

    bool HasSUMOperator() const override;

    bool HasDIVOperator() const override;

    bool HasMULOperator() const override;

    bool HasSUBOperator() const override;

    std::size_t Hash() const override;

    std::string ToString() const override;

    void Assign(ObjPtr other) override;

    bool HasLTOperator() const override;

    bool HasGTOperator() const override;

    bool HasLTOEOperator() const override;

    bool HasGTOEOperator() const override;

    bool HasEQOperator() const override;

    bool HasNEQOperator() const override;

    bool HasOROperator() const override;

    bool HasANDOperator() const override;

    bool HasGETOperator() const override;

    bool HasISVALOperator() const override;

    bool HasHSNXTOperator() const override;

    bool HasHSPRVOperator() const override;

    bool HasINSAOperator() const override;

    bool HasINSBOperator() const override;

    bool HasERSOperator() const override;


    friend ObjPtr operator<(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator<=(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator>(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator>=(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator==(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr operator!=(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr AND(const ObjPtr &lhs, const ObjPtr &rhs);

    friend ObjPtr OR(const ObjPtr &lhs, const ObjPtr &rhs);

private:
    bool value_;
};


class Iterator : public Obj {
public:

    enum class State {
        IS_VALID,
        IS_INVALID,
    };

    Iterator() : Obj(Obj::Type::BASIC_ITERATOR), current_state(State::IS_INVALID) {}

    bool HasSUMOperator() const override;

    bool HasDIVOperator() const override;

    bool HasMULOperator() const override;

    bool HasSUBOperator() const override;

    std::size_t Hash() const override;

    std::string ToString() const override {
        if (current_state == State::IS_INVALID) {
            return "INVALID";
        }
        return "ITERATOR: " + value->value->ToString();
    }

    void Assign(ObjPtr other) override {
        if (other->type != Obj::Type::BASIC_ITERATOR) {
            throw std::runtime_error("Expected iterator in assignment");
        }

        // возможна утечка
        current_state = State::IS_VALID;
        auto othr = std::dynamic_pointer_cast<Iterator>(other);
        value = othr->value;
    }

    bool HasLTOperator() const override;

    bool HasGTOperator() const override;

    bool HasLTOEOperator() const override;

    bool HasGTOEOperator() const override;

    bool HasEQOperator() const override;

    bool HasNEQOperator() const override;

    bool HasOROperator() const override;

    bool HasANDOperator() const override;

    bool HasGETOperator() const override;

    bool HasISVALOperator() const override;

    bool HasHSNXTOperator() const override;

    bool HasHSPRVOperator() const override;

    bool HasINSAOperator() const override;

    bool HasINSBOperator() const override;

    bool HasERSOperator() const override;


    Iterator(bicycle::Node<ObjPtr> *val)
            : Obj(Obj::Type::BASIC_ITERATOR),
              value(val),
              current_state(value != nullptr ? State::IS_VALID : State::IS_INVALID) {}

    bicycle::Node<ObjPtr> *GetNode() {
        return value;
    }

    bool IsValid() const {
        return value != nullptr && current_state != State::IS_INVALID;
    }

    bool HasNext() const {
        return value != nullptr && value->HasNext();
    }

    bool HasPrev() const {
        return value != nullptr && value->HasPrev();
    }

    ~Iterator() {
    }


private:
    bicycle::Node<ObjPtr> *value;
    State current_state;

};

class LinkedList : public Obj {
public:
    LinkedList() : Obj(Obj::Type::BASIC_LINKED_LIST) {}

    bool HasSUMOperator() const override;

    bool HasDIVOperator() const override;

    bool HasMULOperator() const override;

    bool HasSUBOperator() const override;

    bool HasLTOperator() const override;

    bool HasGTOperator() const override;

    bool HasLTOEOperator() const override;

    bool HasGTOEOperator() const override;

    bool HasEQOperator() const override;

    bool HasNEQOperator() const override;

    bool HasOROperator() const override;

    bool HasANDOperator() const override;

    bool HasGETOperator() const override;

    bool HasISVALOperator() const override;

    bool HasHSNXTOperator() const override;

    bool HasHSPRVOperator() const override;

    bool HasINSAOperator() const override;

    bool HasINSBOperator() const override;

    bool HasERSOperator() const override;


    ObjPtr PushBack(const ObjPtr &value) {
        return std::make_shared<Iterator>(list_.PushBack(value));
    }

    ObjPtr PushFront(const ObjPtr &value) {
        return std::make_shared<Iterator>(list_.PushFront(value));
    }

    ObjPtr InsertBefore(const ObjPtr &iterator, const ObjPtr &value) {
        auto iter = std::dynamic_pointer_cast<Iterator>(iterator);
        return std::make_shared<Iterator>(list_.InsertBefore(iter->GetNode(), value));
    }

    ObjPtr InsertAfter(ObjPtr iterator, ObjPtr value) {
        auto it = std::dynamic_pointer_cast<Iterator>(iterator);
        return std::make_shared<Iterator>(list_.InsertAfter(it->GetNode(),value));
    }

    ObjPtr Erase(const ObjPtr &iterator) {
        auto iter = std::dynamic_pointer_cast<Iterator>(iterator);
        return std::make_shared<Iterator>(list_.Erase(iter->GetNode()));
    }

    std::size_t Hash() const override {
        return 0;
    }

    std::string ToString() const override {
        std::stringstream out;
        out << "<-> ";
        list_.TravelWithCallback([&out](const bicycle::Node<ObjPtr> *val) {
            out <<"("<< val->value->ToString() << ") <-> ";
        });
        return out.str();
    }

    void Assign(ObjPtr other) override {

    }


private:
   bicycle::LinkedList<ObjPtr> list_;
};


ObjPtr MakeObj(Obj::Type type);

std::ostream &operator<<(std::ostream &out, const Int &value);

//////////////////////////////////////////////////////////////////////////////////////////////////////
ObjPtr operator/(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator+(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator-(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator*(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator<(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator<=(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator>(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator>=(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator==(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr operator!=(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr AND(const ObjPtr &lhs, const ObjPtr &rhs);

ObjPtr OR(const ObjPtr &lhs, const ObjPtr &rhs);


ObjPtr GET(const ObjPtr &iterator);

ObjPtr ISVAL(const ObjPtr &iterator);

ObjPtr HSNXT(const ObjPtr &iterator);

ObjPtr HSPRV(const ObjPtr &iterator);

ObjPtr INSA(ObjPtr &lhs, ObjPtr &rhs);

ObjPtr INSA(ObjPtr &container, ObjPtr &iterator, ObjPtr &value);

ObjPtr INSB(ObjPtr &lhs, ObjPtr &rhs);

ObjPtr INSB(ObjPtr &container, ObjPtr &iterator, ObjPtr &value);

ObjPtr ERS(ObjPtr &container, const ObjPtr &iterator);


const std::unordered_map<std::string, Obj::Type> STRING_TO_TYPE = {
        {"Integer", Obj::Type::BASIC_INT},
        {"Bool",    Obj::Type::BASIC_BOOL},
        {"Iterator",    Obj::Type::BASIC_ITERATOR},
        {"LinkedList",    Obj::Type::BASIC_LINKED_LIST},
};


