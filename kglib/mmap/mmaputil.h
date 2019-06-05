/*
 * Provide memory map functionality
 */

#include <vector>
#include <mutex>
#include <exception>
#include <atomic>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace kg
{

using namespace boost::interprocess;

struct MetaEntry
{
    uint16_t kgId;          // unique id per symbol
    size_t offset;          // offset of certern book
    std::atomic<bool> updated{false};
    std::mutex _mtx;
    uint8_t refCount{0};
};

template<typename BOOK>
class BookContainer
{
public:
    BookContainer(size_t _numOfBooks) : numOfBooks(_numOfBooks) {}

    ssize_t init()
    {
        // reserve space for metaHeader
        metaEntries.reserve(numOfBooks * sizeOfMetaEntry);
        metaEntries.resize(numOfBooks * sizeOfMetaEntry);
        sizeOfMeta = metaEntries.size();

        try
        {
            shared_memory_object shm(open_or_create, "BOOKCONTAINER", read_write);
            shm.truncate(metaEntries.size() + sizeOfBook * numOfBooks);
            mapped_region region(shm, read_write);
        }
        catch( interprocess_exception& ex )
        {
            throw std::runtime_error(ex.what());
        }

        // initialize meta entries
        for(int idx = 0; idx < numOfBooks; ++idx)
        {
            metaEntries[idx].offset = idx;
        }

        std::memmove(region.get_address(), &metaEntries[0], metaEntries.size());

        for(int idx = 0; idx < numOfBooks; ++idx)
        // initalize books
        {
            BOOK bk;
            std::memmove(region.get_address() + sizeOfMeta + idx * sizeOfBook, &bk, sizeOfBook);
        }
    }

private:
    std::vector<MetaEntry> metaEntries;
    size_t numOfBooks;
    size_t sizeOfMetaEntry{sizeof(MetaEntry)};
    size_t sizeOfMeta{0};
    size_t sizeOfBook{sizeof(BOOK)};
};

}
