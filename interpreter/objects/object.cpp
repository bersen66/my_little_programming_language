#include <iostream>

#include "object.h"

bool Int::HasSUMOperator() const {
    return true;
}

bool Int::HasDIVOperator() const {
    return true;
}

bool Int::HasMULOperator() const {
    return true;
}

bool Int::HasSUBOperator() const {
    return true;
}

bool Int::HasLTOperator() const {
    return true;
}

bool Int::HasGTOperator() const {
    return true;
}

bool Int::HasLTOEOperator() const {
    return true;
}

bool Int::HasGTOEOperator() const {
    return true;
}

bool Int::HasEQOperator() const {
    return true;
}

bool Int::HasNEQOperator() const {
    return true;
}

bool Int::HasOROperator() const {
    return true;
}

bool Int::HasANDOperator() const {
    return true;
}

bool Int::HasGETOperator() const {
    return false;
};

bool Int::HasISVALOperator() const {
    return false;
};

bool Int::HasHSNXTOperator() const {
    return false;
};

bool Int::HasHSPRVOperator() const {
    return false;
};

bool Int::HasINSAOperator() const {
    return false;
};

bool Int::HasINSBOperator() const {
    return false;
};

bool Int::HasERSOperator() const {
    return false;
};

std::size_t Int::Hash() const {
    return static_cast<size_t>(value_);
}

std::string Int::ToString() const {
    return value_.str();
}

void Int::Assign(ObjPtr other) {
    if (type != other->type) {
        throw std::runtime_error("Assigning different types");
    }
    value_ = std::dynamic_pointer_cast<Int>(other)->value_;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////


bool Bool::HasSUMOperator() const {
    return false;
}

bool Bool::HasDIVOperator() const {
    return false;
}

bool Bool::HasMULOperator() const {
    return false;
}

bool Bool::HasSUBOperator() const {
    return false;
}

bool Bool::HasLTOperator() const {
    return true;
}

bool Bool::HasGTOperator() const {
    return true;
}

bool Bool::HasLTOEOperator() const {
    return true;
}

bool Bool::HasGTOEOperator() const {
    return true;
}

bool Bool::HasEQOperator() const {
    return true;
}

bool Bool::HasNEQOperator() const {
    return true;
}

bool Bool::HasOROperator() const {
    return true;
}

bool Bool::HasANDOperator() const {
    return true;
}

bool Bool::HasGETOperator() const {
    return false;
};

bool Bool::HasISVALOperator() const {
    return false;
};

bool Bool::HasHSNXTOperator() const {
    return false;
};

bool Bool::HasHSPRVOperator() const {
    return false;
};

bool Bool::HasINSAOperator() const {
    return false;
};

bool Bool::HasINSBOperator() const {
    return false;
};

bool Bool::HasERSOperator() const {
    return false;
};

std::size_t Bool::Hash() const {
    return std::hash<bool>{}(value_);
}

std::string Bool::ToString() const {
    return (value_ ? "True" : "False");
}

void Bool::Assign(ObjPtr other) {
    if (type != other->type) {
        throw std::runtime_error("Assigning different types");
    }
    value_ = std::dynamic_pointer_cast<Bool>(other)->value_;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

bool Iterator::HasSUMOperator() const {
    return false;
}

bool Iterator::HasDIVOperator() const {
    return false;
}

bool Iterator::HasMULOperator() const {
    return false;
}

bool Iterator::HasSUBOperator() const {
    return false;
}

std::size_t Iterator::Hash() const {

}

bool Iterator::HasLTOperator() const {
    return false;
}

bool Iterator::HasGTOperator() const {
    return false;
}

bool Iterator::HasLTOEOperator() const {
    return false;
}

bool Iterator::HasGTOEOperator() const {
    return false;
}

bool Iterator::HasEQOperator() const {
    return false;
}

bool Iterator::HasNEQOperator() const {
    return false;
}

bool Iterator::HasOROperator() const {
    return false;
}

bool Iterator::HasANDOperator() const {
    return false;
}

bool Iterator::HasGETOperator() const {
    return true;
}

bool Iterator::HasISVALOperator() const {
    return true;
}

bool Iterator::HasHSNXTOperator() const {
    return true;
}

bool Iterator::HasHSPRVOperator() const {
    return true;
}

bool Iterator::HasINSAOperator() const {
    return true;
}

bool Iterator::HasINSBOperator() const {
    return true;
}

bool Iterator::HasERSOperator() const {
    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////


bool LinkedList::HasSUMOperator() const {
    return false;
}

bool LinkedList::HasDIVOperator() const {
    return false;
}

bool LinkedList::HasMULOperator() const {
    return false;
}

bool LinkedList::HasSUBOperator() const {
    return false;
}


bool LinkedList::HasLTOperator() const {
    return false;
}

bool LinkedList::HasGTOperator() const {
    return false;
}

bool LinkedList::HasLTOEOperator() const {
    return false;
}

bool LinkedList::HasGTOEOperator() const {
    return false;
}

bool LinkedList::HasEQOperator() const {
    return false;
}

bool LinkedList::HasNEQOperator() const {
    return false;
}

bool LinkedList::HasOROperator() const {
    return false;
}

bool LinkedList::HasANDOperator() const {
    return false;
}

bool LinkedList::HasGETOperator() const {
    return true;
}

bool LinkedList::HasISVALOperator() const {
    return true;
}

bool LinkedList::HasHSNXTOperator() const {
    return true;
}

bool LinkedList::HasHSPRVOperator() const {
    return true;
}

bool LinkedList::HasINSAOperator() const {
    return true;
}

bool LinkedList::HasINSBOperator() const {
    return true;
}

bool LinkedList::HasERSOperator() const {
    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
ObjPtr MakeObj(Obj::Type type) {
    switch (type) {
        case Obj::Type::BASIC_INT: {
            return std::make_shared<Int>(0);
        }
            break;
        case Obj::Type::BASIC_BOOL : {
            return std::make_shared<Bool>(false);
        }
            break;

        case Obj::Type::BASIC_LINKED_LIST: {
            return std::make_shared<LinkedList>();
        }
        break;

        case Obj::Type::BASIC_ITERATOR: {
            return std::make_shared<Iterator>();
        }
            break;

    }
}

std::ostream &operator<<(std::ostream &out, const ObjPtr &value) {
    out << value->ToString();
    return out;
}

ObjPtr operator+(const ObjPtr &lhs, const ObjPtr &rhs) {

    if (lhs->type != rhs->type) {
        throw std::runtime_error("Summing different types");
    }

    if (!lhs->HasSUMOperator() || !rhs->HasSUMOperator()) {
        throw std::runtime_error("Doesnt have add operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            auto lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            auto rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Int>(lhs_value + rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator-(const ObjPtr &lhs, const ObjPtr &rhs) {

    if (lhs->type != rhs->type) {
        throw std::runtime_error("Sub different types");
    }

    if (!lhs->HasSUBOperator() || !rhs->HasSUBOperator()) {
        throw std::runtime_error("Doesnt have sub operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Int>(lhs_value - rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator*(const ObjPtr &lhs, const ObjPtr &rhs) {

    if (lhs->type != rhs->type) {
        throw std::runtime_error("Mul different types");
    }

    if (!lhs->HasMULOperator() || !rhs->HasMULOperator()) {
        throw std::runtime_error("Doesnt have mul operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Int>(lhs_value * rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator/(const ObjPtr &lhs, const ObjPtr &rhs) {

    if (lhs->type != rhs->type) {
        throw std::runtime_error("Div different types");
    }

    if (!lhs->HasDIVOperator() || !rhs->HasDIVOperator()) {
        throw std::runtime_error("Doesnt have div operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Int>(lhs_value / rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}


ObjPtr operator<(const ObjPtr &lhs, const ObjPtr &rhs) {
    if (lhs->type != rhs->type) {
        throw std::runtime_error("LT different types");
    }

    if (!lhs->HasLTOperator() || !rhs->HasLTOperator()) {
        throw std::runtime_error("Doesnt have LT operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value < rhs_value);
            return result;
        }
            break;

        case Obj::Type::BASIC_BOOL: {
            const auto &lhs_value = std::dynamic_pointer_cast<Bool>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Bool>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value < rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator<=(const ObjPtr &lhs, const ObjPtr &rhs) {
    if (lhs->type != rhs->type) {
        throw std::runtime_error("LTOE different types");
    }

    if (!lhs->HasLTOEOperator() || !rhs->HasLTOEOperator()) {
        throw std::runtime_error("Doesnt have LTOE operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value <= rhs_value);
            return result;
        }
            break;

        case Obj::Type::BASIC_BOOL: {
            const auto &lhs_value = std::dynamic_pointer_cast<Bool>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Bool>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value <= rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator>(const ObjPtr &lhs, const ObjPtr &rhs) {
    if (lhs->type != rhs->type) {
        throw std::runtime_error("GT different types");
    }

    if (!lhs->HasGTOperator() || !rhs->HasGTOperator()) {
        throw std::runtime_error("Doesnt have GT operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value > rhs_value);
            return result;
        }
            break;

        case Obj::Type::BASIC_BOOL: {
            const auto &lhs_value = std::dynamic_pointer_cast<Bool>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Bool>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value > rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator>=(const ObjPtr &lhs, const ObjPtr &rhs) {
    if (lhs->type != rhs->type) {
        throw std::runtime_error("GTOE different types");
    }

    if (!lhs->HasGTOEOperator() || !rhs->HasGTOEOperator()) {
        throw std::runtime_error("Doesnt have GTOE operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value >= rhs_value);
            return result;
        }
            break;

        case Obj::Type::BASIC_BOOL: {
            const auto &lhs_value = std::dynamic_pointer_cast<Bool>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Bool>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value >= rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator==(const ObjPtr &lhs, const ObjPtr &rhs) {
    if (lhs->type != rhs->type) {
        throw std::runtime_error("EQ different types");
    }

    if (!lhs->HasEQOperator() || !rhs->HasEQOperator()) {
        throw std::runtime_error("Doesnt have EQ operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value == rhs_value);
            return result;
        }
            break;

        case Obj::Type::BASIC_BOOL: {
            const auto &lhs_value = std::dynamic_pointer_cast<Bool>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Bool>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value == rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator!=(const ObjPtr &lhs, const ObjPtr &rhs) {
    if (lhs->type != rhs->type) {
        throw std::runtime_error("NEQ different types");
    }

    if (!lhs->HasNEQOperator() || !rhs->HasNEQOperator()) {
        throw std::runtime_error("Doesnt have NEQ operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value != rhs_value);
            return result;
        }
            break;

        case Obj::Type::BASIC_BOOL: {
            const auto &lhs_value = std::dynamic_pointer_cast<Bool>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Bool>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value != rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr AND(const ObjPtr &lhs, const ObjPtr &rhs) {
    if (lhs->type != rhs->type) {
        throw std::runtime_error("AND different types");
    }

    if (!lhs->HasANDOperator() || !rhs->HasANDOperator()) {
        throw std::runtime_error("Doesnt have AND operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value && rhs_value);
            return result;
        }
            break;

        case Obj::Type::BASIC_BOOL: {
            const auto &lhs_value = std::dynamic_pointer_cast<Bool>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Bool>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value && rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr OR(const ObjPtr &lhs, const ObjPtr &rhs) {
    if (lhs->type != rhs->type) {
        throw std::runtime_error("OR different types");
    }

    if (!lhs->HasOROperator() || !rhs->HasOROperator()) {
        throw std::runtime_error("Doesnt have OR operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT: {
            const auto &lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value || rhs_value);
            return result;
        }
            break;

        case Obj::Type::BASIC_BOOL: {
            const auto &lhs_value = std::dynamic_pointer_cast<Bool>(lhs)->value_;
            const auto &rhs_value = std::dynamic_pointer_cast<Bool>(rhs)->value_;
            ObjPtr result = std::make_shared<Bool>(lhs_value || rhs_value);
            return result;
        }
            break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}


ObjPtr GET(const ObjPtr &iterator) {

    if (iterator->type != Obj::Type::BASIC_ITERATOR) {
        throw std::runtime_error("Value is not an iterator");
    }

    const auto &iter = std::dynamic_pointer_cast<Iterator>(iterator);
    if (iter->IsValid()) {
        return iter->GetNode()->value;
    }

    throw std::runtime_error("Can't get value from invalid iterator");

}

ObjPtr ISVAL(const ObjPtr &iterator) {

    if (iterator->type != Obj::Type::BASIC_ITERATOR) {
        throw std::runtime_error("Value is not an iterator");
    }

    auto iter = std::dynamic_pointer_cast<Iterator>(iterator);
    return std::make_shared<Bool>(iter->IsValid());

}

ObjPtr HSNXT(const ObjPtr &iterator) {

    if (iterator->type != Obj::Type::BASIC_ITERATOR) {
        throw std::runtime_error("Value is not an iterator");
    }

    if (!iterator->HasHSNXTOperator()) {
        throw std::runtime_error("Value doesn't support HasNext operator");
    }

    const auto &iter = std::dynamic_pointer_cast<Iterator>(iterator);
    if (iter->IsValid()) {
        return std::make_shared<Bool>(iter->HasNext());
    }

    return std::make_shared<Bool>(false);
}

ObjPtr HSPRV(const ObjPtr &iterator) {

    if (iterator->type != Obj::Type::BASIC_ITERATOR) {
        throw std::runtime_error("Value is not an iterator");
    }

    if (!iterator->HasHSPRVOperator()) {
        throw std::runtime_error("Value doesn't support HasPrev operator");
    }

    const auto &iter = std::dynamic_pointer_cast<Iterator>(iterator);
    if (iter->IsValid()) {
        return std::make_shared<Bool>(iter->HasPrev());
    }

    return std::make_shared<Bool>(false);
}

ObjPtr INSA(ObjPtr &container, ObjPtr &value) {

    if (container->type != Obj::Type::BASIC_LINKED_LIST) {
        throw std::runtime_error("Expected container");
    }

    if (!container->HasINSAOperator()) {
        throw std::runtime_error("Container doesn't support InsertAfter operation");
    }

    auto cont = std::dynamic_pointer_cast<LinkedList>(container);

    return cont->PushBack(value);

}

ObjPtr INSA(ObjPtr &container, ObjPtr &iterator, ObjPtr &value) {
    if (container->type != Obj::Type::BASIC_LINKED_LIST) {
        throw std::runtime_error("Expected container");
    }

    if (iterator->type != Obj::Type::BASIC_ITERATOR) {
        throw std::runtime_error("Expected iterator");
    }

    if (!container->HasINSAOperator()) {
        throw std::runtime_error("Container doesn't support InsertAfter operation");
    }

     auto cont = std::dynamic_pointer_cast<LinkedList>(container);
     auto iter = std::dynamic_pointer_cast<Iterator>(iterator);


    if (!iter->IsValid()) {
        throw std::runtime_error("expected valid iterator!");
    }

    return cont->InsertAfter(iterator, value);

}


ObjPtr INSB(ObjPtr &container, ObjPtr &value) {

    if (container->type != Obj::Type::BASIC_LINKED_LIST) {
        throw std::runtime_error("Expected container");
    }

    if (!container->HasINSBOperator()) {
        throw std::runtime_error("Container doesn't support InsertBefore operation");
    }

    auto cont = std::dynamic_pointer_cast<LinkedList>(container);

    return cont->PushFront(value);
}

ObjPtr INSB(ObjPtr &container, ObjPtr& iterator, ObjPtr &value) {
    if (container->type != Obj::Type::BASIC_LINKED_LIST) {
        throw std::runtime_error("Expected container");
    }

    if (iterator->type != Obj::Type::BASIC_ITERATOR) {
        throw std::runtime_error("Expected iterator");
    }

    if (!container->HasINSBOperator()) {
        throw std::runtime_error("Container doesn't support InsertBefore operation");
    }

    auto cont = std::dynamic_pointer_cast<LinkedList>(container);
    auto iter = std::dynamic_pointer_cast<Iterator>(iterator);

    if (!iter->IsValid()) {
        throw std::runtime_error("expected valid iterator!");
    }

    return cont->InsertBefore(iter, value);
}


ObjPtr ERS(ObjPtr &container, const ObjPtr &iterator) {
    if (container->type != Obj::Type::BASIC_LINKED_LIST) {
        throw std::runtime_error("Expected container");
    }

    if (iterator->type != Obj::Type::BASIC_ITERATOR) {
        throw std::runtime_error("Expected iterator");
    }

    if (!container->HasERSOperator()) {
        throw std::runtime_error("Container doesn't support Erase operation");
    }

    auto cont = std::dynamic_pointer_cast<LinkedList>(container);
    auto iter = std::dynamic_pointer_cast<Iterator>(iterator);

    if (!iter->IsValid()) {
        throw std::runtime_error("expected valid iterator!");
    }

    return cont->Erase(iter);
}


