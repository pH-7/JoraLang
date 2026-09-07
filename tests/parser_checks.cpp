#include "Parser.hpp"
#include <cassert>
#include <stdexcept>

int main() {
    JoraLang::Parser parser;
    assert(parser.empty());
    assert(!parser.find("missing"));
    assert(!parser.next());
    assert(!parser.isNext("missing"));
    bool throws = false;
    try { parser.cur(); } catch (const std::out_of_range&) { throws = true; }
    assert(throws);
    parser.append(parser.get("  say,\tsay # comment, ignored"));
    assert(parser.find("say"));
    assert(!parser.find("missing"));
    assert(parser.cur() == "say");
    assert(parser.isNext("say"));
    assert(parser.next());
    assert(parser.cur() == "say");
    assert(!parser.isNext("say"));
    assert(!parser.next());
    assert(parser.get("# comment").empty());
    assert(parser.get("  \t").empty());
    parser.append("temporary");
    parser.clear();
    assert(parser.empty());
}
