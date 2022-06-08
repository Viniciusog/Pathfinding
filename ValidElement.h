#ifndef VALID_ELEMENT
#define VALID_ELEMENT
using namespace std;

template<class T>
class ValidElement {
    public:
        ValidElement();
        ~ValidElement();
        bool isValid() const;
        T getElement() const;
        void setElement(T element);
        void setIsValid(bool isValid);
    private:
        bool valid;
        T element;
};

template<class T>
ValidElement<T>::ValidElement() {
    this->setIsValid(false);
}

template<class T>
ValidElement<T>::~ValidElement() {
}

template<class T>
void ValidElement<T>::setElement(T element) {
    this->element = element;
}

template<class T>
void ValidElement<T>::setIsValid(bool isValid) {
    this->valid = isValid;
}

template<class T>
T ValidElement<T>::getElement() const {
    return this->element;
}

template<class T>
bool ValidElement<T>::isValid() const {
    return this->valid;
}

#endif
