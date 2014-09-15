
#ifndef HPP_BUFFERSCONTAINER
#define HPP_BUFFERSCONTAINER

#include <stdexcept>
#include "Debug.hpp"

template<class T>
class BufferContainer
{
    public:
    char const* buffer(int id)
    {
        std::map<int, char const*>::const_iterator it(m_buffers.find(id));

        if (it == m_buffers.end())
            throw(std::runtime_error(std::string(T::manager_id) + " buffer not found"));

        //debug(T::manager_id << ": Buffer " << id << " returning " << static_cast<void const*>(m_buffers[id]) << std::endl);

        return m_buffers[id];
    }

    void set_buffer(int id, char const* buffer)
    {
        if (m_buffers.find(id) != m_buffers.end())
            throw(std::runtime_error(std::string(T::manager_id) + " already set"));

        m_buffers[id] = buffer;
        debug(T::manager_id << ": Buffer " << id << " set to " << static_cast<void const*>(m_buffers[id]) << std::endl);
    }

    protected:
    std::map< int, char const*> m_buffers;
};

#endif

