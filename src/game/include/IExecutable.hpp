
#ifndef HPP_IEXECUTABLE
#define HPP_IEXECUTABLE

class IExecutable
{
    public:
    // Returns the next IExecutable to execute
    virtual IExecutable* execute() = 0;
};

#endif

