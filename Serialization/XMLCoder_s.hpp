//
//  XMLCoder_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 20/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef XMLCoder_s_hpp
#define XMLCoder_s_hpp


template <class TOstream>
XMLEncoder<TOstream>::XMLEncoder(TOstream const &ostream) : _ostream(ostream), _currentLevel(0), _strStdOstream(_strStream) {
    // Add header
    writeHeader();
    
    // Add root object
    startEncode("root", 0);
}

template <class TOstream>
XMLEncoder<TOstream>::~XMLEncoder() {
    stopEncode();
}

template <class TOstream>
void XMLEncoder<TOstream>::startEncode(std::string const &name, int version) {
    std::string beginTag = getIndentation() + "<object name=\"" + name + "\" version=\"" + std::to_string(version) + "\">\n";
    _ostream.writeText(beginTag.c_str());
    
    // Increment current level
    ++_currentLevel;
}

template <class TOstream>
void XMLEncoder<TOstream>::stopEncode() {
    // Decrement current level
    --_currentLevel;
    
    std::string endTag = getIndentation() + "<\\object>\n";
    _ostream.writeText(endTag.c_str());
}

template <class TOstream>
template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type>
void XMLEncoder<TOstream>::encode(TData const &data, std::string const &name) {
    // Reset str stream and write data in it
    _strStream.str("");
    _strStream.clear();
    _strStdOstream.writeText(data);
    
    // Get data string
    std::string dataStr = _strStream.str();
    
    // Remove null char if needed
    correctForEncode<TData>(dataStr);
    
    // Write data string in xml format
    std::string xmlStr = getIndentation() + "<data name=\"" + name + "\">" + dataStr + "<\\data>\n";
    _ostream.writeText(xmlStr.c_str());
}

template <class TOstream>
void XMLEncoder<TOstream>::writeHeader() {
    _ostream.writeText("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n");
}

template <class TOstream>
std::string XMLEncoder<TOstream>::getIndentation() {
    // One indentation is 4 whitespaces
    return std::string(4 * _currentLevel, ' ');
}

template <class TOstream>
template <typename TData, typename std::enable_if<std::is_same<typename std::remove_cv<TData>::type, char const *>::value == false, int>::type>
void XMLEncoder<TOstream>::correctForEncode(std::string &str) {
}

template <class TOstream>
template <typename TData, typename std::enable_if<std::is_same<typename std::remove_cv<TData>::type, char const *>::value == true, int>::type>
void XMLEncoder<TOstream>::correctForEncode(std::string &str) {
    // Remove null char
    str.pop_back();
}

template <class TIstream>
XMLDecoder<TIstream>::XMLDecoder(TIstream const &istream) : _istream(istream), _strStdIstream(_strStream) {
    readHeader();
    
    int version;
    startDecode("root", version);
}

template <class TIstream>
void XMLDecoder<TIstream>::startDecode(std::string const &name, int &version) {
    constexpr char const versionStartToken[] = "version=\"";
    constexpr auto const versionStartTokenSize = sizeof(versionStartToken) - 1;
    
    std::string str = readString();
    
    auto iVersionBegin = str.find(versionStartToken);
    if (iVersionBegin == std::string::npos) {
        return;
    }
    
    iVersionBegin += versionStartTokenSize;
    
    auto iVersionEnd = str.find("\"", iVersionBegin);
    if (iVersionEnd == std::string::npos) {
        return;
    }
    
    version = std::stoi(str.substr(iVersionBegin, iVersionEnd - iVersionBegin));
}

template <class TIstream>
void XMLDecoder<TIstream>::stopDecode() {
    readString();
}

template <class TIstream>
template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type>
void XMLDecoder<TIstream>::decode(TData &data, std::string const &name) {
    constexpr char const dataStartToken[] = ">";
    constexpr auto const dataStartTokenSize = sizeof(dataStartToken) - 1;
    constexpr char const dataEndToken[] = "<\\data>\n";
    
    std::string str = readString();
    
    auto iDataBegin = str.find(dataStartToken);
    if (iDataBegin == std::string::npos) {
        return;
    }
    
    iDataBegin += dataStartTokenSize;
    
    auto iDataEnd = str.rfind(dataEndToken);
    if (iDataEnd == std::string::npos) {
        return;
    }
    
    std::string dataStr = str.substr(iDataBegin, iDataEnd - iDataBegin);
    
    // Add null char if needed
    correctForDecode<TData>(dataStr);
    
    _strStream.str(dataStr);
    _strStream.clear();
    _strStdIstream.readText(data);
}

template <class TIstream>
void XMLDecoder<TIstream>::readHeader() {
    readString();
}

template <class TIstream>
std::string XMLDecoder<TIstream>::readString() {
    char *cstring = nullptr;
    _istream.readText(cstring);
    
    std::string str(cstring);
    std::free(cstring);
    
    return str;
}

template <class TIstream>
template <typename TData, typename std::enable_if<std::is_same<typename std::remove_cv<TData>::type, char *>::value == false, int>::type>
void XMLDecoder<TIstream>::correctForDecode(std::string &str) {
}

template <class TIstream>
template <typename TData, typename std::enable_if<std::is_same<typename std::remove_cv<TData>::type, char *>::value == true, int>::type>
void XMLDecoder<TIstream>::correctForDecode(std::string &str) {
    // Add null char
    str += '\0';
}

#endif /* XMLCoder_s_hpp */
