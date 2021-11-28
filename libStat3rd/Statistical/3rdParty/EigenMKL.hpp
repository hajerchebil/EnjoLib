#ifndef EIGENMKL_HPP
#define EIGENMKL_HPP

#include <Statistical/EigenAbstract.hpp>

namespace EnjoLib
{
class EigenMKL : public EigenAbstract
{
    public:
        EigenMKL();
        virtual ~EigenMKL();

    protected:
        STDFWD::vector<EigenValueVector> GetEigenValVecClient( const Matrix & m ) const;

    private:
};
}

#endif // EIGENMKL_HPP
