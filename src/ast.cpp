#include <string>

#include "ast.hpp"

void ast::ASTNode::set_indent(const int indent) {
    indent_ = indent;
}

std::string ast::ASTNode::get_indent() {
    std::string indent;
    for (int i = 0; i < indent_; i++) {
        indent += "\t";
    }
    return indent;
}

void ast::ASTNode::add_attributes(std::vector<Attribute*>* attributes) {
    if (attributes == nullptr)
        return;

    for (auto attribute : *attributes) {
        attr.push_back(attribute);
    }
}

std::string ast::ASTNode::attrib_str(bool indent) {
    if (attr.size() == 0)
        return "";

    std::string str = "\n" + (indent ? get_indent() + "\t" : "") + "Attributes: ";
    for (auto attribute : attr) {
        str += "(" + attribute->str() + "), ";
    }
    return str;
}

ast::Attribute::~Attribute() {
    delete expression_;
}

std::string ast::Attribute::str() {
    return expression_->str(false);
}

std::string ast::DummyNode::str(bool indent) {
    return (indent ? get_indent() : "") + "DummyNode: " + name_ + attrib_str();
}

void ast::NodeList::add(ASTNode* node) {
    nodes_.push_back(node);
}

std::string ast::NodeList::str(bool indent) {
    std::string str = (indent ? get_indent() : "") + "NodeList: " + name_ + attrib_str() + "\n";
    for (auto node : nodes_) {
        node->set_indent((indent ? indent_ : 0) + 1);
        str += node->str() + "\n";
    }
    return str;
}

ast::NodeList::~NodeList() {
    for (auto node : nodes_) {
        delete node;
    }
}

std::string ast::ParentOf::str(bool indent) {
    child_->set_indent((indent ? indent_ : 0) + 1);
    current_->set_indent((indent ? indent_ : 0) + 1);
    return (indent ? get_indent() : "") + "ParentOf(" + current_->str(false) + "): " + attrib_str() + "\n" + child_->str();
}

ast::ParentOf::~ParentOf() {
    delete child_;
}

std::string ast::Literal::str(bool indent) {
    return (indent ? get_indent() : "") + "Literal(" + type_ + "): " + valuestr_ + attrib_str();
}

std::string ast::Identifier::str(bool indent) {
    return (indent ? get_indent() : "") + "Identifier: " + name_ + attrib_str();
}

std::string ast::Import::str(bool indent) {
    path_->set_indent((indent ? indent_ : 0) + 1);
    return (indent ? get_indent() : "") + "Import: " + attrib_str() + "\n" + path_->str();
}

ast::Import::~Import() {
    delete path_;
}

std::string ast::ClassDecl::str(bool indent) {
    if (parent_ != nullptr) {
        parent_->set_indent((indent ? indent_ : 0)+ 1);
    }
    body_->set_indent((indent ? indent_ : 0) + 1);

    std::string str = (indent ? get_indent() : "") + "ClassDecl: " + name_ + attrib_str() + "\n" + body_->str();
    return str;
}

ast::ClassDecl::~ClassDecl() {
    delete body_;
}

std::string ast::MixinDecl::str(bool indent) {
    if (parent_ != nullptr) {
        parent_->set_indent((indent ? indent_ : 0)+ 1);
    }
    body_->set_indent((indent ? indent_ : 0) + 1);

    std::string str = (indent ? get_indent() : "") + "MixinDecl: " + name_ + attrib_str() + "\n" + body_->str();
    return str;
}

ast::MixinDecl::~MixinDecl() {
    delete body_;
}

std::string ast::FuncDecl::str(bool indent) {
    std::string str = (indent ? get_indent() : "") + "FunctionDecl: " + name_ + attrib_str() + "\n";
    if (args_ != nullptr) {
        args_->set_indent((indent ? indent_ : 0) + 1);
        str += args_->str();
    }
    if (body_ != nullptr) {
        body_->set_indent((indent ? indent_ : 0) + 1);
        str += body_->str();
    }
    return str;
}

ast::FuncDecl::~FuncDecl() {
    delete args_;
    delete body_;
}

std::string ast::ParamDecl::str(bool indent) {
    return (indent ? get_indent() : "") + "ParamDecl: " + name_ + attrib_str() + " (" + type_ + ")";
}

std::string ast::VarDecl::str(bool indent) {
    if (value_ != nullptr) {
        value_->set_indent((indent ? indent_ : 0) + 1);
        return (indent ? get_indent() : "") + "VarDecl: " + name_ + attrib_str() + " (" + type_->str(true) + ")\n" + value_->str();
    } else {
        return (indent ? get_indent() : "") + "VarDecl: " + name_ + attrib_str() + " (" + type_->str(true) + ")";
    }
}

ast::VarDecl::~VarDecl() {
    delete value_;
}

std::string ast::FuncCall::str(bool indent) {
    func_->set_indent((indent ? indent_ : 0) + 1);
    args_->set_indent((indent ? indent_ : 0) + 1);
    return (indent ? get_indent() : "") + "FuncCall(" + func_->str(false) + "):\n" + args_->str();
}

ast::FuncCall::~FuncCall() {
    delete args_;
}

std::string ast::KeyValue::str(bool indent) {
    value_->set_indent((indent ? indent_ : 0) + 1);
    return (indent ? get_indent() : "") + "KeyValue: " + key_ + "\n" + value_->str();
}

ast::KeyValue::~KeyValue() {
    delete value_;
}
