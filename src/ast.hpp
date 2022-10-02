#ifndef AST_HPP_
#define AST_HPP_

#include <string>
#include <vector>

#include "location.hh"

namespace ast {
    class ASTNode {
    protected:
        int indent_ = 0;
    public:
        ASTNode() { }
        virtual ~ASTNode() = default;
        virtual std::string str() = 0;

        void set_indent(const int indent);

        std::string get_indent();
    };

    class DummyNode : public ASTNode {
    private:
        std::string name_;

    public:
        DummyNode(std::string name = "") : name_(name) { }

        std::string str() override;
    };

    class NodeList : public ASTNode {
    private:
        std::string name_;
        std::vector<ASTNode*> nodes_;

    public:
        NodeList(std::string name = "") : name_(name) { }

        void add(ASTNode* node);

        std::string str() override;
    };

    class Literal : public ASTNode {
    private:
        std::string valuestr_;
        std::string typestr_;

    public:
        Literal(
            const std::string valuestr,
            const std::string typestr) :
                valuestr_(valuestr),
                typestr_(typestr) { }
        
        std::string str() override;
    };

    class Identifier : public ASTNode {
    private:
        std::string name_;

    public:
        Identifier(std::string const& name) : name_(name) { }

        std::string str() override;
    };

    class Import : public ASTNode {
    private:
        ASTNode* path_;

    public:
        Import(ASTNode* path) : path_(path) { }

        std::string str() override;
    };

    class ClassDecl : public ASTNode {
    private:
        std::string name_;
        ASTNode* parent_;
        NodeList* body_;
    
    public:
        ClassDecl(
            std::string name,
            ASTNode* parent,
            NodeList* body) :
                name_(name),
                parent_(parent),
                body_(body) { }

        std::string str() override;
    };

    class FuncDecl : public ASTNode {
    private:
        std::string name_;
        NodeList* args_;
        NodeList* body_;

    public:
        FuncDecl(
            std::string name,
            NodeList* args,
            NodeList* body) :
                name_(name),
                args_(args),
                body_(body) { }

        std::string str() override;
    };
}

#endif  // REPORT_HPP_
