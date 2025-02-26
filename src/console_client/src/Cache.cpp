
#include "Cache.h"


Cache &Cache::instance() {
    static Cache instance;
    return instance;
}


std::string Cache::getTextData() {
    return m_text;
}


int Cache::getTypeData() {
    return m_type;
}


void Cache::setTextData(const std::string &text) {
    m_text = text;
}


void Cache::setTypeData(int type) {
    m_text = type;
}


void Cache::resetCache() {
    m_type = -1;
    m_text = '\0';
}
