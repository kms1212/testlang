#ifndef AST_HPP_
#define AST_HPP_

#include <string>
#include <vector>

#include "location.hh"

namespace ast {
    class Attribute;

    class ASTNode {
    protected:
        std::vector<Attribute*> attr;
        int indent_ = 0;

    public:
        ASTNode() { }
        virtual ~ASTNode() = default;

        virtual std::string str(bool indent = true) = 0;

        void set_indent(const int indent);

        void add_attributes(std::vector<Attribute*>* attributes);
        std::string attrib_str(bool indent = true);

        std::string get_indent();
    };

    class Attribute {
    private:
        ASTNode* expression_;

    public:
        Attribute(ASTNode* expression) : expression_(expression) { }
        ~Attribute();

        std::string str();
    };

    class DummyNode : public ASTNode {
    private:
        std::string name_;

    public:
        DummyNode(std::string name = "") : name_(name) { }

        std::string str(bool indent = true) override;
    };

    class NodeList : public ASTNode {
    private:
        std::string name_;
        std::vector<ASTNode*> nodes_;

    public:
        NodeList(std::string name = "") : name_(name) { }
        ~NodeList();

        void add(ASTNode* node);

        std::string str(bool indent = true) override;
    };

    class Literal : public ASTNode {
    private:
        std::string valuestr_;
        std::string type_;

    public:
        Literal(
            const std::string* valuestr,
            const std::string type) :
                valuestr_(std::string(*valuestr)),
                type_(type) { }
        
        std::string str(bool indent = true) override;
    };

    class Identifier : public ASTNode {
    private:
        std::string name_;

    public:
        Identifier(const std::string* name) :
            name_(std::string(*name)) { }

        std::string str(bool indent = true) override;
    };

    class Import : public ASTNode {
    private:
        ASTNode* path_;

    public:
        Import(ASTNode* path) : path_(path) { }
        ~Import();

        std::string str(bool indent = true) override;
    };

    class ParentOf : public ASTNode {
    private:
        ASTNode* child_;
        ASTNode* current_;
        
    public:
        ParentOf(ASTNode* child, ASTNode* current) : child_(child), current_(current) { }
        ~ParentOf();

        std::string str(bool indent = true) override;
    };

    class ClassDecl : public ASTNode {
    private:
        std::string name_;
        ASTNode* parent_;
        NodeList* body_;
    
    public:
        ClassDecl(
            const std::string* name,
            ASTNode* parent,
            NodeList* body) :
                name_(std::string(*name)),
                parent_(parent),
                body_(body) { }
        ~ClassDecl();

        std::string str(bool indent = true) override;
    };

    class MixinDecl : public ASTNode {
    private:
        std::string name_;
        ASTNode* parent_;
        NodeList* body_;

    public:
        MixinDecl(
            const std::string* name,
            ASTNode* parent,
            NodeList* body) :
                name_(std::string(*name)),
                parent_(parent),
                body_(body) { }
        ~MixinDecl();

        std::string str(bool indent = true) override;
    };

    class FuncDecl : public ASTNode {
    private:
        std::string name_;
        NodeList* args_;
        NodeList* body_;

    public:
        FuncDecl(
            const std::string* name,
            NodeList* args,
            NodeList* body) :
                name_(std::string(*name)),
                args_(args),
                body_(body) { }
        ~FuncDecl();

        std::string str(bool indent = true) override;
    };

    class ParamDecl : public ASTNode {
    private:
        std::string name_;
        std::string type_;

    public:
        ParamDecl(
            const std::string* name,
            const std::string* type) :
                name_(std::string(*name)),
                type_(std::string(*type)) { }

        std::string str(bool indent = true) override;
    };

    class VarDecl : public ASTNode {
    private:
        std::string name_;
        ASTNode* type_;
        ASTNode* value_;

    public:
        VarDecl(
            const std::string* name,
            ASTNode* type,
            ASTNode* value = nullptr) :
                name_(std::string(*name)),
                type_(type),
                value_(value) { }
        ~VarDecl();

        std::string str(bool indent = true) override;
    };

    class FuncCall : public ASTNode {
    private:
        ASTNode* func_;
        NodeList* args_;

    public:
        FuncCall(
            ASTNode* func,
            NodeList* args) :
                func_(func),
                args_(args) { }
        ~FuncCall();

        std::string str(bool indent = true) override;
    };

    class KeyValue : public ASTNode {
    private:
        std::string key_;
        ASTNode* value_;

    public:
        KeyValue(
            const std::string* key,
            ASTNode* value) :
                key_(std::string(*key)),
                value_(value) { }
        ~KeyValue();

        std::string str(bool indent = true) override;
    };
}

#endif  // REPORT_HPP_
