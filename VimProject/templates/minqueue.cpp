template<class T>
struct minqueue {
    int b = 0, e = 0;
    deque<T> d;
    deque<int> di;
    T& get() { return d.front(); }
    void push(T a) {
        while (d.size() && d.back() > a) {
            d.pop_back();
            di.pop_back();
        }
        d.push_back(a);
        di.push_back(b++);
    }
    void pop() {
        if (d.size() && di.front() == e) {
            d.pop_front();
            di.pop_front();
        }
        ++e;
    }
	int size(){ return b - e; }
};
