#include <Util/ToolsMixed.hpp>
#include "Tokenizer.hpp"
#include "CharManipulations.hpp"
#include "StrColour.hpp"
#include <Math/GeneralMath.hpp>

#include <Ios/Osstream.hpp>
#include <Util/Except.hpp>

#include <STD/Iostream.hpp>
#include <STD/Map.hpp>
#include <STD/Iomanip.hpp>
#include <ctime>
#include <mutex>

using namespace std;
using namespace EnjoLib;

EnjoLib::Str ToolsMixed::BinHex2Str(const unsigned char* data, int len) const
{
    EnjoLib::Osstream ss;
    ss.OStr() << std::hex;
    for(int i=0;i<len;++i)
        ss.OStr() << std::setw(2) << std::setfill('0') << (int)data[i];
    return ss.str();
}

void ToolsMixed::AnimationPropeller(int * idx) const
{
    const string anim = "|/-\\";
    AnimationCustom(idx, anim);
}

void ToolsMixed::Animation09AZ(int * idx) const
{
    const string anim = "0123456789ABCDEFGHIJKLMNOPQRSTUWXYZ";
    AnimationCustom(idx, anim);
}

void ToolsMixed::AnimationCustom(int * idx, const EnjoLib::Str & animSeries) const
{
    cout << '\b' << animSeries.at((*idx)++ % animSeries.size()) << flush;
}

Str ToolsMixed::GenBars10(double percentage, const char barFull, const char barEmpty) const
{
    const Str tagStart = "[";
    const Str tagEnd   = "]";
    const Str tagOn    = barFull;
    const Str tagOff   = barEmpty;
    
    const int numBars = 10;
    
    int percentage0_10 = int(GMat().round(percentage / 10.0));
    if (percentage0_10 > numBars)
    {
        percentage0_10 = numBars;
    }
    
    Osstream oss;
    oss << tagStart;
    oss << GenChars(tagOn,  percentage0_10);
    oss << GenChars(tagOff, numBars - percentage0_10);
    oss << tagEnd;
    return oss.str();
}

Str ToolsMixed::GenChars(const Str & pattern, int numberOfRepetitions) const
{
    Osstream oss;
    for (int i = 0; i < numberOfRepetitions; ++i)
    {
        oss << pattern;
    }
    return oss.str();
}

std::map<EnjoLib::Str, EnjoLib::Str> ToolsMixed::FromPythonDict(const EnjoLib::Str & dictStr) const
{
    std::map<EnjoLib::Str, EnjoLib::Str> ret;
    if (dictStr.empty())
        return ret;
    if (dictStr.front() != '{')
        throw EnjoLib::ExceptInvalidArg("Doesn't start with {\n" + dictStr.str());
    if (dictStr.back() != '}')
        throw EnjoLib::ExceptInvalidArg("Doesn't start with }\n" + dictStr.str());

    const EnjoLib::Str & dict = dictStr.str().substr(1, dictStr.size() - 2);
    const Tokenizer tok;
    const CharManipulations cman;
    for (const auto & token : tok.Tokenize(dict, ','))
    {
        const auto & keyVal = tok.Tokenize(token, ':');
        const EnjoLib::Str key = cman.Replace(keyVal.at(0), " ", "");;
        const EnjoLib::Str keyNoQuotes = cman.Replace(key, "'", "");
        const EnjoLib::Str val = cman.Replace(keyVal.at(1), " ", "");;
        ret[keyNoQuotes] = val;
    }
    return ret;
}

void ToolsMixed::SystemCallWarn(const EnjoLib::Str & command, const EnjoLib::Str & functionName) const
{
    if (int err = system(command.c_str()))
    {
        std::cout << StrColour::GenWarn(SystemCallPrepareMessage(command, functionName, err)) << std::endl;
    }
}

bool ToolsMixed::SystemCallWarnBool(const EnjoLib::Str & command, const EnjoLib::Str & functionName) const
{
    if (int err = system(command.c_str()))
    {
        std::cout << StrColour::GenWarn(SystemCallPrepareMessage(command, functionName, err)) << std::endl;
        return false;
    }
    return true;
}

void ToolsMixed::SystemCallThrow(const EnjoLib::Str & command, const EnjoLib::Str & functionName) const
{
    if (int err = system(command.c_str()))
        throw EnjoLib::ExceptRuntimeError(SystemCallPrepareMessage(command, functionName, err).c_str());
}

EnjoLib::Str ToolsMixed::SystemCallPrepareMessage(const EnjoLib::Str & command, const EnjoLib::Str & functionName, int err) const
{
    EnjoLib::Osstream oss;
    oss << functionName << ":\nCouldn't call command = \n" << command << "\nerr = " << err;
    return oss.str();
}

EnjoLib::Str ToolsMixed::GenUniqueStringID() const
{
    static std::mutex mut;
    std::lock_guard<std::mutex> lock(mut);
    static int i = 0;
    const int tme = (int)time(NULL);

    EnjoLib::Osstream oss;
    oss << tme << '-' << ++i;

    return oss.str();
}

EnjoLib::Str ToolsMixed::GetTmpDir()
{
#ifdef WIN32
	return "./";
#else
	return "/tmp/";
#endif
}

