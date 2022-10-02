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

std::string ast::DummyNode::str() {
    return get_indent() + "DummyNode^" + std::to_string(indent_) + ": " + name_;
}

void ast::NodeList::add(ASTNode* node) {
    nodes_.push_back(node);
}

std::string ast::NodeList::str() {
    std::string str = get_indent() + "NodeList^" + std::to_string(indent_) + ": " + name_ + "\n";
    for (auto node : nodes_) {
        node->set_indent(indent_ + 1);
        str += node->str() + "\n";
    }
    return str;
}

std::string ast::Literal::str() {
    return get_indent() + "Literal(" + typestr_ + ")^" + std::to_string(indent_) + ": " + valuestr_;
}

std::string ast::Identifier::str() {
    return get_indent() + "Identifier^" + std::to_string(indent_)+ ": " + name_;
}

std::string ast::Import::str() {
    path_->set_indent(indent_ + 1);
    return get_indent() + "Import^" + std::to_string(indent_) + ": \n" + path_->str();
}

std::string ast::ClassDecl::str() {
    if (parent_ != nullptr) {
        parent_->set_indent(indent_ + 1);
    }
    body_->set_indent(indent_ + 1);

    std::string str = get_indent() + "ClassDecl^" + std::to_string(indent_) + ": " + name_ + "\n" + body_->str();
    return str;
}

std::string ast::FuncDecl::str() {
    args_->set_indent(indent_ + 1);
    body_->set_indent(indent_ + 1);
    std::string str = get_indent() + "FunctionDecl^" + std::to_string(indent_) + ": " + name_ + "\n" + args_->str() + body_->str();
    return str;
}
