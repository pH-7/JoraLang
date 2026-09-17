#include "Parser.hpp"
#include <cassert>
#include <stdexcept>

int main() {
    JoraLang::Parser parser;
    assert(parser.empty());
    assert(!parser.find("missing"));
    assert(!parser.next());
    assert(!parser.isNext("missing"));
    assert(!parser.isFront("missing"));
    bool throws = false;
    try { parser.cur(); } catch (const std::out_of_range&) { throws = true; }
    assert(throws);
    parser.append(parser.get("  say,\tsay # comment, ignored"));
    assert(parser.find("say"));
    assert(!parser.find("missing"));
    assert(parser.cur() == "say");
    assert(parser.isFront("say"));
    assert(!parser.isFront("missing"));
    assert(parser.isNext("say"));
    assert(parser.next());
    assert(parser.cur() == "say");
    // A single remaining token is still the front one, but has nothing after it.
    assert(parser.isFront("say"));
    assert(!parser.isNext("say"));
    assert(!parser.next());
    assert(JoraLang::Parser::get("# comment").empty());
    assert(JoraLang::Parser::get("  \t").empty());

    // isFront tracks the front of the list, not its back.
    JoraLang::Parser ordered(JoraLang::Parser::get("alpha beta gamma"));
    assert(ordered.isFront("alpha"));
    assert(!ordered.isFront("gamma"));
    assert(ordered.isNext("beta"));
    parser.append("temporary");
    parser.clear();
    assert(parser.empty());
}
