#ifndef OFSTREAM_H
#define OFSTREAM_H

#include <Ios/Ostream.hpp>
#include <Template/SafePtr.hpp>

//#include <ostream>
//#include <Util/Ofstream.hpp>

namespace EnjoLib
{
/*
class Ofstream : public std::ofstream
{
    public:
        explicit Ofstream(const EnjoLib::Str & fileName, bool tryOpen = true);
        virtual ~Ofstream();

        const EnjoLib::Str & GetFileName() const { return m_fileName; }
        void IsOpenThrow() const;
        //bool is_open() const;

    protected:

    private:
        //SafePtr<std::ofstream> m_stream;
        const EnjoLib::Str m_fileName;
};
*/
class Ofstream : public Ostream
{
    public:
        explicit Ofstream(const EnjoLib::Str & fileName, bool tryOpen = true, bool append = false);
        virtual ~Ofstream();

        const EnjoLib::Str & GetFileName() const { return m_fileName; }
        void IsOpenThrow() const;
        bool is_open() const;
        void flush();
        
        EnjoLib::Str Str() const;
        stdfwd::ostream & OStr() override;
        const stdfwd::ostream & OStr() const override;

    protected:

    private:
        SafePtr<std::ostringstream> m_ostream;
        SafePtr<std::ofstream> m_ofstream;
        const EnjoLib::Str m_fileName;
};

}

#endif // OFSTREAM_H