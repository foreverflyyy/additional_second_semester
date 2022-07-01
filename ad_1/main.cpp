#include <iostream>

//#define MY_OPERATOR
//#define MY_CONSTRUCTOR
using namespace std;

template<typename T>
class First {
    public:
        explicit First(int n) {
            arr  = new T[n];
            std::cout << "First" << "\n";
        }
        #ifdef MY_CONSTRUCTOR
            First(const First & elem) {
                std::cout << "Конструктор копирования First" << std::endl;
                auto m_n = elem.arr;
                auto m_m = getElem();
                m_m = reinterpret_cast<char*>(m_n);
            }
        #endif
        #ifdef MY_OPERATOR
            First(const First & elem) = delete;
            /*template<typename U>
            First operator=(First& elem){
                std::cout << "Operator =" << std::endl;
                auto m_n = elem.getElem();
                auto m_m = getElem();
                m_m = reinterpret_cast<char*>(m_n);
                return *this;
            }*/
        #endif

        ~First() {
            delete arr;
            std::cout << "~First" << "\n";
        }

        auto getElem(){
            return arr;
        }

    protected:
        T *arr = nullptr;
};

class Foo : public First<int> {
    public:
        explicit Foo(int j): First<int>(j) {
            std::cout << "Foo" << "\n";
        }

        virtual ~Foo() {
            std::cout << "~Foo" << "\n";
        }

        #ifdef MY_CONSTRUCTOR
            template<typename U>
                Foo(const Foo & elem) {
                    std::cout << "Конструктор копирования Foo" << std::endl;
                    auto m_n = elem.arr;
                    auto m_m = getElem();
                    m_m = reinterpret_cast<int*>(m_n);

                    /*int size = elem.size;
                    auto data = new int[size];
                    for (int i = 0; i < size; i++) {
                        data[i] = elem.data[i];
                    }
                    return m_m;
                    return *this;*/
                }
        #endif

        #ifdef MY_OPERATOR
            Foo(const Foo & elem) = delete;
            //template<typename U>
            Foo operator=(First& elem){
                std::cout << "Operator =" << std::endl;
                auto m_n = elem.getElem();
                auto m_m = getElem();
                m_m = reinterpret_cast<int*>(m_n);
                //return *this;
            }
        #endif

};

class Bar : public First<char> {
    public:
        explicit Bar(int j): First<char>(j) {
            std::cout << "Bar" << "\n";
        }

        #ifdef MY_CONSTRUCTOR
            template<typename U>
                Bar(const Bar & elem) {
                    std::cout << "Конструктор копирования Bar" << std::endl;

                    auto m_n = elem.arr;
                    auto m_m = getElem();
                    m_m = reinterpret_cast<char*>(m_n);

                    /*int size = elem.size;
                    auto data = new int[size];
                    for (int i = 0; i < size; i++) {
                        data[i] = elem.data[i];
                    }
                    return *this;*/
                }
        #endif

        virtual ~Bar() {
            std::cout << "~Bar" << "\n";
        }

        #ifdef MY_OPERATOR
            Bar(const Bar & elem) = delete;
            //template<typename U>
            Bar operator=(First& elem){
                std::cout << "Operator =" << std::endl;
                auto m_n = elem.getElem();
                auto m_m = getElem();
                m_m = reinterpret_cast<char*>(m_n);
                //return *this;
            }
        #endif
};


int main() {
    Foo *f = new Foo(100);
    Bar *d = new Bar(200);

    //*d = reinterpret_cast<First<char> &>(*f);
    //*d = dynamic_cast<First<char> &>(*f);
    //Foo *b = reinterpret_cast<Foo *>(new Bar(200));

    Foo *b = reinterpret_cast<Foo *>(new Bar(200));

    *f = *b;
    delete f;

    return 0;
}

/*Найти все ошибки в приведенном коде. Предложить варианты исправления.*/

/*class Foo{
public:
    Foo(int j) { i=new int[j]; }
    ~Foo() { delete i; }
private:
    int* i;
};
class Bar: Foo{
public:
    Bar(int j) { i=new char[j]; }
    ~Bar() { delete i; }
private:
    char* i;
};

void main(){
    Foo* f=new Foo(100);
    Foo* b=new Bar(200);
    *f=*b;
    delete f;
    delete b;
}
*/