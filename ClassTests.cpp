#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Book.h"
#include "Person.h"

TEST_CASE("Class construction", "[class created]")
{
    Person aPerson;
    aPerson.setName("Florin Hasna");
    aPerson.setAddress("35 Hendon Way, NW9 7JN");
    aPerson.setEmail("gh435@live.mdx.ac.uk");
    REQUIRE(aPerson.getName() == "Florin Hasna");
    REQUIRE(aPerson.getAddress() == "35 Hendon Way, NW9 7JN");
    REQUIRE(aPerson.getEmail() == "gh435@live.mdx.ac.uk");

    Librarian aLibrarian(1990412, "Florin Hasna", "35 Hendon Way, NW9 7JN", "gh435@live.mdx.ac.uk", 100000);
    REQUIRE(aLibrarian.getStaffID() == 1990412);
    REQUIRE(aLibrarian.getName() == "Florin Hasna");
    REQUIRE(aLibrarian.getAddress() == "35 Hendon Way, NW9 7JN");
    REQUIRE(aLibrarian.getEmail() == "gh435@live.mdx.ac.uk");
    REQUIRE(aLibrarian.getSalary() == 100000);

    Book aBook(199, "The Hobbit", "John", "RR Tolkien");
    REQUIRE(aBook.getBookID() == "199");
    REQUIRE(aBook.getBookName() == "The Hobbit");
    REQUIRE(aBook.getAuthorFirstName() == "John");
    REQUIRE(aBook.getAuthorLastName() == "RR Tolkien");
}