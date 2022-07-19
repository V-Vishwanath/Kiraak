
#include "Errors.h"


std::string Error::SOURCE_CODE;


std::string ErrorMsg::UNEXPECTED_CHAR(char chr)  {
    std::stringstream ss;
    ss << "Lo! Khaali peeli kuch bhi daaldere! Deekhke type karo miya! ";
    ss << "Ye '" << chr << "' kya hai???";
    return ss.str();
}


std::string ErrorMsg::VAR_NOT_DEFINED(std::string_view varname) {
    std::stringstream ss;
    ss << "Ab ye '" << varname << "' boletho kya hai mereko nahi maaloom -_-";
    return ss.str();
}


std::string ErrorMsg::UNDEFINED_BIN_OP_NUM(std::size_t sIndex, std::size_t eIndex) {
    std::stringstream ss;

    ss << "Do numberon ke beech mein '";
    for (std::size_t i = sIndex; i < eIndex; i++) ss << Error::SOURCE_CODE[i];
    ss << "' kya aagaya?! Ye tho ganit nahi hai!";

    return ss.str();
}

std::string ErrorMsg::UNDEFINED_BIN_OP_BOOL(std::size_t sIndex, std::size_t eIndex) {
    std::stringstream ss;

    ss << "sahi aur galat ko bas compare kiya jaa sakta hai re! Ye ''";
    for (std::size_t i = sIndex; i < eIndex; i++) ss << Error::SOURCE_CODE[i];
    ss << "' lagane ka kya matlab hai?";

    return ss.str();
}


std::string Error::getUnderlinedError() const {
    std::stringstream ss;

    std::size_t lastNewlineTillErr = SOURCE_CODE.rfind('\n', token.posStart.index);
    std::size_t idxStart = lastNewlineTillErr == std::string::npos ? 0 : lastNewlineTillErr;

    std::size_t idxEnd = SOURCE_CODE.find('\n', idxStart + 1);
    if (idxEnd == std::string::npos) idxEnd = SOURCE_CODE.length();

    std::size_t lineCount = token.posEnd.line - token.posStart.line + 1;
    for (std::size_t i = 0; i < lineCount; i++) {
        std::string line = SOURCE_CODE.substr(idxStart, idxEnd - idxStart);

        std::size_t colStart = i == 0 ? token.posStart.col : 0;
        std::size_t colEnd = i == lineCount - 1 ? token.posEnd.col : line.length() - 1;

        ss << line << "\n";
        for (std::size_t j = 0; j < colStart; j++) ss << ' ';
        for (std::size_t j = 0; j < colEnd - colStart; j++) ss << '~';

        idxStart = idxEnd;
        idxEnd = SOURCE_CODE.find('\n', idxStart + 1);
        if (idxEnd == std::string::npos) idxEnd = SOURCE_CODE.length();
    }

    std::string errLocStr = ss.str();
    errLocStr = std::regex_replace(errLocStr, std::regex("\t"), " ");
    if (errLocStr[0] == '\n')
        errLocStr.erase(0, 1);

    return errLocStr;
}


std::string Error::compileTimeError() const {
    std::stringstream ss;

    ss << "\n" << name << ": " << msg << "\n";
    ss << "Line no: " << token.posStart.line + 1 << "\n";
    ss << getUnderlinedError();

    return ss.str();
}


std::string IllegalCharError::toString() { return compileTimeError(); }

std::string InvalidSyntaxError::toString() { return compileTimeError(); }


std::string RuntimeError::stackTrace() const {
    std::stringstream ss;

    const Context *currContext = &ctx;
    ParsePosition pos = token.posStart;

    while (currContext) {
        std::stringstream temp;
        temp << "Line " << (pos.line + 1) << ", in " << currContext->contextName << "\n" << ss.rdbuf();
        ss.swap(temp);

        pos = currContext->parentCallPos;
        currContext = (currContext->parent).get();
    }

    std::stringstream temp;
    temp << "Error Traceback (last vala sabse recent call):\n" << ss.rdbuf();
    return temp.str();
}

std::string RuntimeError::toString() { return compileTimeError() + "\n\n" + stackTrace(); }
