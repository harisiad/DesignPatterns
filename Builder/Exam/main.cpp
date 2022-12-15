#include <string>
#include <ostream>
#include <vector>
#include <iostream>

using namespace std;

class ClassEntity
{
    string className_;
    string name_;
    string type_;
    vector<ClassEntity> entities_;
public:
    ClassEntity() {}
    ClassEntity(const string& className) : className_(className) {}
    ClassEntity(const string& name, const string& type) : name_(name), type_(type) {}

    string getName() const { return name_; }
    string getType() const { return type_; }
    void addToEntities(ClassEntity ce)
    {
        entities_.push_back(ce);
    }

    friend ostream& operator<<(ostream& os, const ClassEntity& obj)
    {
        os << "class " << obj.className_ << endl;
        os << "{" << endl;
        for (auto entity : obj.entities_) {
            os << "  " << entity.type_ << " " << entity.name_ << ";" << endl;
        }
        os << "};" << endl;

        return os;
    }
};

class CodeBuilder
{
    ClassEntity cEntity_;
public:
    CodeBuilder(const string& class_name)
    {
        cEntity_ = {class_name};
    }

    CodeBuilder& add_field(const string& name, const string& type)
    {
        ClassEntity v{name, type};
        cEntity_.addToEntities(v);

        return *this;
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
    {
        return os << obj.cEntity_;
    }
};

int main()
{
    auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    cout << cb;

    return 0;
}
