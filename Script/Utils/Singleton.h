#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton {
    public :
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;

    protected :
    Singleton() = default;
};

#endif // SINGLETON_H