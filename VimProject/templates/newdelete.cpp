const int Mb = 230;
const int MAX_MEM = Mb * 1024 * 1024;
size_t mpos = 0;
char mem[MAX_MEM];
inline void* operator new(size_t n)
{
    char * res = mem + mpos;
    mpos += n;
    assert(mpos <= MAX_MEM);
    return (void*)res;
}
inline void operator delete(void*) {}
